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

#include "Parser.h"
#include "GameObject.h"
#include "Camera.h"
#include "Map.h"
#include<algorithm>

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
	/*if (TheParser::Instance()->configGame.objetos.at("arbol").imagen == " "){
		TheTextureManager::Instance()->load("assets/Terrain_tileset2.png","arbol",m_pRenderer);
	}else{
		TheTextureManager::Instance()->load(TheParser::Instance()->configGame.objetos.at("arbol").imagen,"arbol",m_pRenderer);
	}
	if (TheParser::Instance()->configGame.objetos.at("castillo").imagen == " "){
		TheTextureManager::Instance()->load("assets/cubo.png","casa",m_pRenderer);
	}else{
		TheTextureManager::Instance()->load(TheParser::Instance()->configGame.objetos.at("castillo").imagen,"casa",m_pRenderer);
	}
	if (TheParser::Instance()->configGame.objetos.at("agua").imagen == " "){
		TheTextureManager::Instance()->load("assets/Tiles/No-tile.png","agua",m_pRenderer);
	}else{
	TheTextureManager::Instance()->load(TheParser::Instance()->configGame.objetos.at("agua").imagen,"agua",m_pRenderer);
	}
	if (TheParser::Instance()->configGame.objetos.at("tierra").imagen == " "){
		TheTextureManager::Instance()->load("assets/Tiles/No-tile.png","tierra",m_pRenderer);
	}else{
	TheTextureManager::Instance()->load(TheParser::Instance()->configGame.objetos.at("tierra").imagen,"tierra",m_pRenderer);
	}
	// PODRIA HACER QUE CUANDO NO ENCUANTRA UNA DE ESTAS IMAGENES CARGUE ALGUNA POR DEFECTO

*/
	std::vector<string> vectorTipos={"arbol","castillo","juana_de_arco","tierra","agua"};

	for (string tipo: vectorTipos){

		TheTextureManager::Instance()->load(TheParser::Instance()->configGame.objetos.at(tipo).imagen,tipo, m_pRenderer);


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
						5, "animate");   // y el 5 corresponde a la cantidad de Frames
	delete vec;
    m_pMap = new Map();
    m_pMap->load();


    //Estos datos 'hardcodeados' se deben ingresar por el archivo yaml (posicion en el mapa,
    // y string que indique que es, una ves que se sabe el string, es decir el nombre del objeto
    //se puede averiguar cual es el alto y ancho de la imagen fuente y destino y tambien a que frame
    // y row pertenece asi como el offset con el cual se lo debe dibujar)

    for(int i =0; i< TheParser::Instance()->configGame.escenario.entidades.size();i++){

    	if(TheParser::Instance()->configGame.escenario.entidades[i].tipo == "arbol")
    	{
    		cargarEntidad(TheParser::Instance()->configGame.escenario.entidades[i].x,
    					  TheParser::Instance()->configGame.escenario.entidades[i].y,
    					  65,128,65,128,1,8,2,0,128,TheParser::Instance()->configGame.objetos.at("arbol").ancho,
    					  TheParser::Instance()->configGame.objetos.at("arbol").alto,"arbol");

    	}else if(TheParser::Instance()->configGame.escenario.entidades[i].tipo == "castillo"){
    		cargarEntidad(TheParser::Instance()->configGame.escenario.entidades[i].x,
    		    		  TheParser::Instance()->configGame.escenario.entidades[i].y,
    		    		  192,224,130,151.66f,1,1,0,130/4,151,TheParser::Instance()->configGame.objetos.at("castillo").ancho,
    		    		  TheParser::Instance()->configGame.objetos.at("castillo").alto,"castillo");

    	}else if(TheParser::Instance()->configGame.escenario.entidades[i].tipo == "agua"){
    		cargarEntidad(TheParser::Instance()->configGame.escenario.entidades[i].x,
    		    		  TheParser::Instance()->configGame.escenario.entidades[i].y,
    		    		   64,32,64,32,1,1,0,0,0,TheParser::Instance()->configGame.objetos.at("agua").ancho,
    		    		   TheParser::Instance()->configGame.objetos.at("agua").alto,"agua");

    	}else if(TheParser::Instance()->configGame.escenario.entidades[i].tipo == "tierra"){
    		cargarEntidad(TheParser::Instance()->configGame.escenario.entidades[i].x,
    		    		  TheParser::Instance()->configGame.escenario.entidades[i].y,
    		    		   64,32,64,32,1,1,0,0,0,TheParser::Instance()->configGame.objetos.at("tierra").ancho,
    		    		   TheParser::Instance()->configGame.objetos.at("tierra").alto,"tierra");
    	}

    }
   entidades.push_back(m_pAldeano_test);

    return true;
}


