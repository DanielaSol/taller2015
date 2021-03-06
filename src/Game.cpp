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
#include "Objetos/Construcciones/Molino.h"
#include "Objetos/Arbolit.h"
#include "Objetos/Construcciones/Castillo.h"
#include "Objetos/Suelo.h"
#include "ObjectFactory.h"
#include "Pantalla/Barra.h"
#include "SDL2/SDL_ttf.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;


Game* Game::s_pInstance = 0;



Game::Game():
m_pWindow(0),
m_pRenderer(0),
m_bRunning(false),
m_bQuiting(false)
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

	if( TTF_Init() == -1 )
	{	printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;

	}

	//Open the font
	gFont = TTF_OpenFont( "files/fontArial.ttf", 14 );
	if( gFont == NULL ) {
		printf( "No se pudo cargar la fuente! SDL_ttf Error: %s\n", TTF_GetError() );
	}

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

				arch= fopen("log.txt","a+");
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
    m_pMap = new Map();
    m_pMap->load();

    //////////////////////////////////////////////////////////
    // PROVISORIO, RECURSOS


    GameObject* recurso = TheObjectFactory::Instance()->crear("madera", 14, 11);
    cargarRecurso(recurso);
    GameObject* recurso2 = TheObjectFactory::Instance()->crear("oro", 20, 11);
    cargarRecurso(recurso2);
    GameObject* recurso3 = TheObjectFactory::Instance()->crear("comida", 21, 22);
    cargarRecurso(recurso3);

   ////////////////////////////////////////////////////////////

   m_pPantalla = new Pantalla(m_gameWidth,m_gameHeight);
   m_pPantalla->init(m_pRenderer);
   m_pBarra = new Barra();

   //TENGO QUE ARREGLAR ESTO
   m_gameWidth = m_pPantalla->sectores.at("mapa").w;
   m_gameHeight = m_pPantalla->sectores.at("mapa").h;


   /////////////////////////////////////////////////////////////


	Vector2D* vec = new Vector2D(0,0);
	generateRandomPosition(vec);
	int randX = (int)vec->getX();
	int randY = (int)vec->getY();
	//vec->setX(TheParser::Instance()->configGame.protagonista.x);
	//vec->setY(TheParser::Instance()->configGame.protagonista.y);
	vec->toIsometric();

	m_pAldeano_test = new Unit();
	m_pAldeano_test->load(vec->getX(),
						vec->getY(),
						125, 168, 		 //125 y 168 son el ancho y alto de la imagen a cortar
						40,	54.76f,			// 40 y 54.76 son el ancho y alto de la imagen a dibujar
						5, "animate",true);   // y el 5 corresponde a la cantidad de Frames
	m_pAldeano_test->m_mapPosition2.setX(randX);
	m_pAldeano_test->m_mapPosition2.setY(randY);
	delete vec;

	Vector2D* vec2 = new Vector2D(0,0);
	vec2->setX(9);
	vec2->setY(2);
	vec2->toIsometric();
	GameObject* anotherUnit = new Unit();
	anotherUnit->load(vec2->getX(),
						vec2->getY(),
						125, 168, 		 //125 y 168 son el ancho y alto de la imagen a cortar
						40,	54.76f,			// 40 y 54.76 son el ancho y alto de la imagen a dibujar
						5, "animate",true);   // y el 5 corresponde a la cantidad de Frames
	anotherUnit->m_mapPosition2.setX(9);
	anotherUnit->m_mapPosition2.setY(2);
	delete vec2;


   for(uint i =0; i< TheParser::Instance()->configGame.escenario.entidades.size();i++){
		GameObject* objetoACargar = TheObjectFactory::Instance()->crear(
											TheParser::Instance()->configGame.escenario.entidades[i].tipo,
											TheParser::Instance()->configGame.escenario.entidades[i].x,
											TheParser::Instance()->configGame.escenario.entidades[i].y);
		cargarEntidadd(objetoACargar);
   }
   	entidades.push_back(anotherUnit);
   	entidades.push_back(m_pAldeano_test);

   	TheCamera::Instance()->centerAt(m_pAldeano_test->getScreenPosition());
   	m_pAldeano_test->m_isClicked = true;


   return true;

}

void Game::generateRandomPosition(Vector2D* placeholder)
{
    srand(time(NULL));
    bool positionGenerated = false;
    int randX;
	int randY;
	while (positionGenerated == false)
	{
		randX = rand() % 100;
		randY = rand() % 100;
		if (TheGame::Instance()->isTileAvailable(randX, randY))
			positionGenerated = true;
	}
	placeholder->setX(randX);
	placeholder->setY(randY);
}




void Game::render()
{
	if (m_bQuiting)
		return;
	agregarEntidadesAcumuladas();
	SDL_RenderClear(m_pRenderer);

	m_pPantalla->draw(m_pRenderer,m_pMap,entidades);

}

