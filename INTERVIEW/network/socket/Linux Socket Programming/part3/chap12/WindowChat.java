/* WindowChat.java
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
/*** WindowChat.java                                                       ***/
/***                                                                       ***/
/*****************************************************************************/

import java.awt.*;
import java.awt.event.*;
import java.net.*;
import java.io.*;

public class WindowChat extends Frame
	implements ActionListener, Runnable
{
	public void actionPerformed(ActionEvent event)
	{
		if ( event.getActionCommand().equals("Exit") )
			System.exit(0);
		if ( event.getActionCommand().equals("Config") )
		{
			ConfigDialog d = new ConfigDialog(this, hostname, portnum);
			d.show();
			if ( d.getResult().equals("Connect!") )
			{
				hostname = d.getHostName();
				portnum = d.getPortNum();
				try
				{
					if ( host != null )
					{
						reader.destroy();
						host.close();
					}
					host = new Socket(hostname, portnum);
					sender = new PrintWriter(host.getOutputStream(), true);
					reader = new Thread(this);
					reader.start();
				}
				catch (Exception err)
				{
					Dialog derr = new ErrorDialog(this, err);
					derr.show();
					derr.dispose();
				}
			}
			d.dispose();
		}
		if ( event.getActionCommand().equals("Send!") )
			try
			{
				sender.println(msg.getText());
				msg.setText("");
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
			BufferedReader r = new BufferedReader(new InputStreamReader(host.getInputStream()));
			while (true)
			{
				String line = r.readLine();
				history.add(hostname+":"+line);
			}
		}
		catch (Exception err)
		{
			Dialog derr = new ErrorDialog(this, err);
			derr.show();
			derr.dispose();
		}
	}

	public WindowChat()
	{
		addWindowListener(new WindowAdapter()
			{
				public void windowClosing(WindowEvent e){ System.exit(0); }
			});

		//---Window layout
		setSize(600,300);
		setBackground(new Color(225,225,225));
		setLayout(new BorderLayout());
		Panel p = new Panel();
		p.add(new Label("Message:", Label.RIGHT));
		p.add(msg);
		Button b = new Button("Send!");
		b.addActionListener(this);
		p.add(b);
		add(p, "North");
		add(history, "Center");

		//---Configure Menu
		MenuBar mb = new MenuBar();
		Menu m = new Menu("System");
		MenuItem mi = new MenuItem("Config");
		mi.addActionListener(this);
		m.add(mi);
		m.addSeparator();
		mi = new MenuItem("Exit");
		mi.addActionListener(this);
		m.add(mi);
		mb.add(m);
		setMenuBar(mb);
	}

	public static void main(String[] args)
	{
		WindowChat wc = new WindowChat();
		wc.show();
	}

	private TextField msg = new TextField(50);
	private List history = new List();
	private Socket host;
	private String hostname;
	private int portnum;
	private Thread reader;
	private PrintWriter sender;
}

class ConfigDialog extends Dialog
	implements ActionListener
{
	public ConfigDialog(Frame parent, String name, int port)
	{
		super(parent, "Config Window Chat", true);
		addWindowListener(new WindowAdapter()
			{
				public void windowClosing(WindowEvent e){ result=""; setVisible(false);}
			});
		hostname.setText(name);
		portnum.setText(String.valueOf(port));
		setSize(200,200);
		setLayout(new GridLayout(3,2));
		Panel p = new Panel(new FlowLayout(FlowLayout.RIGHT));
		p.add(new Label("Host:", Label.RIGHT));
		add(p);
		p = new Panel();
		p.add(hostname);
		add(p);
		p = new Panel(new FlowLayout(FlowLayout.RIGHT));
		p.add(new Label("Port:", Label.RIGHT));
		add(p);
		p = new Panel();
		p.add(portnum);
		add(p);
		p = new Panel(new FlowLayout(FlowLayout.CENTER));
		Button b = new Button("Connect!");
		b.addActionListener(this);
		p.add(b);
		add(p);
		p = new Panel(new FlowLayout(FlowLayout.CENTER));
		b = new Button("Cancel");
		b.addActionListener(this);
		p.add(b);
		add(p);
	}

	public void actionPerformed(ActionEvent event)
	{
		result = event.getActionCommand();
		setVisible(false);
	}

	public String getHostName()	{ return hostname.getText(); }
	public int getPortNum()
	{
		Integer port = new Integer(portnum.getText());
		return port.intValue();
	}

	public String getResult() { return result; }

	private TextField hostname = new TextField(10);
	private TextField portnum = new TextField(5);
	private String result;
}
