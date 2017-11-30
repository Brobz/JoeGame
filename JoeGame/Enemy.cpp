//
//  Enemy.cpp
//  JoeGame
//
//  Created by Adrian Mancilla on 11/7/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include "Enemy.h"
#include "Loot.h"
#include "Player.h"
#include "Magnet.h"
#include <math.h>

Enemy::Enemy(){};

Enemy::Enemy(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, Weapon* _weapon, int _spriteSheetSize, int _animationSpeed, bool _shooter) : Entity(_mass, _type, _size, _position, texture, _maxHp, _spriteSheetSize, _animationSpeed){
    weapon = *_weapon;
    shooter = _shooter;
    weaponOffset = Vector2f(25, 32);
    weapon.getSprite()->setOrigin(2, 2);
    weapon.setPosition(position + weaponOffset);
};

void Enemy::chasePlayer(Vector2f playerpos, Vector2f speed){
    Vector2f distance = playerpos - position;
    double mag = sqrt(distance.x*distance.x + distance.y*distance.y);
    if(!mag)
        return;
    Vector2f newVelocity = Vector2f(distance.x/mag * speed.x, distance.y/mag * speed.y);
    if(isGrounded){
        if (abs(newVelocity.x) < 1 && distance.y > 100)
            newVelocity.x = -speed.x;
        setSelfVelocity(newVelocity);
    }
    
}

void Enemy::update(vector<Object> &objectCol, vector<Magnet> &magnetCol, Player* playerCol){
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
    
    if(selfVelocity.x > 0)
        setFacingRight(true);
    else if (selfVelocity.x < 0)
        setFacingRight(false);
    
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
    
    // Update Weapon
    if(shooter){
        pointWeapon(playerCol);
        weapon.setPosition(position + weaponOffset);
        weapon.update();
    }
}

void Enemy::pointWeapon(Player* player){
    Vector2f playerPos = Vector2f(player->getPosition().x + player->getSize().x / 2.0, player->getPosition().y + player->getSize().y / 2.0);
    
    float angle = Object::getAtan(Vector2f(playerPos.x - weapon.getPosition().x, playerPos.y - weapon.getPosition().y), false);
    
    /*/
    rayCast = RectangleShape(Vector2f(1, 1000));
    rayCast.setFillColor(sf::Color::Red);
    rayCast.setPosition(weapon.getPosition());
    rayCast.rotate(angle);
     /*/
    
    weapon.getSprite()->setRotation(angle + 90);
    
    if (angle > 180 || angle < 0)
        weapon.getSprite()->setTextureRect(IntRect(0, 0, 16, 16));
    else
        weapon.getSprite()->setTextureRect(IntRect(0, 16, 16, 16));
    
};

void Enemy::draw(RenderWindow* window){
    Entity::draw(window);
    if(shooter){
        weapon.draw(window);
    }
}

void Enemy::fireWeapon(vector<Bullet> &bullets){
    weapon.fire(bullets);
}

Weapon* Enemy::getWeapon(){
    return &weapon;
}

bool Enemy::isShooter(){
    return shooter;
}
