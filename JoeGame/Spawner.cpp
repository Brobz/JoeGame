//
//  Spawner.cpp
//  JoeGame
//
//  Created by Guilherme Bittencourt de Borba on 11/20/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include "Spawner.h"

Spawner::Spawner(){};

Spawner::Spawner(vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, double _spawnRate) : Object::Object(1, _type, _size, _position, texture){
    
    active = false;
    spawnRate = _spawnRate;
    ticksUntillNextSpawn = spawnRate;
    canSpawn = false;
}

void Spawner::update(){
    Object::update();
    if(!active)
        return;
    ticksUntillNextSpawn--;
    if(ticksUntillNextSpawn <= 0){
        canSpawn = true;
        ticksUntillNextSpawn = spawnRate;
    }
}

bool Spawner::isActive(){
    return active;
}

void Spawner::spawned(){
    canSpawn = false;
}

void Spawner::activate(bool inverse){
    active = !inverse;
}

bool Spawner::canItSpawn(){
    return canSpawn;
}


