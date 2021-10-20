#pragma once
#include<iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include "Bomberman.h"
#include "MuroMetal.h"
#include "MapGenerator.h"
#include "system/KeyboardInput.h"
#include "TilesGraph.h"

using namespace std;

const int SCREEN_WIDTH = 850;
const int SCREEN_HEIGHT = 510;
  
class GameManager
{
private:
    //The window we'll be rendering to
    SDL_Window* gWindow;

    //The window renderer
    SDL_Renderer* gRenderer;

    //Current displayed texture
    SDL_Texture* gTexture = nullptr;
       
    vector<GameObject*> actoresJuego;
    MapGenerator* generadorMapa;
    KeyboardInput* keyboardInput;


    SDL_Event evento;
    bool enEjecucion;

    TilesGraph* tilesGraphGM;
public:
    // Constructores & destructores
    GameManager();

    // Metodos especializados
    bool onInit();
    bool loadContent();
    int onExecute();
    void onEvent(SDL_Event* _event);
    void onLoop();
    void onRender();
    void close();    
};
