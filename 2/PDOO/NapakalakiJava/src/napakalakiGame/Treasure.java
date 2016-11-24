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
public class Treasure {
    private String name;
    private int bonus;
    private TreasureKind type;
    
    public Treasure(String n, int bonus, TreasureKind t){
        name=n;
        this.bonus=bonus;
        type=t;
    }
    
    public String getName(){
        return name;
    }
    public int getBonus(){
        return bonus;
    }
    
    public TreasureKind getType(){
        return type;
    }
    
    public String toString(){
      return name + "; tipo: " + type + "; bonus: " + bonus;
    }
    
}
