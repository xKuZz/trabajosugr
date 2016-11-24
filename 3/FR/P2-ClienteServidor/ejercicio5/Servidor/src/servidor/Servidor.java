package servidor;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * @author Alejandro Campoy Nieves
 * @author David Criado Ramón
 * 
 * La clase Servidor se encarga de abrir el socket del Servidor
 * y crear las distintas hebras (clase Hebra) que se encargarán de atender las
 * peticiones.
 */
public class Servidor {
    private static final int PORT = 2036;
    static private ServerSocket socketServidor;
    public static void main(String[] args) {
        try {
            socketServidor = new ServerSocket(PORT);
        }
        catch (IOException io) {
            System.err.println("Error al iniciar servidor en puerto " + PORT);
        }
        
        while (true) {
            try {
                Socket socketServicio = socketServidor.accept();
                Hebra h = new Hebra(socketServicio);
                h.start();
            } catch (IOException io) {
                System.err.println("Error al iniciar conexión con cliente");
            } 
        }
    }
    
}
