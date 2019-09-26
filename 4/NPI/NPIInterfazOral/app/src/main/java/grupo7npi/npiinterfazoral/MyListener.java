package grupo7npi.npiinterfazoral;

import android.content.Context;
import android.os.AsyncTask;
import android.widget.TextView;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;


import java.util.HashMap;
import java.util.Map;

import ai.api.AIDataService;
import ai.api.AIListener;
import ai.api.AIServiceException;
import ai.api.android.AIConfiguration;
import ai.api.android.AIService;
import ai.api.model.AIError;
import ai.api.model.AIRequest;
import ai.api.model.AIResponse;
import ai.api.model.Result;


/**
 * La clase MyListener implementa la interfaz de Acceso a DialogFlow (api.ai) para la interacción oral
 */

public class MyListener implements AIListener {
    private TextView resultTextView; // Referencia al campo de texto de la actividad principal
    private MainActivity mainActivity; // Referencia a la actividad principal
    private final AIService aiService;

    // Api de DialogFlow
    private final String ACCESS_TOKEN="f4670fddb46b4e1ea6094cc272e748df";
    private final String DEVELOPER_TOKEN="c39f569c9b364399876faaf5946972c7";
    private final String URL = "https://api.dialogflow.com/v1/intents/";
    private final AIConfiguration config;

    private AIConfiguration.SupportedLanguages currentLanguage; // Lenguaje actual (hablar)
    private boolean captionsOn; // Indica si los subtítulos están activos

    private AIConfiguration.SupportedLanguages captionsLanguage; // Lenguaje actual (subtítulos)

    /**
     * Constructor de la clase de acceso a la interfaz oral de DialogFlow.
     * @param context Contexto de la actividad principal.
     * @param text Referencia al TextView donde mostar el texto.
     * @param language Lenguaje seleccionado para el habla.
     * @param m Referencia a la actividad principal.
     * @param captions Flag que indica si deseamos activar los subtítulos. Por defecto, false.
     * @param captionsLanguage Lenguaje para los subtítulos. Por defecto, language.
     */
    public MyListener(Context context, TextView text, AIConfiguration.SupportedLanguages language, MainActivity m,
                      boolean captions,
                      AIConfiguration.SupportedLanguages captionsLanguage) {
        this.resultTextView = text;
        currentLanguage = language;
        config = new AIConfiguration(ACCESS_TOKEN, currentLanguage, AIConfiguration.RecognitionEngine.System);
        aiService = AIService.getService(context,config);
        aiService.setListener(this);
        this.captionsOn = captions;
        this.captionsLanguage = captionsLanguage;
        TTS.init(context,currentLanguage, text);
        mainActivity = m;
    }

    /**
     * Constructor de la clase de acceso a la interfaz oral de DialogFlow.
     * @param context Contexto de la actividad principal.
     * @param text Referencia al TextView donde mostar el texto.
     * @param language Lenguaje seleccionado para el habla.
     * @param m Referencia a la actividad principal.
     */
    public MyListener(Context context, TextView text, AIConfiguration.SupportedLanguages language, MainActivity m) {
        this.resultTextView = text;
        currentLanguage = language;
        config = new AIConfiguration(ACCESS_TOKEN, currentLanguage, AIConfiguration.RecognitionEngine.System);
        aiService = AIService.getService(context,config);
        aiService.setListener(this);
        this.captionsOn = false;
        this.captionsLanguage = currentLanguage;
        TTS.init(context,currentLanguage, text);
        mainActivity = m;
    }

    /**
     * Manda una petición en modo texto, el resultado se procesa igual que si fuese una petición oral.
     * @param text Texto con la petición a mandar.
     */
    public void sendTextRequest(String text) {
            final AIConfiguration config = new AIConfiguration(ACCESS_TOKEN,
                    currentLanguage,
                    AIConfiguration.RecognitionEngine.System);

            final AIDataService aiDataService = new AIDataService(config);
            final AIRequest aiRequest = new AIRequest();
            aiRequest.setQuery(text);
            new AsyncTask<AIRequest, Void, AIResponse>() {
                @Override
                protected AIResponse doInBackground(AIRequest... requests) {
                    final AIRequest request = requests[0];
                    try {
                        final AIResponse response = aiDataService.request(aiRequest);
                        return response;
                    } catch (AIServiceException e) {
                    }
                    return null;
                }
                @Override
                protected void onPostExecute(AIResponse aiResponse) {
                    if (aiResponse != null) {
                        onResult(aiResponse);
                    }
                }
            }.execute(aiRequest);
    }


