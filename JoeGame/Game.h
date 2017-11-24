//
//  Game.h
//  JoeGame
//
//  Created by Guilherme Bittencourt de Borba on 11/22/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Game_h
#define Game_h
#include "Level.h"

class Game{
protected:
    int currentLevel;
    vector<Level> levels;
public:
    Game();
    void setTextures(Texture* _goldTexture, Texture* _enemyTexture, Texture* _enemyArmTexture, Texture* _enemyBulletTexture, Texture* _attractorTexture, Texture* _repellerTexture, Texture*  _crossTexture, Texture* _plusTexture, Texture* _plusGreyedOutTexture,  Texture* _attractorGreyedOut, Texture* _repellerGreyedOut, Texture* _attractorGemTexture, Texture* _repellerGemTexture, Font* _font);
    void update(int mouseInputs[], int keyInputs[], Vector2f mousePos);
    void draw(RenderWindow* window);
    void addLevel(Level* _level);
    void setCurrentLevel(int _level);
    void drawButtons(RenderWindow* window, Vector2f mousePos, int mouseInputs[]);
    void drawShopText(RenderWindow* window);
    int getCurrentLevel();
    
};

#endif /* Game_h */
