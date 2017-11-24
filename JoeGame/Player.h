//
//  Player.h
//  JoeGame
//
//  Created by Juan Lizarraga on 11/8/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include "Entity.h"
#include "Weapon.h"
#include "Magnet.h"

class Bullet;

class Player : public Entity{
protected:
    float jumpForce, moveForce;
    bool facingRight;
    Weapon weapon;
    RectangleShape rayCast;
    Magnet lootMagnet;
    int gold, attracctorGems, repellerGems;
    int NM_Bullets, attractors, repellers;
    int firingMode;
    //Inventory inventory (tbi)
    
    
public:
    Player();
    Player(double _mass, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, int _maxHp, float _jumpForce, float _moveForce, Weapon* _weapon, Magnet* lootMagnet, int _spriteSheetSize, int _animationSpeed);
    void update(vector<Object> &objectCol, vector<Magnet> &magnetCol, vector<Loot> &lootCol);
    void draw(RenderWindow* window);
    void pointWeapon(RenderWindow* window);
    void fireWeapon(vector<Bullet> &bullets);
    float getJumpForce();
    float getMoveForce();
    Weapon* getWeapon();
    void getLoot(int lootType, int lootAmount);
    int getGold();
    int getAttractorGems();
    int getRepellerGems();
    int getAttractors();
    int getRepellers();
    int getNMBullets();
    void setAttractors(int _attr);
    void setRepellers(int _rep);
    void setNMBullets(int _nmb);
    void die();
    int getFiringMode();
    void setFiringMode(int _firingMode);
    void revive();
    
};


#endif /* Player_h */
