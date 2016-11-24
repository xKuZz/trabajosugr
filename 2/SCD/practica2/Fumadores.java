import monitor.*;

class Estanco extends AbstractMonitor
{
    /** No hay nada -> Ingrediente -1
     *  Cerillas -> Ingrediente 0 Fumador 0
     *  Papel -> Ingrediente 1 Fumador 1
     *  Tabaco -> Ingrediente 2 Fumador 2
     */
    private int ingrediente;
    private Condition colaEstanquero;
    private Condition[] colaFumadores=new Condition[3];
    private boolean mostradorLleno;
   
            
    public Estanco(){ // Inicializamos las variables condicion y el mostrador vacío
        colaEstanquero=makeCondition();
        for (int i=0; i<colaFumadores.length; ++i)
            colaFumadores[i]=makeCondition();
        mostradorLleno=false;
        
        
    }
    public void obtenerIngrediente (int miIngrediente){
        enter();
        if (!mostradorLleno || ingrediente!=miIngrediente)
            colaFumadores[miIngrediente].await();
        
        switch(miIngrediente){
            case 0:
                 System.out.println("Fumador 0: He obtenido cerillas.");
                 break;
            case 1:
                 System.out.println("Fumador 1: He obtenido papel.");
                 break;
            case 2:
                 System.out.println("Fumador 2: He obtenido tabaco."); 
                 break;
        }
        mostradorLleno=false;
        
        colaEstanquero.signal();
            
        leave();
    }
    
    public void ponerIngrediente( int ingrediente ){
        enter();
        switch(ingrediente){
            case 0:
                System.out.println("Estanquero: Produciendo cerillas.");
                break;
            case 1:
                System.out.println("Estanquero: Produciendo papel.");
                break;
            case 2:
                System.out.println("Estanquero: Produciendo tabaco.");
            break;
        }
            this.ingrediente=ingrediente;
            mostradorLleno=true;
            colaFumadores[ingrediente].signal();
        leave();
        
        
    }
    
    public void esperarRecogidaIngrediente(){
        enter();
            System.out.println("Estanquero: Mostrador lleno (1 objeto).");
            if (mostradorLleno)
                colaEstanquero.await();
            System.out.println("Estanquero: Mostrador vacio (0 objetos).");
        leave();
    }
}

class Estanquero implements Runnable {
    public Thread thr;
    private Estanco estanco;
    
    public Estanquero(Estanco estanco){
        this.estanco=estanco;
        thr=new Thread(this);
    }
    
    public void run(){
        int ingrediente;
        while (true){
            ingrediente = (int) (Math.random () * 3.0); // 0, 1 o 2
            estanco.ponerIngrediente(ingrediente);
            estanco.esperarRecogidaIngrediente();
        }   
    }
}

class Fumador implements Runnable {
    public Thread thr;
    private Estanco estanco; // Estanco al que acude (monitor)
    private int miIngrediente; // Nº de fumador/ingrediente
    
    public Fumador(Estanco estanco, int nfumador){
        this.estanco=estanco;
        this.miIngrediente=nfumador;
        thr=new Thread(this,"Fumador "+Integer.toString(nfumador));
    }
    
    private void Gaste(){
        if (miIngrediente==0)
         System.out.println(thr.getName()+": Me quede sin cerillas.");
        else if (miIngrediente==1)
         System.out.println(thr.getName()+": Me quede sin papel.");
        else
         System.out.println(thr.getName()+": Me quede sin tabaco."); 
    }
    
    public void run(){
        while (true){
            estanco.obtenerIngrediente(miIngrediente);
            aux.dormir_max(2000);
            Gaste();
        }
    }
}

class Fumadores {
    public static void main( String[] args ) {
        // Creamos variables
        Estanco estanco=new Estanco();
        Estanquero estanquero=new Estanquero(estanco);
        Fumador fumadores[]=new Fumador[3];
        
        for (int i=0; i<fumadores.length; ++i)
            fumadores[i]=new Fumador(estanco,i);
        
        
        // Ponemos en marcha las hebras
        estanquero.thr.start();
        for (int i=0; i<fumadores.length; ++i)
            fumadores[i].thr.start();
        
        
    }
}

