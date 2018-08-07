#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <math.h>
#include "Timer.h"
#include "Input.h"
#include "Vector3.h"
#include "Matrix3.h"

using namespace std;

const int WIDTH = 500, HEIGHT = 256;


int main(int argc, char *argv[])
{
	Vector3 a(2, 3, 5);
	Vector3 b(0, 0, 1);
	Vector3 c(1, 0, 1); 

	Vector3 m1(1, 1, 1);
	Vector3 m2(0, 2, 1);
	Vector3 m3(1, 1, 0);

	Vector3 p(6, 9, 1);

	Matrix3 am(a, b, c);

	p = am * a;
	Matrix3 bm(m1, m2, m3);

	Matrix3 cm = am * bm;
	//am.Display();
	//std::cout << std::endl;
	//bm.Display();
	//std::cout << std::endl;
	p.Display();
	std::cout << std::endl;
	cm.Display();
	std::cout << std::endl;
	std::cout << b.Magnitud();
	std::cout << std::endl;
	am.Display();
	std::cout << std::endl;
	am.Transpose();
	std::cout << std::endl;
	am.Display();
	float* scale=new float;

	Vector3 testBase(3, 1, 0);
	Vector3 testPreyection(1,5,0);
	Vector3* result= new Vector3();
	Vector3::Projection(scale, result, testPreyection, testBase);
	std::cout <<*scale<< std::endl;
	result->Display();
	//std::cout << std::endl;
	//std::cout << *scale<<std::endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
	}

	SDL_Window *window = SDL_CreateWindow("Physics Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

	if (window == NULL)
	{
		cout << "Could not create window: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	SDL_Event windowEvent;
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	cout << renderer << endl;
	float position = 0;
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
			{
				break;
			}

			Input::Update(windowEvent);
		}

		Timer::Update();

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	


		position += Timer::GetDeltaTime();
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		SDL_RenderDrawPoint(renderer, position, 50 - 20 * sin(position));
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}