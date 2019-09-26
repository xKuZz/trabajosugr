package grupo7npi.npiinterfazoral;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.PopupMenu;
import android.widget.TextView;


public class MainActivity extends AppCompatActivity {
    private TextView resultTextView;
    private MyListener listener;
    private final int resultGet=0;
    private SensorManager mSensorManager;
    private Sensor mAccelerometer;
    private ShakeDetector mShakeDetector;


    /**
     * Método que se llama cuando se crea la actividad.
     * Solicitamos los permisos necesarios e inicializamos la interfaz para trabajar con Español
     * @param savedInstanceState Datos de la instancia de la actividad anterior
     *
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // Recogemos los datos de la interfaz y activamos el español
        resultTextView = (TextView) findViewById(R.id.texto);
        listener = new MyListener(getApplicationContext(), resultTextView, ai.api.AIConfiguration.SupportedLanguages.Spanish, this);
        resultTextView.setText("");
        updateView_SpanishLanguage();

        // Solicitamos permiso de Audio e Internet
        int permissionAudio = ContextCompat.checkSelfPermission(getApplicationContext(), Manifest.permission.RECORD_AUDIO);
        int permissionInternet = ContextCompat.checkSelfPermission(getApplicationContext(), Manifest.permission.INTERNET);

        if (permissionAudio == PackageManager.PERMISSION_DENIED || permissionInternet == PackageManager.PERMISSION_DENIED) {
            if (ActivityCompat.shouldShowRequestPermissionRationale(this,
                    Manifest.permission.RECORD_AUDIO) || ActivityCompat.shouldShowRequestPermissionRationale(this,
                    Manifest.permission.INTERNET)) {
                    resultTextView.setText("Se necesita permiso para utilizar el micrófono e Internet.");
            }
            else {
                ActivityCompat.requestPermissions(this,
                        new String[]{Manifest.permission.RECORD_AUDIO, Manifest.permission.INTERNET},
                        resultGet);
            }
        }

        // Inicialiamos el detector de agitado.
        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        mShakeDetector = new ShakeDetector();

        // Si se agita empezamos a escuchar.
        mShakeDetector.setOnShakeListener(new ShakeDetector.OnShakeListener() {
            @Override
            public void onShake(int count) {
				listener.startListening();
            }
        });
    }

    /**
     * Método para comprobar si se han obtenido los permisos.
     * Si no se obtienen los permisos deseados se cierra la aplicación.
     * @param requestCode Código de peteición.
     * @param permissions Permisos solicitados [Nombre]
     * @param grantResults Resultados de peticiones [Código]
     */
    @Override
    public void onRequestPermissionsResult(int requestCode, String permissions[], int[] grantResults) {
        switch (requestCode) {
            case resultGet: {
                // If request is cancelled, the result arrays are empty.
                if ((grantResults.length <= 0) || (grantResults[0] != PackageManager.PERMISSION_GRANTED)) {
                    System.out.print("La aplicación se cerrará");
                    int pid = android.os.Process.myPid();
                    android.os.Process.killProcess(pid);
                }
                return;
            }

        }
    }

    /**
     * Callback para el evento de hacer click en los elementos de la vista.
     * Actualizar el listener y el resto de elementos visuales acorde.
     * @param view Recurso de la vista que ha sido pulsado.
     */
    public void listenButtonOnClick(View view) {
        boolean captions;
        switch(view.getId()) {
            case R.id.hablar:
                listener.startListening();
                break;
            case R.id.spanishButton:
                listener = new MyListener(getApplicationContext(), resultTextView, ai.api.AIConfiguration.SupportedLanguages.Spanish, this,
                        listener.areCaptionsOn(), listener.getCaptionsLanguage());
                updateView_SpanishLanguage();
                break;
            case R.id.englishButton:
                listener = new MyListener(getApplicationContext(), resultTextView, ai.api.AIConfiguration.SupportedLanguages.English, this,
                        listener.areCaptionsOn(), listener.getCaptionsLanguage());
                updateView_EnglishLanguage();
                break;
            case R.id.subSpanish:
                captions = !listener.areCaptionsOn() || listener.getCaptionsLanguage() != ai.api.AIConfiguration.SupportedLanguages.Spanish;
                listener = new MyListener(getApplicationContext(), resultTextView, listener.getCurrentLanguage(), this,
                                          captions, ai.api.AIConfiguration.SupportedLanguages.Spanish);
                if (captions)
                    resultTextView.setText("Subtítulos activados");
                else
                    resultTextView.setText("");
                updateView_captions(captions, listener.getCaptionsLanguage());
                break;
            case R.id.subEnglish:
                captions = !listener.areCaptionsOn() || listener.getCaptionsLanguage() != ai.api.AIConfiguration.SupportedLanguages.English;
                listener = new MyListener(getApplicationContext(), resultTextView, listener.getCurrentLanguage(), this,
                        captions, ai.api.AIConfiguration.SupportedLanguages.English);
                if (captions)
                    resultTextView.setText("Captions On");
                else
                    resultTextView.setText("");
                updateView_captions(captions, listener.getCaptionsLanguage());
                break;
            case R.id.iconoPreguntas:
                PopupMenu pmenu = new PopupMenu(this,findViewById(R.id.iconoPreguntas));
                pmenu.setOnMenuItemClickListener(new PopupMenu.OnMenuItemClickListener() {
                    @Override
                    public boolean onMenuItemClick(MenuItem item) {
                        listener.sendTextRequest(item.getTitle().toString());
                        return true;
                    }
                });
                Menu menu = pmenu.getMenu();
                if (listener.getCurrentLanguage() == ai.api.AIConfiguration.SupportedLanguages.Spanish) {
                    menu.add("¿Quién eres?");
                    menu.add("¿De dónde eres?");
                    menu.add("¿Dónde estas?");
                    menu.add("¿En qué año estás?");
                    menu.add("¿Cuántas entradas tiene el monumento?");
                    menu.add("¿Qué hacían los chamanes?");
                    menu.add("¿Qué significado tiene el monumento?");
                    menu.add("¿Qué pinturas hay en las paredes?");
                    menu.add("¿Cómo colocasteis las piedras?");
                    menu.add("¿En qué lugar se construyó el monumento?");
                    menu.add("¿Para qué se creó el monumento?");
                    menu.add("¿Para qué se usaron las piedras?");

                }
                else {
                    menu.add("Who are you?");
                    menu.add("Where are you from?");
                    menu.add("Where are you?");
                    menu.add("In what year do you live?");
                    menu.add("How many entrances does the monument have?");
                    menu.add("What did the shamans do?");
                    menu.add("What is the meaining of the monument?");
                    menu.add("What paintings are on the walls?");
                    menu.add("How did you move rocks?");
                    menu.add("How was the place where it was built?");
                    menu.add("What did you build the monument for?");
                    menu.add("What did you use the rocks for?");
                }
                pmenu.show();
                break;
        }

    }

