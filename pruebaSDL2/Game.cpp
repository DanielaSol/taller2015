/*
 * Game.cpp
 *
 *  Created on: Sep 7, 2015
 *      Author: gonzalo
 */

#include "Game.h"
#include "Unit.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include <iostream>

#include "GameObject.h"
#include "Camera.h"
#include "Map.h"

using namespace std;


Game* Game::s_pInstance = 0;


Game::Game():
m_pWindow(0),
m_pRenderer(0),
m_bRunning(false),
cantDeEntidades(0)
{
}

Game::~Game()
{
    // para evitar memory leaks
    m_pRenderer= 0;
    m_pWindow = 0;
}


bool Game::init(const char* title, int xpos, int ypos, int width, int height, int SDL_WINDOW_flag)
{
    // store the game width and height
    m_gameWidth = width;
    m_gameHeight = height;

    // attempt to initialise SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "SDL init success\n";

        // init the window
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_flag);

        if(m_pWindow != 0) // window init success
        {
            cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);

            if(m_pRenderer != 0) // renderer init success
            {
                cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer, 0,0,0,255);
            }
            else
            {
                cout << "renderer init fail\n";
                return false; // renderer init fail
            }
        }
        else
        {
            cout << "window init fail\n";
            return false; // window init fail
        }
    }
    else
    {
        cout << "SDL init fail\n";
        return false; // SDL init fail
    }

    //CARGA EL ALDEANO, PROBABLEMENTE SE CAMBIE DE LUGAR

	if(!TheTextureManager::Instance()->load("assets/GoblinWalk.png","animate", m_pRenderer))
		return false;
	TheTextureManager::Instance()->load("assets/Terrain_tileset.png","arbol",m_pRenderer);
	TheTextureManager::Instance()->load("assets/casa3.png","casa",m_pRenderer);
	m_pAldeano_test = new Unit();
	m_pAldeano_test->load(10, 10, 125, 168, 70, 84.08, 5, "animate");

    m_pMap = new Map();
    m_pMap->load();

    //Estos datos 'hardcodeados' se deben ingresar por el archivo yaml (posicion en el mapa,
    // y string que indique que es, una ves que se sabe el string, es decir el nombre del objeto
    //se puede averiguar cual es el alto y ancho de la imagen fuente y destino y tambien a que frame
    // y row pertenece asi como el offset con el cual se lo debe dibujar)
    for (int i=0;i<5;i++){
    	for(int j=0;j<5;j++){
    		if((i+j)<5)
    		 cargarEntidad(i,j,65,128,65,128,1,8,2,0,128,"arbol");
    		else
    		{cargarEntidad(i,j,65,128,65,128,1,8,1,0,128,"arbol");}
    	}
    }

    cargarEntidad(2,9,192,224,130,151.66f,1,1,0,130/4,151,"casa");
    cargarEntidad(5,6,192,224,130,151.66f,1,1,0,130/4,151,"casa");
    cargarEntidad(5,9,192,224,130,151.66f,1,1,0,130/4,151,"casa");


    TheCamera::Instance()->init();

    ////////////////////////////////////////////////////////////////////////////////

    m_bRunning = true; // everything inited successfully, start the main loop

    return true;
}


void Game::render()
{

	SDL_RenderClear(m_pRenderer);

	//m_pGameStateMachine->render();// Dejo esto por si despues implementamos maquinaa finita de estados para los estados de jeugo: menu, etc
    m_pMap->draw();
    //primero dibuja entidades, luego el personaje (siempre aparece por arriba de las cosas
    for (int i=0;i<cantDeEntidades;i++){
    	entidades[i]->draw();
    }
    m_pAldeano_test->draw();

    SDL_RenderPresent(m_pRenderer);

}

void Game::update()
{
	TheCamera::Instance()->update();
		//m_pGameStateMachine->update();
	m_pAldeano_test->update();
	m_pMap->update();
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();

	TheCamera::Instance()->handleInput();

	m_pAldeano_test->handleInput();
	m_pMap->handleInput();
}

void Game::clean()
{
    cout << "cleaning game\n";

    TheInputHandler::Instance()->clean();

    //m_pGameStateMachine->clean();
   // m_pGameStateMachine = 0;
   // delete m_pGameStateMachine;
    m_pAldeano_test->clean();
    m_pMap->clean();
    for(int i=0;i<cantDeEntidades;i++){
    	entidades[i]->clean();
    	delete entidades[i];
    }


    delete m_pAldeano_test;
    delete m_pMap;

    TheTextureManager::Instance()->clearTextureMap();

    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

float Game::getMapWidth() const
{
	return m_pMap->getMapSize().getX();
}
float Game::getMapHeight() const
{
	return m_pMap->getMapSize().getY();
}

void Game::cargarEntidad(int posx,int posy,int width,int height,int destWidth,
				int destHeight,int numFrames,int row,int frame,int offsetX,int offsetY,std::string nombre)
{

	cantDeEntidades += 1;
	entidades.resize(cantDeEntidades);
	posx += 1;posy +=1; //por alguna razon esta corrida un espacio (chequear)
	float possx = posx * 32;
	float possy = posy * 32;
	Vector2D* vec = new Vector2D(0,0);
	vec->setX(possx);
	vec->setY(possy);
	vec->toIsometric();
	// Cuando cargo la imagen, en la posicion y le resto la mitad de la altura para que dibuje desde abajo del sprite

	entidades[cantDeEntidades -1] = new GameObject();
	entidades[cantDeEntidades -1]->load(vec->getX(),vec->getY(),width,height,destWidth,destHeight,numFrames,nombre);
	entidades[cantDeEntidades -1]->setRow(row);
	entidades[cantDeEntidades -1]->setFrame(frame);
	entidades[cantDeEntidades -1]->setOffset(offsetX,offsetY);
	delete vec;

}



