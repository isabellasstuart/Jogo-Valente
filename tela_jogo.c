#include <stdio.h>
#include "tela_jogo.h"
#include "personagem.h"

estado executa_tela_jogo(ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE *fila) {
    ALLEGRO_BITMAP *cenario = al_load_bitmap("imagens/stonehenge.png");
    ALLEGRO_EVENT evento;
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0); // Timer para controlar o loop a 60 FPS
    estado proximo = TELA_JOGO;
    personagem merida;
    int fim = 0, cenario_w, cenario_h, desenhar = 0;
    
    al_register_event_source(fila, al_get_timer_event_source(timer));
    al_start_timer(timer);
    inicializa_personagem(&merida, INICIALIZA_X, INICIALIZA_Y);

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
        
        if (evento.type == ALLEGRO_EVENT_TIMER) {
            atualiza_personagem(&merida);
            desenhar = 1;
        }

        if (desenhar && al_is_event_queue_empty(fila)) {
            cenario_w = al_get_bitmap_width(cenario);
            cenario_h = al_get_bitmap_height(cenario);
            al_draw_scaled_bitmap(cenario, 0, 0, cenario_w, cenario_h, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);
            desenha_personagem(&merida);
            al_flip_display();
            desenhar = 0;
        }
    }

    al_destroy_timer(timer);
    al_unregister_event_source(fila, al_get_timer_event_source(timer));
    destroi_personagem(&merida);
    al_destroy_bitmap(cenario);
    
    return proximo;
}