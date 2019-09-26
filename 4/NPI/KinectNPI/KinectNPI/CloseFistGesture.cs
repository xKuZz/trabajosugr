using Microsoft.Kinect;
using System;

namespace NPIGrupo7Kinect
{
    /**
     * Detección del gesto de cerrar el puño
     */
    public class CloseFistGesture
    {
        readonly int WINDOW_SIZE = 50;
        DateTime instante_1;
        DateTime instante_2;
        int umbral_tiempo = 1500;

        IGestureSegment[] _segments;

        int _currentSegment = 0;
        int _frameCount = 0;

        public event EventHandler GestureRecognized;

        /**
         * El gesto se basa en detectar que se ha abierto la mano y que después se ha cerrado
         */
        public CloseFistGesture()
        {
            OpenHandSegment openHandSegment = new OpenHandSegment();
            ClosedHandSegment closedHandSegment = new ClosedHandSegment();

            _segments = new IGestureSegment[]
            {
                openHandSegment,
                closedHandSegment
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
                if (_currentSegment == 1)
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
         * Reinicia el gesto actual
         */
        public void Reset()
        {
            _currentSegment = 0;
            _frameCount = 0;
        }
    }

    /** 
     * Esto gesto detecta cerrar el puño de la mano izquierda
     */
    public class LeftCloseFistGesture
    {
        readonly int WINDOW_SIZE = 50;
        DateTime instante_1;
        DateTime instante_2;
        int umbral_tiempo = 1500;

        IGestureSegment[] _segments;

        int _currentSegment = 0;
        int _frameCount = 0;

        public event EventHandler GestureRecognized;
        /**
         * El gesto se basa en detectar que se ha abierto la mano y que después se ha cerrado
         */
        public LeftCloseFistGesture()
        {
            LeftOpenHandSegment openHandSegment = new LeftOpenHandSegment();
            LeftClosedHandSegment closedHandSegment = new LeftClosedHandSegment();

            _segments = new IGestureSegment[]
            {
                openHandSegment,
                closedHandSegment
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
                if (_currentSegment == 1)
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
         * Reinicia los contadores del gesto
         */
        public void Reset()
        {
            _currentSegment = 0;
            _frameCount = 0;
        }
    }
}
