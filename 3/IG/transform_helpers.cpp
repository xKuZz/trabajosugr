#include "transform_helpers.h"

void transform_rotate::setSpeed(double value)
{
    speed = value;
}

void transform_rotate::faster(double value) {
    speed *= value;
}

void transform_rotate::slower(double value) {
    speed /= value;
}

transform_rotate::transform_rotate(double value, double min, double max, double speedy)
{
    current = value;
    min_angle = min;
    max_angle = max;
    speed = speedy;
}

bool transform_rotate::increment()
{
  if ((current + speed) <= max_angle) {
      current += speed;
      return true;
  }
  else
      return false;
}

bool transform_rotate::decrement()
{
  if ((current - speed) >= min_angle) {
      current -= speed;
      return true;
  }
  else
      return false;
}

void transform_rotate::setBound(double min, double max)
{
    min_angle = min;
    max_angle = max;
}

double transform_rotate::getAngle()
{
   return current;
}



double _transform_scale::getX() const
{
    return x;
}

double _transform_scale::getY() const
{
    return y;
}

double _transform_scale::getZ() const
{
    return z;
}

void _transform_scale::applyScale()
{
    glScaled(x,y,z);
}
