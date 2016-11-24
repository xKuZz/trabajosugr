import monitor.* ;

// ****************************************************************************

class MonitorCD extends AbstractMonitor
{ 
  private int num_horas = 0 , 
              num_dias  = 0 ;

  public void nueva_hora() 
  { 
    enter() ;
    num_horas++;
    if ( num_horas == 24 )
    { 
      num_dias++;
      num_horas = 0 ;
    }
    leave() ; 
  }
  public int obtener_dia( )
  { 
    enter() ;
    int valor = num_dias;
    leave() ; 
    return valor;
  }
}
// ****************************************************************************

class Usuario implements Runnable   
{ 
  private MonitorCD cont ;   // monitor contador de dias compartido
  private int                 nveces ; // numero de llamadas a 'nueva_hora'
  public  Thread              thr ;    // objeto Thread encapsulado
  
  Usuario( MonitorCD p_cont, int p_nveces, String nombre )      
  { 
    cont   = p_cont;
    nveces = p_nveces;
    thr    = new Thread(this,nombre);
  }
  public void run() 
  { 
    for( int i = 0; i < nveces; i++ ) 
    { 
      System.out.println("Hebra "+thr.getName()+": incrementa hora");
      cont.nueva_hora();
      System.out.println("Hebra "+thr.getName()+": .... dia "+cont.obtener_dia());
    }
  }
}

// ****************************************************************************

class MainContadorDias
{ 
  public static void main( String[] args ) 
  { 
    try 
    { 
      int num_hebras, num_iters;

      if ( args.length != 2 ) 
      { 
        System.err.println("parámetros: número_de_hebras horas_totales \n  utilizando 4 y 50 por defecto");
        num_hebras = 4;
        num_iters=50;
      }
      else
      { 
        num_hebras = Integer.parseInt(args[0]);
        num_iters  = Integer.parseInt(args[1]);
      }

      System.out.println("creando el contador de días\n");

      MonitorCD contdias = new MonitorCD();
      Usuario[]           usuarios = new Usuario[num_hebras];
      
      for( int i = 0 ; i < usuarios.length; i++) 
      { 
        usuarios[i] =  new Usuario( contdias, num_iters, "usuario "+i );
        System.out.println("creando la hebra " + (i+1) + " y lanzándola\n");
        usuarios[i].thr.start();
      }
      
      for(int i = 0; i < usuarios.length; i++)
        usuarios[i].thr.join();
      
      System.out.println("unidas todas las hebras");
    }
    catch(Exception e) 
    { 
      System.err.println("excepción: " + e);
      e.printStackTrace();
    }
  }
}

// ****************************************************************************
