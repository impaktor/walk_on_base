#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"
#include "dot.h"
#include "npc.h"
#include "common.h"
#include "tiledmap.h"
#include "sprite.h"
#include "character.h"
#include "Camera.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_sdlrenderer.h"

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

//The dimension of the window, (bottom right coordinates)
int WINDOW_WIDTH = 1080;
int WINDOW_HEIGHT = 720;

const int FPS = 60;
const int TICKS_PER_FRAME = 1000 / FPS;

int Character::ID = 0;

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


  // Application init: create a dear imgui context, setup some options, load fonts
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer_Init(renderer);

  // ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  bool show_demo_window = false;
  bool show_debug_window = true;


  //Initialize renderer color
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


  TiledMap map("big.json", renderer);
  //The camera area
  Camera camera(SDL_Rect{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, &map);

  Texture dot_texture;
  // For now: assume sprite sheet has 4 rows, use first column:
  dot_texture.loadFromFile("../data/sprites/character/character.bmp", renderer);
  Sprite dot_sprite(&dot_texture, 32, 32);

  SDL_Rect start_pos = map.get_object("start");
  vec start_map_pos = map.get_map_pos(vec{start_pos.x, start_pos.y});

  Dot dot(&dot_sprite, start_map_pos, &map);

  Texture npc_texture;
  Uint8 color_key[3] = {255,255,255};
  npc_texture.loadFromFile("../data/sprites/character/sheet2.png", renderer, color_key);
  Sprite npc_sprite(&npc_texture, 32, 48);
  NPC npc(&npc_sprite, &map);

  Uint32 starting_tick;
  bool quit = false;
  SDL_Event event;

  while(!quit){
    starting_tick = SDL_GetTicks();

    while(SDL_PollEvent(&event)){
      ImGui_ImplSDL2_ProcessEvent(&event);

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
        case SDLK_d: show_debug_window = !show_debug_window; break;
        default: break;
        }
        break;
      // case SDL_MOUSEBUTTONDOWN:
      //   switch (event.button.button) {
      //   case SDL_BUTTON_LEFT:
      //     SDL_ShowSimpleMessageBox(0, "Mouse", "Left mouse button", window);
      //     break;
      //   case SDL_BUTTON_RIGHT:
      //     SDL_ShowSimpleMessageBox(0, "Mouse", "Right mouse button", window);
      //     break;
      //   default:
      //     SDL_ShowSimpleMessageBox(0, "Mouse", "Some other mosuse button", window);
      //     break;
      // }
      // break;
      }
      dot.handleEvent(event);
    }

    // at start of the Dear ImGui frame
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    dot.update();
    npc.update();

    camera.set(dot.getPos());

    if(show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);
    // ImGui::SetNextWindowPos({ 0, 0 });
    if(ImGui::Begin("Debug##1", &show_debug_window))
    {
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

      ImGui::Separator();
      ImGui::Text("Mouse");
      int xMouse, yMouse;
      SDL_GetMouseState(&xMouse, &yMouse);
      std::ostringstream s1;
      s1 << "screen x,y: " << vec{xMouse, yMouse};
      ImGui::Text(s1.str().c_str());

      vec map_pos = map.get_map_pos(vec(xMouse, yMouse) + camera.getpos());
      std::ostringstream s2;
      s2 << "map x,y: " << map_pos;
      ImGui::Text(s2.str().c_str());
      ImGui::Separator();
    }
    ImGui::End();

    if (ImGui::IsKeyPressed(ImGuiKey_D)) {
      show_debug_window = !show_debug_window;
    }

    //RENDER THE SCENE

    //Recommended: First clear the renderer, (using the set render color)
    SDL_RenderClear(renderer);

    map.render(renderer, camera.get());
    dot.render(renderer, camera.get());
    npc.render(renderer, camera.get());

    // at end of frame
    ImGui::Render();

    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    // SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());


    // Finally Present on screen
    SDL_RenderPresent(renderer);

    cap_framerate(starting_tick);
  }

  // // Cleanup
  ImGui_ImplSDLRenderer_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
