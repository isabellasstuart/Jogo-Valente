#ifndef COLISAO_H
#define COLISAO_H

#include <allegro5/allegro_primitives.h>
#include "personagem.h"
#include "interacoes.h"
#include "obstaculos.h"

int checa_colisao(personagem *p, obstaculo *o);
void processa_colisao(personagem *p, obstaculo *o);
void processa_colisao_escada(personagem *p, escada *e);
void processa_colisao_plataforma(personagem *p, plataforma *pl);
void processa_colisao_wisp(personagem *p, wisp *w);
int processa_colisao_linha_chegada(personagem *p, linha_chegada *l);
void desenha_hitbox_personagem(personagem *p, float camera_x);
void desenha_hitbox_obstaculo(obstaculo *o, float camera_x);

#endif