#pragma once
class Vector3
{
public:
	Vector3(float x, float y, float z);
	Vector3();

	float x() { return m[0]; }
	float y() { return m[1]; }
	float z() { return m[2]; }
	void SetVector(float x, float y, float z);
	Vector3& operator +(const Vector3& rh);
	Vector3& operator +=(const Vector3& rh);
	Vector3& operator -=(const Vector3& rh);
	Vector3& operator -(const Vector3& rh);
	Vector3& operator *(const Vector3& rh);
	Vector3& operator *=(const Vector3& rh);
	Vector3& operator *(const float& rh);
	Vector3& operator *=(const float& rh);
	static void Projection(float* scalarProjection, Vector3* vectorialProjection, const Vector3& vectorProjected,const Vector3& vectorBase);
	float Magnitud();
	static Vector3& Normalize(Vector3& vector);
	float& punto(const Vector3& rh);
	void Display();
private: 
	float m[3];
};

