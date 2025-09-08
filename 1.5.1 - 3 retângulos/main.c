#include <SDL2/SDL.h>
#include <stdlib.h> // for rand()

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
} ColoredRect;

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         500, 500, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect r1 = {40, 20, 120, 60};
    SDL_Rect r2 = {40, 200, 120, 60};
    SDL_Rect r3 = {40, 380, 120, 60};
    SDL_Event evt;

    ColoredRect rects[10];
    int rect_count = 0;

    int timer = 250;

    while (1) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0,0);
        SDL_RenderClear(ren);

        // Draw all user rectangles
        for (int i = 0; i < rect_count; i++) {
            SDL_SetRenderDrawColor(ren, rects[i].color.r, rects[i].color.g, rects[i].color.b, 0xFF);
            SDL_RenderFillRect(ren, &rects[i].rect);
        }

        // Draw the moving blue rectangle
        SDL_SetRenderDrawColor(ren, 0, 0, 255, 0);
        SDL_RenderFillRect(ren, &r1);

        SDL_SetRenderDrawColor(ren, 0, 255, 0, 0);
        SDL_RenderFillRect(ren, &r2);

        SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
        SDL_RenderFillRect(ren, &r3);

        SDL_RenderPresent(ren);
        
        Uint32 antes = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout(&evt, timer);
        if (isevt){
            timer -= (SDL_GetTicks() - antes);
            if (evt.type == SDL_WINDOWEVENT){
                if (evt.window.event == SDL_WINDOWEVENT_CLOSE) {
                    break;
                }
            }
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        r2.y -= 5;
                        if (r2.y == 0){
                            r2.y += 5;                        
                        }
                        break;
                    case SDLK_DOWN:
                        r2.y += 5;
                        if (r2.y == 480){
                            r2.y -= 5;                        
                        }
                        break;
                    case SDLK_LEFT:
                        r2.x -= 5;
                        if (r2.x == 0){
                            r2.x += 5;                        
                        }
                        break;
                    case SDLK_RIGHT:
                        r2.x += 5;
                        if (r2.x == 480){
                            r2.x -= 5;                        
                        }
                        break;
                }
            }
            if (evt.type == SDL_MOUSEMOTION){
                int mousex = 1;
                int mousey = 1;
                SDL_GetMouseState(&mousex, &mousey);
                r3.x = mousex;
                r3.y = mousey;
            }
        } else{
            timer = 500;
            r1.x += 5;
        }
        
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
