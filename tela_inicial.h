#ifndef TELA_INICIAL_H
#define TELA_INICIAL_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "jogo.h"

#define TEXTO_JOGAR_TAM 100
#define TEXTO_JOGAR_X LARGURA_TELA / 2
#define TEXTO_JOGAR_Y 730
#define BOTAO_JOGAR_X TEXTO_JOGAR_X - (TEXTO_JOGAR_X / 5.1)
#define BOTAO_JOGAR_Y TEXTO_JOGAR_Y - 10

estado executa_tela_inicial(ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE *fila);

#endif