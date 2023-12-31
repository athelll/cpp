#include "Point3d.h"
#include "Vector3d.h"			// here we include the full class defincation of the Vector class becuase
													// we are interacting with its members
#include <iostream>

void Point3d::print() const
{
	std::cout << "Vector(" << m_x << ", " << m_y << ", " << m_z << ")\n";
}

void Point3d::moveByVector(const Vector3d& v)
{
	m_x += v.m_x;				// we interacted with its members here (V.m_x)
	m_y += v.m_y;				// here too
	m_z += v.m_z;				// here too
}
