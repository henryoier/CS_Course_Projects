import java.io.*;
import java.util.*;
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class ShowRecord extends JDialog implements ActionListener{
	File file = new File("Ӣ�۰�.txt");
	String name = null;
	Hashtable hashtable = null;
	JButton ��ʾ,���¼Ƿ�;
	JLabel label����[],label�м�[],label�߼�[];
	public ShowRecord(JFrame frame, Hashtable h){
		setTitle("ɨ��Ӣ�۰�");
		hashtable = h;
		setBounds(100,100,320,185);
		setResizable(false);
		setVisible(false);
		setModal(true);
		label���� = new JLabel[3];
		label�м� = new JLabel[3];
		label�߼� = new JLabel[3];
		for(int i = 0;i<3;i++){
			label���� [i] = new JLabel();
			label���� [i].setBorder(null);
			label�м� [i] = new JLabel();
			label�м� [i].setBorder(null);
			label�߼� [i] = new JLabel();
			label�߼� [i].setBorder(null);
		}
		label���� [0].setText("");
		label���� [1].setText(""+999);
		label���� [2].setText("");
		label�м� [0].setText("");
		label�м� [1].setText(""+999);
		label�м� [2].setText("");
		label�߼� [0].setText("");
		label�߼� [1].setText(""+999);
		label�߼� [2].setText("");
		JPanel pCenter = new JPanel();
		pCenter.setLayout(new GridLayout(3,3));
		for(int i = 0; i<3;i++)
			pCenter.add(label����[i]);
		for(int i = 0; i<3;i++)
			pCenter.add(label�м�[i]);
		for(int i = 0; i<3;i++)
			pCenter.add(label�߼�[i]);
		pCenter.setBorder(BorderFactory.createTitledBorder("ɨ��Ӣ�۰�"));
		��ʾ = new JButton("��ʾ�ɼ�");
		���¼Ƿ� = new JButton("���¼Ƿ�");
		��ʾ.addActionListener(this);
		���¼Ƿ�.addActionListener(this);
		 JPanel pSouth = new JPanel();
		 pSouth.setLayout(new FlowLayout(FlowLayout.RIGHT));
		 pSouth.add(���¼Ƿ�);
		 pSouth.add(��ʾ);
		 add(pCenter,BorderLayout.CENTER);
		 add(pSouth,BorderLayout.CENTER);
	}
	public void readAndShow(){
		try{
			FileInputStream in = new FileInputStream(file);
			ObjectInputStream object_in = new ObjectInputStream(in);
			hashtable = (Hashtable)object_in.readObject();
			object_in.close();
			in.close();
			String temp = (String)hashtable.get("����");
			StringTokenizer fenxi = new StringTokenizer(temp,"#");
			label���� [0].setText(fenxi.nextToken());
			label���� [0].setText(fenxi.nextToken());
			label���� [0].setText(fenxi.nextToken());
			
			temp = (String)hashtable.get("�м�");
			fenxi = new StringTokenizer(temp,"#");
			label�м� [0].setText(fenxi.nextToken());
			label�м� [0].setText(fenxi.nextToken());
			label�м� [0].setText(fenxi.nextToken());
			
			temp = (String)hashtable.get("�߼�");
			fenxi = new StringTokenizer(temp,"#");
			label�߼� [0].setText(fenxi.nextToken());
			label�߼� [0].setText(fenxi.nextToken());
			label�߼� [0].setText(fenxi.nextToken());
		}
		catch(Exception e){}
	}
	public void actionPerformed(ActionEvent e){
		if(e.getSource() == ���¼Ƿ�){
			hashtable.put("����","����#"+ 999 + "#����");
			label����[0].setText("����");
			label����[1].setText(""+999);
			label����[2].setText("����");
			hashtable.put("�м�","�м�#"+ 999 + "#����");
			label�м� [0].setText("�м�");
			label�м� [1].setText(""+999);
			label�м� [2].setText("����");
			hashtable.put("�߼�","�߼�#"+ 999 + "#����");
			label�߼� [0].setText("�߼�");
			label�߼� [1].setText(""+999);
			label�߼� [2].setText("����");
			try{
				FileOutputStream out = new FileOutputStream(file);
				ObjectOutputStream object_out = new ObjectOutputStream(out);
                object_out.writeObject(hashtable);
				object_out.close();
				out.close();
			}
			catch(IOException event){}
			setVisible(false);
		}
		if(e.getSource() == ��ʾ){
			readAndShow();
		}
	}
}