package cliente;


/**
 *
 * @author Alejandro Campoy Nieves.
 * @author David Criado Ramón.
 */
public class Reader extends Thread {
    private final ClienteTCP cliente;
    Reader(ClienteTCP c) {
        cliente = c;
    }
    @Override
    public void run() {
        while (true) {
           try {
                Thread.sleep(1000);
                cliente.receiveMessage();
            
           } catch (InterruptedException ex) {
                System.err.println(ex);
                System.err.println("Problemas temporales.");
            }
        }
    }
}
