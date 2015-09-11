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
#include "Map.h"

using namespace std;


Game* Game::s_pInstance = 0;


Game::Game():
m_pWindow(0),
m_pRenderer(0),
m_bRunning(false)
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
	m_aldeano_test = new Unit();
    m_aldeano_test->load(100, 100, 125, 168, 5, "animate");

    map = new Map();
    map->load();

    ////////////////////////////////////////////////////////////////////////////////

    m_bRunning = true; // everything inited successfully, start the main loop

    return true;
}


void Game::render()
{
    SDL_RenderClear(m_pRenderer);

	//m_pGameStateMachine->render();// Dejo esto por si despues implementamos maquinaa finita de estados para los estados de jeugo: menu, etc
    map->draw();
    m_aldeano_test->draw();

    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
		//m_pGameStateMachine->update();
	m_aldeano_test->update();

}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();

	m_aldeano_test->handleInput();

}

void Game::clean()
{
    cout << "cleaning game\n";

    TheInputHandler::Instance()->clean();

    //m_pGameStateMachine->clean();
   // m_pGameStateMachine = 0;
   // delete m_pGameStateMachine;
    m_aldeano_test->clean();
    delete m_aldeano_test;
    delete map;

    TheTextureManager::Instance()->clearTextureMap();

    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}




