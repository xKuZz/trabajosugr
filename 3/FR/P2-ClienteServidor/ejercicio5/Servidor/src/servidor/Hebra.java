
package servidor;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;

/**
 *
 * @author Alejandro Campoy Nieves.
 * @author David Criado Ramón.
 * 
 * La clase hebra se encarga de atender las comunicaciones TCP del Servidor
 */
public class Hebra extends Thread {
    private final Socket socketServicio;
    private PrintWriter outPrinter;
    private BufferedReader inReader;
    private final Procesador procesador;
    private final ArrayList<String> toSend = new ArrayList();
    
    /** Constructor de la clase Hebra.
     * 
     * @param s Socket del servidor que atiende al cliente.
     */
    Hebra(Socket s) {
        socketServicio = s;
        procesador = Procesador.getInstance(socketServicio, toSend);
        try {
            outPrinter = new PrintWriter(socketServicio.getOutputStream(), true);
            outPrinter.println("50 HELLO");
        } catch (IOException ex) {
            System.err.println(ex);
            System.err.println("Error al mandar mensaje de bienvenida.");
        }
        
    }
    
    /** Método encargado de leer, atender y responder una conexión TCP de un cliente.
     * 
     */
    private void atender() {
        try {
            outPrinter = new PrintWriter(socketServicio.getOutputStream(), true);
            inReader = new BufferedReader(new InputStreamReader(socketServicio.getInputStream()));
            
            // Leer petición
            String peticion = inReader.readLine();
            if (peticion == null) return;
            System.out.println(peticion);
            
            // Procesar petición con Procesador
            String respuesta = procesador.parse(peticion, socketServicio);
            
            if ("401 BYE".equals(respuesta)) {
                outPrinter.println("401 BYE");
                socketServicio.close();
            }
            else if ("200 UPDATE".equals(peticion)) {
                System.out.println("Recibido " + peticion);
                String message;
                while (!toSend.isEmpty()) {
                   message = toSend.remove(0);
                   System.out.println("Enviado " + message);
                    outPrinter.println("201 " + message);
                }
                outPrinter.println("202 END");
                
            }   
            else {
                System.out.println(respuesta);
                outPrinter.println(respuesta);
            }
               
          
                    
        } catch(IOException io) {
            System.err.println("Error al leer/escribir en el socket");
        }
    }
    
    /** Método de la hebra que atiende la conexión TCP mientras esta abierta.
     * 
     */
    @Override
    public void run() {
        while (!socketServicio.isClosed())
            atender();
    }
}
