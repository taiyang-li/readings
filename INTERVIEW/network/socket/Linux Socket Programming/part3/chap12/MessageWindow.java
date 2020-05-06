/* MessageWindow.java
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
/*** MessageWindow.java                                                    ***/
/***                                                                       ***/
/*****************************************************************************/

import java.awt.*;
import java.awt.event.*;
import java.net.*;
import java.io.*;

public class MessageWindow extends Frame
	implements ActionListener, Runnable
{
	public MessageWindow()
	{
		try
		{
			socket = new DatagramSocket();
			Integer port = new Integer(socket.getLocalPort());
			setTitle("Messenger (local port="+port.intValue()+")");
		}
		catch (Exception err)
		{
			Dialog derr = new ErrorDialog(this, err);
			derr.show();
			derr.dispose();
		}
		addWindowListener(new WindowAdapter()
		{
			public void windowClosing(WindowEvent e){ System.exit(0); }
		});
		setSize(600,300);
		setBackground(Color.lightGray);
		setLayout(new BorderLayout());
		Panel p = new Panel(new FlowLayout(FlowLayout.CENTER));
		p.add(new Label("Host name:", Label.RIGHT));
		p.add(hostname);
		p.add(new Label("Port:", Label.RIGHT));
		p.add(portnum);
		Button b = new Button("Send!");
		b.addActionListener(this);
		p.add(b);
		add(p, "North");
		add(msg);
		Thread t = new Thread(this);
		t.start();
	}

	public void actionPerformed(ActionEvent event)
	{
		if ( event.getActionCommand().equals("Send!") )
			try
			{
				byte[] data = msg.getText().getBytes();
				InetAddress addr = InetAddress.getByName(hostname.getText());
				Integer port = new Integer(portnum.getText());
				DatagramPacket pckt = new DatagramPacket(data, data.length, addr, port.intValue());
				socket.send(pckt);
			}
			catch (Exception err)
			{
				Dialog derr = new ErrorDialog(this, err);
				derr.show();
				derr.dispose();
			}
	}

	public void run()
	{
		try
		{
			while (true)
			{
				byte[] data = new byte[2048];
				DatagramPacket pckt = new DatagramPacket(data, data.length);
				socket.receive(pckt);
				Message m = new Message(socket, pckt);
				m.show();
			}
		}
		catch (Exception err)
		{
			Dialog derr = new ErrorDialog(this, err);
			derr.show();
			derr.dispose();
		}
	}

	public static void main(String[] arg)
	{
		MessageWindow mw = new MessageWindow();
		mw.show();
	}

	private DatagramSocket socket;
	private TextArea msg = new TextArea();
	private TextField hostname = new TextField(10);
	private TextField portnum = new TextField(4);
}

class Message extends Frame
	implements ActionListener
{
	public Message(DatagramSocket sock, DatagramPacket pckt)
	{
		socket = sock;
		packet = pckt;
		try
		{
			String hostname = pckt.getAddress().getHostName();
			String addr = pckt.getAddress().getHostAddress();
			Integer port = new Integer(pckt.getPort());
			setTitle("Message from "+hostname+"("+addr+":"+port.intValue()+")");
		}
		catch (Exception err)
		{
			Dialog derr = new ErrorDialog(this, err);
			derr.show();
			derr.dispose();
		}
		addWindowListener(new WindowAdapter()
		{
			public void windowClosing(WindowEvent e){ System.exit(0); }
		});
		setSize(250,200);
		setBackground(new Color(225,225,225));
		setLayout(new BorderLayout());
		add(new Label("Edit message and press 'Reply!'"), "North");
		String data = new String(pckt.getData());
		msg.setText(data);
		add(msg, "Center");
		Panel p = new Panel(new FlowLayout(FlowLayout.CENTER));
		Button b = new Button("Reply!");
		b.addActionListener(this);
		p.add(b);
		b = new Button("Close");
		b.addActionListener(this);
		p.add(b);
		add(p, "South");
	}

	public void actionPerformed(ActionEvent event)
	{
		if ( event.getActionCommand().equals("Reply!") )
		{
			try
			{
				packet.setData(msg.getText().getBytes());
				socket.send(packet);
			}
			catch (Exception err)
			{
				Dialog derr = new ErrorDialog(this, err);
				derr.show();
				derr.dispose();
			}
		}
		dispose();
	}

	private DatagramPacket packet;
	private DatagramSocket socket;
	private TextArea msg = new TextArea();
}