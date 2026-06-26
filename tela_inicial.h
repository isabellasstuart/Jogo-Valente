#ifndef TELA_INICIAL_H
#define TELA_INICIAL_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "jogo.h"

#define TEXTO_JOGAR_TAM 80
#define ESPACO_BOTOES   20
#define BOTAO_JOGAR_X   (LARGURA_TELA / 6)
#define BOTAO_JOGAR_Y   (ALTURA_TELA / 2)
#define BOTAO_SAIR_X    BOTAO_JOGAR_X

estado executa_tela_inicial(ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE *fila);

#endif