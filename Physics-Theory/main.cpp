#include <iostream>
#include <Windows.h>
#include "SDL2-2.0.12/include/SDL.h"
#include "main.h"
#define GRAVITY 10

class Player
{
public:
	SDL_Rect playerRect;
	float angle;
	float velocityX;
	float velocityY;

	Player(int x_, int y_, int w_, int h_)
	{
		playerRect =
		{
			x_,y_,w_,h_
		};
		angle = 0;
		velocityX = 0;
		velocityY = 0;
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
	//Player object
	Player* player = new Player(610, 690, 40, 40);

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

		if (keysArray[SDL_SCANCODE_LEFT])
			player->angle -= 0.5f;
		if (keysArray[SDL_SCANCODE_RIGHT])
			player->angle += 0.5f;
		if (keysArray[SDL_SCANCODE_UP])
		{
			player->velocityY += 0.01f * sin(player->angle);
			player->velocityX += 0.01f * cos(player->angle);
		}
		if (keysArray[SDL_SCANCODE_DOWN])
		{
			player->velocityY -= 0.01f * sin(player->angle);
			player->velocityX -= 0.01f * cos(player->angle);
		}
			


		//PLAYER SPEED
		
		player->playerRect.x += player->velocityX;

		if (player->playerRect.x < 0)
			player->playerRect.x = 0;
		if (player->playerRect.x > 1280 - player->playerRect.w)
			player->playerRect.x = 1280 - player->playerRect.w;

		player->playerRect.y += player->velocityY;

		if (player->playerRect.y < 0)
			player->playerRect.y = 0;
		if (player->playerRect.y > 720 - player->playerRect.h)
			player->playerRect.y = 720 - player->playerRect.h;

		//DRAW
			//BACKGROUND
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		//PLAYER
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &player->playerRect);

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		SDL_RenderPresent(renderer);

		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 100 / 60) SDL_Delay(100 / 60 - frameTime);

	}
	return 0;
}