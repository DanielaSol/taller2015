
/*
 * main.cpp
 *
 *  Created on: Sep 8, 2015
 *      Author: gonzalo
 */

#include "Game.h"
#include <iostream>
#include "Logger.h"
#include "Parser.h"

using namespace std;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char **argv)
{
    Uint32 frameStart, frameTime;

	Logger* myLog = new Logger();
	FILE* arch;
	arch= fopen("prueba.txt","w+");
	fclose(arch);



	TheParser::Instance();

	std::cout << "game init attempt...\n";

	if (TheGame::Instance()->init("TP of Empires", 400, 150, TheParser::Instance()->configGame.pantalla.ancho, TheParser::Instance()->configGame.pantalla.alto, 0)) //flag por ejemplo: SDL_WINDOW_FULLSCREEN_DESKTOP

	{
		std::cout << "game init success!\n";
		while (TheGame::Instance()->running()) {
		
			frameStart = SDL_GetTicks();
			
			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();
			
			frameTime = SDL_GetTicks() - frameStart;
			
			//std::cout << "FPS = " << 1/ (frameTime/1000.0f) << "\n";
			if (frameTime < DELAY_TIME) {
				SDL_Delay((int) ((DELAY_TIME - frameTime)));
            }
        }
    }
    else
    {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }

    std::cout << "game closing...\n";
    TheGame::Instance()->clean();
    delete myLog; // delete llama al destructor y libera la memoria. Valgrind se quejaba sino
    TheParser::Instance()->~Parser(); //por ahora no tiene nada que liberar. El destructor lo puse privado por singleton

    return 0;
}
