/* rpcproc_server.c
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
/*** rpcproc_server.c                                                      ***/
/***                                                                       ***/
/*****************************************************************************/

#include <fcntl.h>
#include <errno.h>
#include "rpcproc.h"

#define MAXPATH		100
#define MAXBUFFER	10240
#define PROC_ROOT	"/proc/"

proc_res *
readproc_1_svc(char **argp, struct svc_req *rqstp)
{	int fd, bytes;
	char path[MAXPATH];
	static proc_res  result;

	/*---Create the full path---*/
	strncpy(path, PROC_ROOT, sizeof(path));
	strncat(path, *argp, sizeof(path));

	/*---Free up the memory from the last execution---*/
	xdr_free((xdrproc_t)xdr_proc_res, (void*)&result);

	/*---Get scratch space, open file, and read data---*/
	if ( (result.proc_res_u.Data = malloc(MAXBUFFER)) != NULL )
		if ( (fd = open(path, O_RDONLY)) > 0 )
			if ( (bytes = read(fd, result.proc_res_u.Data, MAXBUFFER)) > 0 )
			{
				result.Err = 0;
				result.proc_res_u.Data[bytes] = 0;
				return &result;
			}

	/*---Return any error---*/
	result.Err = errno;
	return &result;
}
