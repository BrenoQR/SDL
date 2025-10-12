#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdbool.h>

typedef enum {
    IDLE,       
    PRESSED,    
    DRAGGING,   
} SquareState;


typedef struct {
    int x, y;           
    int size;          
    int orig_x, orig_y; // posicao original para cancelar
    SquareState state;
} Square;


int AUX_WaitEventTimeout(SDL_Event* ev, int timeout) {
    Uint32 start = SDL_GetTicks();
    
    while (1) {
        if (SDL_WaitEventTimeout(ev, timeout))
            return 1;
            
        if ((SDL_GetTicks() - start) >= timeout)
            return 0;
    }
}

// Verifica se ponto está dentro do quadrado
bool point_in_square(int px, int py, Square* square) {
    return (px >= square->x && px <= square->x + square->size &&
            py >= square->y && py <= square->y + square->size);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Drag, Click, or Cancel",
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    
    Square square = {
        .x = 350,      
        .y = 250,      
        .size = 100,   
        .orig_x = 350, 
        .orig_y = 250, 
        .state = IDLE  
    };

    int drag_offset_x = 0;
    int drag_offset_y = 0;
    bool running = true;

    while (running) {
        SDL_Event ev;
        if (AUX_WaitEventTimeout(&ev, 16)) {
            switch (ev.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (ev.button.button == SDL_BUTTON_LEFT &&
                        square.state == IDLE &&
                        point_in_square(ev.button.x, ev.button.y, &square)) {
                        
                        square.state = PRESSED;
                        drag_offset_x = ev.button.x - square.x;
                        drag_offset_y = ev.button.y - square.y;
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if (ev.button.button == SDL_BUTTON_LEFT) {
                        if (square.state == PRESSED) {
                            // Era um clique
                            printf("Click!\n");
                        }
                        else if (square.state == DRAGGING) {
                            // Finalizou arrasto
                            printf("Drop!\n");
                        }
                        square.state = IDLE;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (square.state == PRESSED || square.state == DRAGGING) {
                        square.state = DRAGGING;
                        square.x = ev.motion.x - drag_offset_x;
                        square.y = ev.motion.y - drag_offset_y;
                    }
                    break;

                case SDL_KEYDOWN:
                    if (ev.key.keysym.sym == SDLK_ESCAPE &&
                        (square.state == PRESSED || square.state == DRAGGING)) {
                        // Cancela
                        square.x = square.orig_x;
                        square.y = square.orig_y;
                        square.state = IDLE;
                        printf("Cancelled!\n");
                    }
                    break;
            }
        }

        
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        
        boxRGBA(ren, square.x, square.y, 
                square.x + square.size, square.y + square.size,
                255, 255, 255, 255);

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}