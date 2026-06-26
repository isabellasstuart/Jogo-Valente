#include <stdio.h>
#include "tela_jogo.h"
#include "personagem.h"
#include "hud.h"
#include "obstaculos.h"
#include "interacoes.h"
#include "colisao.h"

void inicializa_objetos(personagem *merida, hud *h,
                        obstaculo obstaculos[], 
                        escada escadas[],
                        plataforma plataformas[],
                        wisp wisps[],
                        linha_chegada *l) {

    inicializa_personagem(merida, INICIALIZA_X, INICIALIZA_Y);
    inicializa_hud(h);

    inicializa_obstaculo(&obstaculos[0], LARGURA_MUNDO - 1000, CHAO - (FRAME_H_URSO / 2),
                         VEL_X_URSO, VEL_Y_URSO, "imagens/sprites/sprite_sheet_urso.png",
                         FRAMES_URSO, FRAME_H_URSO, FRAME_W_URSO);
    inicializa_obstaculo(&obstaculos[1], LARGURA_MUNDO, CHAO - (FRAME_H / 16),
                         VEL_X_FLECHA, VEL_Y_FLECHA, "imagens/sprites/sprite_sheet_flecha.png",
                         FRAMES_FLECHA, FRAME_H_FLECHA, FRAME_W_FLECHA);
    inicializa_obstaculo(&obstaculos[2], (3 * LARGURA_MUNDO / 4), CHAO + (FRAME_H / 2),
                         VEL_X_FLECHA, VEL_Y_FLECHA, "imagens/sprites/sprite_sheet_flecha.png",
                         FRAMES_FLECHA, FRAME_H_FLECHA, FRAME_W_FLECHA);
    inicializa_obstaculo(&obstaculos[3], 1500, CHAO + (FRAME_H_TRONCO / 1.5),
                         VEL_X_TRONCO, VEL_Y_TRONCO, "imagens/sprites/tronco.png",
                         FRAMES_TRONCO, FRAME_H_TRONCO, FRAME_W_TRONCO);
    inicializa_obstaculo(&obstaculos[4], 3000, 0,
                         VEL_X_ESPADA, VEL_Y_ESPADA, "imagens/sprites/espada.png",
                         FRAMES_ESPADA, FRAME_H_ESPADA, FRAME_W_ESPADA);
    inicializa_obstaculo(&obstaculos[5], 3500, ALTURA_TELA - (FRAME_H_ESPADA + FRAME_H_ESPADA / 16),
                         VEL_X_ESPADA, VEL_Y_ESPADA, "imagens/sprites/espada.png",
                         FRAMES_ESPADA, FRAME_H_ESPADA, FRAME_W_ESPADA);
    inicializa_obstaculo(&obstaculos[6], 4000, 0,
                         VEL_X_ESPADA, VEL_Y_ESPADA, "imagens/sprites/espada.png",
                         FRAMES_ESPADA, FRAME_H_ESPADA, FRAME_W_ESPADA);
    inicializa_obstaculo(&obstaculos[7], 4800, CHAO + (FRAME_H_ESPINHOS),
                         VEL_X_ESPINHOS, VEL_Y_ESPINHOS, "imagens/sprites/espinhos.png",
                         FRAMES_ESPINHOS, FRAME_H_ESPINHOS, FRAME_W_ESPINHOS);
    inicializa_obstaculo(&obstaculos[8], 1000, CHAO + (FRAME_H_URSO_BEBE),
                         VEL_X_URSO_BEBE, VEL_Y_URSO_BEBE, "imagens/sprites/sprite_sheet_urso_bebe.png",
                         FRAMES_URSO_BEBE, FRAME_H_URSO_BEBE, FRAME_W_URSO_BEBE);
    inicializa_obstaculo(&obstaculos[9], LARGURA_MUNDO - 1155, CHAO - (FRAME_H_ROCHA / 16),
                         VEL_X_ROCHA, VEL_Y_ROCHA, "imagens/sprites/sprite_sheet_rocha.png",
                         FRAMES_ROCHA, FRAME_H_ROCHA, FRAME_W_ROCHA);
    obstaculos[9].ativo = 0;
    obstaculos[9].x_ativacao = (LARGURA_MUNDO - 1000) - LARGURA_TELA;

    inicializa_escada(&escadas[0], 5500, CHAO - (FRAME_H_ESCADA / 2),
                      FRAME_H_ESCADA, "imagens/sprites/escada.png");
    inicializa_plataforma(&plataformas[0], 5500, CHAO - (FRAME_H_ESCADA / 2),
                          "imagens/sprites/plataforma.png");
    inicializa_wisp(&wisps[0], 6100, CHAO - FRAME_H_ESCADA,
                    "imagens/sprites/wisp.png");
    inicializa_linha_chegada(l, LARGURA_MUNDO - 500, CHAO - (FRAME_H / 16),
                             FRAME_W_LINHA_CHEGADA, FRAME_H_LINHA_CHEGADA,
                             "imagens/sprites/fim.png");
}

