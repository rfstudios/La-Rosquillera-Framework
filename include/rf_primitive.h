#ifndef RF_PRIMITIVE_H
#define RF_PRIMITIVE_H

#include "rf_engine.h"
#include "rf_declares.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <string>
using namespace std;

class RF_Primitive
{
    public:
        RF_Primitive() {}
        virtual ~RF_Primitive() {}

        static void drawLine(SDL_Surface* surf, Vector2<int> p0, Vector2<int> p1, Uint32 color){
            int dX = p1.x - p0.x;
            int dY = p1.y - p0.y;

            float pasos = abs(dX);
            if(abs(dY) >= abs(dX))
            {
                pasos = abs(dY);
            }

            Vector2<float> inc = Vector2<float>(dX/pasos, dY/pasos);
            Vector2<float> pF = Vector2<float>((float)p0.x,(float)p0.y);
            for(int i = 0; i < pasos; i++)
            {
                RF_Primitive::putPixel(surf,(int)pF.x,(int)pF.y,color);
                pF.x += inc.x;
                pF.y += inc.y;
            }
        }
        static void drawFCircle(SDL_Surface* surf, Vector2<int> p, int r, Uint32 color){
            for(float i = 0; i <= r; i+=0.1)
            {
                float j2 = r*r-i*i;
                float j = sqrt(j2);

                drawLine(surf,Vector2<int>(p.x-round(i),p.y-round(j)), Vector2<int>(p.x+round(i),p.y-round(j)),color);
                drawLine(surf,Vector2<int>(p.x-round(i),p.y+round(j)), Vector2<int>(p.x+round(i),p.y+round(j)),color);
            }
        }
        static void drawCircle(SDL_Surface* surf, Vector2<int> p, int r, Uint32 color){
            for(float i = 0; i <= r; i+=0.1)
            {
                float j2 = r*r-i*i;
                float j = sqrt(j2);

                putPixel(surf,p.x+round(i),p.y+round(j),color);
                putPixel(surf,p.x-round(i),p.y+round(j),color);

                putPixel(surf,p.x+round(i),p.y-round(j),color);
                putPixel(surf,p.x-round(i),p.y-round(j),color);
            }
        }
        static Uint32 getPixel(SDL_Surface* surface, int x, int y){
            int bpp = surface->format->BytesPerPixel;
            /* Here p is the address to the pixel we want to retrieve */
            Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

            switch(bpp) {
            case 1:
                return *p;
                break;

            case 2:
                return *(Uint16 *)p;
                break;

            case 3:
                if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                    return p[0] | p[1] << 8 | p[2] << 16;
                else
                    return p[0] << 16 | p[1] << 8 | p[2];
                break;

            case 4:
                return *(Uint32 *)p;
                break;

            default:
                return 0;       /* shouldn't happen, but avoids warnings */
            }
        }
        static void putPixel(SDL_Surface* surface, int x, int y, Uint32 pixel){
            if(0 > x || 0 > y || surface->w <= x || surface->h <= y){return;}

            int bpp = surface->format->BytesPerPixel;
            Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

            switch(bpp) {
            case 1:
                *p = pixel;
                break;

            case 2:
                *(Uint16 *)p = pixel;
                break;

            case 3:
                if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                    p[0] = (pixel >> 16) & 0xff;
                    p[1] = (pixel >> 8) & 0xff;
                    p[2] = pixel & 0xff;
                } else {
                    p[0] = pixel & 0xff;
                    p[1] = (pixel >> 8) & 0xff;
                    p[2] = (pixel >> 16) & 0xff;
                }
                break;

            case 4:
                *(Uint32 *)p = pixel;
                break;
            }
        }
};

#endif // RF_PRIMITIVE_H
