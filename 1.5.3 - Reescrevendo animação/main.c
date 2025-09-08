#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main(int argc, char* args[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Animacao Orientada a Eventos",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    float y = 0;            
    float speed = 80.0f;   // pixels por segundo
    Uint32 lastTick = SDL_GetTicks();
    int running = 1;

    Uint32 circleColor = 0xFF0000FF; // vermelho inicial
    int direction = 1;               // 1 = descendo, -1 = subindo

    SDL_Event e;

    while(running){
        // processa todos os eventos pendentes
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = 0;
            }
            else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_SPACE){
                    // evento: inverter direção e cor
                    direction *= -1;
                    if(circleColor == 0xFF0000FF) // vermelho → verde
                        circleColor = 0x00FF00FF;
                    else
                        circleColor = 0xFF0000FF;
                }
            }
        }

        // cálculo do delta
        Uint32 now = SDL_GetTicks();
        float delta = (now - lastTick) / 1000.0f;
        lastTick = now;

        // atualiza posição
        y += direction * speed * delta;

        // mantém dentro dos limites (loop vertical)
        if(y > 200) y = -10;
        if(y < -10) y = 200;

        // desenha
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        filledCircleColor(ren, 100, (int)y, 10, circleColor);
        SDL_RenderPresent(ren);

        SDL_Delay(10); // reduz uso da CPU
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
