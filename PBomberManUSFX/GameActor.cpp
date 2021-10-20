#include "GameActor.h"

TilesGraph* GameActor::tilesGraph = nullptr;

GameActor::GameActor() :GameObject() {
	posicionX = 0;
	posicionY = 0;
	imagenX = 0;
	imagenY = 0;
	ancho = 34;
	alto = 34;

	solido = true;
	indestructible = false;
	visible = true;
	movil = false;
	enMovimiento = false;
	aereo = false;
	terrestre = true;
	subterraneo = false;

	velocidad = 1;
	energia = 100;
	vidas = 3;

	textura = nullptr;
	tileActual = nullptr;
	tileSiguiente = nullptr;
	direccionActual = MOVE_DIRECTION_NONE;
	direccionSiguiente = MOVE_DIRECTION_NONE;
}


GameActor::GameActor(Texture* _textura, Tile* _tileActual) :GameObject() {
	posicionX = 0;
	posicionY = 0;
	imagenX = 0;
	imagenY = 0;
	ancho = 34;
	alto = 34;

	solido = true;
	indestructible = false;
	visible = true;
	movil = false;
	enMovimiento = false;
	aereo = false;
	terrestre = true;
	subterraneo = false;

	velocidad = 1;
	energia = 100;
	vidas = 3;

	textura = _textura;
	tileActual = _tileActual;
	tileSiguiente = nullptr;
	direccionActual = MOVE_DIRECTION_NONE;
	direccionSiguiente = MOVE_DIRECTION_NONE;
}

void GameActor::render()
{
	if (visible) {
		SDL_Rect* cuadroAnimacion = new SDL_Rect({ imagenX, imagenY, getAncho(), getAlto() });
		textura->render(getPosicionX(), getPosicionY(), cuadroAnimacion);
	}
}

bool GameActor::tratarDeMover(MoveDirection _direccionNueva) {

	Tile* tileDestino = nullptr;

	switch (_direccionNueva)
	{
	case MOVE_DIRECTION_ARRIBA:
		tileDestino = tilesGraph->getTileEn(tileActual->getPosicionTileX(), tileActual->getPosicionTileY() - 1);
		break;
	case MOVE_DIRECTION_ABAJO:
		tileDestino = tilesGraph->getTileEn(tileActual->getPosicionTileX(), tileActual->getPosicionTileY() + 1);
		break;
	case MOVE_DIRECTION_IZQUIERDA:
		tileDestino = tilesGraph->getTileEn(tileActual->getPosicionTileX() - 1, tileActual->getPosicionTileY());
		break;
	case MOVE_DIRECTION_DERECHA:
		tileDestino = tilesGraph->getTileEn(tileActual->getPosicionTileX() + 1, tileActual->getPosicionTileY());
		break;
	}

	// Si tileDestino es nullptr, no se puede avanzar
	if (tileDestino == nullptr) {
		setTileSiguiente(nullptr);
		return false;
	}

	if (tileDestino->getMuroMetal() != nullptr)
	{
		setTileSiguiente(nullptr);
		return false;
	}

	if (tileDestino->getMuroCeramica() != nullptr)
	{
		setTileSiguiente(nullptr);
		return false;
	}

	setTileSiguiente(tileDestino);
	return true;
}