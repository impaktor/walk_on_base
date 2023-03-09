#include <iostream>
#include <sstream>
#include "dot.h"
#include "character.h"
#include "common.h"
#include "imgui/imgui.h"


Dot::Dot(Sprite *sprite, vec start_pos, TiledMap* map):
  Character(sprite, map){

  //Initialize the offsets
  mPos.x = start_pos.x;
  mPos.y = start_pos.y;

  // Don't print debug each tick, just each event
  mEvent = true;
}

Dot::Dot(Sprite *sprite, const SDL_Rect& start_pos, TiledMap* map):
  Character(sprite, map){
  Dot(sprite, vec{start_pos.x, start_pos.y}, map);
}

void Dot::handleEvent(SDL_Event &event){

  // Suggest new position
  if(event.type == SDL_KEYDOWN){
    switch(event.key.keysym.sym){
    case SDLK_UP:
      mPos.y--;
      break;
    case SDLK_DOWN:
      mPos.y++;
      break;
    case SDLK_LEFT:
      mPos.x--;
      break;
    case SDLK_RIGHT:
      mPos.x++;
      break;
    }
    mEvent = true;
  }
}


void Dot::update(){

  Character::update();

  // Only print keypress if it was updated:
  if (mEvent){
    std::cout << "\r" << mPos << "; " << std::flush;
    // don't need to print this event more (until next event)
    mEvent = false;
  }
}


void Dot::setCamera(SDL_Rect &camera){
  // size of a tile, w x h
  vec tile = map->get_tile_size();

  //Center the camera over the player, regardless of map projection
  vec screen_pos = map->get_screen_pos(mPos);
  camera.x = (screen_pos.x + tile.x / 2) - camera.w / 2;
  camera.y = (screen_pos.y + tile.y / 2) - camera.h / 2;

  int y_max_map = map->getHeight();
  int x_max_map = map->getWidth();

  // Map corners to screen coordinates. Regardless of map
  // projection, we know map corners will be min/max position
  const int x_min_screen = map->get_screen_pos(vec{0,         y_max_map}).x;
  const int x_max_screen = map->get_screen_pos(vec{x_max_map, 0}).x;
  const int y_min_screen = map->get_screen_pos(vec{0,         0}).y;
  const int y_max_screen = map->get_screen_pos(vec{x_max_map, y_max_map}).y;

  //Keep the camera in bounds
  if(camera.x < x_min_screen)
    camera.x = x_min_screen;
  if(camera.y < y_min_screen)
    camera.y = y_min_screen;
  if(camera.x + camera.w > x_max_screen)
    camera.x = x_max_screen - camera.w;
  if(camera.y + camera.h > y_max_screen)
    camera.y = y_max_screen - camera.h;

  if(ImGui::Begin("camera##1")){
    std::ostringstream ss, s1, s2, s3;
    ss << "x_min: " << x_min_screen << " x_max: " << x_max_screen;
    ImGui::Text(ss.str().c_str());
    s1 << "y_min: " << y_min_screen << " y_max: " << y_max_screen;
    ImGui::Text(s1.str().c_str());

    s2 << "camera: " << vec{camera.x, camera.y} << " : c.w=" << camera.w << " c.h=" << camera.h;
    ImGui::Text(s2.str().c_str());

    s3 << "screen pos: " << screen_pos;
    ImGui::Text(s3.str().c_str());
  }
  ImGui::End();
}
