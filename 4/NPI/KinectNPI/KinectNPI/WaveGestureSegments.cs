using Microsoft.Kinect;
using System;

namespace NPIGrupo7Kinect
{
  
    public interface IGestureSegment
    {
        /**
         * Método que se llama para actualizar un fragmento de un gesto.
         * @param skeleton Frame del cuerpo actual.
         * @return Si el fragmento del gesto ha sido existoso o no.
         */
        GesturePartResult Update(Body skeleton);
    }

    // Detecta la mano a la izquierda
    public class WaveSegment1 : IGestureSegment
    {
        public GesturePartResult Update(Body skeleton)
        {
            // Mano derecha abierta por encima del codo derecho
            if (skeleton.HandRightState==HandState.Open &&
                skeleton.Joints[JointType.HandRight].Position.Y > skeleton.Joints[JointType.ElbowRight].Position.Y &&
                skeleton.HandLeftState != HandState.Open)
            {
                // Mano derecha a la izquierda del codo derecho
                if (skeleton.Joints[JointType.HandRight].Position.X > skeleton.Joints[JointType.ElbowRight].Position.X)
                {
                    return GesturePartResult.Succeeded;
                }
            }

            return GesturePartResult.Failed;
        }
    }
    
    // Detecta la mano a la derecha
    public class WaveSegment2 : IGestureSegment
    {
        
        public GesturePartResult Update(Body skeleton)
        {
            // Mano derecha abierta por encima del codo y sin la mano izquierda abierta
            if (skeleton.HandRightState == HandState.Open &&
                skeleton.Joints[JointType.HandRight].Position.Y > skeleton.Joints[JointType.ElbowRight].Position.Y &&
                skeleton.HandLeftState != HandState.Open)
            {
                // Mano a la derecha del codo
                if (skeleton.Joints[JointType.HandRight].Position.X < skeleton.Joints[JointType.SpineShoulder].Position.X)
                {
                    return GesturePartResult.Succeeded;
                }
            }
            
            return GesturePartResult.Failed;
        }
    }

    // Mano izquierda a la izquierda
    public class LeftWaveSegment1 : IGestureSegment
    {
        
        public GesturePartResult Update(Body skeleton)
        {
            // Mano izquierda abierta por encima del codo izquierdo
            if (skeleton.HandLeftState == HandState.Open &&
                skeleton.Joints[JointType.HandLeft].Position.Y > skeleton.Joints[JointType.ElbowLeft].Position.Y &&
                skeleton.HandRightState != HandState.Open)
            {
                // Mano a la izquierda del codo izquierdo
                if (skeleton.Joints[JointType.HandLeft].Position.X < skeleton.Joints[JointType.ElbowLeft].Position.X)
                {
                    return GesturePartResult.Succeeded;
                }
            }

            // Hand dropped
            return GesturePartResult.Failed;
        }
    }

    // Mano izquierda a la derecha
    public class LeftWaveSegment2 : IGestureSegment
    {
        
        public GesturePartResult Update(Body skeleton)
        {
            // Mano izquierda abierta por encima del codo izquiero
            if (skeleton.HandLeftState == HandState.Open &&
                skeleton.Joints[JointType.HandLeft].Position.Y > skeleton.Joints[JointType.ElbowLeft].Position.Y &&
                skeleton.HandRightState != HandState.Open)
            {
                // Mano izquierda a la derecha del codo izquierdo
                if (skeleton.Joints[JointType.HandLeft].Position.X > skeleton.Joints[JointType.ElbowLeft].Position.X)
                {
                    return GesturePartResult.Succeeded;
                }
            }

            return GesturePartResult.Failed;
        }
    }
}
