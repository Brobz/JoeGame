//
//  Bullet.cpp
//  JoeGame
//
//  Created by Adrian Mancilla on 11/8/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>

#include "Bullet.h"
#include "Magnet.h"
#include "Player.h"

Bullet::Bullet(){};

Bullet::Bullet(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _damage, bool _isPlayer) : Object(_mass, _type, _size, _position, texture){
    damage = _damage;
    isDestroyed = false;
    isPlayer = _isPlayer;
    if(!isPlayer)
        type.at(1) = 0;
}

void Bullet::update(vector<Object> &objectcol, Player* playercol, vector<Enemy> &enemycol, vector<Magnet> &magnetCol, vector<Resource> &resourceCol, vector<Loot> &_loots){
    // Add gravity force
    addForce(Vector2f(0, GRAVITY * mass), 0);
    // Add acceleration to velocity
    velocity += acceleration;
    // Reset acceleration
    acceleration = Vector2f();
    // Add velocity to position on the x axis
    position += velocity;
    sprite.setPosition(position);
    for(int i = 0; i < objectcol.size(); i++){
        if(collidesWith(objectcol.at(i))){
            Destroy();
        }
    }
    
    for(int i = 0; i < magnetCol.size(); i++){
        if(collidesWith(magnetCol.at(i))){
            DealDamage(magnetCol.at(i), damage);
            Destroy();
            return;
        }
    }

    if(!isPlayer){
        if(collidesWith(*playercol)){
            DealDamage(*playercol, damage);
            Destroy();
            return;
        }

    }else{
        for(int i = 0; i < enemycol.size(); i++){
            if(collidesWith(enemycol.at(i))){
                DealDamage(enemycol.at(i), damage);
                Destroy();
                return;
            }
        }
        for(int i = 0; i < resourceCol.size(); i++){
            if(collidesWith(resourceCol.at(i))){
                DealDamage(resourceCol.at(i), damage, _loots);
                Destroy();
                return;
            }
        }
    }
    
}


void Bullet::DealDamage(Entity &other, int _damage){
    other.recieveDamage(_damage);
}

void Bullet::DealDamage(Resource &other, int _damage, vector<Loot> &_loots){
    other.recieveDamage(_damage, _loots);
}

bool Bullet::collidesWith(Object &other){
    center = Vector2f(getPosition().x + getSize().x / 2.0 , getPosition().y + getSize().y / 2.0);
    Rect<float> otherBounds = other.getSprite()->getGlobalBounds();
    
    if(center.x > otherBounds.left && center.x < otherBounds.left + otherBounds.width && center.y > otherBounds.top && center.y < otherBounds.top + otherBounds.height){
        return true;
    }
    
    return false;
}

