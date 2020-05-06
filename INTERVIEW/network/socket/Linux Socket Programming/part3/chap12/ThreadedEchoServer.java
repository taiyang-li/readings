/* ThreadedEchoServer.java
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
/*** ThreadedEchoServer.java                                               ***/
/***                                                                       ***/
/*****************************************************************************/

import java.io.*;
import java.net.*;

public class ThreadedEchoServer
{
	public ThreadedEchoServer(int portnum)
	{
		try
		{
			server = new ServerSocket(portnum);
		}
		catch (Exception err)
		{
			System.out.println(err);
		}
	}

	public void serve()
	{
		try
		{
			while (true)
			{
				Socket client = server.accept();
				Thread t = new EchoServlet(client);
				t.start();
			}
		}
		catch (Exception err)
		{
			System.out.println(err);
		}
	}

	public static void main(String[] args)
	{
		ThreadedEchoServer s = new ThreadedEchoServer(9999);
		s.serve();
	}

	private ServerSocket server;
}

class EchoServlet extends Thread
{
	public EchoServlet(Socket s)
	{
		client = s;
	}

	public void run()
	{
		try
		{
			BufferedReader r = new BufferedReader(new InputStreamReader(client.getInputStream()));
			PrintWriter w = new PrintWriter(client.getOutputStream(), true);
			w.println("Welcome to the Java Threaded EchoServer.  Type 'bye' to close.");
			String line;
			do
			{
				line = r.readLine();
				if ( line != null )
					w.println("Got: "+ line);
			}
			while ( !line.trim().equals("bye") );
		}
		catch (Exception err)
		{
			System.err.println(err);
		}
		finally
		{
			try {client.close();}
			catch (Exception err) {System.err.println(err);}
		}

	}

	private Socket client;
}