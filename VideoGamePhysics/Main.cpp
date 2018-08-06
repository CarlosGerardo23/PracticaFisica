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
	Vector3 a(5, 2, 1);
	Vector3 b(0, 2, 9);
	Vector3 c(3,9,6); 

	Vector3 p(6, 9, 1);

	Matrix3 am(a, b, c);

	p = am * a;
	Matrix3 bm(c, a, b);

	Matrix3 cm = bm * am;
	am.Display();
	std::cout << std::endl;
	bm.Display();
	std::cout << std::endl;
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

	Vector3 testBase(5, 4, 4);
	Vector3 testPreyection(-9,-2,0);
	Vector3* result= new Vector3();
	Vector3::Projection(NULL, result, testPreyection, testBase);
	std::cout << std::endl;
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