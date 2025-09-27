#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    int finished;   // 1 = já cruzou a linha de chegada
    int place;      // ordem de chegada
    const char* name;
} Runner;

int main(int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Corrida de Retângulos",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       600, 500, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    SDL_Event evt;
    int running = 1;

    while (running) {
        // estado inicial
        Runner runners[3] = {
            {{40, 20, 120, 60},  {0, 0, 255, 255}, 0, 0, "Azul"},     // automático
            {{40, 200, 120, 60}, {0, 255, 0, 255}, 0, 0, "Verde"},   // teclado
            {{40, 380, 120, 60}, {255, 0, 0, 255}, 0, 0, "Vermelho"} // mouse
        };

        int finishedCount = 0;
        int winner = -1;
        int order = 1;
        int finishX = 500; // linha de chegada

        Uint32 timeout = 50;

        while (finishedCount < 3 && running) {
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
            SDL_RenderClear(ren);

            // desenhar linha de chegada
            SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
            SDL_RenderDrawLine(ren, finishX, 0, finishX, 500);

            // desenhar corredores
            for (int i = 0; i < 3; i++) {
                SDL_SetRenderDrawColor(ren,
                                       runners[i].color.r,
                                       runners[i].color.g,
                                       runners[i].color.b,
                                       255);
                SDL_RenderFillRect(ren, &runners[i].rect);
            }

            SDL_RenderPresent(ren);

            // esperar evento ou timeout
            Uint32 antes = SDL_GetTicks();
            int isevt = SDL_WaitEventTimeout(&evt, timeout);
            Uint32 depois = SDL_GetTicks();
            Uint32 gasto = depois - antes;
            if (gasto >= timeout) timeout = 0;
            else timeout -= gasto;

            if (isevt) {
                if (evt.type == SDL_WINDOWEVENT &&
                    evt.window.event == SDL_WINDOWEVENT_CLOSE) {
                    running = 0;
                    break;
                }
                if (evt.type == SDL_KEYDOWN) {
                    switch (evt.key.keysym.sym) {
                        case SDLK_UP:    runners[1].rect.y -= 5; break;
                        case SDLK_DOWN:  runners[1].rect.y += 5; break;
                        case SDLK_LEFT:  runners[1].rect.x -= 5; break;
                        case SDLK_RIGHT: runners[1].rect.x += 5; break;
                    }
                }
                if (evt.type == SDL_MOUSEMOTION) {
                    runners[2].rect.x = evt.motion.x;
                    runners[2].rect.y = evt.motion.y;
                }
            } else {
                timeout = 50; // reinicia timeout

                // mover somente o azul automaticamente
                if (!runners[0].finished) {
                    runners[0].rect.x += (rand() % 10) + 1;
                }
            }

            // checar chegada
            for (int i = 0; i < 3; i++) {
                if (!runners[i].finished &&
                    runners[i].rect.x + runners[i].rect.w >= finishX) {
                    runners[i].finished = 1;
                    runners[i].place = order++;
                    finishedCount++;
                    if (winner == -1) {
                        winner = i;
                    }
                }
            }
        }

        if (!running) break;

        // anunciar vencedor no console (via SDL_Log)
        SDL_Log("Vencedor: %s", runners[winner].name);

        // Substituir SDL_Delay(3000) com um timer
        Uint32 waitStart = SDL_GetTicks();
        while (SDL_GetTicks() - waitStart < 3000 && running) {
            SDL_Event tempEvent;
            if (SDL_WaitEventTimeout(&tempEvent, 100)) {
                if (tempEvent.type == SDL_WINDOWEVENT &&
                    tempEvent.window.event == SDL_WINDOWEVENT_CLOSE) {
                    running = 0;
                }
            }
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
