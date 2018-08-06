#include "Particula.h"



void Particula::SetMasa(float & pmasa)
{
	if (pmasa >= 0)
		masa = pmasa;
	else
		masa = 1;
}

void Particula::SetMasaInversa(float & pmasaInversa)
{
	if (pmasaInversa >= 0)
	{
		masaInversa = 1 / masa;
	}
}

Particula::Particula()
{
}


Particula::~Particula()
{
}