void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	//m_pGameStateMachine->render();// Dejo esto por si despues implementamos maquinaa finita de estados para los estados de jeugo: menu, etc
    m_pMap->draw();
    //primero dibuja entidades, luego el personaje (siempre aparece por arriba de las cosas
    for (uint i=0;i<entidades.size();i++){
    	if (entidades[i])
    		entidades[i]->draw();
    }
   // m_pAldeano_test->draw();

    SDL_RenderPresent(m_pRenderer);

}

void Game::update()
{
	TheCamera::Instance()->update();
		//m_pGameStateMachine->update();

	//if (!entidades.empty())
		//sort(entidades.begin(), entidades.end(), CompareGameObject());
	m_pAldeano_test->update();
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
				int destHeight,int numFrames,int row,int frame,int offsetX,int offsetY,
				int longBase,int longAlt,std::string nombre)
{
	for(int i=posx;i<posx +longBase;i++){
			for(int j=posy;j<posy+longAlt;j++){
				if(m_pMap->getValue(i,j) == 0)
					{
						LOG("TILE OCUPADO, NO ES POSIBLE UBICAR");
						return;
					}
				else{m_pMap->setValue(i,j,0);}
		}
	}

	//cantDeEntidades += 1;
	//entidades.resize(cantDeEntidades);
	//rposx += 1;posy +=1; //por alguna razon esta corrida un espacio (chequear)
	float possx = posx * TILE_WIDTH/2;
	float possy = posy * TILE_HEIGHT;
	Vector2D* vec = new Vector2D(0,0);
	vec->setX(possx);
	vec->setY(possy);
	vec->toIsometric();
	// Cuando cargo la imagen, en la posicion y le resto la mitad de la altura para que dibuje desde abajo del sprite

	GameObject* temp = new GameObject();
	temp->load(vec->getX(),vec->getY(),width,height,destWidth,destHeight,numFrames,nombre);
	temp->setRow(row);
	temp->m_mapPosition2.setX(posx);
	temp->m_mapPosition2.setY(posy);
	temp->setFrame(frame);
	temp->setOffset(offsetX,offsetY);
	entidades.push_back(temp);
	/*entidades[cantDeEntidades -1] = new GameObject();
	entidades[cantDeEntidades -1]->load(vec->getX(),vec->getY(),width,height,destWidth,destHeight,numFrames,nombre);
	entidades[cantDeEntidades -1]->setRow(row);
	entidades[cantDeEntidades -1]->m_mapPosition2.setX(posx);
	entidades[cantDeEntidades -1]->m_mapPosition2.setY(posy);
	entidades[cantDeEntidades -1]->setFrame(frame);
	entidades[cantDeEntidades -1]->setOffset(offsetX,offsetY);*/

	delete vec;
}

void Game::restart() //Con Q
{
	m_bQuiting = true;
	//LIMPIA EL ESTADO DEL JUEGO

   m_pAldeano_test->clean();
   m_pMap->clean();
   for(int i=0;i < entidades.size() ;i++){
	   if (entidades[i])
	   {
			entidades[i]->clean();
			delete entidades[i];
	   }
	}
	entidades.clear();

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



