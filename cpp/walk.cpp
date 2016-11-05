#include <json/json.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"


// Two great resouces:
// https://github.com/bjorn/tiled/wiki/JSON-Map-Format
// https://en.wikibooks.org/wiki/JsonCpp

int WINDOW_WIDTH = 640;
int WINDOW_HEIGHT = 480;

class TiledMap{
public:

  TiledMap(const std::string &str, SDL_Renderer *rend);

  //~TiledMap();

  int getWidth() const {
    return mWidth;
  }

  int getHeight() const {
    return mHeight;
  };

  void render(SDL_Renderer *rend);


private:
  // Dimensions of entire level/map in tiles
  int mWidth;
  int mHeight;

  Json::Value mRoot;

  struct clip{
    SDL_Rect rect;
    std::string tileSetName;
  };

  // Each element holds the clip to a (single) tileset
  //std::vector<SDL_Rect> mClips;
  std::vector<clip> mClips;

  // Dimensions of one tile in pixels
  int mTileWidth;
  int mTileHeight;

  // My (single) tile texture
  //Texture *mTileTexture;

  std::map<std::string, Texture> mTileTextures;

  // Either orthogonal or isometric (diamond), staggered
  std::string mOrientation;

  // Auto-increments for each placed object
  int mNextObjectId;

};


TiledMap::TiledMap(const std::string &name, SDL_Renderer *renderer){
  std::ifstream ifile(name, std::ifstream::in);
  ifile >> mRoot;

  mWidth = mRoot["width"].asInt();
  mHeight = mRoot["height"].asInt();

  mTileWidth = mRoot["tileheight"].asInt();
  mTileHeight = mRoot["tilewidth"].asInt();

  // (Default to orthographic, if field not found)
  mOrientation = mRoot.get("orientation", "orthographic").asString();


  for(int i = 0; i < mRoot["tilesets"].size(); ++i){
    Json::Value tileset = mRoot["tilesets"][i];
    std::cout << "image " << tileset["image"].asString() << std::endl;
    std::cout << "columns " << tileset["columns"].asInt() << std::endl;
    std::cout << "firstgid " << tileset["firstgid"].asInt() << std::endl;
    std::cout << "imageheight " << tileset["imageheight"].asInt() << std::endl;
    std::cout << "imagewidth " << tileset["imagewidth"].asInt() << std::endl;
    std::cout << "tileHeight " << tileset["tileHeight"].asInt() << std::endl;
    std::cout << "tileWidth " << tileset["tileWidth"].asInt() << std::endl;
  }


  // Populate mClips vector, where each element is a unique "gid" id from tile.
  mClips.clear();
  for(int i = 0; i < mRoot["tilesets"].size(); ++i){
    Json::Value tileset = mRoot["tilesets"][i];
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

    std::cout << "firstGid\t" << firstGid << std::endl;

    for(int j = firstGid -1; j < tileCount + firstGid -1; ++j){
      std::cout << j << "; x=" << x << ", y=" << y << std::endl;
      //SDL_Rect tmp = {x, y, tileH, tileW};
      mClips[j].rect = {x, y, tileH, tileW};
      x += tileW;

      if((j + 1) % col == 0){
        x = 0;
        y += tileH;
      }
    }
  }
  // debug print out
  for(int i = 0; i < mClips.size(); ++i)
    std::cout << i << "| " << mClips[i].rect.x << " "
              << mClips[i].rect.y << " " << mClips[i].rect.h << " "
              << mClips[i].rect.w << " " << mClips[i].tileSetName << std::endl;
  std::cout << "************* mClips done" << std::endl;

}


void TiledMap::render(SDL_Renderer *renderer){

  // HORRIBLE! Assumes one single tile set
  Json::Value tileset = mRoot["tilesets"][0];
  int tileH = tileset["tileheight"].asInt();
  int tileW = tileset["tilewidth"].asInt();

  std::cout << tileH << " - " << tileW << std::endl;

  for(int i = 0; i < mRoot["layers"].size(); ++i){
    Json::Value layer = mRoot["layers"][i];
    std::cout << "Name of tile layer [" << i << "]: " << layer["name"] << std::endl;

    int x = 0;
    int y = 0;
    for(int j = 0; j < layer["data"].size(); ++j){
      int tileId = layer["data"][j].asInt();   // "gid coordinate"
      std::cout << "(" << x << "," << y << ") " << tileId << std::endl;

      if(tileId > 0)
        mTileTextures[mClips[tileId - 1].tileSetName].render(renderer, x, y, &mClips[tileId - 1].rect);

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


const int FPS = 60;
const int TICKS_PER_FRAME = 1000 / FPS;

void cap_framerate(Uint32 starting_tick){
  if((TICKS_PER_FRAME) > SDL_GetTicks() - starting_tick)
    SDL_Delay(TICKS_PER_FRAME - (SDL_GetTicks() - starting_tick));
}


int main(int argc, char *argv[])
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


  TiledMap map("scroll.json", renderer);
  std::cout << "H: " << map.getHeight() << std::endl;
  std::cout << "W: " << map.getWidth() << std::endl;


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
    }

    //RENDER THE SCENE
    //Recommended: First clear the renderer, (using the set render color)
    SDL_RenderClear(renderer);

    map.render(renderer);

    //player.render(renderer);

    // FInally Present on screen
    SDL_RenderPresent(renderer);

    cap_framerate(starting_tick);
  }


  return 0;
}
