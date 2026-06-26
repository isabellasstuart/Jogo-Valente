#ifndef OBSTACULOS_H
#define OBSTACULOS_H

#include <allegro5/allegro.h>
#include "jogo.h"
#include "personagem.h"

#define NUM_OBSTACULOS 10

#define SEMPRE_ATIVO -1

#define FRAMES_URSO 11
#define FRAMES_URSO_BEBE 4
#define FRAMES_FLECHA 4
#define FRAMES_TRONCO 1
#define FRAMES_ESPADA 1
#define FRAMES_ESPINHOS 1
#define FRAMES_ROCHA 8

#define FRAME_W_URSO 255
#define FRAME_H_URSO 400

#define FRAME_W_URSO_BEBE 170
#define FRAME_H_URSO_BEBE 100

#define FRAME_W_FLECHA 100
#define FRAME_H_FLECHA 50

#define FRAME_W_TRONCO 350
#define FRAME_H_TRONCO 150

#define FRAME_W_ESPADA 80
#define FRAME_H_ESPADA 400

#define FRAME_W_ESPINHOS 300
#define FRAME_H_ESPINHOS 150

#define FRAME_W_ROCHA 200
#define FRAME_H_ROCHA 200

#define VEL_X_URSO 0.0f
#define VEL_Y_URSO 0.0f

#define VEL_X_URSO_BEBE -3.0f
#define VEL_Y_URSO_BEBE 0.0f

#define VEL_X_FLECHA -30.0f
#define VEL_Y_FLECHA 0.0f

#define VEL_X_TRONCO 0.0f
#define VEL_Y_TRONCO 0.0f

#define VEL_X_ESPADA 0.0f
#define VEL_Y_ESPADA 6.0f

#define VEL_X_ESPINHOS 0.0f
#define VEL_Y_ESPINHOS 0.0f

#define VEL_X_ROCHA -10.0f
#define VEL_Y_ROCHA 0.0f

typedef struct {
    ALLEGRO_BITMAP *spritesheet;
    float x, y;
    float w, h;
    float vel_x;
    float vel_y;
    float x_ativacao;
    int direcao_y;
    int ativo;
    int n_frames;
    int frame_h;
    int frame_w;
    int frame_atual;
    int contador_frame;
} obstaculo;

void inicializa_obstaculo(obstaculo *o, float x, float y, 
                          float vel_x, float vel_y, 
                          const char *caminho_img, int n_frames,
                          int frame_h, int frame_w);
void atualiza_obstaculo(obstaculo *o, float camera_x);
void desenha_obstaculo(obstaculo *o, float camera_x);
void destroi_obstaculo(obstaculo *o);

#endif