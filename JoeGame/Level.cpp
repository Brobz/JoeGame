//
//  Level.cpp
//  JoeGame
//
//  Created by Guilherme Bittencourt de Borba on 11/22/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include "Level.h"

Level::Level(){};

Level::Level(Player* _player, vector<Object> _objects, vector<Enemy> _enemies, vector<Bullet> _bullets, vector<Magnet> _magnets, vector<Spawner> _spawners, vector<Resource> _resources, vector<Loot> _loots){
    player = _player;
    objects = _objects;
    enemies = _enemies;
    bullets = _bullets;
    magnets = _magnets;
    spawners = _spawners;
    resources = _resources;
    loots = _loots;
}
void Level::draw(RenderWindow* window){
    // Draw Bullets
    for(int i = 0; i < bullets.size(); i++){
        bullets.at(i).draw(window);
    }
    
    // Draw Magnets
    for(int i = 0; i < magnets.size(); i++){
        magnets.at(i).draw(window);
    }
    
    // Draw all objects
    for(int i = 0; i < objects.size(); i++){
        objects.at(i).draw(window);
    }
    
    
    // Draw all resources
    for(int i = 0; i < resources.size(); i++){
        resources.at(i).draw(window);
    }
    
    // Draw Player
    if(!player->isItDestroyed())
        player->draw(window);
    
    
    // Draw Enemies
    for(int i = 0; i < enemies.size(); i++){
        enemies.at(i).draw(window);
    }
    
    
    // Draw Loot
    for(int i = 0; i < loots.size(); i++){
        loots.at(i).draw(window);
    }
}
void Level::update(int mouseInputs[], int keyInputs[]){
    // Input arrays
    if(mouseInputs[0])
        player->fireWeapon(bullets);
    
    if(keyInputs[3]){
        player->setFacingRight(true);
        player->setSelfVelocity(Vector2f(player->getMoveForce(), player->getSelfVelocity().y));
    }
    
    if(keyInputs[1]){
        player->setFacingRight(false);
        player->setSelfVelocity(Vector2f(-player->getMoveForce(), player->getSelfVelocity().y));
        
    }
    
    if(!keyInputs[1] && !keyInputs[3]){
        player->setSelfVelocity(Vector2f(0, player->getSelfVelocity().y));
    }
    
    // Update Magnet physics
    for(int i = 0; i < magnets.size(); i++){
        if (magnets.at(i).isItDestroyed()){
            magnets.erase(magnets.begin() + i);
            continue;
        }
        magnets.at(i).update(objects, bullets, player, enemies);
    }
    
    // Update Bullet physicss
    for(int i = 0; i < bullets.size(); i++){
        if (bullets.at(i).isItDestroyed()){
            bullets.erase(bullets.begin() + i);
            continue;
        }
        bullets.at(i).update(objects, player, enemies, magnets, resources, loots);
    }
    
    // Update Player physics
    if(!player->isItDestroyed())
        player->update(objects, magnets, loots);
    
    
    // Update Loot Physics
    for(int i = 0; i < loots.size(); i++){
        if (loots.at(i).isItDestroyed()){
            loots.erase(loots.begin() + i);
            continue;
        }
        loots.at(i).update(objects, player);
    }
    
    // Update Enemy physics
    for(int i = 0; i < enemies.size(); i++){
        if (enemies.at(i).isItDestroyed()){
            
            for(int j = 0; j < 5; j++)
                loots.push_back(Loot(0.05, type, Vector2f(10, 10), enemies.at(i).getPosition(), &goldTexture, 0, 1));
            enemies.erase(enemies.begin() + i);
            continue;
        }
        
        if(enemies.at(i).isShooter() && !player->isItDestroyed()){
            enemies.at(i).fireWeapon(bullets);
        }
        
        enemies.at(i).chasePlayer(player->getPosition(), Vector2f(1, 8));
        enemies.at(i).update(objects, magnets, player);
        
    }
    
    // Update Object physics
    for(int i = 0; i < objects.size(); i++){
        objects.at(i).update();
    }
    
    // Update Resource Physics
    for(int i = 0; i < resources.size(); i++){
        if(resources.at(i).isItDestroyed()){
            resources.erase(resources.begin() + i);
            continue;
        }
        resources.at(i).update(objects);
    }
    
    // Update Spawner physics
    for(int i = 0; i < spawners.size(); i++){
        spawners.at(i).update();
        if(spawners.at(i).canItSpawn()){
            enemies.push_back(Enemy(0.75, type, Vector2f(50,50), spawners.at(i).getPosition(), &enemyTexture, 50, new Weapon(type_NG_NM, Vector2f(45,45), &enemyArmTexture, 0.5, 0.5, enemyBulletTexture, false, type_NG, 0.15, 20, Vector2f(8, 8)), 9, 60, true));
            spawners.at(i).spawned();
        }
    }
}


void Level::setTextures(Texture* _goldTexture, Texture* _enemyTexture, Texture* _enemyArmTexture, Texture* _enemyBulletTexture){
    goldTexture = *_goldTexture;
    enemyTexture = *_enemyTexture;
    enemyArmTexture = *_enemyArmTexture;
    enemyBulletTexture = *_enemyBulletTexture;
}
