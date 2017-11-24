//
//  Player.cpp
//  JoeGame
//
//  Created by Juan Lizarraga on 11/8/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include "Player.h"
#include <math.h>
#include "Bullet.h"


Player::Player(){};

Player::Player(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, float _jumpForce, float _moveForce, Weapon* _weapon, Magnet* _lootMagnet, int _spriteSheetSize, int _animationSpeed) : Entity(_mass, _type, _size, _position, texture, _maxHp, _spriteSheetSize, _animationSpeed){
    jumpForce = _jumpForce;
    moveForce = _moveForce;
    facingRight = true;
    weapon = *_weapon;
    lootMagnet = *_lootMagnet;
    gold = 0;
    attracctorGems = 0;
    repellerGems = 0;
    NM_Bullets = 0;
    attractors = 0;
    repellers = 0;
    firingMode = 0;
    weaponOffset = Vector2f(25, 32);
    weapon.getSprite()->setOrigin(2, 2);
    weapon.setPosition(position + weaponOffset);
}

void Player::update(vector<Object> &objectCol, vector<Magnet> &magnetCol, vector<Loot> &lootCol){
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
    for(int i = 0; i < objectCol.size(); i++){
        collidesWith(objectCol.at(i), 0);
    }
    
    for(int i = 0; i < magnetCol.size(); i++){
        collidesWith(magnetCol.at(i), 0);
    }
    // Add velocity to position on the y axis
    position.y += velocity.y + selfVelocity.y;
    sprite.setPosition(position);
    // Check for collision with each of the provided objects
    for(int i = 0; i < objectCol.size(); i++){
        collidesWith(objectCol.at(i), 1);
    }
    
    for(int i = 0; i < magnetCol.size(); i++){
        collidesWith(magnetCol.at(i), 1);
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
        die();
    
    // Update Weapon
    weapon.setPosition(position + weaponOffset);
    weapon.update();
    //pointWeapon();
    
    // Update Loot Magnet
    lootMagnet.setPosition(position);
    lootMagnet.update(lootCol);
    
}

void Player::setFiringMode(int _firingMode){
    firingMode = _firingMode;
}

int Player::getFiringMode(){
    return firingMode;
}

void Player::draw(RenderWindow* window){
    Entity::draw(window);
    weapon.draw(window);
    pointWeapon(window);
    //((*window).draw(rayCast);
}

void Player::pointWeapon(RenderWindow* window){
    Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    
    float angle = Object::getAtan(Vector2f(mousePos.x - weapon.getPosition().x, mousePos.y - weapon.getPosition().y), false);
    
    weapon.getSprite()->setRotation(angle + 90);
    
    if (angle > 180 || angle < 0){
        weapon.getSprite()->setTextureRect(IntRect(0, 0, 16, 16));
        setFacingRight(true);
    }
    else{
        weapon.getSprite()->setTextureRect(IntRect(0, 16, 16, 16));
        setFacingRight(false);
    }
}

float Player::getJumpForce(){
    return jumpForce;
}
float Player::getMoveForce(){
    return moveForce;
}

void Player::fireWeapon(vector<Bullet> &bullets){
    NM_Bullets = weapon.fire(bullets, NM_Bullets);
}

int Player::getGold(){
    return gold;
}

int Player::getRepellerGems(){
    return repellerGems;
}

int Player::getAttractorGems(){
    return attracctorGems;
}

Weapon* Player::getWeapon(){
    return &weapon;
}

void Player::die(){
    Destroy();
}

void Player::getLoot(int lootType, int lootAmount){
    if(!lootType)
        gold += lootAmount;
    else if(lootType == 1)
        attracctorGems += lootAmount;
    else if(lootType == 2)
        repellerGems += lootAmount;
    
}

int Player::getAttractors(){
    return attractors;
}
int Player::getRepellers(){
    return repellers;
}
int Player::getNMBullets(){
    return NM_Bullets;
}


void Player::setAttractors(int _attr){
    attractors = _attr;
}
void Player::setRepellers(int _rep){
    repellers = _rep;
}
void Player::setNMBullets(int _nmb){
    NM_Bullets = _nmb;
}

void Player::revive(){
    isDestroyed = false;
}


