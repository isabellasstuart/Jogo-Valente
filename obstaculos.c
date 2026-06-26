#include "obstaculos.h"
#include "colisao.h"

void inicializa_obstaculo(obstaculo *o, float x, float y, 
                          float vel_x, float vel_y, 
                          const char *caminho_img, int n_frames,
                          int frame_h, int frame_w) {

    o -> spritesheet = al_load_bitmap(caminho_img);
    o -> x = x;
    o -> y = y;
    o -> w = frame_w;
    o -> h = frame_h;
    o -> vel_x = vel_x;
    o -> vel_y = vel_y;
    o -> direcao_y = 1;
    o -> ativo = 1;
    o -> merida_passou = 0;
    o -> x_ativacao = SEMPRE_ATIVO;
    o -> n_frames = n_frames;
    o -> frame_h = frame_h;
    o -> frame_w = frame_w;
    o -> frame_atual  = 0;
    o -> contador_frame = 0;
}

void atualiza_obstaculo(obstaculo *o, float camera_x) {

    if ((o -> x_ativacao) >= 0 && !(o -> ativo)) {
        if (camera_x >= (o -> x_ativacao))
            o -> ativo = 1;
        return;  
    }

    if (!(o -> ativo)) 
        return;

    o -> x += o -> vel_x;
    o -> y += (o -> direcao_y) * (o -> vel_y);

    (o -> contador_frame)++;
    if (o -> contador_frame >= TICKS_POR_FRAME) {
        o -> contador_frame = 0;
        o -> frame_atual = (o -> frame_atual + 1) % (o -> n_frames);
    }

    if (o -> x < -2000)
        o -> x = LARGURA_MUNDO - (o -> frame_w); 
        
    if ((o -> y) < 0 || (o -> y) > ALTURA_TELA - (o -> frame_h + (o -> frame_h / 16)))
        o -> direcao_y = -(o -> direcao_y); 
}

void atualiza_urso(personagem *p, obstaculo *o, float camera_x, int n_frames_ativado) {
    int n_frames = o -> n_frames;
    
    if (!o -> ativo) 
        return;

    if (!o -> merida_passou && (checa_colisao(p, o))) {
        o -> merida_passou  = 1;
        o -> frame_atual    = 0;
        o -> contador_frame = 0;
    }

    o -> x += o -> vel_x;
    (o -> contador_frame)++;

    if (o -> contador_frame >= TICKS_POR_FRAME) {
        o -> contador_frame = 0;

        if (o -> merida_passou)
            n_frames = n_frames_ativado;

        o -> frame_atual = (o -> frame_atual + 1) % n_frames;
    }
}

void desenha_obstaculo(obstaculo *o, float camera_x) {
    float x_tela;
    int flags = 0;
    int x, y;

    if (!(o -> ativo)) 
        return;

    y = 0;
    x = (o -> frame_atual) * (o -> frame_w);
    x_tela = (o -> x) - camera_x;

    al_draw_bitmap_region(o -> spritesheet, x, y, o -> frame_w, o -> frame_h,
                          x_tela, o -> y, flags);
}

void desenha_urso(obstaculo *o, float camera_x) {
    int linha = 0, x, y;
    float x_tela = o->x - camera_x;
    
    if (!o->ativo) 
        return;

    if (o -> merida_passou)
        linha = 1;
    
    x = (o -> frame_atual) * (o -> frame_w);
    y = linha * (o -> frame_h);

    al_draw_bitmap_region(o -> spritesheet, x, y, o -> frame_w, o -> frame_h,
                          x_tela, o -> y, 0);
}

void destroi_obstaculo(obstaculo *o) {
    al_destroy_bitmap(o -> spritesheet);
}