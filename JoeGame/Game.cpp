//
//  Game.cpp
//  JoeGame
//
//  Created by Guilherme Bittencourt de Borba on 11/22/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include "Game.h"

Game::Game(){};

void Game::update(int mouseInputs[], int keyInputs[]){
    levels.at(currentLevel).update(mouseInputs, keyInputs);
}
void Game::draw(RenderWindow* window){
    levels.at(currentLevel).draw(window);
}
void Game::addLevel(Level* _level){
    levels.push_back(*_level);
}
void Game::setCurrentLevel(int _level){
    currentLevel = _level;
}
int Game::getCurrentLevel(){
    return currentLevel;
}

