#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main(int argc, char* args[]) {
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Olho",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            1000, 600, SDL_WINDOW_SHOWN
                        );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    SDL_SetRenderDrawColor(ren, 171, 116, 229, 255);
    SDL_RenderClear(ren);

    // Elipse
    filledEllipseRGBA(ren, 500, 300, 400, 250, 255, 255, 255, 255);
    ellipseRGBA(ren, 500, 300, 400, 250, 0, 0, 0, 255);

    // Circulo
    filledCircleRGBA(ren, 500, 300, 150, 0, 0, 0, 255);

    SDL_RenderPresent(ren);
    SDL_Delay(5000);
    
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}