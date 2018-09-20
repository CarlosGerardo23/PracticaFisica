#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <math.h>
#include "Particula.h"
#include "Timer.h"
#include "Input.h"
#include "Primitiva.h"
#include "Resorte.h"
#include "Flotabilidad.h"

using namespace std;

const int WIDTH = 500, HEIGHT = 500;


int main(int argc, char *argv[])
{

	float force = 1000;
	Vector3 puntoFijo(WIDTH / 2, 0, 0);
	Vector3 posLiquido(WIDTH / 2, WIDTH/2, 0);


	Vector3 pesPosition3(puntoFijo.x(), puntoFijo.y() + 80, 0);
	Flotabilidad* liquido= new Flotabilidad(posLiquido, 200);
	Particula* particula3 = new Particula(puntoFijo, 5,liquido);
	particula3->activeGravity = true;

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
	
	//cubo.Rotate(teta);
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
			{
				break;
			}
			switch (windowEvent.type) {
				/* Look for a keypress */
			case SDL_KEYDOWN:
				/* Check the SDLKey values and move change the coords */
				switch (windowEvent.key.keysym.sym) {
				case SDLK_d:
				{
					particula3->DisplayConsole();
					
				}
					break;
				case SDLK_UP:
				{
					Vector3 temp(0, -force, 0);
					particula3->AddForce(temp);
					
				}
				break;
				case SDLK_DOWN:
				{
					Vector3 temp(0, force, 0);
					particula3->AddForce(temp);
				}
				break;
				case SDLK_RIGHT:
				{
					Vector3 temp(force, 0, 0);
					particula3->AddForce(temp);
				}
				break;
				case SDLK_LEFT:
				{
					Vector3 temp(-force, 0, 0);
					particula3->AddForce(temp);
				}
				break;

				default:
					break;
				}
			}
			Input::Update(windowEvent);
		}
		float g = 0.001;
	
		SDL_RenderPresent(renderer);
		
		Particula::CheckTime(Timer::GetDeltaTime());
		Timer::Update();
	
		particula3->Integrate(Timer::GetDeltaTime());

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
	
		
		//liquido.Draw(renderer);
		particula3->Display(renderer, Image::Cube);
		
		
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}