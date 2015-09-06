/*
 * Game.cpp
 *
 *  Created on: 05/09/2015
 *      Author: facundo
 */

#include <iostream>
#include "Game.h"

Game::Game(){

	m_bRunning = false;
	m_pWindow = NULL;
	m_pRenderer = NULL;
	m_currentFrame = 0;
	mousex = NULL;
	mousey = NULL;
}


bool Game::init(const char* title, int xpos, int ypos, int width,
			int height, int flags)
{
	// intento de inicializar SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		// inicializar la ventana
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if(m_pWindow != 0) // ventana iniciada exitosamente
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if(m_pRenderer != 0) // renderer iniciado exitosamente
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer,0,0,0,255);

			}else
				{
					std::cout << "renderer init fail\n";
					return false; // fallo iniciacion de render
				}
		}else
			{
				std::cout << "window init fail\n";
				return false; // fallo iniciacion de ventana
			}
	}else
		{
			std::cout << "SDL init fail\n";
			return false; // fallo inicializacion SDL
		}
	std::cout << "init success\n";

	m_bRunning = true; // t0do se inicio exitosamente, arrancar el loop

	if(!TheTextureManager::Instance()->load("assets/animate.png","animate", m_pRenderer)) return false;

	m_go.load(100, 100, 45, 48, "animate");
	m_player.load(300, 300, 45, 48, "animate");

	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer); // clear to the draw colour

	m_go.draw(m_pRenderer);
	m_player.draw(m_pRenderer);

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		   case SDL_QUIT:
			m_bRunning = false;
		   break;
		   case SDL_MOUSEMOTION:
			semovioelmouse();
		   break;
		   case SDL_MOUSEBUTTONDOWN:
			   SDL_GetMouseState(&mousex,&mousey);
			   m_go.click(mousex,mousey);
		   break;
		   default:
		   break;
		}
	}
}

void Game::update(){
	m_go.update();
	m_player.update();
}

void Game::semovioelmouse(){

	m_go.aumentarPosDer();
}
