#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "Entity.h"
#include "Weapon.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Magnet.h"
#include "Spawner.h"
#include "GUI_Object.h"
#include "GUI_Text.h"
#include "GUI_Button.h"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(900, 600), "SFML window", sf::Style::Close);
    
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(0);
    window.setVerticalSyncEnabled(true);
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    
    // Load a sprite to display

    sf::Texture playerTexture, enemyTexture, wallTexture, floorTexture, attractorTexture, repellerTexture, gunTexture, bulletTexture, guiTexture, buttonTexture, goldTexture, bgTexture, enemyArmTexture;
    
    
    if (!bgTexture.loadFromFile(resourcePath() + "background.png")) {
        return EXIT_FAILURE;
    }
    
    if (!playerTexture.loadFromFile(resourcePath() + "joeFinal.png")) {
        return EXIT_FAILURE;
    }
    
    if (!enemyTexture.loadFromFile(resourcePath() + "enemy.png")) {
        return EXIT_FAILURE;
    }
    
    if (!gunTexture.loadFromFile(resourcePath() + "arm.png")) {
        return EXIT_FAILURE;
    }
    
    if (!enemyArmTexture.loadFromFile(resourcePath() + "enemyArm.png")) {
        return EXIT_FAILURE;
    }
    
    if (!bulletTexture.loadFromFile(resourcePath() + "bullet.png")) {
        return EXIT_FAILURE;
    }
    
    if (!wallTexture.loadFromFile(resourcePath() + "wall.png")) {
        return EXIT_FAILURE;
    }
    
    if (!attractorTexture.loadFromFile(resourcePath() + "attractor.png")) {
        return EXIT_FAILURE;
    }
    
    if (!repellerTexture.loadFromFile(resourcePath() + "repeller.png")) {
        return EXIT_FAILURE;
    }

    if (!goldTexture.loadFromFile(resourcePath() + "gold.png")) {
        return EXIT_FAILURE;
    }
    
    if (!guiTexture.loadFromFile(resourcePath() + "gui.png")) {
        return EXIT_FAILURE;
    }
    if (!buttonTexture.loadFromFile(resourcePath() + "2.png")) {
        return EXIT_FAILURE;
    }
    if (!floorTexture.loadFromFile(resourcePath() + "ground.png")) {
        return EXIT_FAILURE;
    }

    
    
    int MOUSE_INPUTS[3] = {0, 0, 0}; // LEFT, MIDDLE, RIGHT
    int KEY_INPUTS[5] = {0, 0, 0, 0, 0}; // W, A, S, D, SPACEBAR
    
    Player* player;
    vector<Object> allObjects;
    vector<Enemy> allEnemies;
    vector<Bullet> allBullets;
    vector<Magnet> allMagnets;
    vector<Spawner> allSpawners;
    vector<Loot> allLoots;
    
    
    vector<int> type = {1, 1, 1, 1};
    vector<int> type_NG = {0, 1, 1, 1};
    vector<int> type_NM = {1, 0, 1, 1};
    vector<int> type_NG_NM = {0, 0, 1, 1};
    
    vector<Weapon> playerWeapons;
    
    Sprite bgSprite(bgTexture);
    
    // wait its motion blur
    bgSprite.setColor(Color(255, 255, 255, 205));
    
    allSpawners.push_back(Spawner(type_NG_NM, Vector2f(10, 10), Vector2f(300, 300), &wallTexture, 240));
    
    allSpawners.at(0).activate();

    Weapon playerWeapon = Weapon(type_NG_NM, Vector2f(45,45), &gunTexture, 5, 1.5, &bulletTexture, true, type_NG, 0.15, 20, Vector2f(8, 8));
    
    playerWeapons.push_back(Weapon(type_NG_NM, Vector2f(45,45), &gunTexture, 5, 1.5, &bulletTexture, true, type_NG, 0.15, 10, Vector2f(8, 8)));
    
    Magnet lootMagnet = Magnet(1, type_NG, Vector2f(32, 32), Vector2f(), &attractorTexture, 50, -30, 0, 60);
    
    player = new Player(0.75, type, Vector2f(50, 50), Vector2f(150, 500), &playerTexture, 100, 10, 5, &playerWeapon, &lootMagnet, 9, 60);
    
    player->setSprite(*new Sprite(playerTexture,IntRect(0,0,16,16)));

    allObjects.push_back(Object(5, type_NG_NM, Vector2f(1000, 64), Vector2f(-100, 555), &floorTexture));
    allObjects.push_back(Object(5, type_NG_NM, Vector2f(1000, 64), Vector2f(-100, 150), &wallTexture));
    allObjects.push_back(Object(5, type_NG_NM, Vector2f(64, 800), Vector2f(500, 0), &wallTexture));
    allObjects.push_back(Object(5, type_NG_NM, Vector2f(64, 800), Vector2f(50, 0), &wallTexture));
    
    GUI_Object guiobj = GUI_Object(Vector2f(16,16), Vector2f(200,200), &guiTexture);
    
    Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    GUI_Text guitext = GUI_Text(Vector2f(0,0), "hola", 30, &font, Color::Red);
    GUI_Button guibutton = GUI_Button(Vector2f(16,16), Vector2f(100,100), &buttonTexture, guitext, &guiTexture);
    
    //GUI
    sf::RectangleShape lifeBar, lifeBarBG, goldBar;
    sf::Sprite goldIcon;
    
    lifeBar.setSize(sf::Vector2f(150, 20));
    lifeBar.setPosition(sf::Vector2f(20, 20));
    lifeBar.setFillColor(Color(97, 216, 54));
    
    lifeBarBG.setSize(sf::Vector2f(150, 20));
    lifeBarBG.setPosition(sf::Vector2f(20, 20));
    lifeBarBG.setFillColor(Color(238, 17,0));
    lifeBarBG.setOutlineThickness(3);
    lifeBarBG.setOutlineColor(Color(0,0,0));
    
    goldBar.setSize(sf::Vector2f(75, 20));
    goldBar.setPosition(sf::Vector2f(window.getSize().x-20-goldBar.getSize().x, 20));
    goldBar.setFillColor(Color(246,200,0));
    goldBar.setOutlineThickness(3);
    goldBar.setOutlineColor(Color(0,0,0));
    
    goldIcon.setTexture(goldTexture);
    goldIcon.setPosition(window.getSize().x-16-goldBar.getSize().x, 22);
    
    GUI_Text goldLabel = GUI_Text(Vector2f(window.getSize().x-goldBar.getSize().x + 4,18), std::to_string(player->getGold()), 18, &font, Color::Black);
    
    sf::Clock clock;
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
                KEY_INPUTS[1] = 1;
                //allPlayers.at(0).setSelfVelocity(Vector2f(-fuck_copy_paste, 0));
            }
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
                KEY_INPUTS[3] = 1;
                //allPlayers.at(0).setSelfVelocity(Vector2f(fuck_copy_paste, 0));
            }
            
            if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Space)) {
                if(player->isItGrounded())
                    player->addForce(Vector2f(0, -player->getJumpForce()));
            }
            
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A) {
                KEY_INPUTS[1] = 0;
                //allPlayers.at(0).setSelfVelocity(Vector2f(0, allPlayers.at(0).getSelfVelocity().y));
            }
            
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D) {
                KEY_INPUTS[3] = 0;
                //allPlayers.at(0).setSelfVelocity(Vector2f(0, allPlayers.at(0).getSelfVelocity().y));
            }
            
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
                MOUSE_INPUTS[0] = 1;
                //allPlayers.at(0).fireWeapon(allBullets);
            }
            
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left) {
                MOUSE_INPUTS[0] = 0;
                //allPlayers.at(0).fireWeapon(allBullets);
            }
            
            //Magnet debugging
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N) {
                Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                mousePos -= Vector2f(16,16);
                allMagnets.push_back((Magnet(1, type_NG, Vector2f(32, 32), mousePos, &attractorTexture, 50, -800, 0, 60)));
            }
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
                Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                mousePos -= Vector2f(16,16);
                allMagnets.push_back((Magnet(1, type_NG, Vector2f(32, 32), mousePos, &repellerTexture, 50, 800, 0, 60)));
            }
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B) {
                allMagnets.clear();
            }
        }
        
        // Input arrays
        if(MOUSE_INPUTS[0])
            player->fireWeapon(allBullets);
        
        if(KEY_INPUTS[3]){
            player->setFacingRight(true);
            player->setSelfVelocity(Vector2f(player->getMoveForce(), player->getSelfVelocity().y));
        } 
        
        if(KEY_INPUTS[1]){
            player->setFacingRight(false);
            player->setSelfVelocity(Vector2f(-player->getMoveForce(), player->getSelfVelocity().y));
            
        }
        
        if(!KEY_INPUTS[1] && !KEY_INPUTS[3]){
            player->setSelfVelocity(Vector2f(0, player->getSelfVelocity().y));
        }
        
        
        // Update Magnet physics
        for(int i = 0; i < allMagnets.size(); i++){
            if (allMagnets.at(i).isItDestroyed()){
                allMagnets.erase(allMagnets.begin() + i);
                continue;
            }
            allMagnets.at(i).update(allObjects, allBullets, player, allEnemies);
        }
        
        // Update Bullet physicss
        for(int i = 0; i < allBullets.size(); i++){
            if (allBullets.at(i).isItDestroyed()){
                allBullets.erase(allBullets.begin() + i);
                continue;
            }
            allBullets.at(i).update(allObjects, player, allEnemies, allMagnets);
        }
        
        // Update Player physics
        if(!player->isItDestroyed())
            player->update(allObjects, allMagnets, allLoots);
        
        
        // Update Loot Physics
        for(int i = 0; i < allLoots.size(); i++){
            if (allLoots.at(i).isItDestroyed()){
                allLoots.erase(allLoots.begin() + i);
                continue;
            }
            allLoots.at(i).update(allObjects, player);
        }
        
        // Update Enemy physics
        for(int i = 0; i < allEnemies.size(); i++){
            if (allEnemies.at(i).isItDestroyed()){

                allLoots.push_back(Loot(0.05, type, Vector2f(20, 20), allEnemies.at(i).getPosition(), &goldTexture, 0, 3));
                allEnemies.erase(allEnemies.begin() + i);
                continue;
            }
            
            if(allEnemies.at(i).isShooter()){
                allEnemies.at(i).fireWeapon(allBullets);
            }
            
            allEnemies.at(i).chasePlayer(player->getPosition(), Vector2f(1, 8));
            allEnemies.at(i).update(allObjects, allMagnets, player);
            
        }
        
        // Update Object physics
        for(int i = 0; i < allObjects.size(); i++){
            allObjects.at(i).update();
        }
        
        // Update Spawner physics
        for(int i = 0; i < allSpawners.size(); i++){
            allSpawners.at(i).update();
            if(allSpawners.at(i).canItSpawn()){
                allEnemies.push_back(Enemy(0.75, type, Vector2f(50,50), allSpawners.at(i).getPosition(), &enemyTexture, 50, new  Weapon(type_NG_NM, Vector2f(45,45), &enemyArmTexture, 0.5, 0.5, &bulletTexture, false, type_NG, 0.15, 20, Vector2f(8, 8)), 9, 60, true));
                allSpawners.at(i).spawned();
            }
        }
        
        //Update HP Bar
        lifeBar.setSize(sf::Vector2f((float)player->getHP()/player->getMaxHP()*150, 20));
        goldLabel.setText(std::to_string(player->getGold()));
        
        // Clear screen
        window.draw(bgSprite);
        
        // Draw Bullets
        for(int i = 0; i < allBullets.size(); i++){
            allBullets.at(i).draw(&window);
        }
        
        // Draw Magnets
        for(int i = 0; i < allMagnets.size(); i++){
            allMagnets.at(i).draw(&window);
        }
        
        // Draw all objects
        for(int i = 0; i < allObjects.size(); i++){
            allObjects.at(i).draw(&window);
        }
        
        // Draw Player
        if(!player->isItDestroyed())
            player->draw(&window);
        
        
        // Draw Enemies
        for(int i = 0; i < allEnemies.size(); i++){
            allEnemies.at(i).draw(&window);
        }
        
        
        // Draw Loot
        for(int i = 0; i < allLoots.size(); i++){
            allLoots.at(i).draw(&window);
        }
        
        window.draw(lifeBarBG);
        window.draw(lifeBar);
        window.draw(goldBar);
        window.draw(goldIcon);
        goldLabel.draw(&window);
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
