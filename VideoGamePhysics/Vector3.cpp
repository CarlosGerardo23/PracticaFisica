#include "Vector3.h"
#include <math.h>
#include <iostream>

Vector3::Vector3(float x, float y, float z)
{
	 m[0]=x;
	 m[1]=y;
	 m[2]=z;
}

Vector3::Vector3()
{
	m[0] = 0;
	m[1] = 0;
	m[2] = 0;
}

void Vector3::SetVector(float x, float y, float z)
{
	m[0] = x;
	m[1] = y;
	m[2] = z;
}

Vector3 & Vector3::operator+(const Vector3 & rh)
{
	Vector3 result;
	result.m[0] = m[0] + rh.m[0];
	result.m[1] = m[1] + rh.m[1];
	result.m[2] = m[2] + rh.m[2];

	return result;

}
//
Vector3 & Vector3::operator += (const Vector3 & rh)
{
	Vector3 result;
	result.m[0] = m[0] + rh.m[0];
	result.m[1] = m[1] + rh.m[1];
	result.m[2] = m[2] + rh.m[2];

	return result;

}

Vector3 & Vector3::operator-=(const Vector3 & rh)
{
	Vector3 result;
	result.m[0] = m[0] - rh.m[0];
	result.m[1] = m[1] - rh.m[1];
	result.m[2] = m[2] - rh.m[2];

	return result;

}
//
Vector3 & Vector3::operator-(const Vector3 & rh)
{
	Vector3 result;
	result.m[0] = m[0] - rh.m[0];
	result.m[1] = m[1] - rh.m[1];
	result.m[2] = m[2] - rh.m[2];

	return result;

}
//
Vector3 & Vector3::operator*(const Vector3 & rh)
{
	Vector3 result;
	result.m[0] = (m[1] * rh.m[2]) - (m[2] * rh.m[1]);
	result.m[1] = -((m[0] * rh.m[2]) - (m[2] * rh.m[0]));
	result.m[2] = (m[0] * rh.m[1]) - (m[1] * rh.m[0]);
	return result;

}
//
Vector3 & Vector3::operator*=(const Vector3 & rh)
{
	Vector3 result;
	result.m[0] = (m[1] * rh.m[2]) - (m[2] * rh.m[1]);
	result.m[1] = -((m[0] * rh.m[2]) - (m[2] * rh.m[0]));
	result.m[2] = (m[0] * rh.m[1]) - (m[1] * rh.m[0]);
	return result;

}

Vector3 & Vector3::operator*(const float & rh)
{
	Vector3 result(m[0]*rh,m[1]*rh,m[2]*rh);
	return result;
	
}

Vector3 & Vector3::operator*=(const float & rh)
{
	Vector3 result(m[0] * rh, m[1] * rh, m[2] * rh);
	return result;
}

void Vector3::Projection(float * scalarProjection, Vector3 * vectorialProjection, const Vector3 & vectorProjected, const Vector3 & vectorBase)
{
	Vector3 tempProjected = vectorProjected;
	Vector3 tempBase = vectorBase;
	float scalar = tempBase.punto(tempProjected);
	float magnitud = (tempBase.Magnitud())*(tempBase.Magnitud());
	scalar=scalar/magnitud;
	tempProjected = tempBase * scalar;
	if (vectorialProjection)
		*vectorialProjection = tempBase * scalar;
	else
		vectorialProjection = NULL;
	if (scalarProjection)
		*scalarProjection = tempProjected.Magnitud();
	else
		scalarProjection = NULL;
}

float Vector3::Magnitud()
{
	float square = (m[0] * m[0]) + (m[1] * m[1]) + (m[2] * m[2]);
	float magnitud = sqrt(square);
	return magnitud;
}
Vector3 & Vector3::Normalize()
{
	Vector3 result;
	float magnitud = this->Magnitud();
	result.m[0] =  this->m[0] / magnitud;
	result.m[1] =  this->m[1] / magnitud;
	result.m[2] =  this->m[2] / magnitud;

	return result;

}
//
float & Vector3::punto(const Vector3 & rh)
{
	float final = (m[0] * rh.m[0]) + (m[1] * rh.m[1]) + (m[2] * rh.m[2]);
	return final;
}

void Vector3::Display()
{
	std::cout << "[" << m[0] << "]" << std::endl;
	std::cout << "[" << m[1] << "]" << std::endl;
	std::cout << "[" << m[2] << "]" << std::endl;
}

void Vector3::Rotate()
{
}
