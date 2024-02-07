#include "ModuloCoordenada.h"
#include <Windows.h>

//HECHAS
bool operator== (tCoor c1, tCoor c2)
{
    bool sol = false;
    if (c1.ejeX == c2.ejeX && c1.ejeY == c2.ejeY)
    {
        sol = true;
    }
    return sol;
}
bool operator!= (tCoor c1, tCoor c2)
{
    bool sol = true;
    if (c1.ejeX == c2.ejeX && c1.ejeY == c2.ejeY)
    {
        sol = false;
    }
    return sol;
}
tCoor operator+ (tCoor c1, tCoor c2)
{
    c1.ejeX += c2.ejeX;
    c1.ejeY += c2.ejeY;
    return c1;
}
//SIN HACER