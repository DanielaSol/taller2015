/*
 * Game.h
 *
 *  Created on: Sep 7, 2015
 *      Author: gonzalo
 */

#ifndef GAME_H_
#define GAME_H_

#include "Pantalla/Map.h"
#include "GameObject.h"
#include "Utilitarios/Logger.h"
#include "SDL_image.h"
#include "SDL2/SDL.h"
#include <iostream>
#include "Pantalla/Pantalla.h"
#include "Pantalla/Barra.h"
#include "SDL2/SDL_ttf.h"

using namespace std;


class Game
{
public:
	//constantes globales
	static const int TILE_WIDTH = 64;
	static const int TILE_HEIGHT = 32;



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
    void cargarEntidadd(GameObject*);
    void cargarRecurso(GameObject* entidad);
    void tomarRecurso(int x, int y);
    void changeMapGrid(int x, int y, int value);

    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    SDL_Window* getWindow() const { return m_pWindow; }

    bool running() { return m_bRunning; }

    void restart(); //Al presionar R
    bool m_bQuiting;

    void quit() { m_bRunning = false; }

    int getGameWidth() const { return m_gameWidth; }
    int getGameHeight() const { return m_gameHeight; }

    float getMapWidth() const;
    float getMapHeight() const;
    Map* m_pMap;
    Pantalla* m_pPantalla;
    Barra* m_pBarra;

    GameObject* m_pAldeano_test;

    TTF_Font* gFont;
private:

    //variable temporal, más avanzado en el diseño, la deberiamos mover a otra clase.
    //Yo pense en hacer la clase Player referente al jugador físico, a la persona.
    //GameObject* m_pAldeano_test; // será un Unit,

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
			if ((!obj1) || (!obj2))
				return true;

			int obj1_value = obj1->m_mapPosition2.m_x + obj1->m_mapPosition2.m_y;
			int obj2_value = obj2->m_mapPosition2.m_x + obj2->m_mapPosition2.m_y;

			if ( obj1_value < obj2_value)
				return true;

			if (obj1_value > obj2_value)
				return false;

			if (obj1_value == obj2_value)
			{
				if (obj1->m_mapPosition2.m_y <= obj2->m_mapPosition2.m_y)
					return false;
				else
					return true;
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
