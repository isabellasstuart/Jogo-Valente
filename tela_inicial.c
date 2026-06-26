#include <stdio.h>
#include "tela_inicial.h"

estado executa_tela_inicial(ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE *fila) {
    ALLEGRO_BITMAP *fundo = al_load_bitmap("imagens/tela_inicial.png"), *botao = al_load_bitmap("imagens/botao2.png");
    ALLEGRO_EVENT evento;
    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_COLOR cor_texto_jogar, cor_texto_sair;
    estado proximo = TELA_INICIAL;
    int fim = 0, fundo_w, fundo_h,
    botao_w, botao_h, mx, my;
    float botao_sair_y, texto_jogar_y,
    texto_sair_y;

    fonte = al_load_font("fontes/Abibas.ttf", TEXTO_JOGAR_TAM, 0);

    botao_w = al_get_bitmap_width(botao);
    botao_h = al_get_bitmap_height(botao);
    
    botao_sair_y = BOTAO_JOGAR_Y + botao_h + ESPACO_BOTOES;  
    texto_jogar_y = BOTAO_JOGAR_Y + (botao_h - al_get_font_line_height(fonte)) / 2;
    texto_sair_y  = botao_sair_y  + (botao_h - al_get_font_line_height(fonte)) / 2;
    
    cor_texto_jogar = al_map_rgb(90, 90, 90);
    cor_texto_sair = al_map_rgb(90, 90, 90);

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

            if (mx >= BOTAO_JOGAR_X - (botao_w / 2) && mx <= BOTAO_JOGAR_X + (botao_w / 2) &&
                my >= BOTAO_JOGAR_Y && my <= BOTAO_JOGAR_Y + botao_h)
                cor_texto_jogar = al_map_rgb(148, 130, 74);
            else
                cor_texto_jogar = al_map_rgb(90, 90, 90);

            if (mx >= BOTAO_SAIR_X - (botao_w / 2) && mx <= BOTAO_SAIR_X + (botao_w / 2) &&
                my >= botao_sair_y && my <= botao_sair_y + botao_h)
                cor_texto_sair = al_map_rgb(148, 130, 74);
            else
                cor_texto_sair = al_map_rgb(90, 90, 90);
        }

        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            mx = evento.mouse.x;
            my = evento.mouse.y;
            
            if (mx >= BOTAO_JOGAR_X && mx <= BOTAO_JOGAR_X + botao_w &&
                my >= BOTAO_JOGAR_Y && my <= BOTAO_JOGAR_Y + botao_h) {
                    
                proximo = TELA_JOGO;
                fim = 1;
            }

            if (mx >= BOTAO_SAIR_X - (botao_w / 2) && mx <= BOTAO_SAIR_X + (botao_w / 2) &&
                my >= botao_sair_y && my <= botao_sair_y + botao_h) {
                
                proximo = SAIR;
                fim = 1;
            }
        }

        fundo_w = al_get_bitmap_width(fundo);
        fundo_h = al_get_bitmap_height(fundo);
        al_draw_scaled_bitmap(fundo, 0, 0, fundo_w, fundo_h, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);
        al_draw_bitmap(botao, BOTAO_JOGAR_X - (botao_w / 2), BOTAO_JOGAR_Y, 0);
        al_draw_text(fonte, cor_texto_jogar, BOTAO_JOGAR_X, texto_jogar_y, ALLEGRO_ALIGN_CENTER, "JOGAR");

        al_draw_bitmap(botao, BOTAO_SAIR_X - (botao_w / 2), botao_sair_y, 0);
        al_draw_text(fonte, cor_texto_sair, BOTAO_SAIR_X, texto_sair_y, ALLEGRO_ALIGN_CENTER, "SAIR");
        al_flip_display();
    }

    al_destroy_bitmap(fundo);
    return proximo;
}