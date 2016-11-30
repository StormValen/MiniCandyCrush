#include <SDL\SDL.h>
#include <SDL\SDL_image.h>

int main(int, char*[]) {
	try {
		//INIT DE SDLs
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw SDL_GetError();
		const Uint8 imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
		if(!(IMG_Init(imgFlags) & imgFlags))throw IMG_GetError();	// Comprueba lo que hemos pasado con lo que devuelve, si no es lo mismo  es que hay algun error.
		
		//SDL_Log("Executable built in %s", SDL_GetBasePath());
		//WINDOW
		const int WIDTH = 640, HEIGHT = 480;
		SDL_Window *window = SDL_CreateWindow(" Hello SDL",		//Nombre de la ventana
			SDL_WINDOWPOS_CENTERED,			//Posicion de la ventana por funcion de SDL.
			SDL_WINDOWPOS_CENTERED,			//Posicion de la ventana por funcion de SDL.
			WIDTH,
			HEIGHT,
			SDL_WINDOW_SHOWN
		);

		if (window == nullptr) throw SDL_GetError();

		SDL_Renderer *renderer = SDL_CreateRenderer(window,
													-1,
													SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
		);
		if (renderer == nullptr) throw SDL_GetError();

		SDL_Texture *bgTexture = IMG_LoadTexture(renderer, "../../res/gfx/bg.jpg"); // ../ path relativo, -> flecha atras en carpetas.	
		if (bgTexture == nullptr) throw IMG_GetError();

		SDL_Texture *playerTexture = IMG_LoadTexture(renderer, "../../res/gfx/blue.png"); // ../ path relativo, -> flecha atras en carpetas.	
		if (bgTexture == nullptr || playerTexture == nullptr) throw IMG_GetError();

		SDL_Rect bgRect = { 0, 0, WIDTH, HEIGHT };
		SDL_Rect playerRect = { (WIDTH>>1)-50,(HEIGHT>>1)-50,100,100 };
		SDL_Rect playerTarget = { 0, 0, 100, 100 };

		//Se crea una ventana y se asigna a un puntero del tipo window (struct) y cuando acabe el programa hay que elmiminarla.

		//GAMELOOP.
		SDL_Event evnt;

		for (bool isRunning = true; isRunning;) {		//Mientras isRunnig sea true.
			//INPUT HANDLER
			while (SDL_PollEvent(&evnt)){
				switch (evnt.type) {
				case SDL_QUIT: isRunning = false; break;
				case SDL_MOUSEMOTION: playerTarget.x = evnt.motion.x - 50; playerTarget.y = evnt.motion.y - 50; break;
				default:;
				}
			}
			//UPTDATE	
			playerRect.x += (playerTarget.x - playerRect.x) *0.1f;
			playerRect.y += (playerTarget.y - playerRect.y) *0.1f;
			//DRAW
			SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);	//Guarda las cosas a pintar en un buffer para pintarlo todo de golpe a llamar 
			SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);
			SDL_RenderPresent(renderer);
		}

		SDL_DestroyTexture(bgTexture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
	catch (const char *msg) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", msg);
	}
	SDL_Quit();
	IMG_Quit();

	return 0;
}






//La funcion main de SDL permite compilar en crossplatform.
//SDL_GetBasePath retorna la direccion en la que se guarda el ejecutable.