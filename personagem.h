#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <allegro5/allegro.h>
#include "jogo.h"

#define FRAMES_PARAR   1
#define FRAMES_ANDAR   3
#define FRAMES_AGACHAR 1
#define FRAMES_PULAR   1
#define FRAMES_ESCALAR 1

#define FRAME_W  200
#define FRAME_H  200

#define HB_ESQ  30
#define HB_DIR  30
#define HB_TOP  40

#define TICKS_POR_FRAME 8
#define GRAVIDADE 0.5f
#define FORCA_PULO -18.0f
#define VELOCIDADE_X 10.0f

#define INICIALIZA_X 100
#define INICIALIZA_Y 500

#define CHAO (ALTURA_TELA - FRAME_H - 120)

#define VIDAS_INICIAIS 3
#define LIMITE_VIDAS 4
#define FRAMES_INVENCIVEL 120

typedef enum {
    PARADA,
    ANDANDO,
    AGACHADA,
    PULANDO,
    ESCALANDO
} estado_personagem;

typedef struct {
    ALLEGRO_BITMAP *spritesheet;
    estado_personagem estado;
    float x, y;
    float vel_y;
    int no_chao;
    int na_escada;
    int frame_atual;
    int contador_frame;
    int virado;
    int vidas;
    int wisp_coletado;       
    int invencivel;  
} personagem;

void inicializa_personagem(personagem *p, float x, float y);
void atualiza_personagem(personagem *p);
void desenha_personagem(personagem *p, float camera_x);
void destroi_personagem(personagem *p);

#endif