void Game::update()
{
	if (m_bQuiting)
		return;
	TheCamera::Instance()->update();
		//m_pGameStateMachine->update();
	//sort(entidades.begin(), entidades.end(), CompareGameObject());
	 for (uint i=0;i<entidades.size();i++){
	    	if (entidades[i])
	    		entidades[i]->update();
	}

	if (entidades.size() > 1)
		sort(entidades.begin(), entidades.end(), CompareGameObject());

	//m_pAldeano_test->update();
	m_pMap->update();


	generateRandomRecurso();
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
	 for (uint i=0;i<entidades.size();i++){
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
    m_pPantalla->clean();
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
    delete m_pBarra;

    TheTextureManager::Instance()->clearTextureMap();

	TTF_CloseFont( gFont );
	gFont = NULL;

    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
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
					else{m_pMap->setValue(i,j,0);
					entidades.push_back(entidad);
					}
			}
		}
}

/////////////////// RECURSOS ////////////////////////////

void Game::cargarRecurso(GameObject* entidad){

	for(int i=entidad->m_mapPosition2.getX();i<entidad->m_mapPosition2.getX() + entidad->getAncho();i++){
				for(int j=entidad->m_mapPosition2.getY();j<entidad->m_mapPosition2.getY()+ entidad->getAlto();j++){
					if(m_pMap->getValue(i,j) == 0)
						{
							LOG("TILE OCUPADO, NO ES POSIBLE UBICAR");
							return;
						}
					else{
						m_pMap->setValue(i,j,3);
						entidadesAAgregar.push_back(entidad);
					}
			}
	}


}

void Game::tomarRecurso(int x, int y) {

	int cont = 0;
	for (GameObject* entidad : entidades){
		if (entidad){
			Vector2D vector = entidad->m_mapPosition2;
			if ((vector.m_x == x) && (vector.m_y == y) && entidad->recurso){
				if (entidad){
					m_pBarra->addRecurso(entidad->name.c_str(),entidad->cantidad);
					//cout << "voy a eliminar un: " << entidades[cont]->name << endl;
					entidades.erase(entidades.begin()+ cont);
					m_pMap->m_mapGrid[x][y] = 1;
					m_pMap->m_mapGrid2[x][y] = 1;
					//cuando elimino una entidad del vector, tengo que restar 1 al contador
					cont -=1;

				}
			}
		}
		cont ++;

	}

}


void Game::agregarEntidadesAcumuladas()
{

	 for (uint i=0;i<entidadesAAgregar.size();i++){
		 if (entidadesAAgregar[i])
		 {
				entidades.push_back(entidadesAAgregar.back());
				entidadesAAgregar.pop_back();
		 }
	}
}


void Game::generateRandomRecurso() {

	//srand(time(NULL));
	int randomX = rand() % 5000  ;
	int randomY;
	int randomItem;
	if (randomX < 100){
		randomY = rand() % 5000 ;
		if (randomY < 100){
			randomItem = (rand() % 3) + 1;
			cout <<"random: "<<  randomX << " " << randomY << " item: " << randomItem<< endl;
			switch (randomItem) {
				case 1: {
					GameObject* recurso = TheObjectFactory::Instance()->crear("madera", randomX, randomY);
					cargarRecurso(recurso);
					break;
				}
				case 2: {
					GameObject* recurso2 = TheObjectFactory::Instance()->crear("oro", randomX, randomY);
					cargarRecurso(recurso2);
					break;
				}
				case 3: {
					 GameObject* recurso3 = TheObjectFactory::Instance()->crear("comida", randomX, randomY);
					 cargarRecurso(recurso3);
					 break;
				}

			}
		}
	}
}


/////////////////// FIN RECURSOS ///////////////////////////////


/////////////////////////////////////////////////////////////////

void Game::restart() //Con R
{
	m_bQuiting = true;
	//LIMPIA EL ESTADO DEL JUEGO

   m_pAldeano_test->clean();
   m_pMap->clean();
   m_pPantalla->clean();
   m_pBarra->clean();
   for(uint i=0;i < entidades.size() ;i++){
	   if (entidades[i])
	   {
			entidades[i]->clean();
			delete entidades[i];
	   }
	}
	entidades.clear();

	//delete m_pAldeano_test;
	delete m_pMap;
	delete m_pPantalla;
	delete m_pBarra;
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);


	TheTextureManager::Instance()->clearTextureMap();
	TheParser::Instance()->reset();

	//Reinicializa el juego
	init("TP of Empires", 400, 150, TheParser::Instance()->configGame.pantalla.ancho, TheParser::Instance()->configGame.pantalla.alto, 0);
	TheInputHandler::Instance()->reset();
	TheCamera::Instance()->reset();
	TheCamera::Instance()->centerAt(m_pAldeano_test->getScreenPosition());
	m_bQuiting = false;
}

void Game::changeMapGrid(int x, int y, int value)
{
	if ((x < 0) || (x > getMapWidth()) || (y < 0) || (y > getMapHeight()))
		return;
	m_pMap->m_mapGrid[x][y] = value;
	m_pMap->m_mapGrid2[x][y] = value;
}

void Game::declick(){
	for(uint i=0;i<entidades.size();i++){
		entidades[i]->m_isClicked = false;
	}
}

bool Game::unitVision(int x,int y){
	bool atSight=false;
	for(uint i=0;i<entidades.size();i++){
		if(entidades[i]->positionAtSight(x,y))
			atSight = true;
	}
	return atSight;
}

bool Game::isTileAvailable(int x, int y)
{
	int tileValue = m_pMap->m_mapGrid[x][y];
	if ((tileValue == 0) || (tileValue == 3))
		return false;
	return true;
}