    /**
     * Procesa la respuesta que se ha recibido a una petición.
     * @param response Respuesta recibida desde el servidor.
     */
    public void onResult(final AIResponse response) {
        Result result = response.getResult();
        String action = result.getAction();

        // Diferenciamos las acciones que nos permite interactuar con opciones de la vista
        // de las respuestas que da el personaje al conocimiento adquirido.
        switch (action) {
            case "action.subtitulos_on":
                captionsOn = true;
                captionsLanguage = currentLanguage;
                if (captionsLanguage == ai.api.AIConfiguration.SupportedLanguages.Spanish)
                    resultTextView.setText("Subtítulos activados");
                else
                    resultTextView.setText("Captions On");
                break;
            case "action.subtitulos_off":
                captionsOn = false;
                resultTextView.setText("");
                break;
            case "action.subtitulos_esp":
                captionsOn=true;
                captionsLanguage= ai.api.AIConfiguration.SupportedLanguages.Spanish;
                resultTextView.setText("Subtítulos activados");
                mainActivity.updateView_captions(captionsOn, captionsLanguage);
                break;
            case "action.subtitulos_ing":
                captionsOn=true;
                captionsLanguage = ai.api.AIConfiguration.SupportedLanguages.English;
                resultTextView.setText("Captions On");
                mainActivity.updateView_captions(captionsOn, captionsLanguage);

                break;
            case "action.lenguaje_esp":
                mainActivity.setListener(new MyListener(mainActivity.getApplicationContext(), resultTextView,
                        ai.api.AIConfiguration.SupportedLanguages.Spanish, mainActivity, captionsOn, captionsLanguage));
                mainActivity.updateView_SpanishLanguage();
                break;
            case "action.lenguaje_ing":
                mainActivity.setListener(new MyListener(mainActivity.getApplicationContext(), resultTextView,
                        ai.api.AIConfiguration.SupportedLanguages.English, mainActivity, captionsOn, captionsLanguage));
                mainActivity.updateView_EnglishLanguage();
                break;
            default:
                // Obtenemos la respuesta
                final String speech = result.getFulfillment().getSpeech();

                // Si hay subtítulos
                if (captionsOn)
                    if (captionsLanguage == currentLanguage) // Si ambos lenguajes coinciden mostramos el texto
                        resultTextView.setText(speech);
                    else {
                        // En caso contrario obtenemos mediante HTTPS el JSON correspondiente a nuestro
                        // Intent (DialogFlow) y lo procesamos
                        final String language = (captionsLanguage == ai.api.AIConfiguration.SupportedLanguages.Spanish) ? "es" : "en";
                        final String intentID = result.getMetadata().getIntentId();
                        final String apiVersion = "?v=20150910";
                        final String lang = "&lang="+language;

                        RequestQueue queue = Volley.newRequestQueue(mainActivity);
                        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, URL + intentID
                                +apiVersion+lang, null,
                                new Response.Listener<JSONObject>() {
                                    /**
                                     * Callback si recibimos una respuesta JSON válida.
                                     * @param response Respuesta JSON a procesar.
                                     */
                                    @Override
                                    public void onResponse(JSONObject response)  {
                                        try {
                                            JSONArray respuestas = response.getJSONArray("responses");
                                            JSONObject r = respuestas.getJSONObject(0);
                                            JSONArray mensajes = r.getJSONArray("messages");
                                            JSONObject m = mensajes.getJSONObject(0);
                                            resultTextView.setText(m.getString("speech"));
                                        } catch(JSONException j) {
                                            resultTextView.setText(response.toString());
                                        }

                                    }
                                }, new Response.ErrorListener() {

                            /**
                             * Callback si se recibe una respuesta JSON no válida.
                             * @param error Tipo de error detectada.
                             */
                            @Override
                            public void onErrorResponse(VolleyError error) {
                                if (language == "es")
                                    resultTextView.setText("Error al procesar subtítulos en español.");
                                else
                                    resultTextView.setText("An error has ocurred while processing captions.");
                            }
                        }) {
                            /**
                             * Nos permite redefinir las cabeceras utilizadas para realizar la conexión JSON,
                             * y, por tanto, poder identificarnos con el token de desarrollador con DialogFlow.
                             * @return Cabeceras utilizadas.
                             * @throws AuthFailureError Si hay algún error de autenticación.
                             */
                            @Override
                            public Map<String, String> getHeaders() throws AuthFailureError {
                                Map<String, String> headers = new HashMap<>();
                                headers.put("Authorization", "Bearer " + DEVELOPER_TOKEN);
                                headers.put("Content-Type", "application/json");
                                return headers;
                            }
                        } ;
                        queue.add(request);
                    }

                // Aplicamos Text To Speech
                TTS.speak(speech);
        }

    }

    /**
     * Si se produce un error al procesar el mensaje.
     * @param error Error producido.
     */
    @Override
    public void onError(final AIError error) {
        resultTextView.setText(error.toString());
    }

    /**
     * Hace que el sistema empieze una escucha activa para detectar un mensaje.
     */
    public void startListening() {
        aiService.startListening();
    }

    /**
     * Este método se llama cuando se empieza a escuchar a un mensaje.
     */
    @Override
    public void onListeningStarted() {}

    /**
     * Ese método se llama cuando se cancela la escucha de mensajes.
     */
    @Override
    public void onListeningCanceled() {}

    /**
     * Este método se llama cuando se finaliza la escucha de un mensaje
     */
    @Override
    public void onListeningFinished() {}

    /**
     * Este método se llama cuando se cambia el volumen.
     * @param level Volumen actual.
     */
    @Override
    public void onAudioLevel(final float level) {}

    /**
     * Este método nos devuelve el lenguaje que esta siendo utilizado en el momento.
     * @return Lenguaje utilizado.
     */
    public AIConfiguration.SupportedLanguages getCurrentLanguage() {
        return currentLanguage;
    }

    /**
     * Indica si los subtítulos están activados
     * @return true si los subtítulos están activados, false en caso contrario.
     */
    public boolean areCaptionsOn() {
        return captionsOn;
    }

    /**
     * Devuelve el idioma de los subtítulos.
     * @return Idioma de los subtítulos.
     */
    public AIConfiguration.SupportedLanguages getCaptionsLanguage() {
        return captionsLanguage;
    }


}
