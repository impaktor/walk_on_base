#include <json/json.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <iostream>
#include <string>
#include "tiledmap.h"
#include "imgui/imgui.h"


TiledMap::TiledMap(const std::string &name, SDL_Renderer *renderer){
  std::cout << "tiled map name\t" << name << std::endl;
  std::ifstream ifile(name, std::ifstream::in);
  ifile >> mRoot;

  mShowCollisionLayer = false;

  // Map dimensions in units of tiles
  mWidth = mRoot["width"].asInt();
  mHeight = mRoot["height"].asInt();

  mTileWidthHalf = mWidth / 2;
  mTileHeightHalf = mHeight / 2;

  // dimension of one tile in pixels
  mTileWidth = mRoot["tilewidth"].asInt();
  mTileHeight = mRoot["tileheight"].asInt();

  // (Default to orthographic, if field not found)
  mOrientation = mRoot.get("orientation", "orthographic").asString();

  std::cout << "tiled map dim: " << mWidth << "x" << mHeight << " tiles."
            << " orientation: " << mOrientation << std::endl;

  for(size_t i = 0; i < mRoot["tilesets"].size(); ++i){
    Json::Value tileset = mRoot["tilesets"][(int)i];
    std::cout << "\timage " << tileset["image"].asString() << std::endl;
    std::cout << "\tcolumns " << tileset["columns"].asInt() << std::endl;
    std::cout << "\tfirstgid " << tileset["firstgid"].asInt() << std::endl;
    std::cout << "\timageheight " << tileset["imageheight"].asInt() << std::endl;
    std::cout << "\timagewidth " << tileset["imagewidth"].asInt() << std::endl;
    std::cout << "\ttileHeight " << tileset["tileheight"].asInt() << std::endl;
    std::cout << "\ttileWidth " << tileset["tilewidth"].asInt() << "\n" << std::endl;
  }

  // Get game objects
  for(int i = 0; i < (int)mRoot["layers"].size(); ++i){
    Json::Value layer = mRoot["layers"][i];
    std::string layername = layer["name"].asString();

    if(layername == std::string("GameObjects")){
      for(size_t j = 0; j < layer["objects"].size(); j++){
        object tmp;
        Json::Value objects = layer["objects"][int(j)];
        tmp.name =   objects["name"].asString();
        tmp.rect.x = objects["x"].asInt();
        tmp.rect.y = objects["y"].asInt();
        tmp.rect.w = objects["width"].asInt();
        tmp.rect.h = objects["height"].asInt();
        tmp.rotation = objects["rotation"].asFloat();
        tmp.visible = objects["rotation"].asBool();

        std::cout << tmp.name << " x " << tmp.rect.x << " h: " << tmp.rect.h <<"\n";
        m_objects[tmp.name] = tmp;
      }
    }
  }

  // Populate mClips vector, where each element is a unique "gid" id
  // from tile. (gid is the index of the tile on the map, starts
  // upper left corner of map, there are mWidth x mHeight gids (as
  // many as tiles on map).
  mClips.clear();
  for(size_t i = 0; i < mRoot["tilesets"].size(); ++i){
    Json::Value tileset = mRoot["tilesets"][int(i)];
    int tileCount = tileset["tilecount"].asInt();
    int firstGid = tileset["firstgid"].asInt();

    int tileH = tileset["tileheight"].asInt();
    int tileW = tileset["tilewidth"].asInt();

    int columns = tileset["columns"].asInt();
    // std::cout << "columns: " << columns << " name: " << tileset["name"]
    //           << " firstGid: " << firstGid
    //           << " imagewidth: " << tileset["imagewidth"].asInt() << std::endl;

    // this feels a bit strange, to both index the map on filename,
    // and send it as input arg...
    std::string tileFileName = tileset["image"].asString();
    mTileTextures[tileFileName] = Texture();
    mTileTextures[tileFileName].loadFromFile(tileFileName, renderer);

    clip tmp;
    tmp.rect = SDL_Rect({0,0,0,0});
    tmp.tileSetName = tileset["image"].asString();

    mClips.resize(mClips.size() + tileCount, tmp);

    int x = 0;
    int y = 0;
    int col = 0;
    for(int j = firstGid -1; j < tileCount + firstGid -1; ++j){

      //SDL_Rect tmp = {x, y, tileH, tileW};
      mClips[j].rect = {x, y, tileW, tileH};
      x += tileW;
      col++;
      if(col == columns){
        col = 0;
        x = 0;
        y += tileH;
      }
    }
  }
}


