#pragma once
#include "Vector3.h"
class Matrix3
{
public:
	Matrix3();
	~Matrix3();
	Matrix3(const Vector3& vector1, const Vector3& vector2, const Vector3& vector3 );
	void Transpose();
	Matrix3& operator*(const Matrix3& rh);
	Vector3& operator*(const Vector3& rh);
	void Display();
private:
	Vector3 mt[3];
};

