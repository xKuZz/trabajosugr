import monitor.*;


class Barberia extends AbstractMonitor {
    private Condition despertador=makeCondition();
    private Condition finCorte=makeCondition();
    private Condition colaClientes=makeCondition();
    
    private boolean ocupado=false;
    private boolean durmiendo=false;
    // Invocado por los clientes para cortarse el pelo
    public void cortarPelo(){
      enter();
      if (ocupado)
          colaClientes.await();
      if (durmiendo) {
          System.out.println("Despierte, barbero");
          durmiendo=false;
          despertador.signal();
      }
          
      ocupado=true;
      System.out.println("Me estan cortando el pelo");
      finCorte.await();
      System.out.println("Terminaron de cortarme el pelo");
      leave();
    }
    
    // Invocado por el barbero para esperar(si procede) a un nuevo cliente y sentarlo para el corte
    public void siguienteCliente(){
        enter();
        if (colaClientes.isEmpty()){
            durmiendo=true;
            System.out.println("Barbero durmiendo");
            despertador.await();
        }
        else 
            colaClientes.signal();
        leave();
    }
    
    // Invocado por el barbero para indicar que ha terminado de cortar el pelo
    public void finCliente(){
        enter();
        if (ocupado) {
            finCorte.signal();
            ocupado=false;
        }
        leave();
        
     
    }
}

class Cliente implements Runnable {
    public Thread thr;
    private int ncliente;
    private Barberia barberia;
    public Cliente(Barberia barba, int ncliente){
        barberia=barba;
        this.ncliente=ncliente;
        thr=new Thread(this,"Cliente " + ncliente);
    }
    public void run(){
        while(true) {
            barberia.cortarPelo(); // El cliente espera (si procede) y se corta el pelo
            aux.dormir_max(2000); // El cliente está fuera de la barbería un tiempo
        }
    }
}

class Barbero implements Runnable {
    public Thread thr;
    private Barberia barberia;
    public Barbero(Barberia barba){
        barberia=barba;
        thr=new Thread(this);
    }
    
    public void run(){
        while(true){
            barberia.siguienteCliente(); // Barbero sienta al proximo cliente
            aux.dormir_max(2500); // Barbero cortando pelo al cliente
            barberia.finCliente(); // Barbero ha terminado de cortar el pelo al cliente
        }
    }
}



class main {
    public static void main( String[] args ) {
        
        // Creamos variables
        Barberia barberia=new Barberia();
        Barbero barbero=new Barbero(barberia);
        Cliente clientes[]=new Cliente[3];
        
        for (int i=0; i<clientes.length; ++i)
            clientes[i]=new Cliente(barberia,i);
        
        
        // Ponemos en marcha las hebras
        barbero.thr.start();
        for (int i=0; i<clientes.length; ++i)
            clientes[i].thr.start();
    }
}
