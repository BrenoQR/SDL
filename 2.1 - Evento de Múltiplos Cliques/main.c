#include <SDL2/SDL.h>
#include <stdio.h>

// --- Constantes ---
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define CLICK_TIMEOUT_MS 250

// --- Estrutura para gerenciar o estado do clique múltiplo ---
typedef struct {
    SDL_bool active;   // A sequência de cliques está ativa?
    int count;         // Quantos cliques na sequência atual
    int x, y;          // Posição do primeiro clique da sequência
    Uint32 last_tick;  // Timestamp do último clique (ms)
} MultiClickState;

// --- Variáveis Globais ---
SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
MultiClickState g_multi_click_state = {SDL_FALSE, 0, 0, 0, 0};
// Área clicável do nosso pudim (será calculada depois)
SDL_Rect g_pudding_clickable_area;


// --- Funções Auxiliares ---

// Inicializa SDL, janela e renderer
int initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL não pôde ser inicializado! Erro: %s\n", SDL_GetError());
        return 0;
    }

    g_window = SDL_CreateWindow("Pudim Clicker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!g_window) {
        printf("Janela não pôde ser criada! Erro: %s\n", SDL_GetError());
        return 0;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!g_renderer) {
        printf("Renderer não pôde ser criado! Erro: %s\n", SDL_GetError());
        return 0;
    }
    
    return 1;
}

// Libera recursos e finaliza SDL
void shutdown() {
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    g_renderer = NULL;
    g_window = NULL;
    SDL_Quit();
}

// Função para desenhar nosso pudim com primitivas do SDL
void draw_pudding() {
    int pudim_width = 200;
    int pudim_height = 120;
    int center_x = SCREEN_WIDTH / 2;
    int center_y = SCREEN_HEIGHT / 2;

    // A calda (topo)
    SDL_Rect caramel_rect = {
        center_x - pudim_width / 2,
        center_y - pudim_height / 2,
        pudim_width,
        pudim_height / 3
    };
    SDL_SetRenderDrawColor(g_renderer, 218, 165, 32, 255); // Cor: Goldenrod (dourado)
    SDL_RenderFillRect(g_renderer, &caramel_rect);

    // O corpo do pudim
    SDL_Rect body_rect = {
        center_x - pudim_width / 2,
        caramel_rect.y + caramel_rect.h,
        pudim_width,
        pudim_height * 2 / 3
    };
    SDL_SetRenderDrawColor(g_renderer, 139, 69, 19, 255); // Cor: SaddleBrown (marrom)
    SDL_RenderFillRect(g_renderer, &body_rect);

    // Define a área clicável total do pudim
    g_pudding_clickable_area.x = caramel_rect.x;
    g_pudding_clickable_area.y = caramel_rect.y;
    g_pudding_clickable_area.w = pudim_width;
    g_pudding_clickable_area.h = pudim_height;
}


// Verifica se o tempo de espera de um clique múltiplo expirou.
void check_multiclick_timeout() {
    if (!g_multi_click_state.active) {
        return;
    }

    if (SDL_GetTicks() - g_multi_click_state.last_tick >= CLICK_TIMEOUT_MS) {
        printf("Timeout detectado. Enviando evento de clique múltiplo com contagem: %d\n", g_multi_click_state.count);

        SDL_Event user_event;
        SDL_zero(user_event);
        user_event.type = SDL_USEREVENT;
        user_event.user.windowID = SDL_GetWindowID(g_window);
        user_event.user.code = g_multi_click_state.count;

        SDL_PushEvent(&user_event);

        g_multi_click_state.active = SDL_FALSE;
        g_multi_click_state.count = 0;
    }
}

// --- Função Principal ---
int main(int argc, char* args[]) {
    if (!initialize()) {
        printf("Falha na inicialização!\n");
        return 1;
    }

    SDL_bool quit = SDL_FALSE;
    SDL_Event e;

    // Loop principal da aplicação
    while (!quit) {
        if (SDL_WaitEventTimeout(&e, 1)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = SDL_TRUE;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        SDL_Point mouse_pos = {e.button.x, e.button.y};
                        // Verifica se o clique foi dentro do pudim
                        if (SDL_PointInRect(&mouse_pos, &g_pudding_clickable_area)) {
                            // Se já existe uma sequência ativa E o clique foi no mesmo lugar
                            if (g_multi_click_state.active &&
                                e.button.x == g_multi_click_state.x &&
                                e.button.y == g_multi_click_state.y) {
                                g_multi_click_state.count++;
                                g_multi_click_state.last_tick = SDL_GetTicks();
                                printf("Clique %d na sequência.\n", g_multi_click_state.count);
                            } else {
                                printf("Iniciando nova sequência de cliques.\n");
                                g_multi_click_state.active = SDL_TRUE;
                                g_multi_click_state.count = 1;
                                g_multi_click_state.x = e.button.x;
                                g_multi_click_state.y = e.button.y;
                                g_multi_click_state.last_tick = SDL_GetTicks();
                            }
                        } else {
                             // Se clicar fora do pudim, reseta o estado
                             g_multi_click_state.active = SDL_FALSE;
                        }
                    }
                    break;

                case SDL_USEREVENT: {
                    Sint32 click_count = e.user.code;
                    char window_title[128];

                    if (click_count == 1) {
                        sprintf(window_title, "Pudim Clicker - Clique único!");
                    } else if (click_count == 2) {
                        sprintf(window_title, "Pudim Clicker - Clique duplo! (%d)", click_count);
                    } else if (click_count == 3) {
                        sprintf(window_title, "Pudim Clicker - Clique TRIPLO! (%d)", click_count);
                    } else {
                        sprintf(window_title, "Pudim Clicker - Múltiplos cliques! (%d)", click_count);
                    }
                    // Atualiza o título da janela para dar feedback ao usuário
                    SDL_SetWindowTitle(g_window, window_title);
                    break;
                }
            }
        }

        // A CADA FRAME: Verificamos o timeout do clique múltiplo.
        check_multiclick_timeout();

        // --- Seção de Renderização ---
        SDL_SetRenderDrawColor(g_renderer, 30, 30, 50, 255); // Fundo azul escuro
        SDL_RenderClear(g_renderer);

        // Desenha nosso pudim feito de retângulos
        draw_pudding();

        SDL_RenderPresent(g_renderer);
    }

    shutdown();
    return 0;
}