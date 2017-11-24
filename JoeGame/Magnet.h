//
//  Magnet.h
//  JoeGame
//
//  Created by Guilherme Bittencourt de Borba on 11/10/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Magnet_h
#define Magnet_h

#include "Entity.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Loot.h"

class Player;

class Magnet : public Entity{
protected:
    int tier;
    double pullingForce;
public:
    Magnet();
    Magnet(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, float _pullingForce, int _spriteSheetSize, int _animationSpeed);
    void excertForce(Object* other);
    void update(vector<Loot> &lootCol);
    void update(vector<Object> &objectCol, vector<Bullet>  &bulletCol, Player* playerCol, vector<Enemy> &enemyCol);
    static bool canBePlaced(Magnet magnet, vector<Object> &objectCol);
    double getPullingForce();
    int getTier();
    void setTier(int _tier);
    void draw(RenderWindow* window);
};

#endif /* Magnet_h */
