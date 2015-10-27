import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

public class MineArea extends JPanel implements ActionListener,MouseListener{
	//private static final LayoutManager BorderLayout = null;
	JButton reStart;
	Block [][] block;
	BlockView [][] blockView;
	LayMines lay;
	int row, colum,mineCount,markMount;
	ImageIcon mark;
	int grade;
    JPanel pCenter,pNorth;
    JTextField showTime, showMarkedMineCount;
    Timer time;
    int spendTime = 0;
    Record record;
    public MineArea(int row, int colum, int mineCount, int grade){
    	reStart = new JButton("重新开始");
    	mark = new ImageIcon("mark.gif");
    	time = new Timer(1000,this);
    	showTime = new JTextField(5);
    	showMarkedMineCount = new JTextField(5);
    	showTime.setHorizontalAlignment(JTextField.CENTER);
    	showMarkedMineCount.setHorizontalAlignment(JTextField.CENTER);
    	showMarkedMineCount.setFont(new Font("Arial",Font.BOLD,16));
    	showTime.setFont(new Font("Arial",Font.BOLD,16));
    	pCenter = new JPanel();
    	pNorth = new JPanel();
    	lay = new LayMines();
    	initMineArea(row,colum,mineCount,grade);
    	reStart.addActionListener(this);
    	pNorth.add(showMarkedMineCount);
    	pNorth.add(reStart);
    	pNorth.add(showTime);
    	setLayout(new BorderLayout());
    	add(pNorth,BorderLayout.NORTH);
    	add(pCenter,BorderLayout.CENTER);
    }
    public void initMineArea(int row, int colum,int mineCount,int grade){
    	pCenter.removeAll();
    	spendTime = 0;
    	markMount = mineCount;
    	this.row = row;
    	this.colum = colum;
    	this.mineCount = mineCount;
    	this.grade = grade;
    	block = new Block[row][colum];
    	for(int i = 0;i<row;i++){
    		for(int j = 0;j<colum;j++)
    			block[i][j] = new Block();
    	}
    	lay.layMineForBlock(block,mineCount);
    	blockView = new BlockView[row][colum];
    	pCenter.setLayout(new GridLayout(row,colum));
    	for(int i = 0;i<row;i++){
    		for(int j = 0;j<colum;j++){
    			blockView[i][j] = new BlockView();
    			blockView[i][j].giveView(block[i][j]);
    			pCenter.add(blockView[i][j]);
    			blockView[i][j].getBlockCover().addActionListener(this);
    			blockView[i][j].getBlockCover().addMouseListener(this);
    			blockView[i][j].seeBlockCover();
    			blockView[i][j].getBlockCover().setEnabled(true);
    			blockView[i][j].getBlockCover().setIcon(null);
    		}
    	}
    	showMarkedMineCount.setText("" + markMount);
    	validate();
    }
    
    public void setRow(int row){
    	this.row = row;
    }
    
    public void setColum(int colum){
    	this.colum = colum;
    }
    
    public void setMineCount(int mineCount){
    	this.mineCount = mineCount;
    }
    
    public void setGrade(int grade){
    	this.grade = grade;
    }
    
    public void actionPerformed(ActionEvent e){
    	if(e.getSource() != reStart && e.getSource() != time){
    		time.start();
    		int m = -1;
    		int n = -1;
    		for(int i = 0;i<row;i++){
    			for(int j = 0;j<colum;j++){
    				if(e.getSource() == blockView[i][j].getBlockCover()){
    					m = i;
    					n = j;
    					break;
    				}
    			}
    		}
    	if(block[m][n].isMine()){
    		for(int i = 0;i<row;i++){
    			for(int j = 0;j<colum;j++){
    				blockView[i][j].getBlockCover().setEnabled(false);
    				if(block[i][j].isMine())
    					blockView[i][j].seeBlockNameOrIcon();
    			}
    		}
    		time.stop();
    		spendTime = 0;
    		markMount = mineCount;
    	}
    	else{
    		show(m,n);
    	}
    }
    if(e.getSource() == reStart){
    	initMineArea(row, colum, mineCount,grade);
    }
    if(e.getSource() == time){
    	spendTime++;
    	showTime.setText(""+spendTime);
    }
    inquireWin();
    }
    
    public void show(int m,int n){
    	if(block[m][n].getAroundMineNumber()>0 && block[m][n].getIsOpen() == false){
    		blockView[m][n].seeBlockNameOrIcon();
    		block[m][n].setIsOpen(true);
    		return;
    	}
    	else if(block[m][n].getAroundMineNumber() == 0 && block[m][n].getIsOpen() == false){
    		blockView[m][n].seeBlockNameOrIcon();
    		block[m][n].setIsOpen(true);
    		for(int k =Math.max(m-1, 0);k<=Math.min(m+1,row-1);k++){
    			for(int t = Math.max(n-1, 0);t<=Math.min(n+1,colum-1);t++)
    				show(k,t);
    		}
    	}
    }
    public void mousePressed(MouseEvent e){
    	JButton source = (JButton)e.getSource();
    	for(int i = 0;i<row;i++){
    		for(int j = 0;j<colum;j++){
    			if(e.getModifiers() == InputEvent.BUTTON3_MASK&&
    			     source == blockView[i][j].getBlockCover()){
    				if(block[i][j].getIsMark()){
    					source.setIcon(null);
    					block[i][j].setIsMark(false);
    					markMount = markMount + 1;
    					showMarkedMineCount.setText(""+markMount);
    				}
    				else{
    					source.setIcon(mark);
    					block[i][j].setIsMark(true);
    					markMount = markMount - 1;
    					showMarkedMineCount.setText(""+markMount);
    				}
    			}
    		}
    	}
    }
    public void inquireWin(){
    	int number = 0;
    	for(int i = 0;i<row;i++){
    		for(int j = 0;j<colum;j++){
    			if(block[i][j].getIsOpen() == false)
    				number++;
    		}
    	}
    	if(number == mineCount){
    		time.stop();
    		record = new Record();
    		switch(grade){
    		    case 1:record.setGrade("初级");
                       break;
    		    case 2:record.setGrade("中级");
    		           break;
    		    case 3:record.setGrade("高级");
    		           break;
    		}
    		record.setTime(spendTime);
    		record.setVisible(true);
    	}
    }
    public void mouseReleased(MouseEvent e){}
    public void mouseEntered(MouseEvent e){}
    public void mouseExited(MouseEvent e){}
    public void mouseClicked(MouseEvent e){}
    
}