//
//  Resource.h
//  JoeGame
//
//  Created by Juan Lizarraga on 11/23/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Resource_h
#define Resource_h
#include "Entity.h"
#include "Loot.h"

class Resource : public Entity{
protected:
    vector<int> dropType;
    Texture* dropTexture;
    int gemType;
public:
    Resource();
    Resource(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, int _spriteSheetSize, int _animationSpeed, vector<int> &_dropType, Texture* _dropTexture, int _gemType);
    void recieveDamage(int _damage, vector<Loot> &_loots);
};

#endif /* Resource_h */
