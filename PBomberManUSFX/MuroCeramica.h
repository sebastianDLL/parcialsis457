#pragma once
#include "GameActor.h"
class MuroCeramica :
    public GameActor
{
public:
    MuroCeramica(Texture* _textura, Tile* _tileActual);
    void setTileActual(Tile* _tileNuevo);
};

