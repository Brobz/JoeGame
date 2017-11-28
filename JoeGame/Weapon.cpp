//
//  Weapon.cpp
//  JoeGame
//
//  Created by Adrian Mancilla on 11/7/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include "Weapon.h"
#include "Bullet.h"

Weapon::Weapon(){};

Weapon::Weapon(vector<int> &_type, Vector2f _size, Texture* texture, double _firingRate, double _firingForce, Texture _bulletTexture, bool _isPlayer, vector<int>& _bulletType, float _bulletMass, float _bulletDamage, Vector2f _bulletSize) : Object(0, _type, _size, Vector2f(), texture){
    firingRate = _firingRate;
    firingForce = _firingForce;
    bulletTexture = _bulletTexture;
    isPlayer = _isPlayer;
    bulletType = _bulletType;
    bulletMass = _bulletMass;
    bulletDamage = _bulletDamage;
    bulletSize = _bulletSize;
    canFire = true;
    if(!isPlayer){
        canFire = false;
        timeUntilNextFire = 60 / firingRate;
    }
}

void Weapon::fire(vector<Bullet> &bullets){
    if(!canFire)
        return;
    Bullet newBullet = Bullet(bulletMass, bulletType, bulletSize, Vector2f(position.x, position.y), &bulletTexture, bulletDamage, isPlayer);
    Vector2f force = Vector2f(firingForce * cos(sprite.getRotation() * M_PI / 180), firingForce * sin(sprite.getRotation() * M_PI / 180));
    newBullet.addForce(force);
    bullets.push_back(newBullet);
    canFire = false;
}

int Weapon::fire(vector<Bullet> &bullets, int nmBullets){
    if(!canFire)
        return nmBullets;
    if(nmBullets > 0)
        bulletType.at(1) = 0;
    else
        bulletType.at(1) = 1;
    Bullet newBullet = Bullet(bulletMass, bulletType, bulletSize, Vector2f(position.x, position.y), &bulletTexture, bulletDamage, isPlayer);
    Vector2f force = Vector2f(firingForce * cos(sprite.getRotation() * M_PI / 180), firingForce * sin(sprite.getRotation() * M_PI / 180));
    newBullet.addForce(force);
    bullets.push_back(newBullet);
    canFire = false;
    if (nmBullets > 0)
        return nmBullets - 1;
    else
        return nmBullets;
}

void Weapon::update(){
    sprite.setPosition(position);
    if(!canFire){
        timeUntilNextFire -= 1;
        if(timeUntilNextFire <= 0){
            timeUntilNextFire = 60 / firingRate;
            canFire = true;
        }
    }
}
