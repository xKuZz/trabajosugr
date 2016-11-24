/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package napakalakiGame;

/**
 *
 * @author david
 */
public class Prize {
    private int level;
    private int treasures;
    
    public Prize(int treasures, int level){
        this.level=level;
        this.treasures=treasures;
    }
    
    public Prize(Prize prize){
        this.level=prize.getLevel();
        this.treasures=prize.getTreasures();
    }
    
    public int getLevel(){
        return level;
    }
    
    public int getTreasures(){
        return treasures;
    }
    
    @Override
    public String toString(){
        return "Tesoros =" + Integer.toString(treasures) + " Nivel = " + Integer.toString(level);
    }
}
