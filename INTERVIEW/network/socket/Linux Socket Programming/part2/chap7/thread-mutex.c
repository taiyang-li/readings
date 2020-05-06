/* thread-mutex.c
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
/*** thread-mutex.c                                                        ***/
/***                                                                       ***/
/*** Demonstrates how mutexes work in pThreads.                            ***/
/*****************************************************************************/

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <pthread.h>
#define MAXTIMES    3

/*** Create the shared data ***/
struct
{
    char data[10];
    int top;
} Stack={{0,0,0,0,0,0,0,0,0,0}, 0};

/*** Mutexes must be shared as well ***/
pthread_mutex_t mutx = PTHREAD_MUTEX_INITIALIZER;

/*** The child reads the stack and displays the results ***/
void* Child(void* arg)
{   int i;
    char c;
    int timeout = MAXTIMES;

    /*** While we don't time out, try to lock the stack ***/
    /*** and get data from the stack ***/
    do
    {
        pthread_mutex_lock(&mutx);
        if ( Stack.top > 0 )
            c = Stack.data[--Stack.top];
        else
            c = 0;
        pthread_mutex_unlock(&mutx);
        if ( c != 0 )
        {
            fputc(c, stderr);
            timeout = MAXTIMES;
        }
        else
        {
            sleep(random()); /* pause 0-9 seconds */
            timeout--;
        }
    }
    while ( timeout > 0 );
}

/*** The parent creates the child thread and writes to the ***/
/*** stack. ***/
int main(void)
{   char c;
    pthread_t pchild;

    if ( pthread_create(&pchild, 0, Child, 0) != 0 )
    {
        perror("Thread");
        exit(-1);
    }
    c = 'A';
    while ( c <= 'Z' )
    {
        pthread_mutex_lock(&mutx);
        if ( Stack.top < sizeof(Stack.data) )
            Stack.data[Stack.top++] = c++;
        pthread_mutex_unlock(&mutx);
        sleep(random()%2);  /* pause 0-1 seconds */
    }
    pthread_join(pchild, 0);  /* wait for the child to finish */
    return 0;
}


