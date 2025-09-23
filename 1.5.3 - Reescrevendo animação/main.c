#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Animacao com SDL_WaitEventTimeout",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      200, 200, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    float y = 0;
    float speed = 80.0f; 
    Uint32 lastTick = SDL_GetTicks();
    int running = 1;

    Uint32 circleColor = 0xFF0000FF; 
    int direction = 1;   

    SDL_Event e;

    while (running) {
        if (SDL_WaitEventTimeout(&e, 10)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
        }

        Uint32 now = SDL_GetTicks();
        float delta = (now - lastTick) / 1000.0f;
        lastTick = now;

        y += direction * speed * delta;

        if (y > 210) y = -10;
        if (y < -10) y = 210;

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        filledCircleColor(ren, 100, (int)y, 10, circleColor);
        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}