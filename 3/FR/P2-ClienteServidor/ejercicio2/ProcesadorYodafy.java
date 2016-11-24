// YodafyServidorIterativo
// (CC) jjramos, 2012
//
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Random;


//
// Nota: si esta clase extendiera la clase Thread, y el procesamiento lo hiciera el método "run()",
// ¡Podríamos realizar un procesado concurrente! 
//
public class ProcesadorYodafy {
	// Referencia a un socket para enviar/recibir las peticiones/respuestas
	private Socket socketServicio;
	
	// Para que la respuesta sea siempre diferente, usamos un generador de números aleatorios.
	private Random random;
	
	// Constructor que tiene como parámetro una referencia al socket abierto en por otra clase
	public ProcesadorYodafy(Socket socketServicio) {
		this.socketServicio=socketServicio;
		random=new Random();
	}
	
	
	// Aquí es donde se realiza el procesamiento realmente:
	void procesa(){
		
                
		// Ahor trabajamos con String
		String datosRecibidos;
		
		
		try {
                        
			// Obtiene los flujos de escritura/lectura
                        
                        // Generamos
                        PrintWriter outPrinter= new PrintWriter(socketServicio.getOutputStream(),true);
                        BufferedReader inReader= new BufferedReader(new InputStreamReader(socketServicio.getInputStream()));
			
			// Lee la frase a Yodaficar:
			////////////////////////////////////////////////////////
                        datosRecibidos=inReader.readLine();
			////////////////////////////////////////////////////////
			
			// Yoda hace su magia:
                        // Esta vez no tenemos que pasar los datos recibidos a String porque ya lo hemos recibido de esa forma.
			// Yoda reinterpreta el mensaje:
			String respuesta=yodaDo(datosRecibidos);
			
                        // Enviamos directamente la respuesta sin pasar a bytes
			// Enviamos la traducción de Yoda:
			////////////////////////////////////////////////////////
			outPrinter.println(respuesta);
			////////////////////////////////////////////////////////
			
			
			
		} catch (IOException e) {
			System.err.println("Error al obtener los flujso de entrada/salida.");
		}

	}

	// Yoda interpreta una frase y la devuelve en su "dialecto":
	private String yodaDo(String peticion) {
		// Desordenamos las palabras:
		String[] s = peticion.split(" ");
		String resultado="";
		
		for(int i=0;i<s.length;i++){
			int j=random.nextInt(s.length);
			int k=random.nextInt(s.length);
			String tmp=s[j];
			
			s[j]=s[k];
			s[k]=tmp;
		}
		
		resultado=s[0];
		for(int i=1;i<s.length;i++){
		  resultado+=" "+s[i];
		}
		
		return resultado;
	}
}
