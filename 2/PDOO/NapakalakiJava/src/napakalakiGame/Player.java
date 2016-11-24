/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package napakalakiGame;

import GUI.Dice;
import java.util.ArrayList;
import java.util.Random;

/**
 *
 * @author david
 */
public class Player {
    private String name;
    private static final int MAXLEVEL=10;
    private int level=1;
    private boolean dead=true;
    private boolean canISteal=true;
    protected Player enemy;
    private ArrayList<Treasure> visibleTreasures=new ArrayList();
    private ArrayList<Treasure> hiddenTreasures=new ArrayList();
    private BadConsequence pendingBadConsequence=null;
    
    public Player(String name){
       this.name=name;
    }
    
    public static int getMAXLEVEL(){
        return MAXLEVEL;
    }
    
    public Player(Player p){
        name=p.name;
        level=p.level;
        dead=p.dead;
        canISteal=p.canISteal;
        enemy=p.enemy;
        visibleTreasures=new ArrayList(p.visibleTreasures);
        hiddenTreasures=new ArrayList(p.hiddenTreasures);
        pendingBadConsequence=p.pendingBadConsequence;
    }
    
    public String getName(){
        return this.name;
    }
    
    private void bringToLife(){
        this.dead=false;
    }
    
    protected int getCombatLevel(){
        int l=level;
        for (Treasure t: visibleTreasures){
            l+=t.getBonus();
        }
        return l;
    }
    
    private void incrementLevels(int l){
        if (this.level+l< MAXLEVEL){
            level+=l;
        }
        else {
            level= MAXLEVEL;
        }
        
    }
    
    private void decrementLevels(int l){
        if (this.level-l> 0){
            level-=l;
        }
        else {
            level=1;
        }
    }
    
    private void setPendingBadConsequence(BadConsequence b){
        pendingBadConsequence=b;
    }
    
    
    private void applyPrize(Monster m){
        int nLevels=m.getLevelsGained();
        incrementLevels(nLevels);
        int nTreasures=m.getTreasuresGained();
        if (nTreasures>0){
            CardDealer dealer=CardDealer.getInstance();
            for (int i=0; i<nTreasures; ++i){
                Treasure t=dealer.nextTreasure();
                hiddenTreasures.add(t);
            }
        }
    }
    
    private void applyBadConsequence(Monster m){
        BadConsequence badConsequence=m.getBc();
        int nLevels=badConsequence.getLevels();
        decrementLevels(nLevels);
        BadConsequence pendingBad=badConsequence.adjustToFitTreasureLists(visibleTreasures, hiddenTreasures);        
        setPendingBadConsequence(pendingBad);
    }
    
    private boolean canMakeTreasureVisible(Treasure t){
        int contador=0;
        if (pendingBadConsequence!=null && !pendingBadConsequence.isEmpty())
            return false;
        if(t.getType()==TreasureKind.BOTHHANDS){
             for(Treasure t1: visibleTreasures)
                 if (t1.getType()==TreasureKind.BOTHHANDS || t1.getType()==TreasureKind.ONEHAND)
                     return false;
             
        }
        else if (t.getType()==TreasureKind.ONEHAND){
            for (Treasure t1: visibleTreasures)
                if (t1.getType()==TreasureKind.ONEHAND)
                    contador++;
                else if (t1.getType()==TreasureKind.BOTHHANDS)
                    return false;
            return contador<2;
        }
        else
            for (Treasure t1: visibleTreasures)
                if (t1.getType()==t.getType())
                    return false;
        return true;
    }
    
    private int howManyVisibleTreasures(TreasureKind tKind){
        int contador=0;
        for (Treasure t: visibleTreasures){
            if (t.getType()==tKind){
                if (tKind==TreasureKind.BOTHHANDS){
                    contador+=2;
            }
                else {
                    contador++;
                }
        }
        }
        
        return contador;
    }
    
    private void dieifNoTreasures(){
        if (hiddenTreasures.isEmpty() && visibleTreasures.isEmpty())
            dead=true;
    }
    
    public boolean isDead(){
        return dead;
    }
    
