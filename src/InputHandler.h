/*
 * InputHandler.h
 *
 *  Created on: Sep 7, 2015
 *      Author: gonzalo
 */

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <vector>

#include <SDL2/SDL.h>
#include "Vector2D.h"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:

	//Singleton
    static InputHandler* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new InputHandler();
        }

        return s_pInstance;
    }

    void reset();

    // update and clean the input handler
    void update();
    void clean();

    // keyboard events
    bool isKeyDown(SDL_Scancode key) const;

    // mouse events
    bool getMouseButtonState(int buttonNumber) const;
    Vector2D* getMousePosition() const;

private:

    InputHandler(); // Singleton
    ~InputHandler();

    InputHandler(const InputHandler&);
	InputHandler& operator=(const InputHandler&);

    // private functions to handle different event types

    // handle keyboard events
    void onKeyDown();
    void onKeyUp();

    // handle mouse events
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);

    // keyboard specific
    const Uint8* m_keystates;

    // mouse specific
    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;

    // Singleton
    static InputHandler* s_pInstance;
};
typedef InputHandler TheInputHandler;

#endif /* INPUTHANDLER_H_ */
