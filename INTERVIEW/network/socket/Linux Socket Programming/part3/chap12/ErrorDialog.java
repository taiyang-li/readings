/* ErrorDialog.java
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
/*** ErrorDialog.java                                                      ***/
/***                                                                       ***/
/*****************************************************************************/

import java.awt.*;
import java.awt.event.*;

class ErrorDialog extends Dialog
	implements ActionListener
{
	public ErrorDialog(Frame parent, Exception err)
	{
		super(parent, "Java Error", true);
		addWindowListener(new WindowAdapter()
			{
				public void windowClosing(WindowEvent e){ setVisible(false); }
			});
		setSize(300,100);
		setLayout(new GridLayout(2,1));
		Panel p = new Panel(new FlowLayout(FlowLayout.RIGHT));
		p.add(new Label("Error: "+err.toString(), Label.CENTER));
		add(p);
		p = new Panel(new FlowLayout(FlowLayout.CENTER));
		Button b = new Button("OK");
		b.addActionListener(this);
		p.add(b);
		add(p);
	}

	public void actionPerformed(ActionEvent event)
	{
		setVisible(false);
	}

}