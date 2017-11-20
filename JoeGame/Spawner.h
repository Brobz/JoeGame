//
//  Spawner.h
//  JoeGame
//
//  Created by Guilherme Bittencourt de Borba on 11/20/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Spawner_h
#define Spawner_h

#include "Object.h"

class Spawner : public Object{
  
protected:
    bool active, canSpawn;
    double spawnRate, ticksUntillNextSpawn;
    
public:
    Spawner();
    Spawner(vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture, double _spawnRate);
    void update();
    void activate(bool inverse = false);
    void spawned();
    bool isActive();
    bool canItSpawn();
};


#endif /* Spawner_h */
