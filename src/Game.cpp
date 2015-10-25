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

#include "Utilitarios/Parser.h"
#include "GameObject.h"
#include "Camera.h"
#include "Pantalla/Map.h"
#include "Pantalla/Pantalla.h"
#include "Objetos/Molino.h"
#include "Objetos/Arbolit.h"
#include "Objetos/Castillo.h"
#include "Objetos/Suelo.h"

#include <algorithm>
#include <string>
#include <iostream>

using namespace std;


Game* Game::s_pInstance = 0;



Game::Game():
m_pWindow(0),
m_pRenderer(0),
m_bRunning(false),
m_bQuiting(false),
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
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

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

    if (!initGame())
    	return false;

    TheCamera::Instance()->init();

    m_bRunning = true; // everything inited successfully, start the main loop

    return true;
}



//init Game inicializa el estado del juego. Lo deberia hacer desde el archivo yaml
bool Game::initGame()
{
    //CARGA EL ALDEANO, PROBABLEMENTE SE CAMBIE DE LUGAR

	if(!TheTextureManager::Instance()->load(TheParser::Instance()->configGame.objetos.at("juana_de_arco").imagen,"animate", m_pRenderer))
		return false;

	std::vector<string> vectorTipos={"arbol","castillo","juana_de_arco","tierra","agua","molino"};
	string imgAux;
	for (string tipo: vectorTipos){
		try {
			if (!TheTextureManager::Instance()->load(TheParser::Instance()->configGame.objetos.at(tipo).imagen,tipo, m_pRenderer)){
				FILE* arch;

				time_t rawtime;
				  struct tm * timeinfo;

				  time ( &rawtime );
				  timeinfo = localtime ( &rawtime );

				  string salida = "la imagen del tipo " + tipo + " no existe, se cargará una imagen por defecto " + " - " + asctime (timeinfo);


					arch= fopen("prueba.txt","a+");
					fputs(salida.c_str(),arch);
					fclose(arch);


				if (tipo=="arbol")
					imgAux="assets/no-terrain.png";
				else if (tipo=="castillo")
					imgAux="assets/no-castillo.png";
				else if (tipo=="juana_de_arco")
					imgAux="assets/no-GoblinWalk.png";
				else if (tipo=="tierra")
					imgAux="assets/Tiles/no-tierra.png";
				else if (tipo=="agua")
					imgAux="assets/Tiles/no-agua.png";
				else if (tipo=="molino")
					imgAux="assets/no-windmill.png";

				TheTextureManager::Instance()->load(imgAux,tipo, m_pRenderer);
			}
		}

		catch (std::out_of_range& e){
			continue;
		}

	}

	Vector2D* vec = new Vector2D(0,0);
	vec->setX(TheParser::Instance()->configGame.protagonista.x);
	vec->setY(TheParser::Instance()->configGame.protagonista.y);
	vec->toIsometric();
	m_pAldeano_test = new Unit();
	m_pAldeano_test->load(vec->getX(),
						vec->getY(),
						125, 168, 		 //125 y 168 son el ancho y alto de la imagen a cortar
						40,	54.76f,			// 40 y 54.76 son el ancho y alto de la imagen a dibujar
						5, "animate",true);   // y el 5 corresponde a la cantidad de Frames
	m_pAldeano_test->m_mapPosition2.setX(TheParser::Instance()->configGame.protagonista.x);
	m_pAldeano_test->m_mapPosition2.setY(TheParser::Instance()->configGame.protagonista.y);
	delete vec;
    m_pMap = new Map();
    m_pMap->load();
    m_pPantalla = new Pantalla(m_gameWidth,m_gameHeight);

    GameObject* objetoACargar;

    for(int i =0; i< TheParser::Instance()->configGame.escenario.entidades.size();i++){

    	if(TheParser::Instance()->configGame.escenario.entidades[i].tipo == "arbol")
    	{
    		objetoACargar = new Arbolit(TheParser::Instance()->configGame.escenario.entidades[i].x,
    									TheParser::Instance()->configGame.escenario.entidades[i].y);

    	}else if(TheParser::Instance()->configGame.escenario.entidades[i].tipo == "castillo"){

    		objetoACargar = new Castillo(TheParser::Instance()->configGame.escenario.entidades[i].x,
										 TheParser::Instance()->configGame.escenario.entidades[i].y);

    	}else if(TheParser::Instance()->configGame.escenario.entidades[i].tipo == "agua"){

    		objetoACargar = new Suelo(TheParser::Instance()->configGame.escenario.entidades[i].x,
    	    						  TheParser::Instance()->configGame.escenario.entidades[i].y,"agua");


    	}else if(TheParser::Instance()->configGame.escenario.entidades[i].tipo == "tierra"){

    		objetoACargar = new Suelo(TheParser::Instance()->configGame.escenario.entidades[i].x,
    	    						  TheParser::Instance()->configGame.escenario.entidades[i].y,"tierra");

    	}else if(TheParser::Instance()->configGame.escenario.entidades[i].tipo == "molino"){

    		objetoACargar = new Molino(TheParser::Instance()->configGame.escenario.entidades[i].x,
    								   TheParser::Instance()->configGame.escenario.entidades[i].y);

    	}
    	cargarEntidadd(objetoACargar);
    }
   entidades.push_back(m_pAldeano_test);

   TheTextureManager::Instance()->load("assets/frame/frame4.png","frame", m_pRenderer);
   TheTextureManager::Instance()->load("assets/frame/minimapa.png","minimapa", m_pRenderer);
    return true;
}


