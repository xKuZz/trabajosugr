package grupo7npi.npiinterfazoral;

import android.content.Context;
import android.os.Build;
import android.speech.tts.TextToSpeech;
import android.widget.TextView;
import java.util.Locale;
import ai.api.android.AIConfiguration;

/**
 * Clase que implementa el Text To Speech para reproducir mensajes de texto.
 */
public class TTS {

    private static TextToSpeech textToSpeech;

    /**
     * Inicializa el TextToSpeech
     * @param context Contexto de la actividad.
     * @param language Lenguajde deseado para realizar el TextToSpeech
     * @param output TextView en el que colocar los resultados
     */
    public static void init(final Context context, AIConfiguration.SupportedLanguages language, TextView output) {
        // Si la instancia es nula se genera un TextToSpeech nuevo.
        if (textToSpeech == null) {
            textToSpeech = new TextToSpeech(context, new TextToSpeech.OnInitListener() {
                @Override
                public void onInit(int i) {
                }
            });
        }

        // Comprobamos si el TTS del lenguaje en cuestión está disponible y lo indicamos por pantalla.
        if (language == ai.api.AIConfiguration.SupportedLanguages.Spanish) {
            Locale spanish = new Locale("spa", "ESP");
            if (textToSpeech.isLanguageAvailable(spanish) != TextToSpeech.LANG_NOT_SUPPORTED) {
                textToSpeech.setLanguage(spanish);
                output.setText("Español seleccionado como lenguaje");
            } else {
                output.setText("Idioma español no disponible para reproducir. Instálelo, por favor.");
            }
        }
        else if (language == ai.api.AIConfiguration.SupportedLanguages.English)  {
                if (textToSpeech.isLanguageAvailable(Locale.ENGLISH) != TextToSpeech.LANG_NOT_SUPPORTED) {
                    textToSpeech.setLanguage(Locale.ENGLISH);
                    output.setText("English selected as language");
                } else {
                    output.setText("English TTS not available. Please, install it");
                }
        }
        else {
            output.setText("Error al escoger el idioma para TTS.");
        }

    }

    /**
     * Método que se encarga de realizar el TTS del texto pasado como parámetro.
     * @param text Texto que se desea reproducir.
     */
    public static void speak(final String text) {
        if (Build.VERSION.SDK_INT >= 21)
            textToSpeech.speak(text, TextToSpeech.QUEUE_FLUSH, null, text);
        else
            textToSpeech.speak(text, TextToSpeech.QUEUE_FLUSH, null);
    }
}
