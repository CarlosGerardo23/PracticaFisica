#pragma once
#include "Vector3.h"
#include "Particula.h"
#include "Primitiva.h"
class Resorte
{
public:
	Resorte(Vector3 puntoFijo,Vector3 equlibro, float k, float b,Particula* pesa);
	~Resorte();
	void SetForce(float time);
	void UpdateA();
	void AddForce(Vector3 force);
	float GetA() { return A.Magnitud(); }
	virtual void Draw(SDL_Renderer* render) = 0;

protected:
	
	Vector3 puntoEquilibrio;
	Vector3 puntoFijo;
	float k;
	float b;
	Vector3 A;
	Vector3 force;
	Particula* pesa;
	bool CheckAmplitud();

private:
	Vector3 tempA;

	
};

class ResorteFijo : public Resorte
{
public:
	ResorteFijo(Vector3 puntoFijo,Vector3 equlibro, float k, float b, Particula* pesa);
	void Draw(SDL_Renderer* render) override;
private :
	Cubo* fijo;
	Cubo* eq;
};

class ResorteAncla : public Resorte
{
public:
	ResorteAncla(Particula* ancla,Vector3 equilibrio, float k, float b, Particula* pesa);
	Particula* ancla;
	void Draw(SDL_Renderer* render) override;
	void SetAnclaForce(float time);
private:
	Cubo * eq;
	void UpdateEquilibrio();

	
};

