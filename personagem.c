#include "personagem.h"
#include <allegro5/allegro.h>

static int linha_sprite[] = {
    [PARADA]   = 0,
    [ANDANDO]  = 1,
    [AGACHADA] = 2,
    [PULANDO]  = 3
};

static int frames_por_estado[] = {
    [PARADA]   = FRAMES_PARAR,
    [ANDANDO]  = FRAMES_ANDAR,
    [AGACHADA] = FRAMES_AGACHAR,
    [PULANDO]  = FRAMES_PULAR
};

// velocidade de animação 
#define TICKS_POR_FRAME 8

void inicializa_personagem(personagem *p, float x, float y) {
    p -> spritesheet = al_load_bitmap("imagens/sprites/sprite_sheet.png");
    p -> x = x;
    p -> y = y;
    p -> vel_y = 0;
    p -> no_chao = 1;
    p -> estado = PARADA;
    p -> frame_atual = 0;
    p -> contador_frame = 0;
    p -> virado = 0;
}

void atualiza_personagem(personagem *p) {
    ALLEGRO_KEYBOARD_STATE teclado;
    al_get_keyboard_state(&teclado);
    estado_personagem novo_estado;
    int mover = 0, agachar;

    if (al_key_down(&teclado, ALLEGRO_KEY_RIGHT)) {
        p -> x += VELOCIDADE_X;
        p -> virado = 0;
        mover = 1;
    }
    
    if (al_key_down(&teclado, ALLEGRO_KEY_LEFT)) {
        p -> x -= VELOCIDADE_X;
        p -> virado = 1;
        mover = 1;
    }

    if (al_key_down(&teclado, ALLEGRO_KEY_UP) && (p -> no_chao)) {
        p -> vel_y = FORCA_PULO;
        p -> no_chao = 0;
    }

    agachar = al_key_down(&teclado, ALLEGRO_KEY_DOWN);
    p -> vel_y += GRAVIDADE;
    p -> y += p -> vel_y;
    
    if (p -> y >= CHAO) {
        p -> y = CHAO;
        p -> vel_y = 0;
        p -> no_chao = 1;
    }

    if (!p -> no_chao) 
        novo_estado = PULANDO;
    else if (agachar) 
        novo_estado = AGACHADA;
    else if (mover) 
        novo_estado = ANDANDO;
    else 
        novo_estado = PARADA;

    if (novo_estado != p -> estado) {
        p -> estado = novo_estado;
        p -> frame_atual = 0;
        p -> contador_frame = 0;
    }

    // avança frame da animação
    (p -> contador_frame)++;
    if (p -> contador_frame >= TICKS_POR_FRAME) {
        p -> contador_frame = 0;
        p -> frame_atual = (p -> frame_atual + 1) % frames_por_estado[p -> estado];
    }
}

void desenha_personagem(personagem *p) {
    int linha = linha_sprite[p -> estado], 
    sx = p -> frame_atual * FRAME_W, sy = linha * FRAME_H, 
    flags = p -> virado ? ALLEGRO_FLIP_HORIZONTAL : 0;

    al_draw_bitmap_region(p -> spritesheet, sx, sy, FRAME_W, FRAME_H, p -> x, p -> y, flags);
}

void destroi_personagem(personagem *p) {
    al_destroy_bitmap(p -> spritesheet);
}
