#include "Matrix3.h"
#include <iostream>


Matrix3::Matrix3()
{

	Vector3 vec1(1, 0, 0);
	Vector3 vec2(0, 1, 0);
	Vector3 vec3(0, 0, 1);

	mt[0] = vec1;
	mt[1] = vec2;
	mt[2] = vec3;
}


Matrix3::~Matrix3()
{
}

Matrix3::Matrix3(const Vector3 & vector1, const Vector3 & vector2, const Vector3 & vector3)
{
	mt[0] = vector1;
	mt[1] = vector2;
	mt[2] = vector3;
}

void Matrix3::Transpose()
{
	Vector3 vec1(mt[0].x(),mt[1].x(),mt[2].x());
	Vector3 vec2(mt[0].y(),mt[1].y(),mt[2].y());
	Vector3 vec3(mt[0].z(),mt[1].z(),mt[2].z());

	mt[0] = vec1;
	mt[1] = vec2;
	mt[2] = vec3;


}

Matrix3 & Matrix3::operator*(const Matrix3 & rh)
{

	Matrix3 result;

	Vector3 vec1;
	Vector3 vec2;
	Vector3 vec3;

	Matrix3 tempTranspose;
	tempTranspose.mt[0] = mt[0];
	tempTranspose.mt[1] = mt[1];
	tempTranspose.mt[2] = mt[2];

	tempTranspose.Transpose();

	//I make a copy of my main matrix and turn it to his transpose matrix so I can use the dot product to simplify the multiplication

	vec1.SetVector(tempTranspose.mt[0].punto(rh.mt[0]), tempTranspose.mt[1].punto(rh.mt[0]),tempTranspose.mt[2].punto(rh.mt[0]));
	vec2.SetVector(tempTranspose.mt[0].punto(rh.mt[1]), tempTranspose.mt[1].punto(rh.mt[1]), tempTranspose.mt[2].punto(rh.mt[1]));
	vec3.SetVector(tempTranspose.mt[0].punto(rh.mt[2]), tempTranspose.mt[1].punto(rh.mt[2]), tempTranspose.mt[2].punto(rh.mt[2]));

	
	result.mt[0]=vec1;
	result.mt[1]=vec2;
	result.mt[2]=vec3;

	return result;
	

}

Vector3 & Matrix3::operator*(const Vector3 & rh)
{
	Vector3 result;

	Matrix3 tempTranspose;
	tempTranspose.mt[0] = mt[0];
	tempTranspose.mt[1] = mt[1];
	tempTranspose.mt[2] = mt[2];

	tempTranspose.Transpose();

	//Using the same principle I just make a copy of my main matrix and turn it to his transpose and use dot product with the vector
	result.SetVector(tempTranspose.mt[0].punto(rh), tempTranspose.mt[1].punto(rh), tempTranspose.mt[2].punto(rh));

	return result;
}

void Matrix3::Display()
{
	std::cout << "[" << mt[0].x()<<"," << mt[0].y()<<"," << mt[0].z() << "]"<<std::endl;
	std::cout << "[" << mt[1].x()<<"," << mt[1].y()<<"," << mt[1].z() << "]"<<std::endl;
	std::cout << "[" << mt[2].x()<<"," << mt[2].y()<<"," << mt[2].z() << "]"<< std::endl;
}
