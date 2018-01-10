
#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>

bool leftMouseButtonDown = false;
bool quit = false;
SDL_Event event;


SDL_Window * window;
SDL_Renderer * renderer;
SDL_Texture * texture;
Uint32 * pixels =  (Uint32 *) malloc (sizeof(Uint32) *640 * 380);
typedef enum {FALSE,TRUE} boolean;
SDL_Surface * surf;
SDL_Surface* formattedSurface2;
SDL_Surface* controlsSurfaceBlackDots;
SDL_Texture * blackDotsTexture;

int mouseX,mouseY;

int main(int argc, char ** argv)
{

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("Image loading and draw on it",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 380);

    surf = SDL_CreateRGBSurface(0,640,380,32,0,0,0,0);
    formattedSurface2 = SDL_ConvertSurfaceFormat( surf, SDL_PIXELFORMAT_ARGB8888, NULL );

    controlsSurfaceBlackDots = IMG_Load("controls.png");
    blackDotsTexture = SDL_CreateTextureFromSurface(renderer, controlsSurfaceBlackDots);

    if( formattedSurface2 == NULL )
    {
        printf( "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError() );
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( surf );

    memset(pixels, 255, 640 * 380 * sizeof(Uint32));

    while (!quit)
    {
        SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));
        SDL_PollEvent(&event);

        SDL_Rect DestR;
        DestR.x = 100;
        DestR.y = 100;
        DestR.w = 100;
        DestR.h = 100;

        switch (event.type)
        {
        case SDL_KEYDOWN:
        {
            if (event.key.keysym.sym==SDLK_SPACE)
            {
                break;
            }

            if (event.key.keysym.sym==SDLK_1)
            {
                SDL_Surface *surf= IMG_Load("antipaxoi.png");
                SDL_Surface *toolsFormattedSurface = SDL_ConvertSurfaceFormat( surf, SDL_PIXELFORMAT_ARGB8888, NULL );
                free(surf);
                pixels =  (Uint32*) toolsFormattedSurface->pixels;
                break;
            }


            if (event.key.keysym.sym==SDLK_ESCAPE)
            {
                quit=TRUE;
                break;
            }


        }
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {

            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    leftMouseButtonDown = true;

                    SDL_GetMouseState( &mouseX, &mouseY );

                    std::cout<<mouseX<<","<<mouseY<<std::endl;

                    for(int i=-5;i<5;i++)
                    {
                        for(int j=-5;j<5;j++)
                        {
                            if( (640*(mouseY+j)+mouseX+i < 640*380) && (640*(mouseY+j)+mouseX+i >0) )//was 480
                                pixels[640*(mouseY+j)+mouseX+i]=0;
                        }
                    }

                }

            }
            break;

        case SDL_MOUSEMOTION:
            if (leftMouseButtonDown)
            {



            }
            break;
        case SDL_QUIT:
            quit = true;
            break;

        }

        //gui
        SDL_Rect gui;

        gui.x = 0;
        gui.y = 480-100;//380
        gui.w = 640;
        gui.h = 100;

        //drawing area
        SDL_Rect drawingArea;

        drawingArea.x = 0;
        drawingArea.y = 0;
        drawingArea.w = 640;
        drawingArea.h = 480-100;//380


        SDL_RenderCopy(renderer, texture, NULL, &drawingArea);
        SDL_RenderCopy(renderer, blackDotsTexture, NULL, &gui);


        //update the rendered image
        SDL_RenderPresent(renderer);

    }

    SDL_FreeSurface( formattedSurface2 );

    free(pixels);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


