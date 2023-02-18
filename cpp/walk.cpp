#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"
#include "dot.h"
#include "common.h"
#include "tiledmap.h"


//The dimension of the window, (bottom right coordinates)
int WINDOW_WIDTH = 640;
int WINDOW_HEIGHT = 480;

const int FPS = 60;
const int TICKS_PER_FRAME = 1000 / FPS;

void cap_framerate(Uint32 starting_tick){
  if((TICKS_PER_FRAME) > SDL_GetTicks() - starting_tick)
    SDL_Delay(TICKS_PER_FRAME - (SDL_GetTicks() - starting_tick));
}


int main()
{
  SDL_Init(SDL_INIT_EVERYTHING);

  // I rather have slowdown due to initiation now,
  // then first time an IMG_* function is called:
  IMG_Init(IMG_INIT_PNG);

  //Create a window to which we can render stuff
  SDL_Window *window;
  window = SDL_CreateWindow("Walk on base",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            WINDOW_WIDTH, WINDOW_HEIGHT, 0);

  // Create the renderer we will be using, and associate window with it:
  SDL_Renderer *renderer;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                SDL_RENDERER_PRESENTVSYNC);
  //Initialize renderer color
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


  TiledMap map("big.json", renderer);
  const int LEVEL_HEIGHT = map.getHeight() * 32; // xxx aaarrgghhh!
  const int LEVEL_WIDTH = map.getWidth()  * 32 ;
  std::cout << "H: " << LEVEL_HEIGHT << std::endl;
  std::cout << "W: " << LEVEL_WIDTH << std::endl;


  Texture dot_texture;
  dot_texture.loadFromFile("data/image.png", renderer);
  Dot dot(&dot_texture, LEVEL_HEIGHT, LEVEL_WIDTH);

  // MAIN LOOP
  //The camera area
  SDL_Rect camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

  Uint32 starting_tick;
  bool quit = false;
  SDL_Event event;

  while(!quit){
    starting_tick = SDL_GetTicks();

    while(SDL_PollEvent(&event)){
      switch(event.type){
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_WINDOWEVENT:
        switch(event.window.event) {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
          WINDOW_WIDTH  = event.window.data1; // repaint on window size change
          WINDOW_HEIGHT = event.window.data2;
          SDL_RenderPresent(renderer);
          break;
        case SDL_WINDOWEVENT_EXPOSED:
          SDL_RenderPresent(renderer); // if window was obscured
          break;
        }
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym){
        case SDLK_q: quit = true; break;
        case SDLK_ESCAPE: quit = true; break;
        default: break;
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        switch (event.button.button) {
        case SDL_BUTTON_LEFT:
          SDL_ShowSimpleMessageBox(0, "Mouse", "Left mouse button", window);
          break;
        case SDL_BUTTON_RIGHT:
          SDL_ShowSimpleMessageBox(0, "Mouse", "Right mouse button", window);
          break;
        default:
          SDL_ShowSimpleMessageBox(0, "Mouse", "Some other mosuse button", window);
          break;
        }
        break;
      }
      dot.handleEvent(event);
    }

    dot.move(map);
    dot.setCamera(camera);

    //RENDER THE SCENE
    //Recommended: First clear the renderer, (using the set render color)
    SDL_RenderClear(renderer);

    map.render(renderer, camera);
    dot.render(renderer, camera);

    //player.render(renderer);

    // FInally Present on screen
    SDL_RenderPresent(renderer);

    cap_framerate(starting_tick);
  }


  return 0;
}
