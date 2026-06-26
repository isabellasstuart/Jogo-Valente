#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "jogo.h"

#define MENSAGEM_TAM 160
#define BOTAO_JOGAR_O_X   (LARGURA_TELA / 2.65)
#define BOTAO_JOGAR_O_Y   ALTURA_TELA - (ALTURA_TELA / 4)

estado executa_tela_game_over(ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE *fila);

#endif