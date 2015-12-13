#include "TerrainGenerator.h"
#include "cmath"
float pseudoRandom(int x, int y)
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
    return 1.0 - float(t) * 0.931322574615478515625e-9;
}

float smoothPseudoRandom(float x,float y)
{
    float corners = float(pseudoRandom(x-1,y-1) + pseudoRandom(x-1,y+1) + pseudoRandom(x+1,y-1) + pseudoRandom(x+1,y+1))/16.0;
    float sides = float(pseudoRandom(x,y-1) + pseudoRandom(x-1,y) + pseudoRandom(x+1,y) + pseudoRandom(x,y+1))/8.0;
    float center = float(pseudoRandom(x,y))/4.0;
    return corners + sides + center;
}

float interpolate(float a, float b, float x)
{
    float ft = x * 3.1415927;
	float f = (1.0 - cos(ft)) * 0.5;

	return  a*(1.0-f) + b*f;
}

float interpolatedNoise(float x, float y)
{
    x += 10000;
    y += 10000;
    int intX = floor(x);
    int intY = floor(y);
    float fracX = x-intX;
    float fracY = y-intY;

    float v1 = smoothPseudoRandom(x,y);
    float v2 = smoothPseudoRandom(x+1,y);
    float v3 = smoothPseudoRandom(x,y+1);
    float v4 = smoothPseudoRandom(x+1,y+1);

    float sol = interpolate(interpolate(v1,v2,fracX),interpolate(v3,v4,fracX),fracY);
    return sol;
}

float valueNoise(float x, float y)
{
    float total = 0;
    float p = 1/8.0;
    int n = 4;

    float frequency = 1/32.0;
    float amplitude = 120;
    for(int i=0; i<n; i++)
    {
        frequency*=2.0;
        amplitude*=p;
        total+= interpolatedNoise(x*frequency, y*frequency)*amplitude;
    }
    return total;
}

float getTerrain(float x, float y)
{
    float base = valueNoise(x,y);
    float mountain = interpolatedNoise(x/100,y/100);
    mountain+=0.1;
    if(mountain> 0)
    {
        mountain*=400;
        float peak = interpolatedNoise(x/16,y/16)*50;
        if (peak>0)
            return base+mountain+peak;
        else
            return base+mountain;
    }
    else
    {
        return base;
    }
}
