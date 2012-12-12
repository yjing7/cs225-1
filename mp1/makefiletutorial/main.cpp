#include <iostream>
#include "sphere.h"

using namespace std;

int main()
{
	sphere a(5.0);
	cout << "a's radius is " << a.getRadius() << endl;
	a.setRadius(6.0);
	cout << "a's radius is now " << a.getRadius() << endl;
}
