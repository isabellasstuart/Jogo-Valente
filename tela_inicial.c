#include <stdio.h>
#include "tela_inicial.h"

estado executa_tela_inicial(ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE *fila) {
    ALLEGRO_BITMAP *fundo = al_load_bitmap("imagens/Brave.png");
    ALLEGRO_EVENT evento;
    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_COLOR cor_texto;
    estado proximo = TELA_INICIAL;
    int fim = 0, fundo_w, fundo_h,
    botao_x, botao_y, botao_w, botao_h, mx, my;

    fonte = al_load_font("fontes/Brave.ttf", 160, 0);

    botao_w = al_get_text_width(fonte, "JOGAR");
    botao_h = al_get_font_line_height(fonte);
    botao_x = (400) - (botao_w / 2);
    botao_y = 280;
    
    cor_texto = al_map_rgb(79, 79, 79);

    while (!fim) {
        al_wait_for_event(fila, &evento);

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            proximo = SAIR;
            fim = 1;
        }

        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mx = evento.mouse.x;
            my = evento.mouse.y;

            if (mx >= botao_x && mx <= botao_x + botao_w &&
                my >= botao_y && my <= botao_y + botao_h) {
                cor_texto = al_map_rgb(113, 93, 52);
            }
            else 
                cor_texto = al_map_rgb(79, 79, 79); 
        }

        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            mx = evento.mouse.x;
            my = evento.mouse.y;
            
            if (mx >= botao_x && mx <= botao_x + botao_w &&
                my >= botao_y && my <= botao_y + botao_h) {
                proximo = TELA_JOGO;
                fim = 1;
            }
        }

        fundo_w = al_get_bitmap_width(fundo);
        fundo_h = al_get_bitmap_height(fundo);
        al_draw_scaled_bitmap(fundo, 0, 0, fundo_w, fundo_h, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);
        al_draw_text(fonte, cor_texto, 400, 280, ALLEGRO_ALIGN_CENTRE, "JOGAR");
        al_flip_display();
    }

    al_destroy_bitmap(fundo);
    return proximo;
}