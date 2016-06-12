#include "MonoBehaviour.h"

VECTOR2 Normalize(VECTOR2 vector)
{
    float x = pow(vector.x,2);
    float y = pow(vector.y,2);
    float module = sqrt(x+y);

    vector.x = (vector.x / module) * 5;
    vector.y = (vector.y / module) * 5;

    return vector;
}

VECTOR2 GetVector(VECTOR2 vector1, VECTOR2 vector2)
{
     VECTOR2 newVector;
     newVector.x = vector2.x - vector1.x;
     newVector.y = vector2.y - vector1.y;

    return newVector;
}

int FadeIn(Uint8* alpha)
{
    if((*alpha) <= 0)
        return 1;
    else{
        (*alpha) -= 1;
    }

    return 0;
}

int FadeOut(Uint8* alpha)
{
    if((*alpha) >= 254)
        return 1;
    else{
        (*alpha) += 2;
    }

    return 0;
}


double Degree(VECTOR2 vector1, VECTOR2 vector2)
{
    vector1 = Normalize(vector1);
    vector2 = Normalize(vector2);

    double vetorialProduct = 0;
    vetorialProduct +=  vector1.x * vector2.x;
    vetorialProduct +=  vector1.y * vector2.y;

    double moduleVector1 = 0;
    double x = pow(vector1.x, 2);
    double y = pow(vector1.y, 2);
    moduleVector1 = sqrt((x + y));

    double moduleVector2 = 0;
    double x2 = pow(vector2.x, 2);
    double y2 = pow(vector2.y, 2); 
    moduleVector2 = sqrt((x2 + y2));

    double eq = 0;
    eq = vetorialProduct / (moduleVector1 * moduleVector2);
    printf("%lf\n",acos(eq)*100);
    return acos(eq) * 1000;
}
