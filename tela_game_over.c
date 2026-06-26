#include <stdio.h>
#include "tela_game_over.h"
#include "tela_inicial.h"

estado executa_tela_game_over(ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE *fila, float *volume) {
    ALLEGRO_BITMAP *fundo = al_load_bitmap("imagens/tela_game_over.png"), *botao = al_load_bitmap("imagens/botao2.png"),
    *titulo = al_load_bitmap("imagens/game_over.png");
    ALLEGRO_AUDIO_STREAM *musica = al_load_audio_stream("audio/tela_game_over.ogg", 4, 2048);
    ALLEGRO_EVENT evento;
    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_COLOR cor_texto_jogar, cor_texto_sair;
    estado proximo = TELA_INICIAL;
    int fim = 0, fundo_w, fundo_h,
    botao_w, botao_h, mx, my;
    float botao_sair_x, texto_jogar_y,
    texto_sair_y;

    fonte = al_load_font("fontes/Abibas.ttf", TEXTO_JOGAR_TAM, 0);

    botao_w = al_get_bitmap_width(botao);
    botao_h = al_get_bitmap_height(botao);
    
    texto_jogar_y = BOTAO_JOGAR_O_Y + (botao_h - al_get_font_line_height(fonte)) / 2;
    texto_sair_y  = BOTAO_JOGAR_O_Y  + (botao_h - al_get_font_line_height(fonte)) / 2;
    botao_sair_x = LARGURA_TELA - BOTAO_JOGAR_O_X;
    
    cor_texto_jogar = al_map_rgb(90, 90, 90);
    cor_texto_sair = al_map_rgb(90, 90, 90); 

    al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_gain(musica, *volume);

    while (!fim) {
        al_wait_for_event(fila, &evento);

        if ((evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) || 
            (evento.type == ALLEGRO_EVENT_KEY_DOWN &&
             evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {

            proximo = SAIR;
            fim = 1;
        }

        if (evento.keyboard.keycode == ALLEGRO_KEY_F3) {
            *volume += 0.05f;
            if (*volume > 1.0f) 
                *volume = 1.0f;
            al_set_audio_stream_gain(musica, *volume);
        }
        if (evento.keyboard.keycode == ALLEGRO_KEY_F2) {
            *volume -= 0.05f;
            if (*volume < 0.0f) 
                *volume = 0.0f;
            al_set_audio_stream_gain(musica, *volume);
        }

        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mx = evento.mouse.x;
            my = evento.mouse.y;

            if (mx >= BOTAO_JOGAR_O_X - (botao_w / 2) && mx <= BOTAO_JOGAR_O_X + (botao_w / 2) &&
                my >= BOTAO_JOGAR_O_Y && my <= BOTAO_JOGAR_O_Y + botao_h)
                cor_texto_jogar = al_map_rgb(148, 130, 74);
            else
                cor_texto_jogar = al_map_rgb(90, 90, 90);

            if (mx >= botao_sair_x - (botao_w / 2) && mx <= botao_sair_x + (botao_w / 2) &&
                my >= BOTAO_JOGAR_O_Y && my <= BOTAO_JOGAR_O_Y + botao_h)
                cor_texto_sair = al_map_rgb(148, 130, 74);
            else
                cor_texto_sair = al_map_rgb(90, 90, 90);
        }

        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            mx = evento.mouse.x;
            my = evento.mouse.y;
            
            if (mx >= BOTAO_JOGAR_O_X && mx <= BOTAO_JOGAR_O_X + botao_w &&
                my >= BOTAO_JOGAR_O_Y && my <= BOTAO_JOGAR_O_Y + botao_h) {
                    
                proximo = TELA_INICIAL;
                fim = 1;
            }

            if (mx >= botao_sair_x - (botao_w / 2) && mx <= botao_sair_x + (botao_w / 2) &&
                my >= BOTAO_JOGAR_O_Y && my <= BOTAO_JOGAR_O_Y + botao_h) {
                
                proximo = SAIR;
                fim = 1;
            }
        }

        fundo_w = al_get_bitmap_width(fundo);
        fundo_h = al_get_bitmap_height(fundo);
        al_draw_scaled_bitmap(fundo, 0, 0, fundo_w, fundo_h, 0, 0, LARGURA_TELA, ALTURA_TELA, 0);
        al_draw_bitmap(titulo, 7 * (LARGURA_TELA / 32), (ALTURA_TELA / 32), 0);

        al_draw_bitmap(botao, BOTAO_JOGAR_O_X - (botao_w / 2), BOTAO_JOGAR_O_Y, 0);
        al_draw_text(fonte, cor_texto_jogar, BOTAO_JOGAR_O_X, texto_jogar_y, ALLEGRO_ALIGN_CENTER, "INÍCIO");
    
        al_draw_bitmap(botao, botao_sair_x - (botao_w / 2), BOTAO_JOGAR_O_Y, 0);
        al_draw_text(fonte, cor_texto_sair, botao_sair_x, texto_sair_y, ALLEGRO_ALIGN_CENTER, "SAIR");  
        al_flip_display();
    }

    al_destroy_audio_stream(musica);
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(botao);
    al_destroy_font(fonte);
    return proximo;
}