/* http-dir.c
 *
 * Copyright (c) 2000 Sean Walton and Macmillan Publishers.  Use may be in
 * whole or in part in accordance to the General Public License (GPL).
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
*/

/*****************************************************************************/
/*** http-dir.c                                                            ***/
/***                                                                       ***/
/*****************************************************************************/

#include <stdarg.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>

#define	MY_PORT		9999

void PANIC(char* msg);
#define PANIC(msg)	{ perror(msg); abort(); }
#define MAXBUF	1024
char buffer[MAXBUF];
char *Host="127.0.0.1:9999";

#define MAXPATH	150
char* strtrim(char *str)
{	int tail=strlen(str);
	while ( str[tail] <= ' '  &&  tail > 0 )
		tail--;
	str[tail+1] = 0;
	while ( *str <= ' '  &&  *str != 0 )
		str++;
	return str;
}

void sig_handler(int sig)
{
    if ( sig == SIGCHLD )
    {   int retval;
        wait(&retval);
    }
}

char* dir_up(char* dirpath)
{   static char Path[MAXPATH];
	int len;

	strcpy(Path, dirpath);
	len = strlen(Path);
	if ( len > 1  &&  Path[len-1] == '/' )
		len--;
	while ( Path[len-1] != '/'  &&  len > 1 )
		len--;
	Path[len] = 0;
	return Path;
}

#define MAXNAME	25

void DirListing(FILE* FP, char* Path)
{	struct dirent *dirent;
	struct stat info;
	char Filename[MAXPATH];
	DIR* dir = opendir(Path);
	fprintf(FP, "<html><head><title>Directory Lister</title></body>"
		"<body><font size=+4>Linux Directory Server</font><br><hr width=\"100%%\"><br><center>"
		"<table border cols=4 width=\"100%%\" bgcolor=\"#33CCFF\">");
	fprintf(FP, "<caption><font size=+3>Directory of %s</font></caption>\n", Path);
	if ( dir == 0 )
	{
		fprintf(FP, "</table><font color=\"CC0000\" size=+2>%s</font></body></html>", strerror(errno));
		return;
	}
	while ( (dirent = readdir(dir)) != 0 )
	{
		if ( strcmp(Path, "/") == 0 )
			sprintf(Filename, "/%s", dirent->d_name);
		else
			sprintf(Filename, "%s/%s", Path, dirent->d_name);
		fprintf(FP, "<tr>");
		if ( stat(Filename, &info) == 0 )
		{
			fprintf(FP, "<td>%s</td>", dirent->d_name);
			if ( S_ISDIR(info.st_mode) )
			{
				if ( strcmp(dirent->d_name, "..") == 0 )
					fprintf(FP, "<td><a href=\"http://%s%s\">(parent)</a></td>", Host, dir_up(Path));
				else
					fprintf(FP, "<td><a href=\"http://%s%s\">%s</a></td>", Host, Filename, dirent->d_name);
				fprintf(FP, "<td>Directory</td>");
			}
			else if ( S_ISREG(info.st_mode) )
			{
				fprintf(FP, "<td><a href=\"ftp://%s%s\">%s</a></td>", Host, Filename, dirent->d_name);
				fprintf(FP, "<td>%d</td>", info.st_size);
			}
			else if ( S_ISLNK(info.st_mode) )
				fprintf(FP, "<td>Link</td>");
			else if ( S_ISCHR(info.st_mode) )
				fprintf(FP, "<td>Character Device</td>");
			else if ( S_ISBLK(info.st_mode) )
				fprintf(FP, "<td>Block Device</td>");
			else if ( S_ISFIFO(info.st_mode) )
				fprintf(FP, "<td>FIFO</td>");
			else if ( S_ISSOCK(info.st_mode) )
				fprintf(FP, "<td>Socket</td>");
			else
				fprintf(FP, "<td>(unknown)</td>");
			fprintf(FP, "<td>%s</td>", strtrim(ctime(&info.st_ctime)));
		}
		else
			perror(Path);
		fprintf(FP, "</tr>\n");
	}
	fprintf(FP, "</table></center></body></html>");
}

int main(void)
{	struct sigaction act;
	struct sockaddr_in addr;
	int sd, addrlen = sizeof(addr);

	bzero(&act, sizeof(act));
	act.sa_handler = sig_handler;
    act.sa_flags = SA_NOCLDSTOP;
    sigaction(SIGCHLD, &act, 0);
	if ( (sd = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
		PANIC("Socket");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(MY_PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sd, (struct sockaddr*)&addr, addrlen) < 0 )
		PANIC("Bind");
	if ( listen(sd, 20) < 0 )
		PANIC("Listen");
	while (1)
	{	int len;
		int client;

		client = accept(sd, (struct sockaddr*)&addr, &addrlen);
		if ( client < 0 )
			perror("Accept");
		else
		{
			printf("Connected: %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
			if ( !fork() )
			{
				if ( (len = recv(client, buffer, MAXBUF, 0)) > 0 )
				{
					FILE* ClientFP = fdopen(client, "w");
					if ( ClientFP == NULL )
						perror("fpopen");
					else
					{	char Req[MAXPATH];
						sscanf(buffer, "GET %s HTTP", Req);
						printf("Request: \"%s\"\n", Req);
						DirListing(ClientFP, Req);
						fclose(ClientFP);
					}
				}
				close(client);
				exit(0);
			}
			close(client);
		}
	}
	return 0;
}

