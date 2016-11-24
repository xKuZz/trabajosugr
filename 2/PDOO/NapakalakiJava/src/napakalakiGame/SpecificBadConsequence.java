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
public class SpecificBadConsequence extends BadConsequence{
    private ArrayList<TreasureKind> specificHiddenTreasures = new ArrayList();
    private ArrayList<TreasureKind> specificVisibleTreasures = new ArrayList();
    
    public SpecificBadConsequence(String texto,int levels, ArrayList<TreasureKind> v,ArrayList<TreasureKind> h){
        super(texto,levels);
        specificHiddenTreasures=h;
        specificVisibleTreasures=v;
    }

    @Override
    public boolean isEmpty() {
       return (specificVisibleTreasures.isEmpty() && specificHiddenTreasures.isEmpty());
    }

    @Override
    public void substractVisibleTreasure(Treasure t) {
        int i;
        if ((i=specificVisibleTreasures.indexOf(t.getType()))!=-1)
                specificVisibleTreasures.remove(i);
    }

    @Override
    public void substractHiddenTreasure(Treasure t) {
        int i;
        if ((i=specificHiddenTreasures.indexOf(t.getType()))!=-1)
                specificHiddenTreasures.remove(i);
    }
    
    private ArrayList<TreasureKind> sameSpecific(ArrayList<Treasure> treasures, ArrayList<TreasureKind> specific) {
        ArrayList<TreasureKind> salida=new ArrayList();
        ArrayList<Treasure> aux=new ArrayList(treasures);
        
        for (TreasureKind a : specific){
            for (Treasure b: aux) {
                if (a==b.getType()){
                    salida.add(b.getType());
                    aux.remove(b);
                    break;
                }
            }
        }
        
        return salida;
        
    }
    
    @Override
    public SpecificBadConsequence adjustToFitTreasureLists(ArrayList<Treasure> v, 
                                                           ArrayList<Treasure> h){
        SpecificBadConsequence bc=new SpecificBadConsequence("",0, 
                                            sameSpecific(v, specificVisibleTreasures),
                                            sameSpecific(h, specificHiddenTreasures));
        return bc;
    }
    
    @Override
    public String toString(){
        String s = super.toString();
        s += "Específicos Visibles: " + specificVisibleTreasures.toString() + "\n";
        s += "Específicos Ocultos: "  +  specificHiddenTreasures.toString() + "\n";
        return s;
    }
}
