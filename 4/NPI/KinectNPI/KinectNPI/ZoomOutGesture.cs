using Microsoft.Kinect;
using System;

namespace NPIGrupo7Kinect
{
    // Gesto de reducir zoom
    public class ZoomOutGesture
    {
        readonly int WINDOW_SIZE = 50;
        DateTime instante_1;
        DateTime instante_2;
        int umbral_tiempo = 1500;

        IGestureSegment[] _segments;

        int _currentSegment = 0;
        int _frameCount = 0;

        public event EventHandler GestureRecognized;
        // Gesto de desplazar ambas manos de alejadas a juntas
        public ZoomOutGesture()
        {
            FarHandsSegment farHandsSegment = new FarHandsSegment();
            NearHandsSegment nearHandsSegment = new NearHandsSegment();

            _segments = new IGestureSegment[]
            {
                farHandsSegment,
                nearHandsSegment
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
                if (skeleton.HandRightState == HandState.Closed)
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
         * Reinicia el gesto actual
         */
        public void Reset()
        {
            _currentSegment = 0;
            _frameCount = 0;
        }
    }
}
