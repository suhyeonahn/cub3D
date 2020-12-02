#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "defs.h"
#include "map.h"
#include "player.h"
#include "ray.h"
#include "texture.h"
#include "wall.h"

bool isGameRunning = false;
int ticksLastFrame = 0;

void setup()
{
  // Asks uPNG library to decode all PNG files and loads the wallTextures array
  loadWallTextures();
}

void processInput()
{
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type)
  {
    case SDL_QUIT:
      {
        isGameRunning = false;
        break;
      }
    case SDL_KEYDOWN:
      {
        if (event.key.keysym.sym == SDLK_ESCAPE)
          isGameRunning = false;
        if (event.key.keysym.sym == SDLK_UP)
          player.walkDirection = +1;
        if (event.key.keysym.sym == SDLK_DOWN)
          player.walkDirection = -1;
        if (event.key.keysym.sym == SDLK_RIGHT)
          player.turnDirection = +1;
        if (event.key.keysym.sym == SDLK_LEFT)
          player.turnDirection = -1;
        break;
      }
    case SDL_KEYUP:
      {
        if (event.key.keysym.sym == SDLK_UP)
          player.walkDirection = 0;
        if (event.key.keysym.sym == SDLK_DOWN)
          player.walkDirection = 0;
        if (event.key.keysym.sym == SDLK_RIGHT)
          player.turnDirection = 0;
        if (event.key.keysym.sym == SDLK_LEFT)
          player.turnDirection = 0;
        break;
      }
  }
}

void update()
{
	int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);
	if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH)
		SDL_Delay(timeToWait);
  float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

  ticksLastFrame = SDL_GetTicks();

  //remember to update game objects as a function of deltaTime
  movePlayer(deltaTime);
  castAllRays();
}

void render(void)
{
	clearColorBuffer(0xFF000000);
  
	renderWallProjection();
	
  // display the minimap
	renderMap();
	renderRays();
	renderPlayer();

	renderColorBuffer();
}

void  releaseResources(void)
{
  freeWallTextures();
  destroyWindow();
}

int main(int argc, char* argv[])
{
  isGameRunning = initializeWindow();

  setup();

  while (isGameRunning)
  {
    processInput();
    update();
    render();
  }

  releaseResources();

  return 0;
}
