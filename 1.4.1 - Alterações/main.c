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
    SDL_Rect r = {40, 20, 20, 20};
    SDL_Event evt;

    ColoredRect rects[10];
    int rect_count = 0;

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
        SDL_RenderFillRect(ren, &r);

        SDL_RenderPresent(ren);

        SDL_WaitEvent(&evt);
        if (evt.type == SDL_WINDOWEVENT){
            if (evt.window.event == SDL_WINDOWEVENT_CLOSE) {
                break;
            }
        }
        if (evt.type == SDL_KEYDOWN) {
            switch (evt.key.keysym.sym) {
                case SDLK_UP:
                    r.y -= 5;
                    if (r.y == 0){
                        r.y += 5;                        
                    }
                    break;
                case SDLK_DOWN:
                    r.y += 5;
                    if (r.y == 480){
                        r.y -= 5;                        
                    }
                    break;
                case SDLK_LEFT:
                    r.x -= 5;
                    if (r.x == 0){
                        r.x += 5;                        
                    }
                    break;
                case SDLK_RIGHT:
                    r.x += 5;
                    if (r.x == 480){
                        r.x -= 5;                        
                    }
                    break;
            }
        }
        if (evt.type == SDL_MOUSEBUTTONDOWN) {
            if (evt.button.button == SDL_BUTTON_LEFT && rect_count < 10) {
                rects[rect_count].rect.x = evt.button.x;
                rects[rect_count].rect.y = evt.button.y;
                rects[rect_count].rect.w = 20;
                rects[rect_count].rect.h = 20;
                rects[rect_count].color.r = rand() % 256;
                rects[rect_count].color.g = rand() % 256;
                rects[rect_count].color.b = rand() % 256;
                rects[rect_count].color.a = 0xFF;
                rect_count++;
            }
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}