/*
 * TextureManager.h
 *
 *  Created on: 05/09/2015
 *      Author: facundo
 */

#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <map>
#include <string>
#include "SDL2/SDL.h"
#include "SDL_image.h"

using namespace std;

class TextureManager
{
public:

    static TextureManager* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new TextureManager();
            return s_pInstance;
        }

        return s_pInstance;
    }

    //agrega una textura al map<,> la cual podrá ser accedida por su id
    bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

    //Funciones para eliminar Textures* del map<,>
    void clearTextureMap();
    void clearFromTextureMap(std::string id);


    void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(std::string id, int x, int y, int width, int height,int destWidth, int destHeight, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawArea(std::string id, SDL_Rect dim ,SDL_Renderer* pRenderer);
    std::map<std::string, SDL_Texture*> getTextureMap() { return m_textureMap; }

private:

    TextureManager() {}
    ~TextureManager() {}

    //sobreescribe el operador = y lo hace privado

    TextureManager(const TextureManager&);
	TextureManager& operator=(const TextureManager&);

    std::map<std::string, SDL_Texture*> m_textureMap;

    static TextureManager* s_pInstance;
};

typedef TextureManager TheTextureManager;

#endif /* TEXTUREMANAGER_H_ */
