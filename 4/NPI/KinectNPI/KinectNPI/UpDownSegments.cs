using Microsoft.Kinect;
using System;

namespace NPIGrupo7Kinect
{

    // Detecta la mano en la parte superior
    public class UpSegment : IGestureSegment
    {
        
        public GesturePartResult Update(Body skeleton)
        {
            // La mano derecha está en lasso por encima de la cabeza
            if (skeleton.HandRightState == HandState.Lasso && skeleton.Joints[JointType.HandRight].Position.Y > skeleton.Joints[JointType.Head].Position.Y)
            {
                return GesturePartResult.Succeeded;
            }

            return GesturePartResult.Failed;
        }
    }

    // Detecta la mano en la parte inferior
    public class DownSegment : IGestureSegment
    {
        public GesturePartResult Update(Body skeleton)
        {
            // La mano está derecha en lasso y por debajo de la cabeza
            if (skeleton.HandRightState == HandState.Lasso && skeleton.Joints[JointType.HandRight].Position.Y < skeleton.Joints[JointType.Head].Position.Y)
            {
                return GesturePartResult.Succeeded;
            }

            return GesturePartResult.Failed;
        }
    }
}
