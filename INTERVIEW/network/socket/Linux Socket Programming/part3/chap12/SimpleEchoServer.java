/* SimpleEchoServer.java
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
/*** SimpleEchoServer.java                                                 ***/
/***                                                                       ***/
/*****************************************************************************/

import java.io.*;
import java.net.*;

public class SimpleEchoServer
{
	public static void main(String[] args)
	{
		try
		{
			ServerSocket s = new ServerSocket(9999);
			String str;
			while (true)
			{
				Socket c = s.accept();
				InputStream i = c.getInputStream();
				OutputStream o = c.getOutputStream();
				do
				{
					byte[] line = new byte[100];
					i.read(line);
					o.write(line);
					str = new String(line);
				}
				while ( !str.trim().equals("bye") );
				c.close();
			}
		}
		catch (Exception err)
		{
		   System.err.println(err);
		}
	}
}