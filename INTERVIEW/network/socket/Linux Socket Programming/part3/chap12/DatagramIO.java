/* DatagramIO.java
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
/*** DatagramIO.java                                                       ***/
/***                                                                       ***/
/*****************************************************************************/

import java.io.*;
import java.net.*;

public class DatagramIO
	implements Runnable
{
	private final int port=16900;
	public void transmit()
	{
		try
		{
			InetAddress addr = InetAddress.getByName("127.0.0.1");
			DatagramSocket ds = new DatagramSocket();
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			String line = new String();
			do
			{
				ByteArrayOutputStream os = new ByteArrayOutputStream();
				PrintWriter pr = new PrintWriter(new OutputStreamWriter(os), true);
				for ( int i = 0; i < 3; i++ )
				{
					System.out.print("Enter message #");
					System.out.print(i);
					System.out.print(": ");
					line = in.readLine();
					pr.println(line);
				}
				byte[] arr = os.toByteArray();
				DatagramPacket pkt = new DatagramPacket(arr, arr.length, addr, port);
				ds.send(pkt);
			}
			while ( !line.equals("quit") );
		}
		catch (Exception err)
		{
			System.err.println("sender:"+err);
		}
	}

	public void run()		//Child -- receiver
	{
		try
		{
			DatagramSocket ds = new DatagramSocket(port);
			byte[] buf = new byte[16*1024];
			DatagramPacket pkt = new DatagramPacket(buf, buf.length);
			do
			{
				ds.receive(pkt);
				BufferedReader is = new BufferedReader(new InputStreamReader(new ByteArrayInputStream(pkt.getData())));
				String line;
				do
				{
					line = is.readLine();
					if ( line != null )
						System.out.println(line.trim());
				}
				while ( line != null );
			}
			while (true);
		}
		catch (Exception err)
		{
			System.err.println("receiver:"+err);
		}
	}

	public static void main(String[] args)
	{
		DatagramIO dgio = new DatagramIO();
		Thread t = new Thread(dgio);
		t.start();
		dgio.transmit();
	}
}