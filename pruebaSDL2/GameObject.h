/*
 * GameObject.h
 *
 *  Created on: Sep 7, 2015
 *      Author: gonzalo
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Vector2D.h"
#include <vector>
#include <string>

//Clase base de los elementos del juego

class GameObject
{
public:
    // constructor with default initialisation list
    GameObject() :  m_bSelected(false),
    				m_position(0,0),
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

	// base class needs virtual destructor
	virtual ~GameObject() {}

	// load from file - int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0
	virtual void load(int x, int y, int width, int height, int numFrames, std::string textureID);

	// draw the object
	virtual void draw();

	// do update stuff
	virtual void update();

	// handle input
	virtual void handleInput();

	// remove anything that needs to be deleted
	virtual void clean();

	// getters for common variables
	Vector2D& getPosition() { return m_position; }


	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

    // is the object currently being updated?
    bool updating() { return m_bUpdating; }

    bool getSelected() {return m_bSelected; }

    // set whether to update the object or not
    void setUpdating(bool updating) { m_bUpdating = updating; }

    void setSelected(bool selected) { m_bSelected = selected; }

protected:

    // "Age" Variables
    bool m_bSelected;

    // movement variables
    Vector2D m_position;

    // size variables
    int m_width;
    int m_height;

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
