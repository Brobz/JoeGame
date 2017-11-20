//
//  Enemy.cpp
//  JoeGame
//
//  Created by Adrian Mancilla on 11/7/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include <stdio.h>
#include "Enemy.h"

Enemy::Enemy(){};

Enemy::Enemy(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, Weapon* _weapon, int _spriteSheetSize, int _animationSpeed) : Entity(_mass, _type, _size, _position, texture, _maxHp, _spriteSheetSize, _animationSpeed){
    weapon = *_weapon;
};