void Game::render()
{
	if (m_bQuiting)
		return;

	SDL_RenderClear(m_pRenderer);
	//m_pGameStateMachine->render();// Dejo esto por si despues implementamos maquinaa finita de estados para los estados de jeugo: menu, etc
/*<<<<<<< HEAD
=======
    m_pMap->draw();
    //primero dibuja entidades, luego el personaje (siempre aparece por arriba de las cosas
    for (uint i=0;i<entidades.size();i++){
    	if (entidades[i] && (entidades[i]->m_atSight || entidades[i]->m_wasSeen))
    		entidades[i]->draw();
    }
     TheTextureManager::Instance()->drawFrame("frame",-5,-5,1148,800,TheParser::Instance()->configGame.pantalla.ancho,
        		TheParser::Instance()->configGame.pantalla.alto,1,0,m_pRenderer);
     for(int i = 0 ; i <  m_pMap->getMapSize().getX(); i++)
     	{
     		for(int j = 0 ; j < m_pMap->getMapSize().getY() ; j++)
     		{
     			if (m_pMap->getVisionMapValue(i,j) == 1 || m_pMap->getVisionMapValue(i,j) == 2)
     			{
     				Vector2D* vector = new Vector2D(0,0);
     				vector->setX(i); vector->setY(j); vector->toIsometric();
     				TheTextureManager::Instance()->drawFrame("minimapa",vector->getX()+620,vector->getY()+430,180,150,50,50,1,0,TheGame::Instance()->getRenderer());
     				delete vector;
     			}
     		}
     	}

     // m_pAldeano_test->draw();
>>>>>>> e2dc2e842129e7a4c680730c18706d7f8779c6e5*/

	m_pPantalla->draw(m_pRenderer,m_pMap,entidades);




}

void Game::update()
{
	if (m_bQuiting)
		return;
	TheCamera::Instance()->update();
		//m_pGameStateMachine->update();
	//sort(entidades.begin(), entidades.end(), CompareGameObject());
	 for (int i=0;i<entidades.size();i++){
	    	if (entidades[i])
	    		entidades[i]->update();
	}

	if (entidades.size() > 1)
		sort(entidades.begin(), entidades.end(), CompareGameObject());

	//m_pAldeano_test->update();
	m_pMap->update();
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();

    if(!m_bQuiting)
    {
        if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R))
        {
            restart();
            return;
        }
	}
    else
    {
    	return;
    }

	TheCamera::Instance()->handleInput();
	 for (int i=0;i<entidades.size();i++){
	    	if (entidades[i])
	    		entidades[i]->handleInput();
	}
	//m_pAldeano_test->handleInput();
	m_pMap->handleInput();
}

void Game::clean()
{
    cout << "cleaning game\n";

    TheInputHandler::Instance()->clean();

   // m_pGameStateMachine->clean();
   // m_pGameStateMachine = 0;
   // delete m_pGameStateMachine;
    m_pAldeano_test->clean();
    m_pMap->clean();
    for(uint i = 0; i < entidades.size(); i++){
    	if (entidades [i])
    	{
    		entidades[i]->clean();
    	}
    	delete entidades[i];
    }
    entidades.clear();

    delete m_pAldeano_test;
    delete m_pMap;
    delete m_pPantalla;

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


void Game::cargarEntidadd(GameObject* entidad){

	for(int i=entidad->m_mapPosition2.getX();i<entidad->m_mapPosition2.getX() + entidad->getAncho();i++){
				for(int j=entidad->m_mapPosition2.getY();j<entidad->m_mapPosition2.getY()+ entidad->getAlto();j++){
					if(m_pMap->getValue(i,j) == 0)
						{
							LOG("TILE OCUPADO, NO ES POSIBLE UBICAR");
							return;
						}
					else{m_pMap->setValue(i,j,0);}
			}
		}

	cantDeEntidades += 1;
	entidades.resize(cantDeEntidades);

	entidades[cantDeEntidades -1] = entidad;


}

void Game::restart() //Con R
{
	m_bQuiting = true;
	//LIMPIA EL ESTADO DEL JUEGO

   m_pAldeano_test->clean();
   m_pMap->clean();
   for(uint i=0;i < entidades.size() ;i++){
	   if (entidades[i])
	   {
			entidades[i]->clean();
			delete entidades[i];
	   }
	}
	entidades.clear();
	cantDeEntidades = 0;

	//delete m_pAldeano_test;
	delete m_pMap;
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);


	TheTextureManager::Instance()->clearTextureMap();
	TheParser::Instance()->reset();

	//Reinicializa el juego
	init("TP of Empires", 400, 150, TheParser::Instance()->configGame.pantalla.ancho, TheParser::Instance()->configGame.pantalla.alto, 0);
	TheInputHandler::Instance()->reset();
	TheCamera::Instance()->reset();
	m_bQuiting = false;
}



