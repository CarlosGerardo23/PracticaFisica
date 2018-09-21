#pragma once
#include "Vector3.h"
#include <assert.h>
#include "SDL.h"
#include <iostream>
#include "Flotabilidad.h"
#include "Primitiva.h"

enum Image
{
	Circle,
	Square,
	Cube
};
class Particula
{
public:
	void Display(SDL_Renderer * renderer, Image image);
	void DisplayPoint(SDL_Renderer * renderer);
	void DisplayConsole();
	void SetMasa(float& pmasa);
	
	Vector3 GetForce() { return forceAcum; }
	Vector3 GetPosition() { return position; }
	Vector3 GetVelocity() { return velocity; }

	float GetMasa() { return masa; }
	float GetMasaInversa() { return masaInversa; }
	
	void Integrate(float time);
	void AddForce(Vector3 force);


	bool activeGravity=true;

	static void CheckTime(float time);
	Particula();
	Particula(Vector3 pos, float masa);
	Particula(Vector3 pos, float masa,Flotabilidad* liquido);
	~Particula();

private:

	Vector3 aceleration;
	Vector3 position;
	Vector3 velocity;
	Vector3 forceAcum;

	Flotabilidad* liquido=NULL;
	float volumeCube;
	float reductor = .5;
	float tempTime;
	float masa;
	float masaInversa;
	float volumenTotal=1;
	void ForceFlotabilidad();
	void Gravity();
	void SetMasaInversa();
	void UpdateVelocity(float time);
	void UpdatePosition(float time);
	void UpdateAceleration();
	void VelocityReductor();
	
	float magnitud = 20;

	Cuadrado* cuadrardo;
	Cubo* cubo;
	

};

