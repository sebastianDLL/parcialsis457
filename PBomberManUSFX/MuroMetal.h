#pragma once
#include "GameActor.h"
class MuroMetal :
    public GameActor
{
public:
    MuroMetal(Texture* _textura, Tile* _tileActual);
    void setTileActual(Tile* _tileNuevo);
};

