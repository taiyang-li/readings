/* SimpleEchoClient.java
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
/*** SimpleEchoClient.java                                                 ***/
/***                                                                       ***/
/*****************************************************************************/

import java.net.*;
import java.io.*;

public class SimpleEchoClient
{
	public static void main(String[] args)
	{
		try
		{
			Socket s = new Socket("127.0.0.1", 9999);
			InputStream i = s.getInputStream();
			OutputStream o = s.getOutputStream();
			String str;
			do
			{
				byte[] line = new byte[100];
				System.in.read(line);
				o.write(line);
				i.read(line);
				str = new String(line);
				System.out.println(str.trim());
			}
			while ( !str.trim().equals("bye") );
			s.close();
		}
		catch (Exception err)
		{
			System.err.println(err);
		}
	}
}