#pragma once
#include "GameActor.h"
class SueloCesped :
    public GameActor
{
public:
    SueloCesped(Texture* _textura, Tile* _tileActual);
    void setTileActual(Tile* _tileNuevo);
};

