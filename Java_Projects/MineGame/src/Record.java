import java.io.*;
import java.util.*;
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class Record extends JDialog implements ActionListener{
	int time = 0;
	String grade = null;
	String key = null;
	String message = null;
	JTextField textName;
	JLabel label = null;
	JButton 确定,取消;
	public Record(){
		setTitle("记录你的成绩");
		this.time = time;
		this.grade = grade;
		setBounds(100,100,240,160);
		setResizable(false);
		setModal(true);
		确定 = new JButton("确定");
		取消 = new JButton("取消");
		textName = new JTextField(8);
		textName.setText("匿名");
		确定.addActionListener(this);
		取消.addActionListener(this);
		setLayout(new GridLayout(2,1));
		label = new JLabel("您现在是高手，输入您的大名上榜");
		add(label);
		JPanel p = new JPanel();
		p.add(textName);
		p.add(确定);
		p.add(取消);
		add(p);
		setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
	}
	public void setGrade(String grade){
		this.grade = grade;
		label.setText("您现在是"+grade+"高手，输入您的大名上榜");
	}
	public void setTime(int time){
		this.time = time;
	}
	public void actionPerformed(ActionEvent e){
		if(e.getSource() == 确定){
			message = grade + "#" + time + "#" + " " + textName.getText();
			key = grade;
			writeRecord(key, message);
			setVisible(false);
		}
		if(e.getSource() == 取消){
			setVisible(false);
		}
	}
	public void writeRecord(String key, String message){
		File f = new File("英雄榜.txt");
		try{
			FileInputStream in = new FileInputStream(f);
			ObjectInputStream object_in = new ObjectInputStream(in);
			Hashtable hashtable = (Hashtable)object_in.readObject();
			object_in.close();
			in.close();
			String temp = (String) hashtable.get(key);
			StringTokenizer fenxi = new StringTokenizer(temp,"#");
			fenxi.nextToken();
			int n = Integer.parseInt(fenxi.nextToken());
			if(time < n){
				hashtable.put(key,message);
				FileOutputStream out = new FileOutputStream(f);
				ObjectOutputStream object_out = new ObjectOutputStream(out);
				object_out.writeObject(hashtable);
				object_out.close();
				out.close();
			}
		}
		catch(Exception e){
			System.out.println(e);
		}
	}
}