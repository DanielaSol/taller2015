/*
 * Player.cpp
 *
 *  Created on: 05/09/2015
 *      Author: facundo
 */

#include "Player.h"


void Player::load(int x, int y, int width, int height, std::string textureID)
{
	GameObject::load(x, y, width, height, textureID);
}

void Player::draw(SDL_Renderer* pRenderer)
{
	GameObject::draw(pRenderer);
}

void Player::update()
{
	m_x -= 1;
}
