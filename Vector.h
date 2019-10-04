#include <iostream>
#include <cmath>
#ifndef Vector
#define Vector


struct Vector2f;
Vector2f add ( Vector2f v1, Vector2f v2 );
Vector2f sub ( Vector2f v1, Vector2f v2 );
Vector2f mul( Vector2f v, float a );
float scalar ( Vector2f v1, Vector2f v2 );
float modul ( Vector2f v );
Vector2f normalize ( Vector2f v );


#endif


struct Vector2f{
    float x = 0;
    float y = 0;
};


Vector2f add ( Vector2f v1, Vector2f v2 ){
    Vector2f result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    return result;
}


Vector2f sub ( Vector2f v1, Vector2f v2 ){
    Vector2f result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    return result;
}


Vector2f mul( Vector2f v, float a ){
    Vector2f result;
    result.x = a * v.x;
    result.y = a * v.y;
    return result;
}


float scalar ( Vector2f v1, Vector2f v2 ){
    return v1.x * v2.x + v1.y * v2.y;
}


float modul ( Vector2f v ){
    return sqrt( scalar( v, v) );
}


Vector2f normalize ( Vector2f v ){
    return mul( v, 1/modul( v ) );
}
