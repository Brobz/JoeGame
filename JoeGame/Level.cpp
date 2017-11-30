//
//  Level.cpp
//  JoeGame
//
//  Created by Guilherme Bittencourt de Borba on 11/22/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#include "Level.h"
#include "ResourcePath.hpp"

Level::Level(){};

Level::Level(vector<GUI_Button> _buttons){
    buttons = _buttons;
    inShop = true;
    gamePaused = true;
}

Level::Level(Player* _player, vector<Object> _objects, vector<Object> _shops, vector<Magnet> _portals, vector<Enemy> _enemies, vector<Bullet> _bullets, vector<Magnet> _magnets, vector<Spawner> _spawners, vector<Resource> _resources, vector<Loot> _loots, vector<GUI_Button> _buttons, vector<GUI_Button> _shopButtons){
    player = _player;
    objects = _objects;
    shops = _shops;
    portals = _portals;
    enemies = _enemies;
    bullets = _bullets;
    magnets = _magnets;
    spawners = _spawners;
    resources = _resources;
    loots = _loots;
    buttons = _buttons;
    shopButtons = _shopButtons;
    gamePaused = false;
    inShop = false;
}
void Level::draw(RenderWindow* window){
    // Draw All Shops
    for(int i = 0; i < shops.size(); i++){
        shops.at(i).draw(window);
    }
    
    // Draw all portals
    for(int i = 0; i < portals.size(); i++){
        portals.at(i).draw(window);
    }
    
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
    if(!player->isItDestroyed()){
        player->draw(window);
        if(player->getFiringMode() == 1){
            drawMagnetFiringMode(1, window);
        }else if(player->getFiringMode() == 2){
            drawMagnetFiringMode(2, window);
        }
    }
    
    
    // Draw Enemies
    for(int i = 0; i < enemies.size(); i++){
        enemies.at(i).draw(window);
    }
    
    
    // Draw Loot
    for(int i = 0; i < loots.size(); i++){
        loots.at(i).draw(window);
    }
}
void Level::update(int mouseInputs[], int keyInputs[], Vector2f mousePos, int &level){
    if(inShop){
        if(keyInputs[4] || keyInputs[5]){
            inShop = false;
            gamePaused = false;
            keyInputs[4] = 0;
            keyInputs[5] = 0;
        }
    }
    if(gamePaused){
         if(keyInputs[5]){
             gamePaused = false;
             keyInputs[5] = 0;
         }
        
        return;
    }
    
    // Input arrays
    if(mouseInputs[0]){
        if(!player->getFiringMode())
            player->fireWeapon(bullets);
        else if(player->getFiringMode() == 1){
            updateMagnetFiringMode(1, mousePos, mouseInputs);
            mouseInputs[0] = 0;
        }else if(player->getFiringMode() == 2){
            updateMagnetFiringMode(2, mousePos, mouseInputs);
            mouseInputs[0] = 0;
        }
        
    }
    
    if(mouseInputs[1]){
        player->setFiringMode(player->getFiringMode() + 1);
        if(player->getFiringMode() > 2){
            player->setFiringMode(0);
        }
        
        mouseInputs[1] = 0;
        
    }
    
    if(keyInputs[0] || keyInputs[6]){
       if(player->isItGrounded())
           player->addForce(Vector2f(0, -player->getJumpForce()));
        
        keyInputs[0] = 0;
        keyInputs[6] = 0;
    }
    
    if(keyInputs[3]){
        //player->setFacingRight(true);
        player->setSelfVelocity(Vector2f(player->getMoveForce(), player->getSelfVelocity().y));
    }
    
    if(keyInputs[1]){
        //player->setFacingRight(false);
        player->setSelfVelocity(Vector2f(-player->getMoveForce(), player->getSelfVelocity().y));
        
    }
    
    if(!keyInputs[1] && !keyInputs[3]){
        player->setSelfVelocity(Vector2f(0, player->getSelfVelocity().y));
    }
    
    for(int i = 0; i < shops.size(); i++){
        if(player->getSprite()->getGlobalBounds().intersects(shops.at(i).getSprite()->getGlobalBounds())){
            //drawWindow
            if(keyInputs[4]){
                gamePaused = true;
                inShop = true;
                keyInputs[4] = 0;
                break;
            }
        }
    }
    
    if(keyInputs[5]){
        gamePaused  = true;
        keyInputs[5] = 0;
    }
    
    // Update Magnet physics
    for(int i = 0; i < magnets.size(); i++){
        if (magnets.at(i).isItDestroyed()){
            for(int j = 0; j < MAGNET_GEM_COST * magnets.at(i).getTier(); j++){
                if(magnets.at(i).getPullingForce() < 0)
                    loots.push_back(Loot(0.05, type, Vector2f(10, 10), magnets.at(i).getPosition(), &attractorGemTexture, 1, 1));
                else
                    loots.push_back(Loot(0.05, type, Vector2f(10, 10), magnets.at(i).getPosition(), &repellerGemTexture, 1, 1));
            }
            for(int j = 0; j < MAGNET_GOLD_COST / 3.0 * magnets.at(i).getTier(); j++)
                loots.push_back(Loot(0.05, type, Vector2f(10, 10), magnets.at(i).getPosition(), &goldTexture, 0, 1));
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
    else{
        player->recieveDamage(-player->getMaxHP());
        player->setPosition(Vector2f(650, 475));
        player->revive();
        enemies.clear();
        loots.clear();
        magnets.clear();
        bullets.clear();
        for(int i = 0; i < resources.size(); i++){
            resources.at(i).Entity::recieveDamage(-resources.at(i).getMaxHP());
        }
        level = 0;
    }
    
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
            
            for(int j = 0; j < 15; j++)
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
    
    // Update portals
    for(int i = 0; i < portals.size(); i++){
        //portals.at(i).excertForce(player);
        if(player->getSprite()->getGlobalBounds().intersects(portals.at(i).getSprite()->getGlobalBounds())){
            if(portals.at(i).getPullingForce() < 0){
                player->recieveDamage(-player->getMaxHP());
                player->setPosition(Vector2f(650, 475));
                player->revive();
                enemies.clear();
                loots.clear();
                bullets.clear();
                magnets.clear();
                for(int i = 0; i < resources.size(); i++){
                    resources.at(i).Entity::recieveDamage(-resources.at(i).getMaxHP());
                }
                level = 0;
            }
        }
    }

    
    // Update Shop
    for(int i = 0; i < shops.size(); i++){
        shops.at(i).update(objects);
    }

}

void Level::updateMagnetFiringMode(int mode, Vector2f mousePos, int mouseInputs[]){
    if((player->getAttractors() >= 1 && mode == 1) || (player->getRepellers() >= 1 && mode == 2)){
        Magnet newMagnet;
        if(mode == 1)
            newMagnet = Magnet(1, type_NG, Vector2f(32, 32), Vector2f(mousePos.x - 16, mousePos.y - 16), &attractorTexture, 50, -800, 0, 60);
        else if(mode == 2)
            newMagnet = Magnet(1, type_NG, Vector2f(32, 32), Vector2f(mousePos.x - 16, mousePos.y - 16), &repellerTexture, 50, 800, 0, 60);
        vector<Object> colliders;
        for(int i = 0; i < magnets.size(); i++){
            colliders.push_back(magnets.at(i));
            
            if(!Magnet::canBePlaced(newMagnet, colliders) && ((magnets.at(i).getPullingForce() < 0 && mode == 1) || (magnets.at(i).getPullingForce() > 0 && mode == 2))){
                magnets.at(i).setTier(magnets.at(i).getTier() + 1);
                mouseInputs[0] = 0;
                if(mode == 1)
                    player->setAttractors(player->getAttractors() - 1);
                else if(mode == 2)
                    player->setRepellers(player->getRepellers() - 1);
                break;
            }
        }
        
        colliders.insert(colliders.begin(), objects.begin(), objects.end());
        colliders.insert(colliders.begin(), enemies.begin(), enemies.end());
        
        colliders.insert(colliders.begin(), resources.begin(), resources.end());
        colliders.push_back(*player);
        if(Magnet::canBePlaced(newMagnet, colliders)){
            magnets.push_back(newMagnet);
            
            mouseInputs[0] = 0;
            if(mode == 1)
                player->setAttractors(player->getAttractors() - 1);
            else if(mode == 2)
                player->setRepellers(player->getRepellers() - 1);
        }
    }
}

void Level::drawMagnetFiringMode(int mode, RenderWindow* window){
    Sprite alphaMagnet;
    if(mode == 1)
        alphaMagnet.setTexture(attractorTexture);
    else if(mode == 2)
        alphaMagnet.setTexture(repellerTexture);
    Sprite overlay(plusTexture);
    Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    alphaMagnet.setPosition(Vector2f(mousePos.x - 16, mousePos.y - 16));
    alphaMagnet.setScale(2, 2);
    alphaMagnet.setColor(Color::Color(255, 255, 255, 80));
    if(!(player->getAttractors() >= 1 && mode == 1) && !(player->getRepellers() >= 1 && mode == 2)){
        if(mode == 1)
            alphaMagnet.setTexture(attractorGreyedOut);
        else if(mode == 2)
            alphaMagnet.setTexture(repellerGreyedOut);
        overlay.setTexture(plusGreyedOutTexture);
    }
    
    Magnet newMagnet = Magnet(1, type_NG, Vector2f(32, 32), Vector2f(mousePos.x - 16, mousePos.y - 16), &attractorTexture, 50, -800, 0, 60);
    vector<Object> colliders;
    overlay.setPosition(Vector2f(mousePos.x - 16, mousePos.y - 16));
    overlay.setScale(2, 2);
    overlay.setColor(Color::Color(255, 255, 255, 80));
    for(int i = 0; i < magnets.size(); i++){
        colliders.push_back(magnets.at(i));
        
        if(!Magnet::canBePlaced(newMagnet, colliders)){
            if((magnets.at(i).getPullingForce() < 0 && mode == 1) || (magnets.at(i).getPullingForce() > 0 && mode == 2)){
                overlay.setPosition(magnets.at(i).getPosition().x, magnets.at(i).getPosition().y);
                window->draw(overlay);
                return;
            }else{
                window->draw(alphaMagnet);
                overlay.setTexture(crossTexture);
                window->draw(overlay);
                return;
            }
        }
    }
    colliders.clear();
    colliders.insert(colliders.begin(), objects.begin(), objects.end());
    colliders.insert(colliders.begin(), enemies.begin(), enemies.end());
    colliders.insert(colliders.begin(), resources.begin(), resources.end());
    colliders.push_back(*player);
    window->draw(alphaMagnet);
    if(!Magnet::canBePlaced(newMagnet, colliders)){
        overlay.setTexture(crossTexture);
        window->draw(overlay);
    }
}

void Level::buyFromShop(int item){
    if(item == 1){
        if(player->getAttractorGems() >= MAGNET_GEM_COST && player->getGold() >= MAGNET_GOLD_COST){
            player->setAttractors(player->getAttractors() + 1);
            player->getLoot(0, -MAGNET_GOLD_COST);
            player->getLoot(1, -MAGNET_GEM_COST);
        }
    }
    else if(item == 2){
        if(player->getRepellerGems() >= MAGNET_GEM_COST && player->getGold() >= MAGNET_GOLD_COST){
            player->setRepellers(player->getRepellers() + 1);
            player->getLoot(0, -MAGNET_GOLD_COST);
            player->getLoot(2, -MAGNET_GEM_COST);
        }
    }
    
    else if(item == 3){
        if(player->getGold() >= NM_BULLETS_GOLD_COST){
            player->setNMBullets(player->getNMBullets() + 15);
            player->getLoot(0, -NM_BULLETS_GOLD_COST);
        }
    }
    
    else if(item == 4){
        if(player->getGold() >= HEART_BOX_GOLD_COST){
            player->recieveDamage(-35);
            player->getLoot(0, -HEART_BOX_GOLD_COST);
        }
    }
    
    
    
    
}

void Level::drawButtons(RenderWindow* window, Vector2f mousePos, int mouseInputs[], int &level){
    for(int i = 0; i < buttons.size(); i++){
        buttons.at(i).draw(window);
       
        if(buttons.at(i).wasClicked(mousePos) && mouseInputs[0]){
            level = buttons.at(i).getID();
            mouseInputs[0] = 0;
        }
    }
    
    if(inShop){
        for(int i = 0; i < shopButtons.size(); i++){
            shopButtons.at(i).draw(window);
        }
        
        for(int i = 1; i < shopButtons.size(); i++){
            if(shopButtons.at(i).wasClicked(mousePos) && mouseInputs[0]){
                buyFromShop(i);
                mouseInputs[0] = 0;
            }
        }
    }
    
}

void Level::drawShopText(RenderWindow* window){
    
    for(int i = 0; i < shops.size(); i++){
        
        if(player->getSprite()->getGlobalBounds().intersects(shops.at(i).getSprite()->getGlobalBounds()) && !inShop){
            GUI_Text enterShop = GUI_Text(Vector2f(shops.at(i).getPosition().x - 75,shops.at(i).getPosition().y - 75), "Press [E] to enter shop", 18, &font, Color::White);
            enterShop.draw(window);
        }
    }
}

void Level::setTextures(Texture* _goldTexture, Texture* _enemyTexture, Texture* _enemyArmTexture, Texture* _enemyBulletTexture, Texture* _attractorTexture, Texture* _repellerTexture, Texture*  _crossTexture, Texture* _plusTexture, Texture* _plusGreyedOutTexture, Texture* _attractorGreyedOut, Texture* _repellerGreyedOut, Texture* _attractorGemTexture, Texture* _repellerGemTexture, Font* _font){
    goldTexture = *_goldTexture;
    enemyTexture = *_enemyTexture;
    enemyArmTexture = *_enemyArmTexture;
    enemyBulletTexture = *_enemyBulletTexture;
    attractorTexture = *_attractorTexture;
    repellerTexture = *_repellerTexture;
    crossTexture = *_crossTexture;
    plusTexture = *_plusTexture;
    plusGreyedOutTexture = *_plusGreyedOutTexture;
    attractorGreyedOut = *_attractorGreyedOut;
    repellerGreyedOut = *_repellerGreyedOut;
    attractorGemTexture = *_attractorGemTexture;
    repellerGemTexture = *_repellerGemTexture;
    font = *_font;
    

}
