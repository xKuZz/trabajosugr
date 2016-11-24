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
public class NumericBadConsequence extends BadConsequence {
    private int nVisibleTreasures;
    private int nHiddenTreasures;
    
    public NumericBadConsequence(String texto,int levels,int nVisible,int nHidden){
        super(texto,levels);
        nVisibleTreasures=nVisible;
        nHiddenTreasures=nHidden;
    }
    
    public int getNVisibleTreasures(){
        return nVisibleTreasures;
    }
    
    public int getNHiddenTreasures(){
        return nHiddenTreasures;
    }

    @Override
    public boolean isEmpty() {
        return nVisibleTreasures==0 && nHiddenTreasures==0;
    }

    @Override
    public void substractVisibleTreasure(Treasure t) {
        if (nVisibleTreasures!=0)
            nVisibleTreasures--;
    }

    @Override
    public void substractHiddenTreasure(Treasure t) {
        if (nHiddenTreasures!=0)
            nHiddenTreasures--;
    }
    
    @Override
    public NumericBadConsequence adjustToFitTreasureLists(ArrayList<Treasure> v, ArrayList<Treasure> h){
        NumericBadConsequence bc = new NumericBadConsequence("", 0, Math.min(nVisibleTreasures, v.size()), 
                                             Math.min(nHiddenTreasures,  h.size()));
        return bc;
    }
    
    @Override
    public String toString(){
        String s = super.toString();
        return (s + "Número tesoros visibles: " + Integer.toString(nVisibleTreasures) + "\n" +
                "Número tesoros ocultos: " + Integer.toString(nHiddenTreasures) + "\n");
    }
}
