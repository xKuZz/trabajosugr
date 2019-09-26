using Microsoft.Kinect;
using System;

namespace NPIGrupo7Kinect
{
    // Detecta las manos abiertas y alejadas en posición de hacer zoom 
    public class FarHandsSegment : IGestureSegment
    {
        public GesturePartResult Update(Body skeleton)
        {
            // Ambas manos están abiertas y hacia dentro de sus respectivos codos y por encima de ellos
            if (skeleton.HandRightState==HandState.Open && skeleton.HandLeftState==HandState.Open &&
                skeleton.Joints[JointType.HandRight].Position.Y > skeleton.Joints[JointType.ElbowRight].Position.Y &&
                skeleton.Joints[JointType.HandLeft].Position.Y > skeleton.Joints[JointType.ElbowLeft].Position.Y &&
                skeleton.Joints[JointType.HandRight].Position.X > skeleton.Joints[JointType.ElbowRight].Position.X &&
                skeleton.Joints[JointType.HandLeft].Position.X < skeleton.Joints[JointType.ElbowLeft].Position.X)
            {
                return GesturePartResult.Succeeded;
            }

            return GesturePartResult.Failed;
        }
    }
    // Detecta las manos abiertas y cercanas en posición de hacer zoom 
    public class NearHandsSegment : IGestureSegment
    {
        
        public GesturePartResult Update(Body skeleton)
        {
            // Ambas manos están abiertas y hacia fuera de sus respectivos codos y por encima de ellos
            if (skeleton.HandRightState == HandState.Open && skeleton.HandLeftState == HandState.Open &&
                skeleton.Joints[JointType.HandRight].Position.Y > skeleton.Joints[JointType.ElbowRight].Position.Y &&
                skeleton.Joints[JointType.HandLeft].Position.Y > skeleton.Joints[JointType.ElbowLeft].Position.Y &&
                skeleton.Joints[JointType.HandRight].Position.X < skeleton.Joints[JointType.ElbowRight].Position.X &&
                skeleton.Joints[JointType.HandLeft].Position.X > skeleton.Joints[JointType.ElbowLeft].Position.X)
            {
                return GesturePartResult.Succeeded;
            }

            return GesturePartResult.Failed;
        }
    }
}
