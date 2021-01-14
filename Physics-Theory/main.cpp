#include <iostream>
#include <Windows.h>
#include "SDL2-2.0.12/include/SDL.h"
#include "main.h"

class Player
{
public:
	SDL_Rect playerRect;
	float velocityX;

	Player(int x_, int y_, int w_, int h_)
	{
		playerRect =
		{
			x_,y_,w_,h_
		};
		velocityX = 0;
	}
	~Player();
};

int main(int argc, char** argv)
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event events;

	//bools
	bool close;
	//	bool shoot;
	//	bool enemieShoot;
	//	bool enemieAlive;
		//bool rightTrue;
		//bool leftTrue;
		//int counter;
	//	int counter2;
		//int counterRight;
		//int counterLeft;
		//int deadCounter;
		//int enemyShooting;
		//int playerLives;
		//int deadEnemies;

		//Player object
	Player* player = new Player(610, 690, 80, 20);

	//Boxes object
	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

	SDL_CreateWindowAndRenderer(1280, 720, 0, &window, &renderer);

	//Initialize the window bool
	close = false;

	while (close == false)
	{
		Uint32 startTime = SDL_GetTicks();
		//INPUT
		while (SDL_PollEvent(&events))
		{
			if (events.type == SDL_QUIT)
				close = true;
		}
		//Get the keyboard
		const Uint8* keysArray = SDL_GetKeyboardState(NULL);
		if (keysArray[SDL_SCANCODE_ESCAPE])
			close = true;

		//PLAYER MOVEMENT

		if (keysArray[SDL_SCANCODE_LEFT] && player->playerRect.x > 0)
			player->velocityX -= 0.5f;
		if (keysArray[SDL_SCANCODE_RIGHT] && player->playerRect.x < 1200)
			player->velocityX += 0.5f;

		//PLAYER SPEED
		player->playerRect.x = player->velocityX;

		//ENEMIES DO GO DOWN
		//DRAW
			//BACKGROUND
		SDL_SetRenderDrawColor(renderer, 0, 47, 187, 255);
		SDL_RenderClear(renderer);
		//PLAYER
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &player->playerRect);

		SDL_Rect aim =
		{
			player->playerRect.x + 40, 690, 5, 10
		};

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &aim);

		//GOODBOXES
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		//LIVES
		//BULLETS
		//ENEMIE BULLET
		//ENEMIES
		SDL_RenderPresent(renderer);
		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 100 / 60) SDL_Delay(100 / 60 - frameTime);
		return 0;
	}
}