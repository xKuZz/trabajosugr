/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package napakalakiGame;

import java.util.ArrayList;

/**
 *
 * @author alejandro
 */
public abstract class BadConsequence {
    private static final int MAXTREASURES=10;
    private String text;
    private int levels;
    
    public BadConsequence(String text, int levels){
        this.text=text;
        this.levels=levels;   
    
    }
    
    public String getText(){
        return text;
    }
    
    public int getLevels(){
        return levels;
    }
    
    public static int getMAXTREASURES(){
        return MAXTREASURES;
    }
 
    @Override
    public String toString(){
        return  text + "\nNivel = " + Integer.toString(levels) +"\n";
    }
    
    public abstract boolean isEmpty();  // método abstracto
    
    public abstract void substractVisibleTreasure(Treasure t); //método abstracto
    
    public abstract void substractHiddenTreasure(Treasure t);  //método abstracto
    
    public abstract BadConsequence adjustToFitTreasureLists(ArrayList<Treasure> v, 
                                                            ArrayList<Treasure> h);
  
}