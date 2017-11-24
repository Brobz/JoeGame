//
//  GUI_Button.cpp
//  JoeGame
//
//  Created by Adrian Mancilla on 11/11/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>

#include "GUI_Button.h"

GUI_Button::GUI_Button(){}

GUI_Button::GUI_Button(Vector2f _size, Vector2f _position, Texture* texture, GUI_Text _text, Texture* _hoverTexture) : GUI_Object(_size, _position, texture){
    text = _text;
    idleTexture = *texture;
    hoverTexture = *_hoverTexture;
}

void GUI_Button::draw(RenderWindow* window){
    Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    if(sprite.getGlobalBounds().contains(mousePos))
        sprite.setTexture(hoverTexture);
    else
        sprite.setTexture(idleTexture);
    
    (*window).draw(sprite);
}

bool GUI_Button::wasClicked(Vector2f mousePos){
    if(sprite.getGlobalBounds().contains(mousePos))
        return true;
    
    return false;
}
