#include <SDL2/SDL.h>
#include <stdlib.h>


int AUX_WaitEventTimeout(SDL_Event* evt, Uint32* ms) {
    Uint32 antes = SDL_GetTicks();              
    int ret = SDL_WaitEventTimeout(evt, *ms);   
    Uint32 depois = SDL_GetTicks();             

    Uint32 gasto = depois - antes;             
    if (gasto >= *ms) {
        *ms = 0;                               
    } else {
        *ms -= gasto;                          
    }

    return ret;
}

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
} ColoredRect;

int main (int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo Retângulos",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         500, 500, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);


    SDL_Rect r1 = {40, 20, 120, 60};   // azul (anda sozinho)
    SDL_Rect r2 = {40, 200, 120, 60};  // verde (setas)
    SDL_Rect r3 = {40, 380, 120, 60};  // vermelho (segue mouse)
    SDL_Event evt;

    ColoredRect rects[10];
    int rect_count = 0;

    Uint32 timeout = 250;

    while (1) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
        SDL_RenderClear(ren);

 
        for (int i = 0; i < rect_count; i++) {
            SDL_SetRenderDrawColor(ren, rects[i].color.r, rects[i].color.g, rects[i].color.b, 0xFF);
            SDL_RenderFillRect(ren, &rects[i].rect);
        }


        SDL_SetRenderDrawColor(ren, 0, 0, 255, 0);
        SDL_RenderFillRect(ren, &r1);

        SDL_SetRenderDrawColor(ren, 0, 255, 0, 0);
        SDL_RenderFillRect(ren, &r2);

        SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
        SDL_RenderFillRect(ren, &r3);

        SDL_RenderPresent(ren);

        int isevt = AUX_WaitEventTimeout(&evt, &timeout);
        if (isevt) {
            if (evt.type == SDL_WINDOWEVENT) {
                if (evt.window.event == SDL_WINDOWEVENT_CLOSE) {
                    break;
                }
            }
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        r2.y -= 5;
                        if (r2.y < 0) r2.y = 0;
                        break;
                    case SDLK_DOWN:
                        r2.y += 5;
                        if (r2.y > 440) r2.y = 440;
                        break;
                    case SDLK_LEFT:
                        r2.x -= 5;
                        if (r2.x < 0) r2.x = 0;
                        break;
                    case SDLK_RIGHT:
                        r2.x += 5;
                        if (r2.x > 380) r2.x = 380;
                        break;
                }
            }
            if (evt.type == SDL_MOUSEMOTION) {
                int mousex, mousey;
                SDL_GetMouseState(&mousex, &mousey);
                r3.x = mousex;
                r3.y = mousey;
            }
        } else {

            r1.x += 5;
            if (r1.x > 500) r1.x = -r1.w;
            timeout = 250;
        }
    }


    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
