using Microsoft.Kinect;
using System;

namespace NPIGrupo7Kinect
{

    /**
     * Segmento que detecta la mano abierta
     */
    public class OpenHandSegment : IGestureSegment
    {
        /**
         *
         */
        public GesturePartResult Update(Body skeleton)
        {
            // La mano ha de estar abierta y por encima del hombro derecho, y la mano izquierda no ha de estar abierta
            if (skeleton.HandRightState == HandState.Open && skeleton.Joints[JointType.HandRight].Position.Y > skeleton.Joints[JointType.ElbowRight].Position.Y
                && skeleton.HandLeftState != HandState.Open)
            {
                return GesturePartResult.Succeeded;
            }
            
            return GesturePartResult.Failed;
        }
    }

    /**
     * Segmento que detecta la mano cerrada
     */
    public class ClosedHandSegment : IGestureSegment
    {
    
        public GesturePartResult Update(Body skeleton)
        {
            // La mano derecha ha de estar cerrada por encima del hombro derecho y el cuello
            // mientras que la mano izquierda no está abierta
            if (skeleton.HandRightState == HandState.Closed && skeleton.Joints[JointType.HandRight].Position.Y > skeleton.Joints[JointType.ElbowRight].Position.Y
                && skeleton.HandLeftState != HandState.Open && skeleton.Joints[JointType.HandRight].Position.Y > skeleton.Joints[JointType.Neck].Position.Y)
            {
                return GesturePartResult.Succeeded;
            }

            return GesturePartResult.Failed;
        }
    }

    /**
     * Segmento que detecta la mano izquierda abierta
     */
    public class LeftOpenHandSegment : IGestureSegment
    {
        public GesturePartResult Update(Body skeleton)
        {
            // La mano izquierda ha de estar abierta y por encima del hombro y cuello izquierdo
            // mientras que la mano derecha no está abierta
            if (skeleton.HandLeftState == HandState.Open && skeleton.Joints[JointType.HandLeft].Position.Y > skeleton.Joints[JointType.ElbowLeft].Position.Y
                && skeleton.HandRightState != HandState.Open && skeleton.Joints[JointType.HandLeft].Position.Y > skeleton.Joints[JointType.Neck].Position.Y)
            {
                return GesturePartResult.Succeeded;
            }

            return GesturePartResult.Failed;
        }
    }

    /**
     * Segmento que detecta la mano izquierda cerrada
     */
    public class LeftClosedHandSegment : IGestureSegment
    {
        
        public GesturePartResult Update(Body skeleton)
        {
            // La mano izquierda ha de estar cerrrada por encima del hombro izquierdo
            // y la mano derecha no puede estar abierta.
            if (skeleton.HandLeftState == HandState.Closed && skeleton.Joints[JointType.HandLeft].Position.Y > skeleton.Joints[JointType.ElbowLeft].Position.Y
                && skeleton.HandRightState != HandState.Open)
            {
                return GesturePartResult.Succeeded;
            }

            return GesturePartResult.Failed;
        }
    }
}
