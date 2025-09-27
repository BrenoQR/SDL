#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>

#define MAX_STARS 100
#define MULTI_CLICK_TIMEOUT 250

typedef struct {
    int x, y;
    int visible;
} Star;


int pointInCircle(int px, int py, int cx, int cy, int r) {
    int dx = px - cx;
    int dy = py - cy;
    return (dx * dx + dy * dy) <= (r * r);
}

int AUX_WaitEventTimeout(SDL_Event* ev, int timeout) {
    Uint32 start = SDL_GetTicks();
    
    while (1) {
        if (SDL_WaitEventTimeout(ev, timeout))
            return 1;
            
        if ((SDL_GetTicks() - start) >= timeout)
            return 0;
    }
}

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* win = SDL_CreateWindow("Multi-Click Com Estrelas",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      400, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    Star stars[MAX_STARS] = {0};
    int starCount = 0;
    srand(time(NULL));

    int moonX = 200;
    int moonY = 200;
    int moonRadius = 30;

    int running = 1;
    int clickCount = 0;
    Uint32 lastClickTime = 0;

    SDL_Event e;

    while (running) {
        if (AUX_WaitEventTimeout(&e, 1)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = e.button.x;
                int mouseY = e.button.y;

                if (pointInCircle(mouseX, mouseY, moonX, moonY, moonRadius)) {
                    Uint32 currentTime = SDL_GetTicks();
                    
                    if (currentTime - lastClickTime <= MULTI_CLICK_TIMEOUT) {
                        clickCount++;
                    } else {
                        clickCount = 1;
                    }
                    
                    lastClickTime = currentTime;
                }
            }
            else if (e.type == SDL_USEREVENT) {
                for(int i = 0; i < e.user.code && starCount < MAX_STARS; i++) {
                    stars[starCount].x = rand() % 400;
                    stars[starCount].y = rand() % 400;
                    stars[starCount].visible = 1;
                    starCount++;
                }
            }
        }

        if (clickCount > 0 && SDL_GetTicks() - lastClickTime > MULTI_CLICK_TIMEOUT) {
            SDL_Event userEvent;
            userEvent.type = SDL_USEREVENT;
            userEvent.user.code = clickCount;
            SDL_PushEvent(&userEvent);
            
            SDL_Log("Múltiplos cliques detectados: %d", clickCount);
            
            clickCount = 0;
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 40, 255);
        SDL_RenderClear(ren);

        for(int i = 0; i < starCount; i++) {
            if(stars[i].visible) {
                filledCircleColor(ren, stars[i].x, stars[i].y, 2, 0xFFFFFFFF);
            }
        }

        filledCircleColor(ren, moonX, moonY, moonRadius, 0xFFFFFFFF);

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
