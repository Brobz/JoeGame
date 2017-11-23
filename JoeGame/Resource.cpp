//
//  Resource.cpp
//  JoeGame
//
//  Created by Juan Lizarraga on 11/23/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include "Resource.h"

Resource::Resource(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, int _spriteSheetSize, int _animationSpeed, vector<int> &_dropType, Texture* _dropTexture) : Entity(_mass, _type, _size, _position, texture, _maxHp, _spriteSheetSize, _animationSpeed){
    
    dropType = _dropType;
    dropTexture = _dropTexture;
}

void Resource::recieveDamage(int _damage, vector<Loot> &_loots){
    Entity::recieveDamage(_damage);
    Loot newLoot = Loot(0.05, dropType, Vector2f(20, 20), position, dropTexture, 1, 1);
    _loots.push_back(newLoot);
    
}
