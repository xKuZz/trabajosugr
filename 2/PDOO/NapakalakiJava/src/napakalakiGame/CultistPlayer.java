/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package napakalakiGame;

import java.util.Random;

/**
 *
 * @author alejandro
 */
public class CultistPlayer extends Player{
    private static int totalCultisPlayers=0;
    private Cultist myCultistCard;
    
    public static int getTotalCultistPlayers(){
        return totalCultisPlayers;
    }
    
    public CultistPlayer(Player p,Cultist c){
        super(p);
        myCultistCard=c;
        totalCultisPlayers++;
    }
    
    protected int getCombatLevel(){
        int res=(int)(super.getCombatLevel()*1.2)+myCultistCard.getGainedLevels()*totalCultisPlayers;
        return res;
    }
    
    protected Treasure giveMeATreasure(){
         Random rnd=new Random();
        int a=(int)(rnd.nextDouble() * getVisibleTreasures().size());
        return getVisibleTreasures().remove(a);
    }
    
    public boolean canYouGiveMeATreasure(){
        return !getVisibleTreasures().isEmpty();
    }
    
    protected int getOponentLevel(Monster m){
        return m.getCombatLevelAgainstCultisPlayer();
    }


    protected boolean shouldConvert(){
        return false;
    }
    
}
