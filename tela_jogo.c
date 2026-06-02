#include <stdio.h>
#include "tela_jogo.h"

estado executa_tela_jogo(ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE *fila) {
    ALLEGRO_BITMAP *cenario = al_load_bitmap("imagens/stonehenge.png");
    ALLEGRO_EVENT evento;
    estado proximo = TELA_JOGO;
    int fim = 0, cenario_w, cenario_h;

    while (!fim) {
        al_wait_for_event(fila, &evento);

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            proximo = SAIR;
            fim = 1;
        }

        if (evento.type == ALLEGRO_EVENT_KEY_DOWN &&
            evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            proximo = TELA_INICIAL;
            fim = 1;
        }

        cenario_w = al_get_bitmap_width(cenario);
        cenario_h = al_get_bitmap_height(cenario);
        al_draw_scaled_bitmap(cenario, 0, 0, cenario_w, cenario_h, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);
        al_flip_display();
    }

    al_destroy_bitmap(cenario);
    return proximo;
}