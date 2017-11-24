//
//  GUI_Button.h
//  JoeGame
//
//  Created by Adrian Mancilla on 11/11/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef GUI_Button_h
#define GUI_Button_h

#include "GUI_Object.h"
#include "GUI_Text.h"

class GUI_Button : public GUI_Object{

protected:
    Texture idleTexture, hoverTexture;
    int ID;
public:
    GUI_Button();
    GUI_Button(Vector2f _size, Vector2f _position, Texture* texture, Texture* _hoverSprite, int _ID);
    void draw(RenderWindow* window);
    bool wasClicked(Vector2f mousePos);
    int getID();
};

#endif /* GUI_Button_h */
