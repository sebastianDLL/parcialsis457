#include "GameManager.h"


GameManager::GameManager() {
	gWindow = nullptr;
	gRenderer = nullptr;
	generadorMapa = nullptr;
	keyboardInput = KeyboardInput::Instance();
	enEjecucion = true;
	tilesGraphGM = nullptr;
}

bool GameManager::onInit() {

	//Initialization flag
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("Bomberman Man USFX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{

			////Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == nullptr)
			{
				cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool GameManager::loadContent()
{
	tilesGraphGM = new TilesGraph(25, 15, 850, 510);
	GameActor::tilesGraph = tilesGraphGM;

	generadorMapa = new MapGenerator(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, tilesGraphGM);
	generadorMapa->crearObjetosJuego("resources/level1.txt");
	generadorMapa->transferirObjetosJuego(actoresJuego);

	if (actoresJuego.size() > 0)
		return true;

	return false;
}

void GameManager::onEvent(SDL_Event* _event)
{
	if (_event->type == SDL_QUIT) {
		enEjecucion = false;
	}

	switch (_event->type) {
	case SDL_KEYDOWN:
		keyboardInput->TurnKeyOn(_event->key.keysym.sym);
		break;
	case SDL_KEYUP:
		keyboardInput->TurnKeyOff(_event->key.keysym.sym);
		break;
	//	switch (_event->key.keysym.sym) {
	//	case SDLK_f:
	//		//SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
	//		break;
	//	case SDLK_n:
	//		//SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_MAXIMIZED);
	//		break;
	//	}
	}
}

void GameManager::onLoop() {
	for (int i = 0; i < actoresJuego.size(); i++) {
		actoresJuego[i]->update();
	}
}

void GameManager::onRender() {
	SDL_RenderClear(gRenderer);
	for (int i = 0; i < actoresJuego.size(); i++) {
		actoresJuego[i]->render();
	}

	SDL_RenderPresent(gRenderer);
}

void GameManager::close()
{
	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = nullptr;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int GameManager::onExecute() {
	if (!onInit()) {
		cout << "Failed to initialize!" << endl;
		return -1;
	}

	if (loadContent() == false) {
		cout << "Failed to load content!" << endl;
		return -1;
	}

	//While application is running
	while (enEjecucion)
	{
		//Handle events on queue
		while (SDL_PollEvent(&evento) != 0)
		{
			onEvent(&evento);
		}

		onLoop();
		onRender();
	}

	//Free resources and close SDL
	close();

	std::cout << "Numero de objetos en el vector: " << actoresJuego.size() << std::endl;
	std::cout << "Numero de objetos creados:" << GameObject::numeroGameObjectCreados << std::endl;

	return 0;

}