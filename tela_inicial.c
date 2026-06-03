#include <stdio.h>
#include "tela_inicial.h"

estado executa_tela_inicial(ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE *fila) {
    ALLEGRO_BITMAP *fundo = al_load_bitmap("imagens/Brave.png"), *botao = al_load_bitmap("imagens/botao.png");
    ALLEGRO_EVENT evento;
    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_COLOR cor_texto;
    estado proximo = TELA_INICIAL;
    int fim = 0, fundo_w, fundo_h,
    texto_w, texto_h, botao_w, botao_h, mx, my;

    fonte = al_load_font("fontes/Brave.ttf", TEXTO_JOGAR_TAM, 0);

    botao_w = al_get_bitmap_width(botao);
    botao_h = al_get_bitmap_height(botao);
    
    cor_texto = al_map_rgb(90, 90, 90);

    while (!fim) {
        al_wait_for_event(fila, &evento);

        if ((evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) || 
            (evento.type == ALLEGRO_EVENT_KEY_DOWN &&
             evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {

            proximo = SAIR;
            fim = 1;
        }

        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mx = evento.mouse.x;
            my = evento.mouse.y;

            if (mx >= BOTAO_JOGAR_X && mx <= BOTAO_JOGAR_X + botao_w &&
                my >= BOTAO_JOGAR_Y && my <= BOTAO_JOGAR_Y + botao_h) {

                cor_texto = al_map_rgb(148, 130, 74);
            }
            else 
                cor_texto = al_map_rgb(90, 90, 90);
            
        }

        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            mx = evento.mouse.x;
            my = evento.mouse.y;
            
            if (mx >= BOTAO_JOGAR_X && mx <= BOTAO_JOGAR_X + botao_w &&
                my >= BOTAO_JOGAR_Y && my <= BOTAO_JOGAR_Y + botao_h) {
                    
                proximo = TELA_JOGO;
                fim = 1;
            }
        }

        fundo_w = al_get_bitmap_width(fundo);
        fundo_h = al_get_bitmap_height(fundo);
        al_draw_scaled_bitmap(fundo, 0, 0, fundo_w, fundo_h, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);
        al_draw_bitmap(botao, BOTAO_JOGAR_X, BOTAO_JOGAR_Y, 0);
        al_draw_text(fonte, cor_texto, TEXTO_JOGAR_X, TEXTO_JOGAR_Y, ALLEGRO_ALIGN_CENTER, "JOGAR");
        al_flip_display();
    }

    al_destroy_bitmap(fundo);
    return proximo;
}