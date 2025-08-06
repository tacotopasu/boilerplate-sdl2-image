#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

#include "include/ECS.h"
#include "include/DeltaTimer.h"

static EntityManager em;
static ComponentStorage cs;
static DeltaTimer deltaTimer;

int main(int argc, char* argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init() error: %s", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("Scalpel", 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        600, 800, 0);

    if (!window) {
        SDL_Log("SDL_CreateWindow() error: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer() error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Texture *tex = IMG_LoadTexture(renderer, "taco.png");
    if(!tex) {
        SDL_Log("IMG_Load() error: %s", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    DeltaTimer_Init(&deltaTimer);

    bool running = true;

    for(int i = 0; i < 1000; i++) {
        EntityID id = ECS_CreateEntity(&em);
        ECS_AddPosition(&cs, id, {(double)(rand() % 1080), (double)(rand() % 1920)});
        ECS_AddSize(&cs, id, {(double)(rand() % 100 + 1), (double)(rand() % 100 + 1)});
    }

    while(running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        DeltaTimer_Update(&deltaTimer);
        double dt = DeltaTimer_GetDeltaTime(&deltaTimer);

        // Clear screen before rendering!!
        SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
        SDL_RenderClear(renderer);

        for(int i = 0; i < 1000; i++) {
            cs.positions[i] = {cs.positions[i].x + rand() % 5 - 2, cs.positions[i].y + rand() % 5 - 2};
            cs.sizes[i] = {cs.sizes[i].w + rand() % 3 - 1, cs.sizes[i].h + rand() % 3 - 1};
            cs.sprites[i].color.r = rand() % 256;
            cs.sprites[i].color.g = rand() % 256;
            cs.sprites[i].color.b = rand() % 256;
            
            if (cs.positions[i].y < 0) cs.positions[i].y = 0;
            if (cs.positions[i].x < 0) cs.positions[i].x = 0;
        }

        for(int i = 0; i < 1000; i++) {
            // SDL_SetRenderDrawColor(renderer, cs.sprites[i].color.r, cs.sprites[i].color.g, cs.sprites[i].color.b, 255);
            SDL_Rect sdlRect = { (int)cs.positions[i].x, (int)cs.positions[i].y, (int)cs.sizes[i].w, (int)cs.sizes[i].h };
            SDL_SetTextureColorMod(tex, cs.sprites[i].color.r, cs.sprites[i].color.g, cs.sprites[i].color.b);
            SDL_RenderCopy(renderer, tex, nullptr, &sdlRect);
        }

        // Present rendered content!!
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(tex);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}