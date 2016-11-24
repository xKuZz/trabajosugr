/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package napakalakiGame;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class CardDealer {
    private static final CardDealer instance = new CardDealer();
    private CardDealer() { }
    public static CardDealer getInstance() {
        return instance;
    }
    
    private ArrayList<Monster> unusedMonsters= new ArrayList();
    private ArrayList<Monster> usedMonsters = new ArrayList();
    private ArrayList<Treasure> unusedTreasures = new ArrayList();
    private ArrayList<Treasure> usedTreasures = new ArrayList();
    private ArrayList<Cultist> unusedCultists = new ArrayList();
    
    
    private void initTreasureCardDeck() {
        Treasure t=new Treasure("¡Si mi amo!", 4, TreasureKind.HELMET);
        unusedTreasures.add(t);
        
        t=new Treasure("Botas de investigacion", 3, TreasureKind.SHOES);
        unusedTreasures.add(t);
        
        t=new Treasure("Capucha de Cthulhu", 3, TreasureKind.HELMET);
        unusedTreasures.add(t);
        
        t=new Treasure("A prueba de babas", 2, TreasureKind.ARMOR);
        unusedTreasures.add(t);
        
        t=new Treasure("Botas de lluvia acida", 1, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t);
        
        t=new Treasure("Casco minero", 2, TreasureKind.HELMET);
        unusedTreasures.add(t);
        
        t=new Treasure("Ametralladora Thompson", 4, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t);
        
        t=new Treasure("Camiseta de la UGR", 1, TreasureKind.ARMOR);
        unusedTreasures.add(t);
        
        t=new Treasure("Clavo de rail ferroviario", 3, TreasureKind.ONEHAND);
        unusedTreasures.add(t);
        
        t=new Treasure("Cuchillo de sushi arcano", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(t);
        
        t=new Treasure("Fez alopodo", 3, TreasureKind.HELMET);
        unusedTreasures.add(t);
        
        t=new Treasure("Hacha prehistorica", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(t);
        
        t=new Treasure("El aparato del Pr. Tesla", 4, TreasureKind.ARMOR);
        unusedTreasures.add(t);
        
        t=new Treasure("Gaita", 4, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t);
        
        t=new Treasure("Insecticida", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(t);
        
        t=new Treasure("Escopeta de 3 cañones", 4, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t);
        
        t=new Treasure("Garabato mistico", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(t);
        
        t=new Treasure("La rebeca metalica", 2, TreasureKind.ARMOR);
        unusedTreasures.add(t);
        
        t=new Treasure("Lanzallamas", 4, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t);
        
        t=new Treasure("Necro comicon", 1, TreasureKind.ONEHAND);
        unusedTreasures.add(t);
        
        t=new Treasure("Necronomicon", 5, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t);
        
        t=new Treasure("Linterna a 2 manos", 3, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t);
        
        t=new Treasure("Necro-gnomicon", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(t);
        
        t=new Treasure("Necrotelecom", 2, TreasureKind.HELMET);
        unusedTreasures.add(t);
        
        t=new Treasure("Mazo de los antiguos", 3, TreasureKind.ONEHAND);
        unusedTreasures.add(t);
        
        t=new Treasure("Necro playboycon", 3, TreasureKind.ONEHAND);
        unusedTreasures.add(t);
        
        t=new Treasure("Porra preternatural", 2, TreasureKind.ONEHAND);
        unusedTreasures.add(t);
        
        t=new Treasure("Shogulador", 1, TreasureKind.BOTHHANDS);
        unusedTreasures.add(t);
        
        t=new Treasure("Varita de atizamiento", 3, TreasureKind.ONEHAND);
        unusedTreasures.add(t);
        
        t=new Treasure("Tentaculo de pega", 2, TreasureKind.HELMET);
        unusedTreasures.add(t);
        
        t=new Treasure("Zapato deja-amigos", 1, TreasureKind.SHOES);
        unusedTreasures.add(t);
        
    }
    
    public void initMonsterCardDeck() {
        BadConsequence bc= new NumericBadConsequence("Pierdes 5 niveles y tres tesoros visibles",5,3,0);
        Prize pc = new Prize(4,2);
        Monster mn=new Monster("El rey de rosa",13,bc,pc);
        unusedMonsters.add(mn);
        
        bc= new NumericBadConsequence("Pierdes 2 niveles y 2 tesoros ocultos",2,0,2);
        pc = new Prize(2,1);
        mn=new Monster("Semillas Cthulhu",4,bc,pc);
        unusedMonsters.add(mn);
       
        bc= new SpecificBadConsequence("Te atrapan para llevarte de fiesta y te dejan caer en mitad del vuelo. Descarta 1 mano visible y 1 mano oculta",0,new ArrayList(Arrays.asList(TreasureKind.ONEHAND)),new ArrayList(Arrays.asList(TreasureKind.ONEHAND)));
        pc = new Prize(4,1);
        mn=new Monster("Angeles de la noche ibicenca",14,bc,pc);
        unusedMonsters.add(mn);
        
        bc= new SpecificBadConsequence("Sientes bichos bajo la ropa. Descarta la armadura visible.",0,new ArrayList(Arrays.asList(TreasureKind.ARMOR)),new ArrayList());
        pc = new Prize(1,1);
        mn=new Monster("Bichgooth",2,bc,pc);
        unusedMonsters.add(mn);     
        
        bc= new DeathBadConsequence("La familia te atrapa. Estas muerto.");
        pc = new Prize(4,1);
        mn=new Monster("Familia feliz",1,bc,pc);
        unusedMonsters.add(mn);
        
        bc= new DeathBadConsequence("Estos monstruos resultan bastante superficiales y te aburren mortalmente. Estás muerto.");
        pc= new Prize(2,1);
        mn= new Monster("Los hondos",8,bc,pc);
        unusedMonsters.add(mn);
        
        bc= new SpecificBadConsequence("Te intentas escaquear,pierdes una mano visible",0,new ArrayList(Arrays.asList(TreasureKind.ONEHAND)),new ArrayList());
        pc = new Prize(2,1);
        mn=new Monster("Dameargo",1,bc,pc);
        unusedMonsters.add(mn);
        
        bc= new NumericBadConsequence("Da mucho asquito.Pierdes 3 niveles",3,0,0);
        pc = new Prize(1,1);
        mn=new Monster("Pollipolipo volante",3,bc,pc);
        unusedMonsters.add(mn);
        
        bc= new DeathBadConsequence("No le hace gracia que pronuncien mal su nombre.Estás muerto.");
        pc = new Prize(3,1);
        mn=new Monster("YskhtihyssgGoth",12,bc,pc);
        unusedMonsters.add(mn);
        
        bc= new SpecificBadConsequence("La quinta directiva primaria te obliga a perder 2 niveles y 1 tesoro 2 manos visibles",2,new ArrayList(Arrays.asList(TreasureKind.BOTHHANDS)),new ArrayList());
        pc = new Prize(2,1);
        mn=new Monster("Roboggoth",8,bc,pc);
        unusedMonsters.add(mn);
        
        bc= new SpecificBadConsequence("Te asusta en la noche.Pierdes un casco visible.",0,new ArrayList(Arrays.asList(TreasureKind.HELMET)),new ArrayList());
        pc = new Prize(1,1);
        mn=new Monster("El espia",5,bc,pc);
        unusedMonsters.add(mn);
        
        bc = new NumericBadConsequence("Menudo Susto te llevas. Pierdes 2 niveles y 5 tesoros visibles.",2,5,0);
        pc = new Prize(1,1);
        mn=new Monster("El lenguas",20,bc,pc);
        unusedMonsters.add(mn);
   
        bc= new SpecificBadConsequence("Te faltan manos para tanta cabeza. Pierdes 3 niveles y tus tesoros visibles de las manos",3,new ArrayList(Arrays.asList(TreasureKind.BOTHHANDS)),new ArrayList());
        pc = new Prize(1,1);
        mn = new Monster("Bicefalo",20,bc,pc);
        unusedMonsters.add(mn);
        
        bc= new SpecificBadConsequence("Pierdes tu armadura visible y otra oculta.",0,new ArrayList(Arrays.asList(TreasureKind.ARMOR)),new ArrayList(Arrays.asList(TreasureKind.ARMOR)));
        pc = new Prize(2,1);
        mn=new Monster("3 Byakhees de bonanza",8,bc,pc);
        unusedMonsters.add(mn);
        
        bc= new SpecificBadConsequence("Embobados con el lindo primigenio te descartas de tu casco visible",0,new ArrayList(Arrays.asList(TreasureKind.HELMET)),new ArrayList());
        pc = new Prize(1,1);
        mn=new Monster("Chibithulhu",2,bc,pc);
        unusedMonsters.add(mn);
        
        bc= new SpecificBadConsequence("El primordial bostezo contagioso. Pierdes el calzado visible",0,new ArrayList(Arrays.asList(TreasureKind.SHOES)),new ArrayList());
        pc = new Prize(1,1);
        mn=new Monster("El sopor de Dunwich",2,bc,pc);
        unusedMonsters.add(mn);
       
        bc= new NumericBadConsequence("Pierdes todos tus tesoros visibles",0,BadConsequence.getMAXTREASURES(),0);
        pc = new Prize(3,1);
        mn=new Monster("El gorron en el umbral",10,bc,pc);
        unusedMonsters.add(mn);
        
        bc= new SpecificBadConsequence("Pierdes la Armadura visible.",0,new ArrayList(Arrays.asList(TreasureKind.ARMOR)),new ArrayList());
        pc = new Prize(2,1);
        mn=new Monster("H.P. Munchcraft",6,bc,pc);
        unusedMonsters.add(mn);
        
        bc= new NumericBadConsequence("Toses los pulmones y pierdes 2 niveles.",2,0,0);
        pc = new Prize(1,1);
        mn=new Monster("La que redacta en las tinieblas",2,bc,pc);
        unusedMonsters.add(mn);
        
        //Monstruos que se comportan distinto contra sectarios:
        
        bc=new SpecificBadConsequence("Pierdes una mano visible",0,new ArrayList(Arrays.asList(TreasureKind.ONEHAND)),new ArrayList());
        pc= new Prize(3,1);
        mn=new Monster("El mal indecible impronunciable",10,bc,pc,-2);
        unusedMonsters.add(mn);
        
        bc=new NumericBadConsequence("Pierdes tus tesoros vivibles.Jajaja.",0,BadConsequence.getMAXTREASURES(),0);
        pc= new Prize(2,1);
        mn=new Monster("Testigos Oculares",6,bc,pc,2);
        unusedMonsters.add(mn);
        
        bc=new DeathBadConsequence("Hoy no es tu día de suerte. Mueres.");
        pc= new Prize(2,5);
        mn=new Monster("El gran cthulhu",20,bc,pc,4);
        unusedMonsters.add(mn);
        
        bc=new NumericBadConsequence("Tu gobierno te recorta 2 niveles",2,0,0);
        pc= new Prize(2,1);
        mn=new Monster("Serpiente politico",8,bc,pc,-2);
        unusedMonsters.add(mn);
        
        bc=new SpecificBadConsequence("Pierdes tu casco y tu armadura visible. Pierdes tus manos ocultas.",0,new ArrayList(Arrays.asList(TreasureKind.ARMOR,TreasureKind.HELMET)),new ArrayList(Arrays.asList(TreasureKind.BOTHHANDS)));
        pc= new Prize(1,1);
        mn=new Monster("Felpuggoth",2,bc,pc,5);
        unusedMonsters.add(mn);
        
        bc=new NumericBadConsequence("Pierdes 2 niveles.",2,0,0);
        pc= new Prize(4,2);
        mn=new Monster("Shoggoth",16,bc,pc,-4);
        unusedMonsters.add(mn);
        
        bc=new NumericBadConsequence("Pintalabios negro. Pierdes 2 niveles",2,0,0);
        pc= new Prize(1,1);
        mn=new Monster("Lolitagooth",2,bc,pc,3);
        unusedMonsters.add(mn);
        
    }
    
    private void initCultistCardDeck(){
        unusedCultists.add(new Cultist("Sectario",1));
        unusedCultists.add(new Cultist("Sectario",2));
        unusedCultists.add(new Cultist("Sectario",1));
        unusedCultists.add(new Cultist("Sectario",2));
        unusedCultists.add(new Cultist("Sectario",1));
        unusedCultists.add(new Cultist("Sectario",1));
    }
    
    private void shuffleCultists(){
        Collections.shuffle(unusedCultists);
    } 
    
    
    private void shuffleTreasures() {
        Collections.shuffle(unusedTreasures);
    }
    
    private void shuffleMonsters() {
        Collections.shuffle(unusedMonsters);
    }
    
    public Cultist nextCultist(){
        return unusedCultists.remove(0);
    }
    
    public Treasure nextTreasure(){
        if (unusedTreasures.isEmpty()){
           unusedTreasures.addAll(usedTreasures);
           usedTreasures.clear();
           shuffleTreasures();
        }
        return unusedTreasures.remove(0);
    }
    
    public Monster nextMonster(){
        if (unusedMonsters.isEmpty()){
           unusedMonsters.addAll(usedMonsters);
           usedMonsters.clear();
           shuffleMonsters();
        }
        return unusedMonsters.remove(0);  
    }
    
    public void giveTreasureBack(Treasure t){
        usedTreasures.add(t);
    }
    
    public void giveMonsterBack(Monster m){
        usedMonsters.add(m);
    }
    
    public void initCards(){
        initTreasureCardDeck();
        initMonsterCardDeck();
        initCultistCardDeck();
        shuffleMonsters();
        shuffleTreasures();
        shuffleCultists();
    }
    
}
