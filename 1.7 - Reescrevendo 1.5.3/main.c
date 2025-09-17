#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char* args[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* win = SDL_CreateWindow("Animacao com Sprites",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      400, 200, SDL_WINDOW_SHOWN
                                     );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

   
    SDL_Surface* surface = IMG_Load("bird.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);

    // Variáveis de movimento
    float x = 0;
    float speed = 100.0f; // pixels por segundo
    Uint32 lastTick = SDL_GetTicks();
    int running = 1;

    SDL_Rect clips[2];
    int textureH;
    SDL_QueryTexture(texture, NULL, NULL, NULL, &textureH);

    clips[0].x = 0;
    clips[0].y = 0;
    clips[0].w = 100;
    clips[0].h = textureH;

    clips[1].x = 100;
    clips[1].y = 0;
    clips[1].w = 100;
    clips[1].h = textureH;

    int currentFrame = 0;
    Uint32 lastFrameChange = SDL_GetTicks();
    const int ANIMATION_DELAY = 150;

    SDL_Event e;

    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = 0;
            }
        }

        Uint32 now = SDL_GetTicks();
        float delta = (now - lastTick) / 1000.0f;
        lastTick = now;

        x += speed * delta;

        if (now - lastFrameChange > ANIMATION_DELAY) {
            currentFrame = (currentFrame + 1) % 2;
            lastFrameChange = now;
        }

        if(x > 400) x = -clips[currentFrame].w;

        SDL_Rect destRect;
        destRect.x = (int)x;
        destRect.y = 80;
        destRect.w = clips[currentFrame].w;
        destRect.h = clips[currentFrame].h;

        SDL_SetRenderDrawColor(ren, 135, 206, 235, 255);
        SDL_RenderClear(ren);

        SDL_RenderCopy(ren, texture, &clips[currentFrame], &destRect);

        SDL_RenderPresent(ren);

        SDL_Delay(10); // reduz uso da CPU
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return 0;
}