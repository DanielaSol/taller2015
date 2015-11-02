#include "Unit.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Utilitarios/Parser.h"
#include "Game.h"
#include "Camera.h"

#include <iostream>
#include <math.h>

#include "Astar/MapSearchNode.h"
#include "Astar/stlastar.h"

using namespace std;

Unit::Unit(): GameObject(),
m_velocity(TheParser::Instance()->configGame.configuracion.vel_personaje,
			TheParser::Instance()->configGame.configuracion.vel_personaje),
m_direction(0,0),
m_bChangingDestination(false),
m_bMoving(false),
m_vision(3)
{
}

void Unit::load(int x, int y, int width, int height,int destWidth, int destHeight, int numFrames, std::string textureID,bool visibility)
{
    GameObject::load(x, y, width, height, destWidth, destHeight, numFrames, textureID,visibility);
	m_mapPosition.setX(m_screenPosition.getX() - TheGame::Instance()->TILE_WIDTH/2);
	m_mapPosition.setY(m_screenPosition.getY() - TheGame::Instance()->TILE_HEIGHT/2);
	m_mapPosition.screenToWorld();

	m_lastMapPosition.setX(m_mapPosition.getX());
	m_lastMapPosition.setY(m_mapPosition.getY());
	TheGame::Instance()->changeMapGrid(m_lastMapPosition.getX(), m_lastMapPosition.getY(), 0);

	TheCamera::Instance()->centerAt(m_screenPosition);
    //
	//m_destination.setX(m_screenPosition.getX());
	//m_destination.setY(m_screenPosition.getY());
}

void Unit::draw()
{
	// Esta funcion en realidad deberia estar implementada en gameObject ya que todos los personajes
	// van a tener la misma funcionalidad para moverse.

	if (m_bMoving)
	{
		aumentarFrame();
		checkSpriteDirection();
	}
	TheTextureManager::Instance()->drawFrame(m_textureID, m_screenPosition.getX() - TheCamera::Instance()->offsetX - m_destWidth/2,
												m_screenPosition.getY()  - TheCamera::Instance()->offsetY - m_destHeight/1.5f,
												m_width, m_height,m_destWidth,m_destHeight, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());

}

void Unit::update(){


	//GameObject::update();
	//Si no se encuentra donde en la direccion destino asignada, se dirige hacia allá
	if (m_bMoving)
	{
		if (((m_mapPosition.getX() != m_destination.getX()) || (m_mapPosition.getY() != m_destination.getY())))
		{
			//actualiza la ultima posicion
			m_lastMapPosition.setX(m_mapPosition.getX());
			m_lastMapPosition.setY(m_mapPosition.getY());

			//se mueve hacia el destino
			moveTo(m_destination);

		}
		else
		{
			//ocupa la nueva posicion y desocupa la ultima
			occupyTile(m_mapPosition);

			//agarra la solucion siguiente
			m_node = astarsearch.GetSolutionNext();
			if (!m_node)
			{
				m_bMoving = false;
				astarsearch.FreeSolutionNodes();
				//astarsearch.EnsureMemoryFreed();
				return;
			}
			m_destination.setX(m_node->x);
			m_destination.setY(m_node->y);
			//cout << "Next node = ( " << (int) m_node->x << " , " << (int)m_node->y << " ) \n";

		}
	}
	else
	{
		m_bMoving = false;
	}

	int tileValue1 = TheGame::Instance()->m_pMap->m_mapGrid[m_mapPosition.getX()][m_mapPosition.getY()];
	/*int tileValue2 = TheGame::Instance()->m_pMap->m_mapGrid[m_mapPosition.getX()+1][m_mapPosition.getY()];
	int tileValue3 = TheGame::Instance()->m_pMap->m_mapGrid[m_mapPosition.getX()+1][m_mapPosition.getY()+1];
	int tileValue4 = TheGame::Instance()->m_pMap->m_mapGrid[m_mapPosition.getX()][m_mapPosition.getY()+1];
	int tileValue5 = TheGame::Instance()->m_pMap->m_mapGrid[m_mapPosition.getX()-1][m_mapPosition.getY()];
	int tileValue6 = TheGame::Instance()->m_pMap->m_mapGrid[m_mapPosition.getX()-1][m_mapPosition.getY()-1];
	int tileValue7 = TheGame::Instance()->m_pMap->m_mapGrid[m_mapPosition.getX()][m_mapPosition.getY()-1];*/

	if ( TheGame::Instance()->m_pMap->m_pTileHandler->isGetable(tileValue1))  {
		TheGame::Instance()->tomarRecurso(m_mapPosition.getX(),m_mapPosition.getY());

	}
	/*else if ( TheGame::Instance()->m_pMap->m_pTileHandler->isGetable(tileValue2))  {
		TheGame::Instance()->tomarRecurso(m_mapPosition.getX()+1,m_mapPosition.getY());
	}
	if ( TheGame::Instance()->m_pMap->m_pTileHandler->isGetable(tileValue3))  {
		TheGame::Instance()->tomarRecurso(m_mapPosition.getX()+1,m_mapPosition.getY()+1);

	}
	else if ( TheGame::Instance()->m_pMap->m_pTileHandler->isGetable(tileValue4))  {
		TheGame::Instance()->tomarRecurso(m_mapPosition.getX(),m_mapPosition.getY()+1);
	}
	if ( TheGame::Instance()->m_pMap->m_pTileHandler->isGetable(tileValue5))  {
		TheGame::Instance()->tomarRecurso(m_mapPosition.getX()-1,m_mapPosition.getY());

	}
	else if ( TheGame::Instance()->m_pMap->m_pTileHandler->isGetable(tileValue6))  {
		TheGame::Instance()->tomarRecurso(m_mapPosition.getX()-1,m_mapPosition.getY()-1);
	}
	if ( TheGame::Instance()->m_pMap->m_pTileHandler->isGetable(tileValue7))  {
		TheGame::Instance()->tomarRecurso(m_mapPosition.getX(),m_mapPosition.getY()-1);

	}*/
}

