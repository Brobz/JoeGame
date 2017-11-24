// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "Game.h"

int main(int, char const**)
{
    const int WIDTH = 900, HEIGHT = 600;
    const double SCALE = 1.3;
    Vector2f MOUSE_POS;
    
    // Seed random
    srand((int)time(NULL));
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML window", sf::Style::Close);
    // Create the main view
    sf::View view(Vector2f(WIDTH / 2.0, HEIGHT / 2.0), Vector2f(WIDTH * SCALE, HEIGHT * SCALE));
    
    window.setView(view);
    
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
   sf::Texture bgTexture, playerTexture, enemyTexture, wallTexture, floorTexture, shopTexture, attractorTexture, repellerTexture, gunTexture, bulletTexture, guiTexture, buttonTexture, goldTexture, enemyArmTexture, attractorGemTexture, attractorResourceTexture, repellerGemTexture, repellerResourceTexture, crossTexture, attractorGreyedOutTexture, repellerGreyedOutTexture, plusTexture, plusGreyedOutTexture, aboutButtonTexture, aboutButtonHoverTexture, playButtonTexture, playButtonHoverTexture;
    
    vector<Texture*> allTextures = {&bgTexture, &playerTexture, &enemyTexture, &wallTexture, &floorTexture, &shopTexture, &attractorTexture, &repellerTexture, &gunTexture, &bulletTexture, &guiTexture, &buttonTexture, &goldTexture, &enemyArmTexture, &attractorGemTexture, &attractorResourceTexture, &repellerGemTexture, &repellerResourceTexture, &crossTexture, &attractorGreyedOutTexture, &repellerGreyedOutTexture, &plusTexture, &plusGreyedOutTexture, &aboutButtonTexture, &aboutButtonHoverTexture, &playButtonTexture, &playButtonHoverTexture};
    
    vector<string> textureID = {"background.png", "joeFinal.png", "enemy.png", "wall.png", "ground.png", "shop.png", "attractor.png", "repeller.png", "arm.png", "bullet.png", "gui.png", "2.png", "gold.png", "enemyArm.png", "attractorGem.png", "attractorResource.png", "repellerGem.png", "repellerResource.png", "cross.png", "attractorGreyedOut.png", "repellerGreyedOut.png", "plus.png", "plusGreyedOut.png", "aboutButton.png", "aboutButtonHover.png", "playButton.png", "playButtonHover.png"};
    
    
    for (int i = 0; i < allTextures.size(); i++){
        if(!allTextures.at(i)->loadFromFile( resourcePath() + textureID.at(i) ))
            return EXIT_FAILURE;
    }
    
    int MOUSE_INPUTS[3] = {0, 0, 0}; // LEFT, MIDDLE, RIGHT
    int KEY_INPUTS[7] = {0, 0, 0, 0, 0, 0, 0}; // W, A, S, D, E, ESCAPE, SPACEBAR
    
    Player* player;
    vector<Object> allObjects;
    vector<Object> allShops;
    vector<Enemy> allEnemies;
    vector<Bullet> allBullets;
    vector<Magnet> allMagnets;
    vector<Spawner> allSpawners;
    vector<Resource> allResources;
    vector<Loot> allLoots;
    vector<GUI_Button> allButtons;
    vector<GUI_Button> allShopButtons;
    
    
    vector<int> type = {1, 1, 1, 1};
    vector<int> type_NG = {0, 1, 1, 1};
    vector<int> type_NM = {1, 0, 1, 1};
    vector<int> type_NG_NM = {0, 0, 1, 1};
    
    Sprite bgSprite(bgTexture);
    
    Weapon playerWeapon = Weapon(type_NG_NM, Vector2f(45,45), &gunTexture, 5, 1.5, bulletTexture, true, type_NG, 0.15, 20, Vector2f(8, 8));
    
    Magnet lootMagnet = Magnet(1, type_NG, Vector2f(32, 32), Vector2f(), &attractorTexture, 50, -30, 0, 60);
    
    allSpawners.push_back(Spawner(type_NG_NM, Vector2f(10, 10), Vector2f(300, 300), &wallTexture, 225));
    
    allResources.push_back(Resource(3, type_NM, Vector2f(100, 50), Vector2f(200, 80), &repellerResourceTexture, 600, 0, 60, type, &repellerGemTexture, 2));
    
    allResources.push_back(Resource(3, type_NM, Vector2f(100, 50), Vector2f(400, 80), &attractorResourceTexture, 600, 0, 60, type, &attractorGemTexture, 1));
    
    allSpawners.at(0).activate();
    
    player = new Player(0.75, type, Vector2f(50, 50), Vector2f(50, 50), &playerTexture, 100, 10, 5, &playerWeapon, &lootMagnet, 9, 60);
    
    player->setSprite(*new Sprite(playerTexture,IntRect(0,0,16,16)));
    
    
    allObjects.push_back(Object(5, type_NG_NM, Vector2f(32, 250), Vector2f(0, 0), &wallTexture));
    allObjects.push_back(Object(5, type_NG_NM, Vector2f(32, 250), Vector2f(0, 900), &wallTexture));
    allObjects.push_back(Object(5, type_NG_NM, Vector2f(900, 32), Vector2f(0, 0), &wallTexture));
    allObjects.push_back(Object(5, type_NG_NM, Vector2f(900, 32), Vector2f(0, 250), &wallTexture));
    
    allShops.push_back(Object(5, type_NM, Vector2f(32, 24), Vector2f(100, 80), &shopTexture));
    
    Font font;
    if (!font.loadFromFile(resourcePath() + "munro.ttf")) {
        return EXIT_FAILURE;
    }
    
    GUI_Button playButton = GUI_Button(Vector2f(61,37), Vector2f(0,400), &playButtonTexture, &playButtonHoverTexture, 2);
    GUI_Button aboutButton = GUI_Button(Vector2f(61,37), Vector2f(250,400), &aboutButtonTexture, &aboutButtonHoverTexture, 1);
    
    allButtons.push_back(playButton);
    allButtons.push_back(aboutButton);
    
    
    //GUI
    sf::RectangleShape lifeBar, lifeBarBG, goldBar, attractorBar, repellerBar;
    sf::Sprite goldIcon, attractorIcon, repellerIcon;
    
    //LifeBar
    lifeBar.setSize(sf::Vector2f(150, 20));
    lifeBar.setPosition(sf::Vector2f(20, 20));
    lifeBar.setFillColor(Color(97, 216, 54));
    
    lifeBarBG.setSize(sf::Vector2f(150, 20));
    lifeBarBG.setPosition(sf::Vector2f(20, 20));
    lifeBarBG.setFillColor(Color(238, 17,0));
    lifeBarBG.setOutlineThickness(3);
    lifeBarBG.setOutlineColor(Color(0,0,0));
    
    //GoldBar
    goldBar.setSize(sf::Vector2f(75, 20));
    goldBar.setPosition(sf::Vector2f(window.getSize().x-20-goldBar.getSize().x, 20));
    goldBar.setFillColor(Color(246,200,0));
    goldBar.setOutlineThickness(3);
    goldBar.setOutlineColor(Color(0,0,0));
    
    goldIcon.setTexture(goldTexture);
    goldIcon.setPosition(window.getSize().x-16-goldBar.getSize().x, 22);
    
    GUI_Text goldLabel = GUI_Text(Vector2f(window.getSize().x-goldBar.getSize().x + 4,18), std::to_string(player->getGold()), 18, &font, Color::Black);
    
    //Attractor counter
    attractorBar.setSize(sf::Vector2f(75, 20));
    attractorBar.setPosition(sf::Vector2f(window.getSize().x-20-goldBar.getSize().x, 54));
    attractorBar.setFillColor(Color(30,146,255));
    attractorBar.setOutlineThickness(3);
    attractorBar.setOutlineColor(Color(0,0,0));
    
    attractorIcon.setTexture(attractorGemTexture);
    attractorIcon.setPosition(window.getSize().x-16-goldBar.getSize().x, 56);
    
    GUI_Text attractorLabel = GUI_Text(Vector2f(window.getSize().x-goldBar.getSize().x + 4,52), std::to_string(player->getAttractorGems()), 18, &font, Color::Black);
    
    //Repeller counter
    repellerBar.setSize(sf::Vector2f(75, 20));
    repellerBar.setPosition(sf::Vector2f(window.getSize().x-20-goldBar.getSize().x, 88));
    repellerBar.setFillColor(Color(255,0,0));
    repellerBar.setOutlineThickness(3);
    repellerBar.setOutlineColor(Color(0,0,0));
    
    repellerIcon.setTexture(repellerGemTexture);
    repellerIcon.setPosition(window.getSize().x-16-goldBar.getSize().x, 90);
    
    GUI_Text repellerLabel = GUI_Text(Vector2f(window.getSize().x-goldBar.getSize().x + 4,86), std::to_string(player->getRepellerGems()), 18, &font, Color::Black);
    
    sf::Clock clock;
    
    Level main_menu = Level(allButtons);
    
    allButtons.clear();
    
    Level level_zero = Level(player, allObjects, allShops, allEnemies, allBullets, allMagnets, allSpawners, allResources, allLoots, allButtons, allShopButtons);
    
    
    
    
    Game GAME;
    GAME.addLevel(&main_menu);
    GAME.addLevel(&level_zero);
    GAME.setTextures(&goldTexture, &enemyTexture, &enemyArmTexture, &bulletTexture, &attractorTexture, &repellerTexture, &crossTexture, &plusTexture, &plusGreyedOutTexture, &attractorGreyedOutTexture, &repellerGreyedOutTexture, &attractorGemTexture, &repellerGemTexture);
    GAME.setCurrentLevel(0);
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
                KEY_INPUTS[1] = 1;
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
                KEY_INPUTS[3] = 1;
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
                KEY_INPUTS[4] = 1;
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                KEY_INPUTS[5] = 1;
            
            if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Space))
                if(player->isItGrounded())
                    player->addForce(Vector2f(0, -player->getJumpForce()));
            
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A)
                KEY_INPUTS[1] = 0;
            
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D)
                KEY_INPUTS[3] = 0;
            
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::E)
                KEY_INPUTS[4] = 0;
            
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
                KEY_INPUTS[5] = 0;
            
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left)
                MOUSE_INPUTS[0] = 1;
            
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left)
                MOUSE_INPUTS[0] = 0;
            
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Right)
                MOUSE_INPUTS[1] = 1;
            
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Right)
                MOUSE_INPUTS[1] = 0;
            
        }
        
        window.setView(view);
        MOUSE_POS = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        window.setView(window.getDefaultView());
        
        GAME.update(MOUSE_INPUTS, KEY_INPUTS, MOUSE_POS);
        
        //Update HP and GUI
        if(GAME.getCurrentLevel() > 1){
            lifeBar.setSize(sf::Vector2f((float)player->getHP()/player->getMaxHP()*150, 20));
            goldLabel.setText(std::to_string(player->getGold()));
            attractorLabel.setText(std::to_string(player->getAttractorGems()));
            repellerLabel.setText(std::to_string(player->getRepellerGems()));
        }
        
        window.clear(sf::Color::White);
        //window.draw(bgSprite);
        
        view.setCenter(player->getPosition());
        window.setView(view);
        
        GAME.draw(&window);
        
        // Reset view and draw GUI
        window.setView(window.getDefaultView());
        
         MOUSE_POS = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        GAME.drawButtons(&window, MOUSE_POS, MOUSE_INPUTS);
        
        if(GAME.getCurrentLevel() > 1){
            window.draw(lifeBarBG);
            window.draw(lifeBar);
            
            window.draw(goldBar);
            window.draw(goldIcon);
            
            window.draw(attractorBar);
            window.draw(attractorIcon);
            
            window.draw(repellerBar);
            window.draw(repellerIcon);
            
            goldLabel.draw(&window);
            attractorLabel.draw(&window);
            repellerLabel.draw(&window);
        }
        
        window.display();
    
    }

    return EXIT_SUCCESS;
}
