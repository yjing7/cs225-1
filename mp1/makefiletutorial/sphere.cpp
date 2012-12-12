#include "sphere.h"

sphere::sphere(double radius)
	: myRadius(radius)
{ }

void sphere::setRadius(double radius)
{
	myRadius = radius;
}

double sphere::getRadius()
{
	return myRadius;
}
