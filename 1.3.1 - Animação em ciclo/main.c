#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main(int argc, char* args[]){
    
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Animacao em Loop",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    float y = 0;            // posição vertical do círculo
    float speed = 10.0f;   // pixels por segundo
    Uint32 lastTick = SDL_GetTicks();
    int running = 1;

    SDL_Event e; // evento único

    while(running){
        // processa um único evento por iteração
        if(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) running = 0;
        }

        // cálculo do delta
        Uint32 now = SDL_GetTicks();
        float delta = (now - lastTick) / 1000.0f;
        lastTick = now;

        // atualiza posição
        y += speed * delta;

        // loop vertical contínuo
        if(y > 200) y = -10;

        // desenha
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        filledCircleColor(ren, 100, (int)y, 10, 0xFF0000FF);
        SDL_RenderPresent(ren);

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
