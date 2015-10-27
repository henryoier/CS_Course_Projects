import java.awt.event.*;
import java.awt.*;

import javax.swing.*;
import javax.swing.border.*;

import java.util.*;
import java.io.*;

public class MineGame extends JFrame implements ActionListener{
	JMenuBar bar;
	JMenu fileMenu;
	JMenuItem 初级,中级,高级,扫雷英雄榜;
	MineArea mineArea = null;
	File 英雄榜 = new File("英雄榜.txt");
	Hashtable hashtable = null;
	ShowRecord showHeroRecord = null;
	MineGame(){
		mineArea = new MineArea(16,16,40,1);
		add(mineArea,BorderLayout.CENTER);
		bar = new JMenuBar();
		fileMenu = new JMenu("游戏");
		初级 = new JMenuItem("初级");
		中级 = new JMenuItem("中级");
		高级 = new JMenuItem("高级");
		扫雷英雄榜 = new JMenuItem("扫雷英雄榜");
		fileMenu.add(初级);
		fileMenu.add(中级);
		fileMenu.add(高级);
		fileMenu.add(扫雷英雄榜);
		bar.add(fileMenu);
		setJMenuBar(bar);
		初级.addActionListener(this);
		中级.addActionListener(this);
		高级.addActionListener(this);
		扫雷英雄榜.addActionListener(this);
		hashtable = new Hashtable();
		hashtable.put("初级","初级#"+999+"#匿名"); 	
		hashtable.put("中级","中级#"+999+"#匿名"); 	
		hashtable.put("高级","高级#"+999+"#匿名"); 	
		if(!英雄榜.exists()){
			try{
				FileOutputStream out = new FileOutputStream(英雄榜);
				ObjectOutputStream objectOut = new ObjectOutputStream(out);
				objectOut.writeObject(hashtable);
				objectOut.close();
				out.close();
			}
			catch(IOException e){}
		}
		showHeroRecord = new ShowRecord(this, hashtable);
		setBounds(100,100,280,380);
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		validate();
     }
	public void actionPerformed(ActionEvent e){
		if(e.getSource() == 初级){
			mineArea.initMineArea(8,8,10,1);
			setBounds(100,100,200,280);
		}
		if(e.getSource() == 中级){
			mineArea.initMineArea(16,16,40,2);
			setBounds(100,100,280,380);
		}
		if(e.getSource() == 高级){
			mineArea.initMineArea(22,22,99,3);
			setBounds(100,100,350,390);
		}
		if(e.getSource() == 扫雷英雄榜){
			if(showHeroRecord != null)
				showHeroRecord.setVisible(true);
		}
		validate();
	}
	public static void main(String args[]){
		new MineGame();
	}
	
}