#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "jogo.h"
#include "tela_inicial.h"
#include "tela_jogo.h"
#include "tela_game_over.h"
#include "tela_fim_de_jogo.h"

int main() {
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_mouse();
    al_install_keyboard();
    al_init_primitives_addon();

    ALLEGRO_DISPLAY *janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    ALLEGRO_EVENT_QUEUE *fila = al_create_event_queue();
    estado estado_atual = TELA_INICIAL;

    al_register_event_source(fila, al_get_display_event_source(janela));
    al_register_event_source(fila, al_get_mouse_event_source());
    al_register_event_source(fila, al_get_keyboard_event_source());

    al_set_window_title(janela, "Valente - Isabella Stuart");

    while (estado_atual != SAIR) {
        switch (estado_atual) {
            case TELA_INICIAL:
                estado_atual = executa_tela_inicial(janela, fila);
                break;
            case TELA_JOGO:
                estado_atual = executa_tela_jogo(janela, fila);
                break;
            case TELA_GAME_OVER:
                estado_atual = executa_tela_game_over(janela, fila);
                break;
            case TELA_FIM_DE_JOGO:
                estado_atual = executa_tela_fim_de_jogo(janela, fila);
                break;  
            default:
                estado_atual = SAIR;
        }
    }

    al_destroy_display(janela);
    al_destroy_event_queue(fila);
    return 0;
}