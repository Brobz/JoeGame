//
//  Level.h
//  JoeGame
//
//  Created by Guilherme Bittencourt de Borba on 11/22/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Level_h
#define Level_h
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Weapon.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Magnet.h"
#include "Spawner.h"
#include "Resource.h"
#include "GUI_Object.h"
#include "GUI_Text.h"
#include "GUI_Button.h"

class Level{
protected:
    vector<Object> objects;
    vector<Enemy> enemies;
    vector<Bullet> bullets;
    vector<Magnet> magnets;
    vector<Spawner> spawners;
    vector<Resource> resources;
    vector<Loot> loots;
    Texture goldTexture, enemyTexture, enemyArmTexture, enemyBulletTexture, attractorTexture, repellerTexture, crossTexture;
    vector<int> type = {1, 1, 1, 1};
    vector<int> type_NG = {0, 1, 1, 1};
    vector<int> type_NM = {1, 0, 1, 1};
    vector<int> type_NG_NM = {0, 0, 1, 1};
public:
    Player* player;
    Level();
    Level(Player* _player, vector<Object> _objects, vector<Enemy> _enemies, vector<Bullet> _bullets, vector<Magnet> _magnets, vector<Spawner> _spawners, vector<Resource> _resources, vector<Loot> _loots);
    void setTextures(Texture* _goldTexture, Texture* _enemyTexture, Texture* _enemyArmTexture, Texture* _enemyBulletTexture, Texture* _attractorTexture, Texture* _repellerTexture, Texture*  _crossTexture);
    void draw(RenderWindow* window);
    void update(int mouseInputs[], int keyInputs[], Vector2f mousePos);
};

#endif /* Level_h */