    /**
     * Setter del listener utilizado para el procesado oral.
     * @param listener MyListener necesario para el procesado oral de las respuestas.
     */
    public void setListener(MyListener listener) {
        this.listener = listener;
    }

    /**
     * Actualiza la vista cuando se activa el idioma español.
     */
    public void updateView_SpanishLanguage() {
        FloatingActionButton boton  = (FloatingActionButton) findViewById(R.id.spanishButton);
        boton.setEnabled(false);
        boton.setClickable(false);
        boton.getBackground().setColorFilter(Color.GRAY,PorterDuff.Mode.MULTIPLY);
        boton = (FloatingActionButton) findViewById(R.id.englishButton);
        boton.setEnabled(true);
        boton.setClickable(true);
        boton.getBackground().setColorFilter(null);
    }

    /**
     * Actualiza la vista cuando se activa el idioma inglés.
     */
    public void updateView_EnglishLanguage() {
        FloatingActionButton boton  = (FloatingActionButton) findViewById(R.id.englishButton);
        boton.setEnabled(false);
        boton.setClickable(false);
        boton.getBackground().setColorFilter(Color.GRAY,PorterDuff.Mode.MULTIPLY);
        boton = (FloatingActionButton) findViewById(R.id.spanishButton);
        boton.setEnabled(true);
        boton.setClickable(true);
        boton.getBackground().setColorFilter(null);
    }


    /**
     * Actualiza la vista de los botones de subtitulos cuando se cambia alguno de ellos.
     * @param captions Booleano que indica si están activados o desactivados los subtítulos
     * @param lang Lenguaje del que hemos activado los subtítulos
     */
    public void updateView_captions(boolean captions, ai.api.AIConfiguration.SupportedLanguages lang) {
        FloatingActionButton botonIngles = (FloatingActionButton) findViewById(R.id.subEnglish);
        FloatingActionButton botonSpanish = (FloatingActionButton) findViewById(R.id.subSpanish);

        // Desactivamos los colores de ambos
        botonIngles.getBackground().setColorFilter(null);
        botonSpanish.getBackground().setColorFilter(null);

        // Activamos el sombreado del que está marcado
        if (captions && lang == ai.api.AIConfiguration.SupportedLanguages.Spanish)
            botonSpanish.getBackground().setColorFilter(Color.GRAY, PorterDuff.Mode.MULTIPLY);
        else if (captions && lang == ai.api.AIConfiguration.SupportedLanguages.English)
            botonIngles.getBackground().setColorFilter(Color.GRAY, PorterDuff.Mode.MULTIPLY);
    }

    /**
     * Método que se llama cuando se vuelve a abrir la aplicación cuando se ha salido sin cerrarla.
     */
    @Override
    public void onResume() {
        super.onResume();
        mSensorManager.registerListener(mShakeDetector, mAccelerometer,	SensorManager.SENSOR_DELAY_UI);
    }

    /**
     * Método que se llama cuando se sale de la aplicación si cerrarla
     */
    @Override
    public void onPause() {
        mSensorManager.unregisterListener(mShakeDetector);
        super.onPause();
    }

}
