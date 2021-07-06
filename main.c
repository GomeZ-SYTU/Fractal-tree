#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include <math.h>

#define he 680
#define we 780
#define GROWTH_COEFF 0.8
#define ANGLE_Growth M_PI/8

int ColorR = 0;

void Draw_Tree(SDL_Renderer *renderer, float x1, float y1, float x2, float y2, double direction, float dis, int precision)
{
    SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
    
    //recursion
    if (precision > 0)
    {
        //right   
        Draw_Tree(renderer, x2, y2, x2 + dis*sin(direction + ANGLE_Growth), y2 - dis*cos(direction + ANGLE_Growth), direction + ANGLE_Growth , dis*GROWTH_COEFF ,precision-1);
        
        //left
        Draw_Tree(renderer, x2, y2, x2 + dis*sin(direction - ANGLE_Growth), y2 - dis*cos(direction - ANGLE_Growth), direction - ANGLE_Growth , dis*GROWTH_COEFF ,precision-1);
    }
    else
    {
        return;
    }
}

int main(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Window *screen = NULL;
    SDL_Surface *windowSurface = NULL;
    SDL_Renderer *renderer = NULL;

    screen = SDL_CreateWindow("Tree Fractal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, we, he, SDL_WINDOW_OPENGL);
    if (screen == NULL)
    {
        fprintf(stderr, "Error creating the window : %s\n", SDL_GetError());
    }
    else
    {
        renderer = SDL_CreateRenderer(screen, -1, 0);
        windowSurface = SDL_GetWindowSurface(screen);

        SDL_UpdateWindowSurface(screen);

        //set the screen
        SDL_SetRenderDrawColor(renderer, 38, 38, 38, 255); // gray background color
        SDL_RenderClear(renderer);

        float hight_Line = 100;

        //Draw
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Line color
        Draw_Tree(renderer, windowSurface->w / 2, windowSurface->h, windowSurface->w / 2, windowSurface->h - hight_Line, 0, hight_Line, 15);

        //Show the renderings
        SDL_RenderPresent(renderer);

        //wait
        pause();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();

    return 0;
}

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
        }
    }
}