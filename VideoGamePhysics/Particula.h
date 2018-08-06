#pragma once
#include "Vector3.h"
class Particula
{
public:
	Vector3 aceleration;
	Vector3 position;
	Vector3 velocity;
	float reductor;
	void SetMasa(float& pmasa);
	void SetMasaInversa(float& pmasaInversa);
	float GetMasa() { return masa; }
	float GetMasaInversa() { return masaInversa; }


	Particula();
	~Particula();
	private:
	float masa;
	float masaInversa;

};

