using Microsoft.Kinect;
using System;

namespace NPIGrupo7Kinect
{
    /**
     * Gesto de subir de abajo a arriba.
     */
    public class UpGesture
    {
        readonly int WINDOW_SIZE = 50;
        DateTime instante_1;
        DateTime instante_2;
        int umbral_tiempo = 1500;

        IGestureSegment[] _segments;

        int _currentSegment = 0;
        int _frameCount = 0;

        public event EventHandler GestureRecognized;

        // Partimos de la mano en lasso por debajo de la cabeza hacia arriba.
        public UpGesture()
        {
            UpSegment upSegment = new UpSegment();
            DownSegment downSegment = new DownSegment();

            _segments = new IGestureSegment[]
            {
                downSegment,
                upSegment
            };
        }

        /**
         * Actualiza el estado del gesto actual. Se permite 1,5 segundos para completar el gesto.
         */
        public void Update(Body skeleton)
        {
            GesturePartResult result = _segments[_currentSegment].Update(skeleton);

            if (result == GesturePartResult.Succeeded)
            {
                if (_currentSegment == 0)
                {
                    instante_1 = DateTime.Now;
                }
                if (_currentSegment + 1 < _segments.Length)
                {
                    _currentSegment++;
                    _frameCount = 0;
                }
                else
                {
                    if (GestureRecognized != null)
                    {
                        GestureRecognized(this, new EventArgs());
                        Reset();
                    }
                }
            }
            else if (result == GesturePartResult.Failed || _frameCount == WINDOW_SIZE)
            {
                if (skeleton.HandRightState == HandState.Closed || skeleton.HandRightState == HandState.Open)
                {
                    Reset();
                }
                else if (_currentSegment == 1)
                {
                    instante_2 = DateTime.Now;
                    TimeSpan intervalo = instante_2.Subtract(instante_1);
                    if (intervalo.TotalMilliseconds > umbral_tiempo)
                    {
                        Reset();
                    }
                }
                else
                {
                    Reset();
                }

            }
            else
            {
                _frameCount++;
            }
        }

        /**
         * Reinicia el gsto actual
         */
        public void Reset()
        {
            _currentSegment = 0;
            _frameCount = 0;
        }
    }
}
