/* servlet-chummer.c
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
/*** servlet-chummer.c                                                     ***/
/***                                                                       ***/
/*****************************************************************************/

/************************************************************/
/***  Chumming connections example                        ***/
/************************************************************/
int delay=MAXDELAY;
time_t lasttime;
void sig_child(int signum)
{
    wait(0);                     /* Acknowledge termination */
    time(&lasttime);                  /* get the time stamp */
    delay = MAXDELAY;                 /* reset chummer back */
}

void Chummer(void (*servlet)(void))
{
    time(&lasttime);                /* Initialize timestamp */
    for (;;)
    {
        if ( !fork() )               /* first, set the chum */
            servlet();  /* call the task (must have exit()) */
        sleep(delay);                  /* dream for a while */
        /* If no child terminated, double frequency         */
        if ( time(0) - times[1] >= delay-1 )
            if ( delay > MINDELAY )   /* don't go below min */
                delay /= 2;        /* double chum frequency */
    }
}

