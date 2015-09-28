/*
 * GameObject.h
 *
 *  Created on: Sep 7, 2015
 *      Author: gonzalo
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Vector2D.h"
#include <string>

//Clase base de los elementos del juego - VENDRIAN A SER TODAS LAS ENTIDADES MENOS LAS DE TERRENO: AGUA, TIERRA

class GameObject
{
public:

    GameObject() :  m_bSelected(false),
    				m_screenPosition(0,0),
                    m_width(0),
                    m_height(0),
                    m_currentRow(0),
                    m_currentFrame(0),
					m_numFrames(0),
                    m_bUpdating(false)/*,
                    m_angle(0),
                    m_alpha(255)*/
    {
    }

	virtual ~GameObject() {}

	virtual void load(int x, int y, int width, int height,int destWidth, int destHeight, int numFrames, std::string textureID);

	virtual void draw();

	virtual void update();

	virtual void handleInput();

	virtual void clean();

	virtual void setRow(int row);

	virtual void setFrame(int frame);

	virtual void setOffset(int x, int y);

	// aumenta el frame a animar
	virtual void aumentarFrame();

	Vector2D& getMapPosition() { return m_screenPosition; }
	Vector2D& getScreenPosition() { return m_screenPosition; }


	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

    // is the object currently being updated?
    bool updating() { return m_bUpdating; }

    bool getSelected() {return m_bSelected; }

    // set whether to update the object or not
    void setUpdating(bool updating) { m_bUpdating = updating; }

    void setSelected(bool selected) { m_bSelected = selected; }

    Vector2D m_mapPosition;

    Vector2D m_mapPosition2;

    bool operator< (const GameObject &obj2);

protected:

    // "Age" Variables
    bool m_bSelected;

    // movement variables
    Vector2D m_screenPosition;

    // size variables
    int m_width;
    int m_height;

    // destiny size
    int m_destWidth;
    int m_destHeight;

    // punto desde donde se dibuja
    int offsetX;
    int offsetY;

    // animation variables
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;

    std::string m_textureID;

    // common boolean variables
    bool m_bUpdating;
/*
    // rotation
    double m_angle;

    // blending
    int m_alpha;*/

};

#endif /* GAMEOBJECT_H_ */