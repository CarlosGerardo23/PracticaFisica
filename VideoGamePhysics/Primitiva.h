#pragma once
#include "Vector3.h"
#include "SDL.h"
#include "Quaternion​.h"
#include <vector>
#include <iostream>
class Primitiva
{

protected:
	std::vector<Vector3*> vertices;
	float longitud;
	Vector3 centro;
	Primitiva( Vector3&  centro, const float& longitud);
	virtual void DisplayConsole()=0;
	virtual void SetVertices()=0;
	~Primitiva();
public:
	Vector3 GetCentro() { return centro; }
	float GetLongitud() { return longitud; }
	void Draw(SDL_Renderer* renderer);
	void Draw(SDL_Renderer* renderer, Vector3& color);
	void UpdateCentro(Vector3& Ucentro);
	std::vector<Vector3*> GetVertices() { return vertices; }
	void Clear();
	void Rotate(Quaternion​& q );
	void RotateLocalAxis(Quaternion​& q);
private:
	std::vector<Vector3> tempVertices;
	std::vector<Vector3> oldOffset;
	void CopyVertices();
	int copy = 0;
};

class  Triangulo : public Primitiva
{

public:
	void SetVertices() override;
	void DisplayConsole()override;
	Triangulo(Vector3& center, float& Longitud);
};

class  Cuadrado : public Primitiva
{

	
public:
	void SetVertices() override;
	void DisplayConsole()override;
	Cuadrado(Vector3& center, float& Longitud);
};

class  Cubo : public Primitiva
{

	
public:
	void SetVertices() override;
	void DisplayConsole()override;
	Cubo(Vector3& center, float& Longitud);
};

class  Tetraedro : public Primitiva
{
private:
	
public:
	Tetraedro(Vector3& center, float& Longitud);
	void SetVertices() override;
	void DisplayConsole()override;
};

