#pragma once
#include <iostream>
#include "GamePawn.h"

using namespace std;

class Bomberman : public GamePawn
{
private:

public:
	//Constructor
	Bomberman(Texture* _textura, Tile* _tileActual);
	void setTileActual(Tile* _tileNuevo) override;

	void update();
	void render();

};

