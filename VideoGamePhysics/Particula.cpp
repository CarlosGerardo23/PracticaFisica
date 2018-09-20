#include "Particula.h"

#define PI 3.141592

void Particula::Display(SDL_Renderer * renderer, Image image)
{
	switch (image)
	{
	case Image::Square:
		cuadrardo = new Cuadrado(position, magnitud);
		cuadrardo->SetVertices();
		cuadrardo->Draw(renderer);
		cuadrardo->Clear();
		cuadrardo->UpdateCentro(position);
		break;
	case Image::Circle:
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		
		for (int angulo = 0; angulo < 360; ++angulo)
		{

			int x = 10 * std::cos((angulo*(PI / 180.0)));
			int y = 10 * std::sin((angulo*PI / 180.0));
			SDL_RenderDrawPoint(renderer, x+position.x(), y+position.y());
			//putPixel(x + WIDTH / 2, y + HEIGHT / 2, a);
		}
		break;
	case Image::Cube:
		cubo = new Cubo(position, magnitud);
		cubo->SetVertices();
		cubo->Draw(renderer);
		cubo->Clear();
		cubo->UpdateCentro(position);
	default:
		break;
	}
	if (liquido != NULL)
		liquido->Draw(renderer);
	
}

void Particula::DisplayPoint(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawPoint(renderer, position.x(),position.y());
}

void Particula::DisplayConsole()
{
	std::cout << "La posicion es:" << std::endl;
	position.Display();
	std::cout << std::endl;

	std::cout << "La velocidad es:" << std::endl;
	velocity.Display();
	std::cout << std::endl;

	std::cout << "La aceleracion es:" << std::endl;
	aceleration.Display();
	std::cout << std::endl;

	std::cout << "La fuerza es:" << std::endl;
	forceAcum.Display();
	std::cout << std::endl;
}

void Particula::SetMasa(float & pmasa)
{
	if (pmasa >= 0)
		masa = pmasa;
	else
		masa = 1;
	SetMasaInversa();
}




void Particula::Gravity()
{
	
	/*Vector3 temp(0, 9.81, 0);
	float forceY = forceAcum.y();
	
	if (aceleration.y() > temp.y()&&forceY==0)
	{
		float airResistance = -2;
		float y = aceleration.y()-airResistance;
		if (y <= 9.81)
			y = 9.81;
		temp.SetVector(0, airResistance, 0);
		aceleration = aceleration + temp;
	}
	else
	{
		aceleration = aceleration + temp;
	}*/
	if (activeGravity)
	{
		Vector3 gravityForce(0, 9.81*masa, 0);
		if (aceleration.y()<9.81)
			AddForce(gravityForce);
	}
}


void Particula::SetMasaInversa()
{
		masaInversa = 1 / masa;
}

void Particula::Integrate(float time)
{
	if (time == 0)
		tempTime = time;
	else if (masaInversa >= 0)
	{
		
		Gravity();
		if (liquido != NULL)
		{
			cubo->SetVertices();
			if (liquido->IsSumerged(cubo->GetVertices()))
			{
				ForceFlotabilidad();
				//std::cout << "Toque el agua" << std::endl;
			}
			cubo->Clear();
		}
			
		UpdateAceleration();
		UpdateVelocity(time);
		
		UpdatePosition(time);
		forceAcum.SetVector(0,0,0);
		aceleration.SetVector(0, 0, 0);
	}
	
}

void Particula::ForceFlotabilidad()
{
	float b = 0.9;
	Vector3 amortiguador(0, b, 0);
	amortiguador = amortiguador * velocity;
	float liquidDensity = 1000;
	float gravity = 9.81;
	float relativeVolume = liquido->CalculateRelativeVolume();
	float Eforce = relativeVolume;
	Eforce = Eforce * liquidDensity*gravity;
	
	Vector3 finalForce(0, -Eforce, 0);
	finalForce = finalForce - amortiguador;
	
	AddForce(finalForce);
}
void Particula::AddForce(Vector3 force)
{
	
	forceAcum = forceAcum+force;
}

void Particula::CheckTime(float time)
{
	bool test = time < 0;

	assert(!test);
}

Particula::~Particula()
{
}

void Particula::UpdateVelocity(float time)
{
	Vector3 tempVel = velocity;
	Vector3 tempAcel = aceleration;
	tempAcel = tempAcel * time;
	Vector3 temp = tempVel + tempAcel;
	velocity.SetVector(temp.x() , temp.y() , 0);
}

void Particula::UpdatePosition(float time)
{
	Vector3 temp = position;
	position.SetVector(temp.x()+(time*velocity.x()), temp.y() + (time*velocity.y()),0);
}

void Particula::UpdateAceleration()
{
	Vector3 temp= forceAcum * masaInversa;

	aceleration = aceleration + temp;
}

void Particula::VelocityReductor()
{
	velocity *= reductor;
}

Particula::Particula()
{
	float m = 1;
	SetMasa(m);

}

Particula::Particula(Vector3 pos, float masa) : position(pos), masa(masa)
{
	SetMasaInversa();
}

Particula::Particula(Vector3 pos, float masa, Flotabilidad * liquido) : position(pos), masa(masa), liquido(liquido)
{
	SetMasaInversa();
	cubo = new Cubo(position, magnitud);
	cubo->SetVertices();
	this->liquido->TotalVolume = (magnitud/100) * (magnitud/100)*(magnitud/100);
}

