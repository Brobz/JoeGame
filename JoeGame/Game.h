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
    void update(int mouseInputs[], int keyInputs[]);
    void draw(RenderWindow* window);
    void addLevel(Level* _level);
    void setCurrentLevel(int _level);
    int getCurrentLevel();
};

#endif /* Game_h */