    public ArrayList<Treasure> getHiddenTreasures(){
        return hiddenTreasures;
    }
    
    public ArrayList<Treasure> getVisibleTreasures(){
        return visibleTreasures;
    }
    
    public CombatResult combat(Monster m){
        int myLevel=getCombatLevel();
        int monsterLevel=this.getOponentLevel(m);
        if (myLevel>monsterLevel){
            applyPrize(m);
            if (level>=MAXLEVEL)
                return CombatResult.WINGAME;
            else
                return CombatResult.WIN;
        }
        else{
            applyBadConsequence(m);
            if(shouldConvert())
                return CombatResult.LOSEANDCONVERT;
            else
                return CombatResult.LOSE;
        }
        
    }
    
    public void makeTreasureVisible(Treasure t){
        boolean canI=canMakeTreasureVisible(t);
        if (canI){
            visibleTreasures.add(t);
            hiddenTreasures.remove(t);
        }
    }
    
    public void discardVisibleTreasure(Treasure t){
        visibleTreasures.remove(t);
        if (pendingBadConsequence!=null && !pendingBadConsequence.isEmpty())
            pendingBadConsequence.substractVisibleTreasure(t);
        dieifNoTreasures();
    }
    
    public void discardHiddenTreasure(Treasure t){
        hiddenTreasures.remove(t);
        if (pendingBadConsequence!=null && !pendingBadConsequence.isEmpty())
            pendingBadConsequence.substractHiddenTreasure(t);
        dieifNoTreasures();

    }
    
    public boolean validState(){
        return (pendingBadConsequence==null || pendingBadConsequence.isEmpty())
                && hiddenTreasures.size()<=4;
    }
        
    
    public void initTreasures(){
        CardDealer dealer=CardDealer.getInstance();
        Dice dice=Dice.getInstance();
        bringToLife();
        hiddenTreasures.add(dealer.nextTreasure());
        int number=dice.nextNumber();
        if (number>1)
            hiddenTreasures.add(dealer.nextTreasure());
        if (number==6)
            hiddenTreasures.add(dealer.nextTreasure());
    }
    
    public int getLevels(){
        return level;
    }
    
    public Treasure stealTreasure(){
        Treasure treasure=null;
        boolean canI=canISteal();
        if (canI){
            boolean canYou = enemy.canYouGiveMeATreasure();
            if (canYou){
                treasure=enemy.giveMeATreasure();
                hiddenTreasures.add(treasure);
                haveStolen();
            }
        }
        return treasure;
    }
    
    public Player getEnemy() {
      return enemy;
    }
    
    public void setEnemy(Player enemy){
        this.enemy=enemy;
        
    }
    public BadConsequence getPendingBadConsequence() {
      return pendingBadConsequence;
    }
    protected Treasure giveMeATreasure(){
        Random rnd=new Random();
        int a=(int)(rnd.nextDouble() * hiddenTreasures.size());
        return hiddenTreasures.remove(a);
    }
    
    public boolean canISteal(){
        return canISteal;
    }
    
    public boolean canYouGiveMeATreasure(){
        return !hiddenTreasures.isEmpty();
    }
    
    private void haveStolen(){
        canISteal=false;
        
    }
    
    public void discardAllTreasures(){
        ArrayList<Treasure> copia=new ArrayList(visibleTreasures);
        for (Treasure t: copia)
            discardVisibleTreasure(t);
        
        copia=new ArrayList(hiddenTreasures);
        for (Treasure t: copia)
            discardHiddenTreasure(t);
    }
    public String toString(){
        String a="Nombre: " + name + "\n" +
        " Nivel: " + Integer.toString(level) + "\n" +
        " Enemigo: " + enemy.getName() + "\n";
        return a;
                    
    }
    
    protected int getOponentLevel(Monster m){
        return m.getLevel();
    }
    
    protected boolean shouldConvert(){
        Dice dice=Dice.getInstance();
        int n =dice.nextNumber();
        if(n==1){
            return true;
        }
        else{
            return false;
        }
    }
}

 
