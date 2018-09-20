#include "Primitiva.h"
#include <vector>
#include <cmath>

#define PI 3.141592
Primitiva::Primitiva( Vector3 & centro, const float & longitud)
{
	this->centro = centro;
	this->longitud = longitud;
}

void Primitiva::Draw(SDL_Renderer * renderer)
{
	float porcentaje = (longitud * 99) / 100;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int i = 0; i<vertices.size(); i++)
	{
		for (int j = i+1; j < vertices.size(); j++)
		{
			Vector3 temp = *vertices[i] - *vertices[j];
			float a = temp.Magnitud();
			if(a>=porcentaje&&a<=longitud+2)
				SDL_RenderDrawLine(renderer, vertices[i]->x(), vertices[i]->y(), vertices[j]->x(), vertices[j]->y());
		}
	}
}

void Primitiva::Draw(SDL_Renderer * renderer,  Vector3 & color)
{
	float porcentaje = (longitud * 99) / 100;
	SDL_SetRenderDrawColor(renderer, color.x(), color.y(), color.z(), 255);
	for (int i = 0; i<vertices.size(); i++)
	{
		for (int j = i + 1; j < vertices.size(); j++)
		{
			Vector3 temp = *vertices[i] - *vertices[j];
			float a = temp.Magnitud();
			if (a >= porcentaje && a <= longitud + 2)
				SDL_RenderDrawLine(renderer, vertices[i]->x(), vertices[i]->y(), vertices[j]->x(), vertices[j]->y());
		}
	}
}

void Primitiva::UpdateCentro(Vector3 & Ucentro)
{
	centro = Ucentro;
}

void Primitiva::Clear()
{
	for (auto& v: vertices)
	{
		delete (v);
	}
	vertices.clear();
}

void Primitiva::Rotate(Quaternion​& q)
{
	float radians = (q.real*PI) / 180;
	float angle = std::sin(radians);
	Quaternion​ qf(std::cos(radians),q.ijk*std::sin(radians));
	Quaternion​ qC = qf;
	qC.Conjugate();
	for (Vector3* ver : vertices)
	{
		Quaternion​ v;
		v.real = 0;
		v.ijk = *ver;
		Quaternion​ vqC = v * qC;
		Quaternion​ result = qf * vqC;
		*ver = result.ijk;
	}
}

void Primitiva::RotateLocalAxis(Quaternion​& q)
{
	std::vector<Vector3> offset;
	Vector3 tempCenter = centro;
	centro = centro - centro;
	CopyVertices();
	if (copy == 0) {
	Clear();
	
	SetVertices();
	
	int count2 = 0;
	
		for (Vector3* ver : vertices)
		{
			Vector3 a = tempVertices[count2];
			Vector3 b = *ver;
			Vector3 c = a - b;
			offset.push_back(c);
			count2++;
		}
		copy++;
	}else
	{
		for (Vector3 vec : oldOffset)
		{
			offset.push_back(vec);
		}
		int countOfss = 0;
		for (Vector3* vec : vertices)
		{
			*vec = *vec - oldOffset[countOfss];
			countOfss++;
		}
		oldOffset.clear();
	}
	Rotate(q);
	tempVertices.clear();
	for (Vector3* vec : vertices)
	{
		tempVertices.push_back(*vec);
	}
	int count = 0;
	for (Vector3* ver : vertices)
	{
		*ver = *ver+ offset[count];
		count++;
	}
	centro = tempCenter;
	int count3 = 0;
	for (Vector3* vec : vertices)
	{
		Vector3 a = *vec;
		Vector3 b = tempVertices[count3];
		Vector3 c = a - b;
		oldOffset.push_back(c);
		count3++;
	}
	tempVertices.clear();
}

void Primitiva::CopyVertices()
{
	for (Vector3* ver : vertices)
	{
		tempVertices.push_back(*ver);
	}
}



Primitiva::~Primitiva()
{
}