void Unit::moveTo(const Vector2D& position)
{
	//calcula posicion actual
	m_mapPosition.setX(m_screenPosition.getX() - TheGame::Instance()->TILE_WIDTH/2);
	m_mapPosition.setY(m_screenPosition.getY() - TheGame::Instance()->TILE_HEIGHT/2);
	m_mapPosition.screenToWorld();

	m_mapPosition2.setX(m_screenPosition.getX() - TheGame::Instance()->TILE_WIDTH/2);
	m_mapPosition2.setY(m_screenPosition.getY() - TheGame::Instance()->TILE_HEIGHT/2);
	m_mapPosition2.screenToWorld();

	//calcula las coordenadas en pantalla a la que debe moverse
	float x = position.m_x;
	float y = position.m_y;
	m_screenCoordDestination.setX(x);
	m_screenCoordDestination.setY(y);
	m_screenCoordDestination.worldToScreen();
	m_screenCoordDestination.m_x += 32;
	m_screenCoordDestination.m_y += 16;

	//calcula el vector direccion y lo normaliza (solo lo queremos para indicar dirección de movimiento, no velocidad)
	m_direction.setX(m_screenCoordDestination.getX() - m_screenPosition.getX());
	m_direction.setY(m_screenCoordDestination.getY() - m_screenPosition.getY());
	m_direction.normalize();

	//clamp
	float nextPositionX = m_screenPosition.m_x + (m_direction.getX() * m_velocity.getX());
	float nextPositionY = m_screenPosition.m_y + (m_direction.getY() * m_velocity.getY());
	if ((((m_screenPosition.m_x < m_screenCoordDestination.m_x) && (nextPositionX >= m_screenCoordDestination.m_x )) ||
		((m_screenPosition.m_x > m_screenCoordDestination.m_x) && (nextPositionX <= m_screenCoordDestination.m_x ))) &&
		(((m_screenPosition.m_y < m_screenCoordDestination.m_y) && (nextPositionY >= m_screenCoordDestination.m_y )) ||
		((m_screenPosition.m_y > m_screenCoordDestination.m_y) && (nextPositionY <= m_screenCoordDestination.m_y ))))
	{
		m_screenPosition.m_x = m_screenCoordDestination.m_x;
		m_screenPosition.m_y = m_screenCoordDestination.m_y;
	}
	else
	{
		//mueve al personaje
		m_screenPosition.m_x += (m_direction.getX() * m_velocity.getX());
		m_screenPosition.m_y += (m_direction.getY() * m_velocity.getY());
	}

}


