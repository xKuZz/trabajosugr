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
public class Monster {
    private String name;
    private int combatLevel;
    private Prize prize;
    private BadConsequence bc;
    private int levelChangeAgainstCultistPlayer=0;
    
    public Monster(String name, int level, BadConsequence bc, Prize price){
        this.name=name;
        this.combatLevel=level;
        this.bc=bc;
        this.prize=new Prize(price);
    }
    
    public Monster(String name, int level, BadConsequence bc, Prize price,int IC){
        this.name=name;
        this.combatLevel=level;
        this.bc=bc;
        this.prize=new Prize(price);
        levelChangeAgainstCultistPlayer=IC;
    }
    
    public int getCombatLevelAgainstCultisPlayer(){
        return getLevel()+levelChangeAgainstCultistPlayer;
    }
    
    public String getName(){
        return name;
    }
    
    public int getLevel(){
        return combatLevel;
    }
    
    public BadConsequence getBc(){
        return bc;
    }
    
    public Prize getPrize(){
        return prize;
    }
    
    public String toString(){
        return "Nombre = " + name + "\nNivel Combate = " + Integer.toString(combatLevel) +
        "\nPremio = " + prize.toString() + "\nMal rollo = " + bc.toString();
    }
    
    public int getLevelsGained(){
        return prize.getLevel();
    }
    
    public int getTreasuresGained(){
        return prize.getTreasures();
    }
}
