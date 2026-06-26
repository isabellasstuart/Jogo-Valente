#ifndef INTERACOES_H
#define INTERACOES_H

#include <allegro5/allegro.h>
#include "jogo.h"

typedef struct {
    float x, y, w, h;
    ALLEGRO_BITMAP *sprite;
} plataforma;

typedef struct {
    float x, y, w, h;   
    ALLEGRO_BITMAP *sprite;
} escada;

typedef struct {
    float x, y, w, h;
    ALLEGRO_BITMAP *sprite;
    int coletado;
} wisp;

typedef struct {
    float x, y, w, h;   
    ALLEGRO_BITMAP *sprite;
} linha_chegada;

#define NUM_PLATAFORMAS 1
#define NUM_ESCADAS 1
#define NUM_WISPS 1

#define FRAME_W_ESCADA 160
#define FRAME_H_ESCADA 400
#define FRAME_W_LINHA_CHEGADA 150
#define FRAME_H_LINHA_CHEGADA 200

void inicializa_plataforma(plataforma *pl, float x, float y, const char *caminho_img);
void desenha_plataforma(plataforma *pl, float camera_x);
void destroi_plataforma(plataforma *pl);

void inicializa_escada(escada *e, float x, float y, float h, const char *caminho_img);
void desenha_escada(escada *e, float camera_x);
void destroi_escada(escada *e);

void inicializa_wisp(wisp *w, float x, float y, const char *caminho_img);
void desenha_wisp(wisp *w, float camera_x);
void destroi_wisp(wisp *w);

void inicializa_linha_chegada(linha_chegada *l, float x, float y, float w,float h, const char *caminho_img);
void desenha_linha_chegada(linha_chegada *l, float camera_x);
void destroi_linha_chegada(linha_chegada *l);

#endif