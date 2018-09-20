#pragma once
#include "Vector3.h"
class Quaternion​
{
public:
	Vector3 ijk;
	float real;
	Quaternion​& operator + (const Quaternion​ RH);
	Quaternion​& operator += (const Quaternion​ RH);
	Quaternion​& operator - (const Quaternion​ RH);
	Quaternion​& operator -= (const Quaternion​ RH);
	Quaternion​& operator* (const Quaternion​ RH);
	Quaternion​& operator*=(const Quaternion​ RH);
	Quaternion​& operator* (const Vector3 RH);
	Quaternion​& operator*=(const Vector3 RH);
	Quaternion​& operator * (const float RH);
	Quaternion​& operator *= (const float RH);
	void Conjugate();
	float Magnitud();
	static Quaternion​& Normalize(Quaternion​& quaternion);
	static Quaternion​& Identity();
	
	

	Quaternion​();

	Quaternion​(float escalar, Vector3 ijk);
	
	~Quaternion​();
};
