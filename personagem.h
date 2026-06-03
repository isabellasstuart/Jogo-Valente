#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <allegro5/allegro.h>
#include "jogo.h"

// número de frames de cada animação
#define FRAMES_PARAR 1
#define FRAMES_ANDAR 3
#define FRAMES_AGACHAR 1
#define FRAMES_PULAR 1

// tamanho de cada frame na spritesheet 
#define FRAME_W  200
#define FRAME_H  200

#define GRAVIDADE       0.5f
#define FORCA_PULO     -12.0f
#define VELOCIDADE_X    10.0f

#define INICIALIZA_X 100
#define INICIALIZA_Y 500

#define CHAO (ALTURA_TELA - FRAME_H - 200)

typedef enum {
    PARADA,
    ANDANDO,
    AGACHADA,
    PULANDO
} estado_personagem;

typedef struct {
    ALLEGRO_BITMAP *spritesheet;
    float x, y;           // posição
    float vel_y;          // velocidade vertical (física)
    int no_chao;          // 1 se está tocando o chão
    estado_personagem estado;
    int frame_atual;
    int contador_frame;   // conta ticks para trocar de frame
    int virado;           // 0 = direita, 1 = esquerda
} personagem;

void inicializa_personagem(personagem *p, float x, float y);
void atualiza_personagem(personagem *p);
void desenha_personagem(personagem *p);
void destroi_personagem(personagem *p);

#endif