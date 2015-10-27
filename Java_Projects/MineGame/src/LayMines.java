import java.util.*;
import javax.swing.*;

public class LayMines{
	ImageIcon mineIcon;
	LayMines(){
		mineIcon = new ImageIcon("mine.gif");
	}
	public void layMineForBlock(Block block[][], int mineCount){
		int row = block.length;
		int column = block[0].length;
		LinkedList<Block>list = new LinkedList <Block>();
		for(int i = 0;i<row;i++){
			for(int j = 0;j<column;j++)
				list.add(block[i][j]);
		}
		while(mineCount>0){
			int size = list.size();
			int randomIndex = (int)(Math.random()*size);
			Block b = list.get(randomIndex);
			b.setIsMine(true);
			b.setName("À×");
			b.setMineIcon(mineIcon);
			list.remove(randomIndex);
			mineCount--;
		}
		for(int i = 0;i<row;i++){
			for(int j = 0;j<column;j++){
				if(block[i][j].isMine()){
					block[i][j].setIsOpen(false);
					block[i][j].setIsMark(false);
				}
				else{
					int mineNumber = 0;
					for(int k = Math.max(i-1,0);k<=Math.min(i+1,row-1);k++){
						for(int t=Math.max(j-1,0);t<=Math.min(j+1,column-1);t++){
							if(block[k][t].isMine())
								mineNumber++;
						}
					}
					block[i][j].setIsOpen(false);
					block[i][j].setIsMark(false);
					block[i][j].setName(""+mineNumber);
					block[i][j].setAroundMineNumber(mineNumber);
				}
			}
		}
	}
}