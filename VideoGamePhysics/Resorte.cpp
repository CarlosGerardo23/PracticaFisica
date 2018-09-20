#include "Resorte.h"




Resorte::Resorte( Vector3 puntoFijo,Vector3 equlibro, float k, float b, Particula* pesa):puntoFijo(puntoFijo), puntoEquilibrio(equlibro),k(k),b(b),pesa(pesa)
{
	A = pesa->GetPosition() - puntoEquilibrio;
	pesa->activeGravity = true;
}

Resorte::~Resorte()
{
}

void Resorte::SetForce(float time)
{
	UpdateA();
	if (time > 0)
	{
		/*if (A.Magnitud() < 0.1 && A.Magnitud() > -0.1)
		{

			A.SetVector(0, 0, 0);
		}*/
		Vector3 debug = A * -k;
		Vector3 debug2 = pesa->GetVelocity()*b;
		force = debug - debug2;
		pesa->AddForce(force);
		pesa->Integrate(time);
	}
	
}
																				   
void Resorte::UpdateA()															   
{																				   
																				   
		tempA = A;																   
		Vector3 debugPosition = pesa->GetPosition();							   
		A = pesa->GetPosition() - puntoEquilibrio;								   
																				   
	//std::cout << A.Magnitud() << std::endl;									   
}

void Resorte::AddForce(Vector3 force)
{
	pesa->AddForce(force);

	
}

bool Resorte::CheckAmplitud()
{
	if (tempA.Magnitud() > 1)
		return false;
	return true;

}

ResorteFijo::ResorteFijo(Vector3 puntofijo, Vector3 equlibro, float k, float b, Particula* pesa): Resorte(puntofijo,equlibro,k,b,pesa)
{
	float c= 10;
	float e = 5;
	fijo = new Cubo(puntoFijo, c);
	eq = new Cubo(puntoEquilibrio, e );
	fijo->SetVertices();
	eq->SetVertices();
}

void ResorteFijo::Draw(SDL_Renderer* render)
{
	fijo->Draw(render);
	eq->Draw(render);
	pesa->Display(render, Image::Circle);
	SDL_RenderDrawLine(render, fijo->GetCentro().x(), fijo->GetCentro().y(), pesa->GetPosition().x(), pesa->GetPosition().y());
}

ResorteAncla::ResorteAncla(Particula* ancla,  Vector3 equilibrio,float k, float b, Particula* pesa):Resorte(ancla->GetPosition(),equilibrio,k,b,pesa), ancla(ancla)
{
	float e = 5;

	pesa->activeGravity = true;
}

void ResorteAncla::Draw(SDL_Renderer* render)
{
	ancla->Display(render, Image::Circle);
	pesa->Display(render, Image::Circle);
	
	SDL_RenderDrawLine(render, ancla->GetPosition().x(), ancla->GetPosition().y(), pesa->GetPosition().x(), pesa->GetPosition().y());
}

void ResorteAncla::SetAnclaForce(float time)
{
	UpdateEquilibrio();
	SetForce(time);
}

void ResorteAncla::UpdateEquilibrio()
{
	puntoEquilibrio = ancla->GetPosition();
}
