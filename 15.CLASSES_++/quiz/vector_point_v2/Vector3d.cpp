#include "Vector3d.h"		// this is a no-brainer
#include <iostream>

void Vector3d::print() const
{
		std::cout << "Vector(" << m_x << ", " << m_y << ", " << m_z << ")\n";
}
