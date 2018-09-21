#pragma once
#include "Vector3.h"
#include "Primitiva.h"
#include "SDL.h"
#include <iostream>
#include <vector>
class Flotabilidad
{
  public: 
	  float waterSurface;
	  Flotabilidad(Vector3& centro, float Longitud);
	  void Draw(SDL_Renderer* render);
	  float CalculateRelativeVolume(float objectLongitud,float volumeTotal);
	  bool IsSumerged(std::vector<Vector3*> verticesObjeto);
	  float TotalVolume;
  private:  
	  Cubo* liquido;
	  Vector3* firstVertexSumerged;
	  Vector3* lastVertexSumerged;
	
};

