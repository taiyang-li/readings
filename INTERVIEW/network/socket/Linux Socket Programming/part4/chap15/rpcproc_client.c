/* rpcproc_client.c
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
/*** rpcproc_client.c                                                      ***/
/***                                                                       ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include "rpcproc.h"


void
rpcproc_1(char *host, char *file)
{
	CLIENT *clnt;
	proc_res  *result_1;

#ifndef	DEBUG
	clnt = clnt_create (host, RPCPROC, RPCPROCVERSION, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = readproc_1(&file, clnt);
	if (result_1 == (proc_res *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	if ( result_1->Err != 0 )
	{
		errno = result_1->Err;
		perror(file);
	}
	else
		printf("%s", result_1->proc_res_u.Data);

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{	char *host;
	char *file;

	if (argc != 3) {
		printf ("usage: %s <server_host> <file>\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	file = argv[2];
	rpcproc_1 (host, file);
exit (0);
}
