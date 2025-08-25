#include <SDL2/SDL.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Noite Estrelada",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         1000, 600, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_SetRenderDrawColor(ren, 0x00,0x00,0x00,0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0x00,0x00);
    SDL_Rect r1 = {40, 20, 5, 5};
    SDL_RenderFillRect(ren, &r1);
    SDL_Rect r2 = {200, 500, 5, 5};
    SDL_RenderFillRect(ren, &r2);
    SDL_Rect r3 = {300, 100, 5, 5};
    SDL_RenderFillRect(ren, &r3);
    SDL_Rect r4 = {800, 400, 5, 5};
    SDL_RenderFillRect(ren, &r4);
    SDL_Rect r5 = {900, 50, 5, 5};
    SDL_RenderFillRect(ren, &r5);
    SDL_Rect r6 = {600, 300, 5, 5};
    SDL_RenderFillRect(ren, &r6);
    SDL_Rect r7 = {750, 200, 5, 5};
    SDL_RenderFillRect(ren, &r7);
    SDL_Rect r8 = {500, 150, 5, 5};
    SDL_RenderFillRect(ren, &r8);
    SDL_Rect r9 = {400, 400, 5, 5};
    SDL_RenderFillRect(ren, &r9);
    SDL_Rect r10 = {150, 250, 5, 5};
    SDL_RenderFillRect(ren, &r10);
    SDL_Rect r11 = {350, 350, 5, 5};
    SDL_RenderFillRect(ren, &r11);
    SDL_Rect r12 = {250, 450, 5, 5};
    SDL_RenderFillRect(ren, &r12);
    SDL_Rect r13 = {450, 50, 5, 5};
    SDL_RenderFillRect(ren, &r13);
    SDL_Rect r14 = {700, 500, 5, 5};
    SDL_RenderFillRect(ren, &r14);
    SDL_Rect r15 = {850, 300, 5, 5};
    SDL_RenderFillRect(ren, &r15);
    SDL_RenderPresent(ren);
    SDL_Delay(5000);

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}