//
//  Game.cpp
//  JoeGame
//
//  Created by Guilherme Bittencourt de Borba on 11/22/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include "Game.h"

Game::Game(){};

void Game::update(int mouseInputs[], int keyInputs[], Vector2f mousePos){
    levels.at(currentLevel).update(mouseInputs, keyInputs, mousePos, currentLevel);
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

void Game::drawButtons(RenderWindow* window, Vector2f mousePos, int mouseInputs[]){
    levels.at(currentLevel).drawButtons(window, mousePos, mouseInputs, currentLevel);
}

void Game::setTextures(sf::Texture *_goldTexture, sf::Texture *_enemyTexture, sf::Texture *_enemyArmTexture, sf::Texture *_enemyBulletTexture, sf::Texture *_attractorTexture, sf::Texture *_repellerTexture, sf::Texture *_crossTexture, sf::Texture *_plusTexture, sf::Texture *_plusGreyedOutTexture, sf::Texture *_attractorGreyedOut, sf::Texture *_repellerGreyedOut, sf::Texture *_attractorGemTexture, sf::Texture *_repellerGemTexture){
    for(int i = 0; i < levels.size(); i++){
        levels.at(i).setTextures(_goldTexture, _enemyTexture, _enemyArmTexture, _enemyBulletTexture, _attractorTexture, _repellerTexture, _crossTexture, _plusTexture, _plusGreyedOutTexture, _attractorGreyedOut, _repellerGreyedOut, _attractorGemTexture, _repellerGemTexture);
    }
}

