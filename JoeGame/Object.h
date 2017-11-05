//
//  Object.h
//  JoeGame
//
//  Created by Juan Lizarraga on 11/4/17.
//  Copyright © 2017 Juan Lizarraga. All rights reserved.
//

#ifndef Object_h
#define Object_h

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <math.h>
#include <vector>

using namespace std;
using namespace sf;


/*/

 TYPE MATRIX = [Gravity, Repeller, Attractor, Collision]

/*/

class Object{

protected:
    Vector2f acceleration;
    Vector2f velocity;
    Vector2f position;
    Vector2f size;
    vector<int> type;
    double density, mass, theta;
    bool isGrounded;
    Sprite sprite;
public:
    Object();
    Object(double _density, vector<int> &_type, Vector2f _size, Texture* texture);
    Object(double _density, vector<int> &_type, Vector2f _size, Vector2f _position, Texture* texture);
    void update(vector<Object> &colliders);
    void draw(RenderWindow* window);
    bool collidesWith(Object &other, int axis);
    void underlap(Rect<float> &otherBounds, int axis);
    void addForce(Vector2f force);
    void addForce(Vector2f force, int index);
    void setVelocity(Vector2f _velocity);
    void setVelocity(float _x, float _y);
    Vector2f getVelocity();
    float getVelocityX();
    float getVelocityY();
    //void setSprite(Sprite* sprite); TBI
    Sprite getSprite();
    bool isItGrounded();
    
};

//(&(*this))->a = a;



#endif /* Object_h */
