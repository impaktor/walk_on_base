#include <json/json.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <iostream>
#include <string>
#include "tiledmap.h"

TiledMap::TiledMap(const std::string &name, SDL_Renderer *renderer){
  std::ifstream ifile(name, std::ifstream::in);
  ifile >> mRoot;

  mWidth = mRoot["width"].asInt();
  mHeight = mRoot["height"].asInt();

  // dimension of one tile in pixels
  mTileWidth = mRoot["tilewidth"].asInt();
  mTileHeight = mRoot["tileheight"].asInt();

  // (Default to orthographic, if field not found)
  mOrientation = mRoot.get("orientation", "orthographic").asString();


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


  // Populate mClips vector, where each element is a unique "gid" id from tile.
  mClips.clear();
  for(size_t i = 0; i < mRoot["tilesets"].size(); ++i){
    Json::Value tileset = mRoot["tilesets"][(int)i];
    int tileCount = tileset["tilecount"].asInt();
    int firstGid = tileset["firstgid"].asInt();

    int tileH = tileset["tileheight"].asInt();
    int tileW = tileset["tilewidth"].asInt();

    int col = tileset["columns"].asInt();

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

    //-- std::cout << "firstGid\t" << firstGid << std::endl;

    for(int j = firstGid -1; j < tileCount + firstGid -1; ++j){
      //-- std::cout << j << "; x=" << x << ", y=" << y << std::endl;

      //SDL_Rect tmp = {x, y, tileH, tileW};
      mClips[j].rect = {x, y, tileW, tileH};
      x += tileW;

      if((j + 1) % col == 0){
        x = 0;
        y += tileH;
      }
    }
  }
  //-- // debug print out
  //-- for(size_t i = 0; i < mClips.size(); ++i)
  //--   std::cout << i << "| " << mClips[i].rect.x << " "
  //--             << mClips[i].rect.y << " " << mClips[i].rect.h << " "
  //--             << mClips[i].rect.w << " " << mClips[i].tileSetName << std::endl;
  //-- std::cout << "************* mClips done" << std::endl;

}


void TiledMap::render(SDL_Renderer *renderer, SDL_Rect &camera){

  // HORRIBLE! Assumes one single tile set
  Json::Value tileset = mRoot["tilesets"][0];
  int tileH = tileset["tileheight"].asInt();
  int tileW = tileset["tilewidth"].asInt();

  //-- std::cout << tileH << " - " << tileW << std::endl;

  for(size_t i = 0; i < mRoot["layers"].size(); ++i){
    int indexi = i;
    Json::Value layer = mRoot["layers"][indexi];
    //-- std::cout << "Name of tile layer [" << indexi << "]: " << layer["name"] << std::endl;

    int x = 0;
    int y = 0;
    for(size_t j = 0; j < layer["data"].size(); ++j){
      int indexj = j;
      int tileId = layer["data"][indexj].asInt();   // "gid coordinate"
      //-- std::cout << "(" << x << "," << y << ") " << tileId << std::endl;

      if(tileId > 0)
        mTileTextures[mClips[tileId - 1].tileSetName].render(renderer, x - camera.x, y - camera.y, &mClips[tileId - 1].rect);

      x += tileW;
      //std::cout << mRoot["layers"][i]["data"][j] << " ";
      if((j + 1) % mWidth == 0){
        //std::cout << std::endl;
        y += tileH;
        x = 0;
      }
    }
  }
}
