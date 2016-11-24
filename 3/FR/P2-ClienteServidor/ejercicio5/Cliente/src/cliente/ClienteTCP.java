package cliente;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashSet;
/**
 *
 * @author Alejandro Campoy Nieves.
 * @author David Criado Ramón.
 * La clase ClienteTCP se encarga de establecer y tratar las conexiones del cliente con el Servidor.
 */
public class ClienteTCP {
    private String host;
    private final int PORT = 2036;
    private PrintWriter outPrinter;
    private BufferedReader inReader;
    private Socket socket;
    private String userName;
    private HashSet<String> usuarios = new HashSet();
    private final Reader reader = new Reader(this);
    private GUI gui;

    /** Nos permite acceder al nombre del host
     * 
     * @return Host al que nos hemos conectado.
     */
    public String getHost() {
        return host;
    }

    /** Nos permite acceder al nombre de Usuario que tenemos puesto
     * 
     * @return Nombre de usuario que tenemos puesto.
     */
    public String getUserName() {
        return userName;
    }
    
    /** Configura e inicia conexión TCP con el host indicado. Además inicializa buffers TCP
     *  de entrada y salida
     * @param h Host con el que conectar.
     * @return Si la conexión ha sido existosa.
     */
    public boolean setHost(String h) {
        host = h;
        try {
            socket = new Socket(host, PORT);
            outPrinter = new PrintWriter(socket.getOutputStream(), true);
            inReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            System.out.println("Conexión a " + host + ":" + Integer.toString(PORT) 
                    + " iniciada correctamente");
            
            // Probamos la conexión con el servidor
            String bienvenida = inReader.readLine();
            return "50 HELLO".equals(bienvenida);
        } catch (IOException io) {
            System.err.println(io);
            System.err.println("Error al conectar con el host");
            return false;
        }
    }
    
    /** Da acceso al socket del cliente.
     * 
     * @return Socket del cliente.
     */
    
    public Socket getSocket() {
        return socket;
    }


    
    /** Da acceso al conjunto de usuarios conectados.
     * 
     * @return Conjunto de usuarios conectados.
     */
    public HashSet<String> getUsuarios() {
        return usuarios;
    }
    
    /** Configura el nombre de usuario del cliente
     * 
     * @param name Nombre de usuario a utilizar.
     * @return Si el nombre de usuario ha podido ser utilizado.
     */
    public boolean setUserName(String name) {
        try {
            outPrinter.println("100 LOGIN " + name);
            String respuesta = inReader.readLine();
            if ("101 OK".equals(respuesta)) {
                userName = name;
                usuarios.add(name);
                System.out.println("Usando nombre: " + name);
                return true;
            }
            
        } catch (IOException io) {
            System.err.println(io);
            System.err.println("Error de conexión al intentar poner usuario");
        }
       return false;
    }
    
    
    /** Envia un mensaje de chat público al servidor
     * 
     * @param message Mensaje a enviar
     */
    synchronized void  sendMessage(String message) {
        try {
            String toSend = "300 SEND " + message;
            outPrinter.println(toSend);
            
            String response = inReader.readLine();
            if (!"301 SENT".equals(response))
                System.err.println("Error al enviar mensaje");
        } catch (IOException ex) {
            System.err.println(ex);
            System.err.println("Excepcion al enviar mensaje");
        }
    }
    
    /**
     * Pone ClienteTCP en modo activo. Habilita la hebra y asocia una interfaz
     * gráfica a la clase
     * @param gui Interfaz gráfica a asociar
     */
    public void startup(GUI gui) {
        this.gui = gui;
        reader.start();
    }
    
    /** Intenta actualizar los mensajes recibidos del servidor.
     * 
     * 
     */
    void receiveMessage() {
        try {
            outPrinter.println("200 UPDATE");
            ArrayList<String> toProcess = new ArrayList();
            String line = null;
            while (!"202 END".equals(line = inReader.readLine()) ) {
               toProcess.add(line);
            }
        
            for (String message : toProcess) {
                if ("202 END".equals(message)) break;
                if ("301 SENT".equals(message)) break;
           
                int pos = message.indexOf(' ');
                pos = message.indexOf(' ', pos+1);
                System.out.println(message);
                String accion = message.substring(0, pos);
                String data = message.substring(pos + 1);
                
                if ("201 PUT".equals(accion))
                    gui.addMessage(data + "\n");
                else if ("201 JOIN".equals(accion)) {
                    usuarios.add(data);
                    gui.updateList(usuarios);
                }
                else if ("201 LEFT".equals(accion)){ 
                    usuarios.remove(data);
                    gui.updateList(usuarios);
                }
                else {
                    System.err.println("Código inválido");
                }
            }
        }
        catch (IOException io) {
            System.err.println(io);
            System.err.println("Error con socket del cliente");
        }
    }
    
    /** Cierra la conexión con el servidor.
     *  @return Si la conexión ha sido cerrada correctamente.
     */
    public boolean close() {
        outPrinter.println("400 CLOSE");
        String message = "";
        try {
            message = inReader.readLine();
        } catch (IOException ex) {
            System.err.println(ex);
            System.err.println("Error al cerrar la conexión");
        }
        return "401 BYE".equals(message);
    }
    
    
}