void TiledMap::render(SDL_Renderer *renderer, SDL_Rect &camera){

  // HORRIBLE! Assumes one single tile set
  // No, assumes tiles in all tilesets have same size, e.g. 32x32
  Json::Value tileset = mRoot["tilesets"][0];
  int tileH = tileset["tileheight"].asInt();
  int tileW = tileset["tilewidth"].asInt();

  for(size_t i = 0; i < mRoot["layers"].size(); ++i){
    Json::Value layer = mRoot["layers"][int(i)];
    std::string layername = layer["name"].asString();

    // Don't render collision layer (typically we use a red tile for this)
    if(layername == mCollisionLayerName && !mShowCollisionLayer){
      continue;
    }

    int x = 0;
    int y = 0;
    for(size_t j = 0; j < layer["data"].size(); ++j){
      int tileId = layer["data"][int(j)].asInt();   // "gid coordinate"

      if(tileId > 0)
        mTileTextures[mClips[tileId - 1].tileSetName].render(renderer, x - camera.x, y - camera.y, &mClips[tileId - 1].rect);

      x += tileW;
      if((j + 1) % mWidth == 0){
        y += tileH;
        x = 0;
      }
    }
  }

  if(ImGui::Begin("Debug##1")){
    ImGui::Checkbox(mCollisionLayerName.c_str(), &mShowCollisionLayer);
  }
  ImGui::End();
}


bool TiledMap::isCollision(vec pos){

  // If we go outside the level, count as "collision"
  if (pos.x < 0 || pos.x > mTileWidth * mWidth)
    return true;
  if (pos.y < 0 || pos.y > mTileHeight * mHeight)
    return true;

  // loop through all layers to find collision layer
  for(size_t i = 0; i < mRoot["layers"].size(); ++i){
    Json::Value layer = mRoot["layers"][int(i)];
    std::string layername = layer["name"].asString();

    if(layername != mCollisionLayerName){
      continue;
    }

    // convert 2D coordinates to 1D (assuming we can only move in
    // steps of full tiles)
    int j = float(pos.x)/mTileWidth + float(pos.y)/mTileHeight * mWidth;
    int tileId = layer["data"][j].asInt();   // "gid coordinate"

    // if there is a tile on this coordinate, it's a collision
    return tileId > 0;
  }
  return false;
}

bool TiledMap::isOnMap(vec pos){
  return !(pos.x < 0 || pos.x > (mWidth-1)*mTileWidth ||
           pos.y < 0 || pos.y > (mHeight-1)*mTileHeight);
}


vec TiledMap::get_map_pos(vec screen){
  vec map;
  if(mOrientation == std::string("orthogonal")){
    map.x = screen.x / mTileWidth;
    map.y = screen.y / mTileHeight;
  }
  else if(mOrientation == std::string("isometric")){
    map.x = (screen.x / mTileWidthHalf  + (screen.y / mTileHeightHalf)) /2;
    map.y = (screen.y / mTileHeightHalf - (screen.x / mTileWidthHalf)) /2;
  }
  return map;
}


vec TiledMap::get_screen_pos(vec map){
  vec screen;
  if(mOrientation == std::string("orthogonal")){
    screen.x = map.x * mTileWidth;
    screen.y = map.y * mTileHeight;
  }
  else if(mOrientation == std::string("isometric")){
    screen.x = (map.x - map.y) * mTileWidthHalf;
    screen.y = (map.x + map.y) * mTileHeightHalf;
  }
  return screen;
}

vec TiledMap::get_tile_size() const {
  return vec(mTileWidth, mTileHeight);
}


SDL_Rect TiledMap::get_object(const char* key) const {
  return m_objects.at(key).rect;
}


AStar::CoordinateList TiledMap::getBlocking(){
  AStar::CoordinateList path;

  // loop through all layers to find collision layer
  for(size_t i = 0; i < mRoot["layers"].size(); ++i){
    Json::Value layer = mRoot["layers"][int(i)];
    std::string layername = layer["name"].asString();

    if(layername != mCollisionLayerName){
      continue;
    }

    int columns = layer["width"].asInt();

    int x = 0;
    int y = 0;
    for(size_t j = 0; j < layer["data"].size(); ++j){
      int tileId = layer["data"][int(j)].asInt();

      if(tileId > 0){
        AStar::Vec2i coordinate;
        coordinate.x = x;
        coordinate.y = y;
        path.push_back(coordinate);
      }

      x++;
      if(x == columns){
        x = 0;
        y++;
      }
    }
  }

  // for(size_t i = 0; i < path.size(); i++){
  //   std::cout << i << ": " << path[i].x << ", " << path[i].y << "\n";
  // }

  // zero indexed tile-coordinates (not pixel coordinates),
  return path;
}


AStar::CoordinateList TiledMap::getPath(AStar::Vec2i start, AStar::Vec2i end){

  AStar::Generator generator;

  AStar::CoordinateList wall = getBlocking();

  generator.setCollisions(wall);

  // Set 2d map size.
  generator.setWorldSize({mWidth, mHeight});

  // You can use a few heuristics : manhattan, euclidean or octagonal.
  generator.setHeuristic(AStar::Heuristic::euclidean);
  generator.setDiagonalMovement(false);

  std::cout << "Generate path ... \n";
  // This method returns vector of coordinates from target to source.
  AStar::CoordinateList path = generator.findPath(start, end);

  for(auto& coordinate : path) {
    std::cout << coordinate << " -> ";
  }
  std::cout << "Done" << std::endl;

  return path;
}
