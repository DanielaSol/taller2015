/*
 * Camera.h
 *
 *  Created on: Sep 13, 2015
 *      Author: gonzalo
 */

#include "Vector2D.h"
#include "SDL2/SDL.h"

class Camera
{
public:

    static Camera* Instance()
    {
        if(s_pCamera == 0)
        {
            s_pCamera = new Camera();
        }

        return s_pCamera;
    }

    SDL_Rect m_cameraViewport; //offsetX,offsetY en coordenadas de pantalla, width, height

    void init();
    void update();
    void handleInput();
    void clean();

    bool isVisible(int mapPosX, int mapPosY);

    void setDirection(const Vector2D& direction) { m_direction = direction; }
    void setVelocity(const Vector2D& velocity) { m_scrollSpeed = velocity; }

    const Vector2D getScrollSpeed() const {return m_scrollSpeed;}
    const Vector2D getDirection() const {return m_direction;}

    float offsetX;
    float offsetY;

private:

    Camera();
    ~Camera();

    Vector2D m_direction;
    Vector2D m_scrollSpeed;

    //determinado por yaml
    Vector2D MAX_SCROLLSPEED;
    float SLOPE_X; // pendiente de la recta para calcular la velocidad. Uso interno, pero en principio constante
    float SLOPE_Y;

    int m_scrollMargin; // margen

    //límites
    int m_boundY_top;
    int m_boundY_bot;
    int m_boundX_left;
    int m_boundX_right;

    SDL_Rect gameObjectRect; //buffer

    static Camera* s_pCamera;
};

typedef Camera TheCamera;


