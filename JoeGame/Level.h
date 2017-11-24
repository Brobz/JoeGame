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
    static const int MAGNET_GEM_COST = 8, MAGNET_GOLD_COST = 15;
    static const int NM_BULLETS_GOLD_COST = 25, HEART_BOX_GOLD_COST = 50;
    vector<Object> objects;
    vector<Object> shops;
    vector<Magnet> portals;
    vector<Enemy> enemies;
    vector<Bullet> bullets;
    vector<Magnet> magnets;
    vector<Spawner> spawners;
    vector<Resource> resources;
    vector<Loot> loots;
    vector<GUI_Button> buttons;
    vector<GUI_Button> shopButtons;
    Font font;
    Texture goldTexture, enemyTexture, enemyArmTexture, enemyBulletTexture, attractorTexture, repellerTexture, crossTexture, plusTexture, plusGreyedOutTexture, attractorGreyedOut, repellerGreyedOut, attractorGemTexture, repellerGemTexture;
    vector<int> type = {1, 1, 1, 1};
    vector<int> type_NG = {0, 1, 1, 1};
    vector<int> type_NM = {1, 0, 1, 1};
    vector<int> type_NG_NM = {0, 0, 1, 1};
    bool gamePaused, inShop;
public:
    Player* player;
    Level();
    Level(vector<GUI_Button> _buttons);
    Level(Player* _player, vector<Object> _objects, vector<Object> _shops, vector<Magnet> _portals, vector<Enemy> _enemies, vector<Bullet> _bullets, vector<Magnet> _magnets, vector<Spawner> _spawners, vector<Resource> _resources, vector<Loot> _loots, vector<GUI_Button> _buttons, vector<GUI_Button> _shopButtons);
    void setTextures(Texture* _goldTexture, Texture* _enemyTexture, Texture* _enemyArmTexture, Texture* _enemyBulletTexture, Texture* _attractorTexture, Texture* _repellerTexture, Texture*  _crossTexture, Texture* _plusTexture, Texture* _plusGreyedOutTexture,  Texture* _attractorGreyedOut, Texture* _repellerGreyedOut, Texture* _attractorGemTexture, Texture* _repellerGemTexture, Font* _font);
    void draw(RenderWindow* window);
    void update(int mouseInputs[], int keyInputs[], Vector2f mousePos, int &level);
    void updateMagnetFiringMode(int mode, Vector2f mousePos, int mouseInputs[]);
    void drawMagnetFiringMode(int mode, RenderWindow* window);
    void buyFromShop(int item);
    void drawButtons(RenderWindow* window, Vector2f mousePos, int mouseInputs[], int &level);
    void drawShopText(RenderWindow* window);
};

#endif /* Level_h */
