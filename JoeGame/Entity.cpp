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

Entity::Entity(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, int _spriteSheetSize, int _animationSpeed) : Object(_mass, _type, _size, _position, texture){
    
    maxHp = _maxHp;
    hp = maxHp;
    isGrounded = false;
    facingRight = true;
    spriteSheetSize = _spriteSheetSize;
    animationSpeed = _animationSpeed;
    selfVelocity = Vector2f();
    currentAnimFrame = 0;
    spriteOffset = 0;
    
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
    
    // Add friction to velocity
    if(velocity.x > 0){
        velocity.x -= velocity.x * FRICTION;
        if(velocity.x < 0)
            velocity.x = 0;
    }
    else if(velocity.x < 0){
        velocity.x += -velocity.x * FRICTION;
        if(velocity.x > 0)
            velocity.x = 0;
    }
    
    if (velocity.y != 0)
        isGrounded = false;
    
    if(hp <= 0)
        Destroy();
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
}

void Entity::draw(RenderWindow* window){
    if(selfVelocity.x > 0){
        currentAnimFrame++;
        if(currentAnimFrame >= 60 / animationSpeed){
            spriteOffset++;
            currentAnimFrame = 0;
            if(spriteOffset >= spriteSheetSize)
                spriteOffset = 0;
        }
        if(facingRight)
            sprite.setTextureRect(IntRect(16 * spriteOffset, 0, 16, 16));
        else
            sprite.setTextureRect(IntRect(16 * spriteOffset, 16, 16, 16));
    }
    
    else if(selfVelocity.x < 0){
        currentAnimFrame++;
        if(currentAnimFrame >= 60 / animationSpeed){
            spriteOffset++;
            currentAnimFrame = 0;
            if(spriteOffset >= spriteSheetSize)
                spriteOffset = 0;
        }
        if(facingRight)
            sprite.setTextureRect(IntRect(16 * spriteOffset, 0, 16, 16));
        else
            sprite.setTextureRect(IntRect(16 * spriteOffset, 16, 16, 16));
    }
    else{
        currentAnimFrame = 0;
        spriteOffset = 0;
        if(facingRight || spriteSheetSize == 0)
            sprite.setTextureRect(IntRect(0, 0, 16, 16));
        else
            sprite.setTextureRect(IntRect(0, 16, 16, 16));
    }
    
    Object::draw(window);
}

bool Entity::isItGrounded(){
    return isGrounded;
}

void Entity::recieveDamage(int _damage){
    hp -= _damage;
}

void Entity::setSelfVelocity(Vector2f _selfVelocity){
    selfVelocity = _selfVelocity;
}
Vector2f Entity::getSelfVelocity(){
    return selfVelocity;
}

void Entity::setFacingRight(bool _bool){
    facingRight = _bool;
}

bool Entity::getFacingRight(){
    return facingRight;
}

int Entity::getHP(){
    return hp;
}

int Entity::getMaxHP(){
    return maxHp;
}
