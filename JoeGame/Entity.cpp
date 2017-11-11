//
//  Entity.cpp
//  JoeGame
//
//  Created by Juan Lizarraga on 11/4/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include "Entity.h"

Entity::Entity(){};

Entity::Entity(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp) : Object(_density, _type, _size, _position, texture){
    
    maxHp = _maxHp;
    hp = maxHp;
    isGrounded = false;
    
}

void Entity::die(){
    cout << "endl" << endl;
    Destroy();
}

void Entity::update(vector<Object> &colliders){
    // Add gravity force
    addForce(Vector2f(0, GRAVITY * mass), 0);
    // Add acceleration to velocity
    velocity += acceleration;
    // Reset acceleration
    acceleration = Vector2f();
    // Add velocity to position on the x axis
    position.x += velocity.x + selfVelocity.x;
    sprite.setPosition(position);
    // Check for collision with each of the provided objects
    for(int i = 0; i < colliders.size(); i++){
        collidesWith(colliders.at(i), 0);
    }
    // Add velocity to position on the y axis
    position.y += velocity.y + selfVelocity.y;
    sprite.setPosition(position);
    // Check for collision with each of the provided objects
    for(int i = 0; i < colliders.size(); i++){
        collidesWith(colliders.at(i), 1);
    }
    
    if (velocity.y != 0)
        isGrounded = false;
    
    if(hp <= 0)
        die();
}

bool Entity::collidesWith(Object &other, int axis){
    Rect<float> ownBounds = sprite.getGlobalBounds();
    Rect<float> otherBounds = other.getSprite()->getGlobalBounds();
    
    if(ownBounds.left + ownBounds.width > otherBounds.left)
        if(ownBounds.left < otherBounds.left + otherBounds.width)
            if(ownBounds.top + ownBounds.height > otherBounds.top)
                if(ownBounds.top < otherBounds.top + otherBounds.height){
                    underlap(otherBounds, axis);
                    //underlap(other, axis);
                    return true;
                }
    
    return false;
}

void Entity::underlap(Rect<float> &otherBounds, int axis){
    if(!axis){
        if((velocity.x + selfVelocity.x) > 0 ){
            position.x -= position.x + size.x - otherBounds.left;
        }
        
        if((velocity.x + selfVelocity.x) < 0 ){
            position.x += otherBounds.left + otherBounds.width - position.x;
        }
        
        velocity = Vector2f(0, velocity.y);
    }
    
    else{
        if((velocity.y + selfVelocity.y) > 0 ){
            position.y -= position.y + size.y - otherBounds.top;
            isGrounded = true;
        }
        
        if((velocity.y + selfVelocity.y) < 0 ){
            position.y += otherBounds.top + otherBounds.height - position.y;
        }
        
        velocity = Vector2f(velocity.x, 0);
    }
    
    sprite.setPosition(position);
    //acceleration = Vector2f(0, 0);
    
}

bool Entity::isItGrounded(){
    return isGrounded;
}

void Entity::recieveDamage(int _damage){
    hp -= _damage;
    cout << hp << endl;
}

void Entity::setSelfVelocity(Vector2f _selfVelocity){
    selfVelocity = _selfVelocity;
}
Vector2f Entity::getSelfVelocity(){
    return selfVelocity;
}

