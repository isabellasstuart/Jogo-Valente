#include "interacoes.h"

void inicializa_plataforma(plataforma *pl, float x, float y, const char *caminho_img) {
    pl -> sprite = al_load_bitmap(caminho_img);
    pl -> x = x;
    pl -> y = y;
    pl -> w = al_get_bitmap_width(pl -> sprite);
    pl -> h = al_get_bitmap_height(pl -> sprite);
}

void desenha_plataforma(plataforma *pl, float camera_x) {
    al_draw_bitmap(pl -> sprite, pl -> x - camera_x, pl -> y, 0);
}

void destroi_plataforma(plataforma *pl) {
    al_destroy_bitmap(pl -> sprite);
}

void inicializa_escada(escada *e, float x, float y, float h, const char *caminho_img) {
    e -> sprite = al_load_bitmap(caminho_img);
    e -> x = x;
    e -> y = y;
    e -> w = al_get_bitmap_width(e -> sprite);
    e -> h = h;   
}

void desenha_escada(escada *e, float camera_x) {
    float tile_h = al_get_bitmap_height(e -> sprite);

    for (float ty = (e -> y); ty < (e -> y) + (e -> h); ty += tile_h)
        al_draw_bitmap(e -> sprite, e -> x - camera_x, ty, 0);
}

void destroi_escada(escada *e) {
    al_destroy_bitmap(e -> sprite);
}

void inicializa_wisp(wisp *w, float x, float y, const char *caminho_img) {
    w -> sprite = al_load_bitmap(caminho_img);
    w -> x = x;
    w -> y = y;
    w -> w = al_get_bitmap_width(w -> sprite);
    w -> h = al_get_bitmap_height(w -> sprite);
    w -> coletado = 0;
}

void desenha_wisp(wisp *w, float camera_x) {
    if (w -> coletado) 
        return;
        
    al_draw_bitmap(w -> sprite, (w -> x) - camera_x, w -> y, 0);
}

void destroi_wisp(wisp *w) {
    al_destroy_bitmap(w -> sprite);
}

void inicializa_linha_chegada(linha_chegada *l, float x, float y, float w, float h, const char *caminho_img) {
    l -> sprite = al_load_bitmap(caminho_img);
    l -> x = x;
    l -> y = y;
    l -> w = al_get_bitmap_width(l -> sprite);
    l -> h = h;   
}

void desenha_linha_chegada(linha_chegada *l, float camera_x) {
    float tile_h = al_get_bitmap_height(l -> sprite);

    for (float ty = l -> y; ty < l -> y + l -> h; ty += tile_h)
        al_draw_bitmap(l -> sprite, l -> x - camera_x, ty, 0);
}

void destroi_linha_chegada(linha_chegada *l) {
    al_destroy_bitmap(l -> sprite);
}