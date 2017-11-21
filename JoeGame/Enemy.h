//
//  Enemy.h
//  JoeGame
//
//  Created by Adrian Mancilla on 11/7/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Enemy_h
#define Enemy_h

#include "Entity.h"
#include "Weapon.h"
#include "Loot.h"

class Magnet;
class Player;

class Enemy : public Entity {
protected:
    Weapon weapon;
    bool shooter;
public:
    Enemy();
    Enemy(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, Weapon* _weapon, int _spriteSheetSize, int _animationSpeed, bool _shooter);
    void chasePlayer(Vector2f playerpos, Vector2f speed);
    void update(vector<Object> &objectCol, vector<Magnet> &magnetCol, Player* playerCol);
    void draw(RenderWindow* window);
    void pointWeapon(Player* player);
    bool isShooter();
    void fireWeapon(vector<Bullet> &bullets);
    Weapon* getWeapon();
};
#endif /* Enemy_h */
