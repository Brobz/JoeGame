//
//  Resource.cpp
//  JoeGame
//
//  Created by Juan Lizarraga on 11/23/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include "Resource.h"

Resource::Resource(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, int _spriteSheetSize, int _animationSpeed, vector<int> &_dropType, Texture* _dropTexture, int _gemType) : Entity(_mass, _type, _size, _position, texture, _maxHp, _spriteSheetSize, _animationSpeed){
    
    dropType = _dropType;
    dropTexture = _dropTexture;
    gemType = _gemType;
}

void Resource::recieveDamage(int _damage, vector<Loot> &_loots){
    Entity::recieveDamage(_damage);
    Loot newLoot = Loot(0.05, dropType, Vector2f(10, 10), Vector2f(position.x + size.x / 2.0, position.y), dropTexture, gemType, 1);
    _loots.push_back(newLoot);
    
}
