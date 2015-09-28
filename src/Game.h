/*
 * Game.h
 *
 *  Created on: Sep 7, 2015
 *      Author: gonzalo
 */

#ifndef GAME_H_
#define GAME_H_

#include "Unit.h"
#include "SDL2/SDL.h"

#include "Map.h"
#include "GameObject.h"
#include "Logger.h"
#include "SDL_image.h"
#include <iostream>
using namespace std;

class Game
{
public:
	//constantes globales
	const int TILE_WIDTH = 64;
	const int TILE_HEIGHT = 32;

	//Singleton
    static Game* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }

        return s_pInstance;
    }


    bool init(const char* title, int xpos, int ypos, int width, int height, int SDL_WINDOW_flag);

    void render();
    void update();
    void handleEvents();
    void clean();
    void cargarEntidad(int posx,int posy,int width,int height,int destWidth,int destHeight,
    				int numFrames,int row,int frame,int offsetX,int offsetY,int longBase,
    				int longAlt, std::string nombre);

    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    SDL_Window* getWindow() const { return m_pWindow; }

    bool running() { return m_bRunning; }

    void restart(); //Al presionar Q
    bool m_bQuiting;

    void quit() { m_bRunning = false; }

    int getGameWidth() const { return m_gameWidth; }
    int getGameHeight() const { return m_gameHeight; }

    float getMapWidth() const;
    float getMapHeight() const;

private:

    //variable temporal, más avanzado en el diseño, la deberiamos mover a otra clase.
    //Yo pense en hacer la clase Player referente al jugador físico, a la persona.
    GameObject* m_pAldeano_test; // será un Unit,
    Map* m_pMap;
    std::vector<GameObject*> entidades;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    bool m_bRunning;

    static Game* s_pInstance;

    int m_gameWidth;
    int m_gameHeight;
    int cantDeEntidades;

	bool initGame();
	void orderGameObjects();

	struct CompareGameObject
	{
		inline bool operator()(const GameObject* obj1, const GameObject* obj2)
		{
			int obj1_value = obj1->m_mapPosition2.m_x + obj1->m_mapPosition2.m_y;
			int obj2_value = obj2->m_mapPosition2.m_x + obj2->m_mapPosition2.m_y;

			if ( obj1_value < obj2_value)
				return true;

			if (obj1_value > obj2_value)
				return false;

			if (obj1_value == obj2_value)
			{
				if (obj1->m_mapPosition2.m_y >= obj2->m_mapPosition2.m_y)
					return true;
				else
					return false;
			}
			return true;
		}
	};

    Game(); // Singleton --> Contructor y destructor privados
    ~Game();

    Game(const Game&);
	Game& operator=(const Game&);
};

typedef Game TheGame;

#endif /* GAME_H_ */