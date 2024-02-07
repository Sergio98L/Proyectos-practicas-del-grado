#ifndef Coordenada_H
#define Coordenada_H
typedef struct
{
    int ejeX;
    int ejeY;
}tCoor;

bool operator== (tCoor c1, tCoor c2);
bool operator!= (tCoor c1, tCoor c2);
tCoor operator+ (tCoor c1, tCoor c2);
#endif