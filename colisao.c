#include "colisao.h"
#include "interacoes.h"
#include "personagem.h"

void calcula_hitbox(personagem *p, float *px, float *py, float *pw, float *ph) {
    float hb_top = 0;

    if (p -> estado == AGACHADA)
        hb_top = HB_TOP;

    *px = (p -> x) + HB_ESQ;
    *pw = FRAME_W - HB_ESQ - HB_DIR;
    *ph = FRAME_H - hb_top;
    *py = (p -> y) + hb_top;
}

int checa_colisao(personagem *p, obstaculo *o) {
    float px, py, pw, ph;
    int colisao = 0;

    if (!(o -> ativo)) 
        return 0;

    calcula_hitbox(p, &px, &py, &pw, &ph);

    if (px < (o -> x) + (o -> w) &&
        px + pw > (o -> x)   &&
        py < (o -> y) + (o -> h) &&
        py + ph > (o -> y))

        colisao = 1;

    return colisao;
}

void processa_colisao(personagem *p, obstaculo *o) {
    if (p -> invencivel > 0) 
        return;

    if (checa_colisao(p, o)) {
        (p -> vidas)--;
        p -> invencivel = FRAMES_INVENCIVEL;
    }
}

void processa_colisao_escada(personagem *p, escada *e) {
    int dentro_x = 0, dentro_y = 0;

    if (((p -> x) + FRAME_W - HB_ESQ) > (e -> x) &&
        ((p -> x) + HB_ESQ) < (e -> x) + (e -> w))

        dentro_x = 1;

    if ((p -> y + FRAME_H) > (e -> y) && 
        (p -> y) < (e -> y) + (e -> h))
        
        dentro_y = 1;

    if (dentro_x && dentro_y)
        p -> na_escada = 1;
    else
        p -> na_escada = 0;
}

void processa_colisao_plataforma(personagem *p, plataforma *pl) {
    float rodape_anterior = (p -> y - p -> vel_y) + FRAME_H;
    float rodape_atual    = p -> y + FRAME_H;
    int dentro_x = 0;

    if (((p -> x) + FRAME_W - HB_ESQ) > (pl -> x) &&
        ((p -> x) + HB_ESQ) < (pl -> x) + (pl -> w))

        dentro_x = 1;

    if (dentro_x && rodape_anterior <= (pl -> y) && 
        rodape_atual >= (pl -> y) && (p -> vel_y) > 0) {

        p -> y = (pl -> y) - FRAME_H;
        p -> vel_y = 0;
        p -> no_chao = 1;
    }
}

void processa_colisao_wisp(personagem *p, wisp *w) {
    int colisao = 0;

    if (w -> coletado) 
        return;

    if ((p -> x) < (w -> x) + (w -> w) &&
        (p -> x) + FRAME_W > (w -> x) &&
        (p -> y) < (w -> y) + (w -> h) &&
        (p -> y) + FRAME_H > (w -> y))

        colisao = 1;

    if (colisao && (p -> vidas < LIMITE_VIDAS)) {
        (p -> vidas)++;
        w -> coletado = 1;
        p -> wisp_coletado = 1;
    }
}

int processa_colisao_linha_chegada(personagem *p, linha_chegada *l) {
    int colisao = 0;
    float px, py, pw, ph;
    
    calcula_hitbox(p, &px, &py, &pw, &ph);

    if (px < l -> x + l -> w &&
        px + pw > l -> x   &&
        py < l -> y + l -> h &&
        py + ph > l -> y)
        
        colisao = 1;
        
    return colisao;
}

void desenha_hitbox_personagem(personagem *p, float camera_x) {
    float px, py, pw, ph;
    calcula_hitbox(p, &px, &py, &pw, &ph);

    px = px - camera_x;

    al_draw_rectangle(px, py, px + pw, py + ph,
                      al_map_rgb(255, 0, 0), 2);
}

void desenha_hitbox_obstaculo(obstaculo *o, float camera_x) {
    float ox, oy;
    if (!(o -> ativo)) 
        return;

    ox = o -> x - camera_x;
    oy = o -> y;

    al_draw_rectangle(ox, oy, ox + o -> w, oy + o -> h,
                      al_map_rgb(0, 255, 0), 2);
}