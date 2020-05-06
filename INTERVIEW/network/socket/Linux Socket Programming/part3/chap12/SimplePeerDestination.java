/* SimplePeerDestination.java
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
/*** SimplePeerDestination.java                                            ***/
/***                                                                       ***/
/*****************************************************************************/

import java.io.*;
import java.net.*;

public class SimplePeerDestination
{
	public static void main(String[] args)
	{
		try
		{
			DatagramSocket s = new DatagramSocket(9998);  // Create socket
			String msg;
			do
			{
				byte[] line = new byte[100];
				DatagramPacket pkt = new DatagramPacket(line, line.length);
				s.receive(pkt);
				msg = new String(pkt.getData());
				System.out.println("From "+pkt.getAddress()+":"+msg.trim());
			}
			while ( !msg.trim().equals("close") );
			s.close();                                 // Close connection
		}
		catch (Exception err)
		{
			System.err.println(err);
		}
	}
}
