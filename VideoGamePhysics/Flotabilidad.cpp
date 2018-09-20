#include "Flotabilidad.h"

Flotabilidad::Flotabilidad(Vector3 & centro, float Longitud)
{
	liquido = new Cubo(centro, Longitud);
	liquido->SetVertices();
	waterSurface = centro.y()-Longitud/2;
	firstVertexSumerged = NULL;
	lastVertexSumerged = NULL;
}

void Flotabilidad::Draw(SDL_Renderer* render)
{
	Vector3 color =  Vector3(63, 211,255);
	liquido->Draw(render,color);
}

float Flotabilidad::CalculateRelativeVolume()
{
	float relativeHeight;
	relativeHeight= firstVertexSumerged->y()- waterSurface;
	float relativeVolume;
	relativeVolume = (liquido->GetLongitud()/100)*(liquido->GetLongitud()/100);
	relativeVolume *= relativeHeight;

	if (relativeVolume >= TotalVolume)
		relativeVolume = TotalVolume;
	
	return relativeVolume;
}


bool Flotabilidad::IsSumerged(std::vector<Vector3*> verticesObjeto)
{
	for (auto& vertex : verticesObjeto)
	{
		if (vertex->y() > waterSurface)
		{
			if (firstVertexSumerged == NULL)
				firstVertexSumerged = vertex;
			else if (vertex->y() > firstVertexSumerged->y())
				firstVertexSumerged = vertex;
		}
		else
		{
			firstVertexSumerged=NULL;
		}
		if (vertex->y() < waterSurface)
		{
			if (lastVertexSumerged == NULL)
				lastVertexSumerged = vertex;
			else if (vertex->y() < lastVertexSumerged->y())
				lastVertexSumerged = vertex;
		}
	}

	if (firstVertexSumerged == NULL)
		return false;
	//std::cout << "Mi vertice es" << firstVertexSumerged->y() << " y mi punto de agua es" << waterSurface << std::endl;
	return true;
}
