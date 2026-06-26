#include "personagem.h"
#include <allegro5/allegro.h>

int linha_sprite[] = {
    [PARADA] = 0,
    [ANDANDO] = 1,
    [AGACHADA] = 2,
    [PULANDO] = 3,
    [ESCALANDO] = 4
};

int frames_por_estado[] = {
    [PARADA] = FRAMES_PARAR,
    [ANDANDO] = FRAMES_ANDAR,
    [AGACHADA] = FRAMES_AGACHAR,
    [PULANDO] = FRAMES_PULAR,
    [ESCALANDO] = FRAMES_ESCALAR
};

void inicializa_personagem(personagem *p, float x, float y) {
    p -> spritesheet = al_load_bitmap("imagens/sprites/sprite_sheet_merida.png");
    p -> x = x;
    p -> y = y;
    p -> vel_y = 0;
    p -> no_chao = 1;
    p -> na_escada = 0;
    p -> estado  = PARADA;
    p -> frame_atual  = 0;
    p -> contador_frame = 0;
    p -> virado  = 0;
    p -> vidas = VIDAS_INICIAIS;
    p -> wisp_coletado = 0;
    p -> invencivel = 0;
}

void atualiza_personagem(personagem *p) {
    ALLEGRO_KEYBOARD_STATE teclado;
    al_get_keyboard_state(&teclado);
    estado_personagem novo_estado;
    int mover = 0, agachar;

    if (al_key_down(&teclado, ALLEGRO_KEY_RIGHT) ||
        al_key_down(&teclado, ALLEGRO_KEY_D)) {

        p -> x += VELOCIDADE_X;
        p -> virado = 0;
        mover = 1;
    }
    if (al_key_down(&teclado, ALLEGRO_KEY_LEFT) ||
        al_key_down(&teclado, ALLEGRO_KEY_A)) {

        p -> x -= VELOCIDADE_X;
        p -> virado = 1;
        mover = 1;
    }

    if (al_key_down(&teclado, ALLEGRO_KEY_DOWN) || 
        al_key_down(&teclado, ALLEGRO_KEY_S))

        agachar = 1;
    else
        agachar = 0;

    if (p -> na_escada) {
        p -> vel_y   = 0;
        p -> no_chao = 0;

        if (al_key_down(&teclado, ALLEGRO_KEY_UP) ||
            al_key_down(&teclado, ALLEGRO_KEY_W))

            p -> y -= VELOCIDADE_X;

        if (al_key_down(&teclado, ALLEGRO_KEY_DOWN) ||
            al_key_down(&teclado, ALLEGRO_KEY_S))

            p -> y += VELOCIDADE_X;

    } else {
        if ((al_key_down(&teclado, ALLEGRO_KEY_UP) ||
             al_key_down(&teclado, ALLEGRO_KEY_W)) && 
            (p -> no_chao)) {

            p -> vel_y = FORCA_PULO;
            p -> no_chao = 0;
        }

        p -> vel_y += GRAVIDADE;
        p -> y += p -> vel_y;
    }

    if (p -> y >= CHAO) {
        p -> y = CHAO;
        p -> vel_y = 0;
        p -> no_chao = 1;
    }

    if ((p -> x) < 0)                       
        p -> x = 0;
    if ((p -> x) > (LARGURA_MUNDO - FRAME_W)) 
        p -> x = LARGURA_MUNDO - FRAME_W;

    if (p -> invencivel > 0)
        p -> invencivel -= 2;

    if (p -> na_escada)
        novo_estado = ESCALANDO;
    else if (!(p -> no_chao))
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

    (p -> contador_frame)++;
    if (p -> contador_frame >= TICKS_POR_FRAME) {
        p -> contador_frame = 0;
        p -> frame_atual = (p -> frame_atual + 1) % frames_por_estado[p -> estado];
    }
}

void desenha_personagem(personagem *p, float camera_x) {
    float x_tela;
    int sy, sx, flags = 0;

    if ((p -> invencivel > 0) && (p -> invencivel / 16) % 2 == 0)
        return;

    sy = linha_sprite[p -> estado] * FRAME_H;
    sx = (p -> frame_atual) * FRAME_W;
    x_tela = (p -> x) - camera_x;

    if (p -> virado)
        flags = ALLEGRO_FLIP_HORIZONTAL;

    al_draw_bitmap_region(p -> spritesheet, sx, sy, FRAME_W, FRAME_H,
                          x_tela, p -> y, flags);
}

void destroi_personagem(personagem *p) {
    al_destroy_bitmap(p -> spritesheet);
}