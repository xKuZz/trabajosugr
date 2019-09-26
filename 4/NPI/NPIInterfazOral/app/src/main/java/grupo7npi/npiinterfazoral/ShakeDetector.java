package grupo7npi.npiinterfazoral;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

/**
 * Clase que implementa el detector de agitado.
 */
public class  ShakeDetector implements SensorEventListener {

    // Parámetros para determinar la fuerza y el tiempo para que se considere un agitado
    private static final float SHAKE_THRESHOLD_GRAVITY = 2.7F; // Umbral de fuerza para determinar agitado
    private static final int SHAKE_SLOP_TIME_MS = 500; // Mínimo intervalo de tiempo para detectar dos agitados
    private static final int SHAKE_COUNT_RESET_TIME_MS = 3000; // Máximo tiempo para contar el número de agitados

    private OnShakeListener mListener;
    private long mShakeTimestamp;
    private int mShakeCount;

    /**
     * Setter para el listener a usar. El listener tendrá un método que se activará cuando
     * se detecte un agitado y recibirá el número de agitados detectados.
     * @param listener Listener a asignar.
     */
    public void setOnShakeListener(OnShakeListener listener) {
        this.mListener = listener;
    }

    public interface OnShakeListener {
        public void onShake(int count);
    }

    /**
     * Método que se activa cuando cambia la precisión [NO USADO]
     * @param sensor Sensor en cuestión.
     * @param accuracy Precisión.
     */
    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }

    /**
     * Método que se activa cuando se produce un cambio en el sensor.
     * Se encarga de llamar al evento del listener si se detecta un agitado.
     * @param event Evento del sensor.
     */
    @Override
    public void onSensorChanged(SensorEvent event) {

        if (mListener != null) {
            float x = event.values[0];
            float y = event.values[1];
            float z = event.values[2];

            float gX = x / SensorManager.GRAVITY_EARTH;
            float gY = y / SensorManager.GRAVITY_EARTH;
            float gZ = z / SensorManager.GRAVITY_EARTH;

            // Calculamos la fuerza
            float gForce = (float) Math.sqrt(gX * gX + gY * gY + gZ * gZ);

            // Si es superior al umbral comprobamos el tiempo
            if (gForce > SHAKE_THRESHOLD_GRAVITY) {
                final long now = System.currentTimeMillis();
                // No tenemos en cuenta dos agitaciones muy seguidas para evitar errores.
                if (mShakeTimestamp + SHAKE_SLOP_TIME_MS > now) {
                    return;
                }

                // Reseteamos si nos pasamos del umbral máximo de tiempo de detección.
                if (mShakeTimestamp + SHAKE_COUNT_RESET_TIME_MS < now) {
                    mShakeCount = 0;
                }

                mShakeTimestamp = now;
                mShakeCount++;

                mListener.onShake(mShakeCount);
            }
        }
    }
}