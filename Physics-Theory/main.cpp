#include <iostream>
#include <Windows.h>
#include "SDL2-2.0.12/include/SDL.h"
#include "main.h"
#define GRAVITY 10
#define RAD 3.1415/180

#define WW 1280
#define WH 720

class Player
{
public:
	SDL_Rect playerRect;
	float x, y;
	float angle;
	float velocity;

	Player(int x_, int y_, int w_, int h_)
	{
		playerRect =
		{
			x_,y_,w_,h_
		};
		x = x_;
		y = y_;
		angle = 0;
		velocity = 0;
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
	Player* player = new Player(WW / 2, WH / 2, 40, 40);

	//Boxes object
	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

	SDL_CreateWindowAndRenderer(WW, WH, 0, &window, &renderer);

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

		if (keysArray[SDL_SCANCODE_LEFT]) player->angle -= 1.0f;
		if (keysArray[SDL_SCANCODE_RIGHT]) player->angle += 1.0f;

		if (keysArray[SDL_SCANCODE_R]) player->velocity = 0;

		if (keysArray[SDL_SCANCODE_UP]) player->velocity += 0.01f;
		if (keysArray[SDL_SCANCODE_DOWN]) player->velocity -= 0.01f;
			


		//PLAYER SPEED
		
		player->x += player->velocity * cos(player->angle * RAD);

		//if (player->playerRect.x < 0) player->playerRect.x = 1;
		//if (player->playerRect.x > 1280 - player->playerRect.w) player->playerRect.x = 1280 - player->playerRect.w-1;

		player->y += player->velocity * sin(player->angle * RAD);

		//if (player->playerRect.y < 0) player->playerRect.y = 1;
		//if (player->playerRect.y > 720 - player->playerRect.h) player->playerRect.y = 720 - player->playerRect.h-1;

		player->playerRect.x = player->x;

		player->playerRect.y = player->y;

		//DRAW
			//BACKGROUND
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		//PLAYER
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &player->playerRect);

		int x1 = player->playerRect.x + player->playerRect.w / 2;
		int y1 = player->playerRect.y + player->playerRect.h / 2;

		int x2 = x1 + 100 * cos(player->angle * RAD);
		int y2 = y1 + 100 * sin(player->angle * RAD);

		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

		SDL_RenderPresent(renderer);

		static char title[256];
		sprintf_s(title, 256, "angle: %.1f | velocity: %.1f", player->angle, player->velocity);
		SDL_SetWindowTitle(window, title);

		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 100 / 60) SDL_Delay(100 / 60 - frameTime);

	}
	return 0;
}