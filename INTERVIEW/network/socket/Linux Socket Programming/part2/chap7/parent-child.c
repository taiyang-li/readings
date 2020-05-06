/* parent-child.c
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
/*** parent-child.c                                                        ***/
/***                                                                       ***/
/*** Demonstrate a simple fork() call to create a child process.           ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>

int main(void)
{   int pchild;

	if ( (pchild = fork()) == 0 )
	{
		int i;
		for ( i = 0; i < 10; i++ )
		{
			printf("Child #%d\n", i);
			sleep(1);
		}
		exit(500);
	}
	else if ( pchild > 0 )
	{
		int i, result;
		for ( i = 0; i < 7; i++ )
		{
			printf("Parent #%d\n", i);
			sleep(1);
		}
		printf("awaiting child's termination...\n");
		wait(&result);
		printf("Child's result=%d\n", result);
	}
	else
		perror("Fork failure");
	exit(0);
}

