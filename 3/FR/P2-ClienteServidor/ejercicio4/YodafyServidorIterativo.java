import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//

public class YodafyServidorIterativo {


	public static void main(String[] args) throws UnknownHostException, SocketException {
                    // Abrimos el socket en modo pasivo, escuchando el en puerto indicado por "port"
                    int port=8989;
                    String host="localhost";
                    InetAddress direccion = InetAddress.getByName(host);
                    DatagramSocket socketServidor = new DatagramSocket(port, direccion);
			
			// Mientras ... siempre!
			do {	
				// Creamos un objeto de la clase ProcesadorYodafy, pasándole como 
				// argumento el nuevo socket, para que realice el procesamiento
				// Este esquema permite que se puedan usar hebras más fácilmente.
				ProcesadorYodafy procesador=new ProcesadorYodafy(socketServidor);
				procesador.procesa();
				
			} while (true);
		

	}

}