void Unit::handleInput()
{
	// deberia checkear tambien si la unidad está seleccionada. La variable isSelected la puse en GameObject, ya que consideré que
	// se puede apretar en cualquier objeto, como en el age.

	if (TheInputHandler::Instance()->getMouseButtonState(RIGHT))
	{
		if (!m_bChangingDestination)
		{
			//El click no puede darse fuera del panel del mapa, se pueden poner funcionalidades del menú
			SDL_Rect sector = TheGame::Instance()->m_pPantalla->sectores.at("mapa");
			if ((TheInputHandler::Instance()->getMousePosition()->getY() >= sector.y + sector.h ) ||
				(TheInputHandler::Instance()->getMousePosition()->getY() <= sector.y  )){
				return;
			}


			float backUpCartesianX = m_destination.getX();
			float backUpCartesianY = m_destination.getY();

			//Calcula la coordenada a moverse en coordenadas cartesianas de mapa
			float coordX = (TheInputHandler::Instance()->getMousePosition()->getX() + TheCamera::Instance()->offsetX) - (TheGame::Instance()->TILE_WIDTH/2);
			float coordY = (TheInputHandler::Instance()->getMousePosition()->getY() + TheCamera::Instance()->offsetY) - (TheGame::Instance()->TILE_HEIGHT/2);

			//vector para que guarda temporalmente la posicion a donde se quiere mover el jugador
			Vector2D* goalDestination = new Vector2D();

			goalDestination->setX(coordX);
			goalDestination->setY(coordY);
			goalDestination->screenToWorld();
			goalDestination->m_x-=1;
			goalDestination->m_y-=1;

			cout << "Tile clicked = ( " << (int) goalDestination->m_x << " , " << (int)goalDestination->m_y << " ) \n";
			//cout << "Screen pos clicked = ( " << (int) coordX << " , " << (int)coordY << " ) \n";

			if (((m_mapPosition.getX() == goalDestination->getX()) && (m_mapPosition.getY() == goalDestination->getY())))
				return;

			//analiza que no se cliquee fuera de los bordes
			if ((goalDestination->getX() >= TheGame::Instance()->getMapWidth()) ||
					(goalDestination->getY() >= TheGame::Instance()->getMapHeight())||
					(goalDestination->getX() < 0) ||
					(goalDestination->getY() < 0))

			{
				//revierte en caso positivo
				m_bChangingDestination = false;
				m_destination.setX(backUpCartesianX);
				m_destination.setY(backUpCartesianY);
				if (goalDestination)
					delete goalDestination;

				return;
			}
			//Si pasa las condiciones, calcula el path
			m_bChangingDestination = true;
			bool pathFound = calculatePath(*goalDestination);
			delete goalDestination;
			//si encuentra camino setea el comienzo del movimiento
			if (pathFound)
			{
				m_node = astarsearch.GetSolutionStart();
				if (!m_node)
				{
					m_bMoving = false;
					astarsearch.FreeSolutionNodes();
					//astarsearch.EnsureMemoryFreed();
					return;
				}
				//cout << "First node = ( " << (int) m_node->x << " , " << (int)m_node->y << " ) \n";
				m_destination.setX(m_node->x);
				m_destination.setY(m_node->y);
			}
			m_bMoving = pathFound;
		}
	}
	else
	{
		m_bChangingDestination = false;
	}
}

void Unit::clean(){

	//nada especial
    GameObject::clean();
}

void Unit::aumentarFrame(){

	m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));

	/*m_currentFrame += 1;

	if(m_currentFrame > m_numFrames)
	{
		m_currentFrame = 1;
	}*/
}

void Unit::checkSpriteDirection()
{
	//se esta moviendo y es hacia abajo
	if ((m_direction.getX() == 0) && (m_direction.getY() == 0))
		return;
	if(m_direction.getY() > 0.4f)
	{
		//abajo a la derecha
		if(m_direction.getX() > 0.4f)
		{
			m_currentRow = 8;
		}
		//abajo a la izquierda
		else if(m_direction.getX() < -0.4f)
		{
			m_currentRow = 2;
		}
		//abajo exclusivo
		else
		{
			m_currentRow = 1;
		}
	}
	//se esta moviendo y es hacia arriba
	else if(m_direction.getY() < -0.4)
	{
		//arriba a la derecha
		if(m_direction.getX() > 0.4)
		{
			m_currentRow = 6;
		}
		//arriba a la izquierda
		else if(m_direction.getX() < -0.4)
		{
			m_currentRow = 4;
		}
		//arriba exclusivo
		else
		{
			m_currentRow = 5;
		}
	}
	// se mueve hacia la izquierda o derecha exclusivamente
	else
	{
		//derecha
		if(m_direction.getX() > 0){
			m_currentRow = 7;
		}
		else
		{
			m_currentRow = 3;
		}
	}
}

bool Unit::calculatePath(Vector2D destination)
{
	//calcula posicion actual
	m_mapPosition.setX(m_screenPosition.getX() - TheGame::Instance()->TILE_WIDTH/2);
	m_mapPosition.setY(m_screenPosition.getY() - TheGame::Instance()->TILE_HEIGHT/2);
	m_mapPosition.screenToWorld();

	bool searchResult = false;

	//node donde esta parado el personaje
	MapSearchNode nodeStart;
	nodeStart.x = m_mapPosition.getX();
	nodeStart.y = m_mapPosition.getY();

	//nodo destino
	MapSearchNode nodeEnd;
	nodeEnd.x = destination.getX();
	nodeEnd.y = destination.getY();

	astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

	unsigned int SearchState;
	do
	{
		SearchState = astarsearch.SearchStep();

	} while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

	//Camino encontrado
	if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
	{
		searchResult = true;
	}
	//Camino no encontrado
	else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED )
	{
		astarsearch.FreeSolutionNodes();
		//astarsearch.EnsureMemoryFreed();
		searchResult = false;
	}
	return searchResult;
}

bool Unit::positionAtSight(int x,int y){

	bool atSight = false;
	for(int i = m_mapPosition2.getX() - m_vision; i <= m_mapPosition2.getX() + m_vision; i++)
	{
		for(int j = m_mapPosition2.getY() - m_vision; j <= m_mapPosition2.getY() + m_vision; j++)
		{
			if(i == x && j == y){atSight = true;}
		}

	}
	return atSight;

}


void Unit::occupyTile(const Vector2D& newPosition)
{
	TheGame::Instance()->changeMapGrid(m_lastMapPosition.getX(), m_lastMapPosition.getY(), 1);
	TheGame::Instance()->changeMapGrid(newPosition.m_x, newPosition.m_y, 0);

}
