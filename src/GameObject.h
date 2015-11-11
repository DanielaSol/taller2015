/*
 * GameObject.h
 *
 *  Created on: Sep 7, 2015
 *      Author: gonzalo
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Vector2D.h"
#include "InputHandler.h"
#include <string>

using namespace std;
//Clase base de los elementos del juego - VENDRIAN A SER TODAS LAS ENTIDADES MENOS LAS DE TERRENO: AGUA, TIERRA

class GameObject
{
public:

    GameObject() :  m_bSelected(false),
    				m_screenPosition(0,0),
                    m_width(0),
                    m_height(0),
                    m_alto(0),
                    m_ancho(0),
                    m_currentRow(0),
                    m_currentFrame(0),
					m_numFrames(0),
					m_atSight(false),
					m_wasSeen(false),
					m_isClicked(false),
                    m_bUpdating(false),/*,
                    m_angle(0),
                    m_alpha(255)*/
    				interactuable(false)


    {
    }

	virtual ~GameObject() {}

	virtual void load(int x, int y, int width, int height,int destWidth, int destHeight, int numFrames, std::string textureID, bool visibility);

	virtual void draw();

	virtual void update();

	virtual void handleInput();

	virtual void clean();

	//virtual int getFrame();

	//virtual int getRow();

	virtual int getAncho();

	virtual int getAlto();

	virtual void setAncho(int ancho);

	virtual void setAlto(int alto);

	virtual void setRow(int row);

	virtual void setFrame(int frame);

	virtual void setOffset(int x, int y);

	virtual bool positionAtSight(int x, int y);

	virtual void isClicked();

	// aumenta el frame a animar
	virtual void aumentarFrame();

	virtual void setTexture(std::string textureID);

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

    bool m_atSight;
    bool m_wasSeen;

    bool m_isClicked;

    //PROVISORIO Hay que pasarlo a protected
    bool recurso;
    string name;
    string descripcion;
    int cantidad;
    bool soyUnidad;
    bool interactuable;

    virtual void drawSelected();

protected:

    // "Age" Variables
    bool m_bSelected;

    // movement variables
    Vector2D m_screenPosition;

    // size variables
    int m_width;
    int m_height;

    // espacio que ocupa el objeto
    int m_ancho;
    int m_alto;

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