void Triangulo::SetVertices()
{
	float altura = std::sin(60 * PI / 180)*longitud;
 	float radio = (2 * altura) / 3;
	float apotema = altura-radio;

	vertices.push_back (new Vector3(centro.x(), radio + centro.y(), 0));

	Vector3 prima(centro.x(), centro.y()-apotema, 0);
	vertices.push_back( new Vector3((longitud/2) + prima.x(), prima.y(), 0));


	vertices.push_back(new Vector3(prima.x()- (longitud / 2), prima.y(), 0));

	Vector3 temp3 = *vertices[0] - prima;
	Vector3 temp4 = centro - prima;
	
	
	std::cout << std::endl << "La altura del triuangulo es: " << altura << std::endl;
	std::cout << std::endl << "El radio del triuangulo es: " << radio << std::endl;
	std::cout << std::endl << "La apotema del triuangulo es: " << apotema << std::endl;
	std::cout << "La magnitud del primer punto al punto prima es " << temp3.Magnitud() << std::endl;
	std::cout << "Y el vector es" << std::endl;
	



	
}

void Triangulo::DisplayConsole()
{
	std::cout << std::endl;
	for (auto& v : vertices)
	{
		std::cout << "The vertices of the triangle are "<<std::endl;
		v->Display();
		
	}
	Vector3 temp;
	temp = *vertices[0] - *vertices[1];
	float a=temp.Magnitud();
	temp = *vertices[1] - *vertices[2];
	float b=temp.Magnitud();
	temp = *vertices[2] - *vertices[0];
	float c=temp.Magnitud();
	std::cout << "Th size A have a magnitud of: " << a << std::endl;
	std::cout << "Th size B have a magnitud of: " << b << std::endl;
	std::cout << "Th size C have a magnitud of: " << c << std::endl;

	temp = *vertices[0] - centro;
	float a1=temp.Magnitud();
	temp = *vertices[1] - centro;
	float b1 = temp.Magnitud();;
	temp = *vertices[2] - centro;
	float c1 = temp.Magnitud();;
	std::cout << "The magnitud of the point 1 to the center is: " << a1 << std::endl;
	std::cout << "The magnitud of the point 2 to the center is: " << b1 << std::endl;
	std::cout << "The magnitud of the point 3 to the center is: " << c1 << std::endl;

}

Triangulo::Triangulo(Vector3& center, float& Longitud): Primitiva(center,Longitud)
{

}

void Cuadrado::SetVertices()
{
	float tempX = (longitud / 2) + centro.x();
	float tempY = (longitud / 2) + centro.y();

	float mTempX = centro.x() - (longitud / 2);
	float mTempY = centro.y() - (longitud / 2) ;
	vertices.push_back( new Vector3(tempX, tempY,0));
	vertices.push_back( new Vector3(tempX, mTempY, 0));
	vertices.push_back( new Vector3(mTempX, mTempY, 0));
	vertices.push_back( new Vector3(mTempX, tempY, 0));
}

void Cuadrado::DisplayConsole()
{
	std::cout << std::endl;
	for (auto& v : vertices)
	{
		std::cout << "The vertices of the square are " << std::endl;
		v->Display();

	}
	Vector3 temp;
	temp = *vertices[0] - *vertices[1];
	float a = temp.Magnitud();
	temp = *vertices[1] - *vertices[2];
	float b = temp.Magnitud();
	temp = *vertices[2] - *vertices[3];
	float c = temp.Magnitud();
	temp = *vertices[3] - *vertices[0];
	float d = temp.Magnitud();
	std::cout << "Th size A have a magnitud of: " << a << std::endl;
	std::cout << "Th size B have a magnitud of: " << b << std::endl;
	std::cout << "Th size C have a magnitud of: " << c << std::endl;
	std::cout << "Th size d have a magnitud of: " << d << std::endl;

}

Cuadrado::Cuadrado(Vector3& center, float& Longitud): Primitiva(center,Longitud)
{
}

void Cubo::SetVertices()
{
	float tempX = (longitud / 2) + centro.x();
	float tempY = (longitud / 2) + centro.y();
	float tempZ = (longitud / 2) + centro.z();

	float mTempX = centro.x() - (longitud / 2) ;;
	float mTempY = centro.y() - (longitud / 2) ;;
	float mTempZ = centro.z() - (longitud / 2) ;;
	vertices.push_back(new Vector3(tempX,  tempY, tempZ));
	vertices.push_back(new Vector3(tempX, mTempY, tempZ));
	vertices.push_back(new Vector3(mTempX,mTempY, tempZ));
	vertices.push_back(new Vector3(mTempX, tempY, tempZ));
			
	vertices.push_back(new Vector3(tempX, tempY, mTempZ));
	vertices.push_back(new Vector3(tempX, mTempY, mTempZ));
	vertices.push_back(new Vector3(mTempX, mTempY, mTempZ));
	vertices.push_back(new Vector3(mTempX, tempY, mTempZ));

}