estado executa_tela_jogo(ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE *fila) {
    ALLEGRO_BITMAP *cenario = al_load_bitmap("imagens/fundo_final.png");
    ALLEGRO_TIMER *timer    = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT evento;
    estado proximo = TELA_JOGO;
    personagem merida;
    hud h;
    obstaculo obstaculos[NUM_OBSTACULOS];
    plataforma plataformas[NUM_PLATAFORMAS];
    escada escadas[NUM_ESCADAS];
    wisp wisps[NUM_WISPS];
    linha_chegada l;
    int fim = 0, desenhar = 0, cw, ch;
    float camera_x = 0, sx, sw;

    al_register_event_source(fila, al_get_timer_event_source(timer));
    al_start_timer(timer);

    inicializa_objetos(&merida, &h, obstaculos, escadas, plataformas, wisps, &l);

    cw = al_get_bitmap_width(cenario);
    ch = al_get_bitmap_height(cenario);

    while (!fim) {
        al_wait_for_event(fila, &evento);

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            proximo = SAIR; 
            fim = 1;
        }
        if (evento.type == ALLEGRO_EVENT_KEY_DOWN &&
            evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            proximo = TELA_INICIAL; 
            fim = 1;
        }

        if (evento.type == ALLEGRO_EVENT_TIMER) {
            atualiza_personagem(&merida);

            camera_x = merida.x - LARGURA_TELA / 2.0f + FRAME_W / 2.0f;
            if (camera_x < 0)
                camera_x = 0;
            if (camera_x > LARGURA_MUNDO - LARGURA_TELA)
                camera_x = LARGURA_MUNDO - LARGURA_TELA;

            for (int i = 0; i < NUM_OBSTACULOS; i++) {
                atualiza_obstaculo(&obstaculos[i], camera_x);
                processa_colisao(&merida, &obstaculos[i]);
            }

            for (int i = 0; i < NUM_ESCADAS; i++)
                processa_colisao_escada(&merida, &escadas[i]);

            for (int i = 0; i < NUM_PLATAFORMAS; i++)
                processa_colisao_plataforma(&merida, &plataformas[i]);

            for (int i = 0; i < NUM_WISPS; i++)
                processa_colisao_wisp(&merida, &wisps[i]);

            if (merida.vidas <= 0) {
                proximo = TELA_GAME_OVER; 
                fim = 1;
            }

            if (processa_colisao_linha_chegada(&merida, &l)) {
                proximo = TELA_FIM_DE_JOGO;
                fim = 1;
            }

            desenhar = 1;
        }

        if (desenhar && al_is_event_queue_empty(fila)) {
            sx = (camera_x / LARGURA_MUNDO) * cw;
            sw = ((float)LARGURA_TELA / LARGURA_MUNDO) * cw;
            al_draw_scaled_bitmap(cenario, sx, 0, sw, ch,
                                  0, 0, LARGURA_TELA, ALTURA_TELA, 0);

            for (int i = 0; i < NUM_PLATAFORMAS; i++)
                desenha_plataforma(&plataformas[i], camera_x);

            for (int i = 0; i < NUM_ESCADAS; i++)
                desenha_escada(&escadas[i], camera_x);

            for (int i = 0; i < NUM_WISPS; i++)
                desenha_wisp(&wisps[i], camera_x);

            for (int i = 0; i < NUM_OBSTACULOS; i++)
                desenha_obstaculo(&obstaculos[i], camera_x);

            desenha_linha_chegada(&l, camera_x);
            desenha_personagem(&merida, camera_x);
            desenha_hud(&h, &merida);

            al_flip_display();
            desenhar = 0;
        }
    }

    al_destroy_timer(timer);
    al_unregister_event_source(fila, al_get_timer_event_source(timer));
    
    for (int i = 0; i < NUM_OBSTACULOS; i++)
        destroi_obstaculo(&obstaculos[i]);

    for (int i = 0; i < NUM_PLATAFORMAS; i++)
        destroi_plataforma(&plataformas[i]);

    for (int i = 0; i < NUM_ESCADAS; i++)
        destroi_escada(&escadas[i]);

    for (int i = 0; i < NUM_WISPS; i++)
        destroi_wisp(&wisps[i]);

    destroi_linha_chegada(&l);
    destroi_personagem(&merida);
    destroi_hud(&h);
    al_destroy_bitmap(cenario);
    return proximo;
}