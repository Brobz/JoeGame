//
//  Bullet.h
//  JoeGame
//
//  Created by Adrian Mancilla on 11/8/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Bullet_h
#define Bullet_h
#include "Entity.h"
#include "Enemy.h"
#include "Resource.h"

class Magnet;
class Player;

class Bullet : public Object{
protected:
    int damage;
    Vector2f center;
    bool isPlayer;
public:
    Bullet();
    Bullet(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _damage, bool isPlayer);
    void update(vector<Object> &objectcol, Player* playercol, vector<Enemy> &enemycol, vector<Magnet> &magnetCol, vector<Resource> &resourceCol, vector<Loot> &_loots);
    void DealDamage(Entity &other, int _damage);
    void DealDamage(Resource &other, int _damage, vector<Loot> &_loots);
    bool collidesWith(Object &other);

};

#endif /* Bullet_h */
