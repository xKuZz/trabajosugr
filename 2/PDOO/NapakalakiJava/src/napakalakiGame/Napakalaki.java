/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package napakalakiGame;
import java.util.ArrayList;
import java.util.Random;

/**
 *
 * @author david
 */
public class Napakalaki {
    // Singleton
    private static final Napakalaki instance = new Napakalaki();
    private Napakalaki() { }
    public static Napakalaki getInstance() {
    return instance;
    }
    private Player currentPlayer;
    private ArrayList<Player> players=new ArrayList();
    private CardDealer dealer=CardDealer.getInstance();
    private Monster currentMonster;
    
    
    private void initPlayers(ArrayList<String> names){
        for (String name :names)
            players.add(new Player(name));
    }
    
    private Player nextPlayer(){
        Player p;
        int a;
        if (currentPlayer==null) {
            Random rnd=new Random();
            a=(int)(rnd.nextDouble() * players.size());
        }
        else {
           
           a=players.indexOf(currentPlayer);
           if (a+1==players.size())
               a=0;
           else
               a=a+1 ;     
        }
        
        return players.get(a);
    }
    
    private boolean nextTurnAllowed(){
        if (currentPlayer==null)
            return true;
        else
            return currentPlayer.validState();
    }
    
    private void setEnemies(){
        Random rnd=new Random();
        int a;
        for (Player p : players){ 
            do{
            a=(int)(rnd.nextDouble() * players.size());
            } while (players.get(a)==p);
            p.setEnemy(players.get(a));
            
        }
    }
    
    public CombatResult developCombat(){
            Monster m=currentMonster;
            CombatResult cr= currentPlayer.combat(m);
            if(cr==CombatResult.LOSEANDCONVERT){
                Cultist carta=dealer.nextCultist();
                CultistPlayer cp=new CultistPlayer(currentPlayer,carta);
                int ind=players.indexOf(currentPlayer);
                players.set(ind,cp);
                currentPlayer=cp;
            }
               
            dealer.giveMonsterBack(m);
            return cr;
    }
    
    public void discardVisibleTreasures(ArrayList<Treasure> treasures){
        ArrayList<Treasure> toRemove = new ArrayList(treasures);
        for (Treasure t : toRemove){
            currentPlayer.discardVisibleTreasure(t);
            dealer.giveTreasureBack(t);
        }
    }
    
    public void discardHiddenTreasures(ArrayList<Treasure> treasures){
        ArrayList<Treasure> toRemove = new ArrayList(treasures);
         for (Treasure t : toRemove){
            currentPlayer.discardHiddenTreasure(t);
            dealer.giveTreasureBack(t);
        }
    }
    
    public void makeTreasuresVisible(ArrayList<Treasure> treasures){
        for (Treasure t:treasures)
            currentPlayer.makeTreasureVisible(t);
    }
    
    public void initGame(ArrayList<String> players){
        initPlayers(players);
        setEnemies();
        dealer.initCards();
        nextTurn();
    }
    
    public Player getCurrentPlayer(){
        return currentPlayer;
    }
    
    public Monster getCurrentMonster(){
        return currentMonster;
    }
    
    public boolean nextTurn(){
        boolean stateOK=nextTurnAllowed();
        if(stateOK){
            currentMonster=dealer.nextMonster();
            currentPlayer=nextPlayer();
            boolean dead=currentPlayer.isDead();
            if (dead){
                currentPlayer.initTreasures();
            }
            
        }
        return stateOK;
        
    }
    
    public boolean endOfGame(CombatResult result){
        return result==CombatResult.WINGAME;
    }
}

