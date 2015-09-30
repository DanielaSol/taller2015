/*
 * TextureManager.cpp
 *
 *  Created on: 05/09/2015
 *      Author: facundo
 */

#include "TextureManager.h"
#include <string>
#include "Logger.h"

using namespace std;
TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if(pTempSurface == 0)
	{
		//acá hay que acomodar bien el nombre para ir a las imágenes por defecto (daniela)
		std::string  nombre= "no-"+fileName;
		pTempSurface = IMG_Load(nombre.c_str());
		LOG("NO SE ENCONTRO LA IMAGEN "+fileName+", SE CARGARA UNA IMAGEN POR DEFECTO");
		//return false; //en realidad cuando cargue la imagen por defecto, esto ya no importaria el return creo (daniela)
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