void Cubo::DisplayConsole()
{
	std::cout << std::endl;
	for (auto& v : vertices)
	{
		std::cout << "The vertices of the cube are " << std::endl;
		v->Display();

	}
	Vector3 temp;
	temp = *vertices[0] - *vertices[4];
	float a = temp.Magnitud();
	temp = *vertices[1] - *vertices[5];
	float b = temp.Magnitud();
	temp = *vertices[2] - *vertices[6];
	float c = temp.Magnitud();
	temp = *vertices[3] - *vertices[7];
	float d = temp.Magnitud();
	std::cout << "Th size A have a magnitud of: " << a << std::endl;
	std::cout << "Th size B have a magnitud of: " << b << std::endl;
	std::cout << "Th size C have a magnitud of: " << c << std::endl;
	std::cout << "Th size d have a magnitud of: " << d << std::endl;
}

Cubo::Cubo(Vector3 & center, float & Longitud):Primitiva(center,Longitud)
{
}

Tetraedro::Tetraedro(Vector3 & center, float & Longitud): Primitiva(center, Longitud)
{
}

void Tetraedro::SetVertices()
{
	float altura = std::sin(60 * PI / 180)*longitud;
	float radio = (2 * altura) / 3;
	float apotema = altura - radio;
	float alturaY= (longitud*sqrt(6)) / 3;
	float apotemaY = (longitud*sqrt(6)) / 12;

	/*Vector3 temp(centro.x(),centro.y()-apotemaY,centro.z());

	std::cout << "La magnitud de p1: " << temp.Magnitud();*/

	vertices.push_back(new Vector3(centro.x(), centro.y()-apotemaY, radio+centro.z()));

	Vector3 prima(centro.x(), centro.y()-apotemaY , centro.z()-apotema);
	vertices.push_back(new Vector3((longitud / 2) + prima.x(), centro.y()-apotemaY, prima.z()));


	vertices.push_back(new Vector3(prima.x() - (longitud / 2), centro.y()-apotemaY, prima.z()));

	float finalY = sqrt((longitud*longitud)-(radio*radio));
	vertices.push_back(new Vector3(centro.x(), prima.y()+alturaY, centro.z()));

}

void Tetraedro::DisplayConsole()
{
	std::cout << std::endl;
	for (auto& v : vertices)
	{
		std::cout << "The vertices of the triangle are " << std::endl;
		v->Display();

	}
	Vector3 temp;
	temp = *vertices[0] - *vertices[1];
	float a = temp.Magnitud();
	temp = *vertices[1] - *vertices[2];
	float b = temp.Magnitud();
	temp = *vertices[2] - *vertices[0];
	float c = temp.Magnitud();

	temp = *vertices[3] - *vertices[0];
	float d = temp.Magnitud();
	temp = *vertices[3] - *vertices[1];
	float e = temp.Magnitud();
	temp = *vertices[3] - *vertices[2];
	float f = temp.Magnitud();
	std::cout << "The size A have a magnitud of: " << a << std::endl;
	std::cout << "The size B have a magnitud of: " << b << std::endl;
	std::cout << "The size C have a magnitud of: " << c << std::endl;
	std::cout << "The size D have a magnitud of: " << d << std::endl;
	std::cout << "The size E have a magnitud of: " << e << std::endl;
	std::cout << "The size F have a magnitud of: " << f << std::endl;

	temp = *vertices[0] - centro;
	float a1 = temp.Magnitud();
	temp = *vertices[1] - centro;
	float b1 = temp.Magnitud();;
	temp = *vertices[2] - centro;
	float c1 = temp.Magnitud();;
	std::cout << "The magnitud of the point 1 to the center is: " << a1 << std::endl;
	std::cout << "The magnitud of the point 2 to the center is: " << b1 << std::endl;
	std::cout << "The magnitud of the point 3 to the center is: " << c1 << std::endl;
}
