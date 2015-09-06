/*
 * Game.h
 *
 *  Created on: 05/09/2015
 *      Author: facundo
 */

#ifndef GAME_H_
#define GAME_H_

#include "Player.h"


class Game{

public:
		Game();
		~Game();
		bool init(const char* title, int xpos, int ypos, int width, int
				height, int flags);
		void render();
		void update();
		void handleEvents();
		void semovioelmouse();
		void clean();
		bool running(){ return m_bRunning;}
private:
		SDL_Window* m_pWindow;
		SDL_Renderer* m_pRenderer;
		int m_currentFrame;
		bool m_bRunning;
		GameObject m_go;
		Player m_player;
		int mousex;
		int mousey;

};



#endif /* GAME_H_ */
