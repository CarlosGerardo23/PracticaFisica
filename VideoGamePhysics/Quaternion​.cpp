#include "Quaternion​.h"
#include <math.h>



Quaternion​ & Quaternion​::operator+(const Quaternion​ RH)
{
	Quaternion​ result;
	result.real = this->real + RH.real;
	result.ijk = this->ijk + RH.ijk;
	return result;
}

Quaternion​ & Quaternion​::operator+=(const Quaternion​ RH)
{
	Quaternion​ result;
	result.real = this->real + RH.real;
	result.ijk = this->ijk + RH.ijk;
	return result;
}

Quaternion​ & Quaternion​::operator-(const Quaternion​ RH)
{
	Quaternion​ result;
	result.real = this->real - RH.real;
	result.ijk = this->ijk - RH.ijk;
	return result;
}

Quaternion​ & Quaternion​::operator-=(const Quaternion​ RH)
{
	Quaternion​ result;
	result.real = this->real - RH.real;
	result.ijk = this->ijk - RH.ijk;
	return result;
}

Quaternion​ & Quaternion​::operator*(const Quaternion​ RH)
{
	Quaternion​ result;
	result.real = (this->real*RH.real)-(this->ijk.punto(RH.ijk));
	Vector3 final;
	
	Vector3 x= RH.ijk;
	x = x * this->real;
	Vector3 y=this->ijk*RH.real;
	Vector3 z=this->ijk*RH.ijk;
	final = x + y;
	final = final + z;
	result.ijk = final;
	return result;
}

Quaternion​ & Quaternion​::operator*=(const Quaternion​ RH)
{
	Quaternion​ result;
	result.real = (this->real*RH.real) - (this->ijk.punto(RH.ijk));
	Vector3 final = RH.ijk;
	final =final* this->real;
	final =final+ this->ijk*RH.real;
	final =final+ this->ijk*RH.ijk;
	result.ijk = final;
	return result;
}

Quaternion​ & Quaternion​::operator*(const Vector3 RH)
{
	Quaternion​ result;
	Quaternion​ quaternion2(0,RH);
	result.real = (this->real*quaternion2.real) - (this->ijk.punto(quaternion2.ijk));
	Vector3 final = quaternion2.ijk;
	final =final* this->real;
	final =final+ this->ijk*quaternion2.real;
	final =final+ this->ijk*quaternion2.ijk;
	result.ijk = final;
	return result;
}

Quaternion​ & Quaternion​::operator*=(const Vector3 RH)
{
	Quaternion​ result;
	Quaternion​ quaternion2(0, RH);
	result.real = (this->real*quaternion2.real) - (this->ijk.punto(quaternion2.ijk));
	Vector3 final = quaternion2.ijk;
	final =final* this->real;
	final =final+ this->ijk*quaternion2.real;
	final =final+ this->ijk*quaternion2.ijk;
	result.ijk = final;
	return result;
}

Quaternion​ & Quaternion​::operator*(const float RH)
{
	Quaternion​ result;
	result.ijk= this->ijk * RH;
	result.real = this->real*RH;
	return result;
}

Quaternion​ & Quaternion​::operator*=(const float RH)
{
	Quaternion​ result;
	result.ijk = this->ijk * RH;
	result.real = this->real*RH;
	return result;
}

void Quaternion​::Conjugate()
{
	this->ijk = this->ijk* -1;
}

float Quaternion​::Magnitud()
{
	float result;
	float real=this->real*this->real;
	float square = (this->ijk.x() *this->ijk.x()) + (this->ijk.y() *this->ijk.y()) + (this->ijk.z() *this->ijk.z());
	result = sqrt(real+square);
	
	return result;

}

Quaternion​ & Quaternion​::Normalize(Quaternion​ & quaternion)
{
	Quaternion​ result;
	float inverseMangnitud = 1 / quaternion.Magnitud();
	result = quaternion * inverseMangnitud;
	return result;

}

Quaternion​ & Quaternion​::Identity()
{
	Quaternion​ result(1,Vector3(0,0,0));

	return result;
	
}

Quaternion​::Quaternion​()
{
	real = 0;
	Vector3 vec(1,1,1);
	ijk = vec;
}

Quaternion​::Quaternion​(float escalar, Vector3 ijk): real(escalar),ijk(ijk)
{

}


Quaternion​::~Quaternion​()
{
}
