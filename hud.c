#include "hud.h"

void inicializa_hud(hud *h) {
    h -> vida = al_load_bitmap("imagens/vida.png");
    h -> vida_extra = al_load_bitmap("imagens/vida_extra.png");
}

void desenha_hud(hud *h, personagem *p) {
    for (int i = 0; i < (p -> vidas); i++) {
        if (p -> wisp_coletado && i == (p -> vidas) - 1)
            al_draw_bitmap(h -> vida_extra, CORACAO_X + i * CORACAO_ESPACO, CORACAO_Y, 0);
        else
            al_draw_bitmap(h -> vida, CORACAO_X + i * CORACAO_ESPACO, CORACAO_Y, 0);
    }
}

void destroi_hud(hud *h) {
    al_destroy_bitmap(h -> vida);
    al_destroy_bitmap(h -> vida_extra); 
}