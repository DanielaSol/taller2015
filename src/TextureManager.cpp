/*
 * TextureManager.cpp
 *
 *  Created on: 05/09/2015
 *      Author: facundo
 */

#include "TextureManager.h"
#include <string>
#include "Utilitarios/Logger.h"
#include "Game.h"

using namespace std;
TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if(pTempSurface == 0)
	{
		LOG("NO SE ENCONTRO LA IMAGEN "+fileName+", SE CARGARA UNA IMAGEN POR DEFECTO");
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	// everything went ok, add the texture to our list
	if(pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}
	//something went wrong
	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height,
						SDL_Renderer* pRenderer,SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);

}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height,
							int destWidth, int destHeight, int currentRow, int currentFrame,
							SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = width;
	srcRect.h = height;
	destRect.w = destWidth;
	destRect.h = destHeight;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::clearTextureMap()
{
    m_textureMap.clear();
}


void TextureManager::clearFromTextureMap(std::string id)
{
	m_textureMap.erase(id);


}

void TextureManager::drawArea(std::string id, SDL_Rect sector ,SDL_Renderer* m_pRenderer) {

	SDL_RenderSetViewport( m_pRenderer, &sector );
	SDL_Texture* gTexture= TheTextureManager::Instance()->getTextureMap().at(id);
	SDL_RenderCopy( m_pRenderer, gTexture, NULL, NULL );

}

void TextureManager::drawText(std::string text, SDL_Color color, SDL_Rect sector ,SDL_Renderer* m_pRenderer) {

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( TheGame::Instance()->gFont,text.c_str(), color );
	if( textSurface == NULL ){
		printf( "No se pudo cargar el texto! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else {
		//Create texture from surface pixels

		SDL_Texture*  mTexture = SDL_CreateTextureFromSurface( m_pRenderer, textSurface );
		if( mTexture == NULL ){
			printf( "No se pudo crear la textura del texto! SDL Error: %s\n", SDL_GetError() );
		}
		else{
			//Get image dimensions
			sector.w = textSurface->w;
			sector.h = textSurface->h;

			SDL_RenderCopyEx( m_pRenderer, mTexture, NULL, &sector, 0, 0, SDL_FLIP_NONE);


		}
		SDL_FreeSurface( textSurface );
		SDL_DestroyTexture(mTexture);

	}


}

