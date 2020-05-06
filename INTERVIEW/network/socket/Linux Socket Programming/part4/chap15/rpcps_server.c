/* rpcps_server.c
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
/*** rpcps_server.c                                                        ***/
/***                                                                       ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include "rpcps.h"

int isnewline(char c);
#define isnewline(c)	((c) == '\n'  ||  (c) == '\r'  ||  (c) == '\f')

void childdie(int sig)
{
	wait(0);
}

int ConvertString(char *String)
{	int cols=0;
	char *srch, *done;

	srch = done = String;
	while ( *srch != 0 )
	{
		if ( isnewline(*srch) )
		{
			cols++;
			*done++ = 0;
			break;
		}
		else if ( srch[0] == ' '  &&  srch[1] == ' ' )
		{
			cols++;
			while ( *srch == ' ' )
				srch++;
			*done++ = 0;
		}
		else
			*done++ = *srch++;
	}
	*done = 0;
	return cols;
}

TableResult *
getps_1_svc(char **argp, struct svc_req *rqstp)
{	int i,j, cols=10;
	FILE *fp;
	TRow row;
	TTable table;
	char TempS[1024], *str;
	static TableResult  result;

	signal(SIGCHLD, childdie);
	strncpy(TempS, "ps ", sizeof(TempS));
	strncat(TempS, *argp, sizeof(TempS));
	if ( (fp = popen(TempS, "r")) != NULL )
	{
		xdr_free((xdrproc_t)xdr_TableResult, (void*)&result);

		table = result.TableResult_u.Table = calloc(1, sizeof(TTable*));
		while ( fgets(TempS, sizeof(TempS), fp) != NULL )
		{
			row = table->Row = calloc(1, sizeof(TRow*));
			cols = ConvertString(TempS);
			str = TempS;
			for ( j = 0; j < cols; j++ )
			{
				row->Field = strdup(str);
				while ( *str++ != 0 );
				if ( j < cols-1 )
				{
					row->Next = calloc(1, sizeof(TRow*));
					row = row->Next;
				}
			}
			if ( !feof(fp) )
			{
				table->Next = calloc(1, sizeof(TTable*));
				table = table->Next;
			}
		}

		result.Err = 0;
		return &result;
	}
	result.Err = errno;
	return &result;
}

