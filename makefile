CC      = gcc
CFLAGS  = -Wall -g -std=c99 $(shell pkg-config allegro_dialog-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_ttf-5 allegro_font-5 allegro_image-5 allegro-5 allegro_font-5 --cflags)
LDLIBS  = $(shell pkg-config allegro_dialog-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_ttf-5 allegro_font-5 allegro_image-5 allegro-5 allegro_font-5 --libs)
MAIN    = main
ENTREGA = $(MAIN)

HDR = tela_inicial.h tela_jogo.h personagem.h obstaculos.h colisao.h hud.h tela_game_over.h interacoes.h tela_fim_de_jogo.h

OBJ = tela_inicial.o tela_jogo.o personagem.o obstaculos.o colisao.o hud.o tela_game_over.o interacoes.o tela_fim_de_jogo.o

$(MAIN): $(MAIN).o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

$(MAIN).o: $(MAIN).c $(HDR)

tela_inicial.o: tela_inicial.c tela_inicial.h
tela_jogo.o: tela_jogo.c tela_jogo.h
personagem.o: personagem.c personagem.h
obstaculos.o: obstaculos.c obstaculos.h
colisao.o: colisao.c colisao.h
hud.o: hud.c hud.h
tela_game_over.o: tela_game_over.c tela_game_over.h
interacoes.o: interacoes.c interacoes.h
tela_fim_de_jogo.o: tela_fim_de_jogo.c tela_fim_de_jogo.h

run: $(MAIN)
	./$(MAIN)

valgrind: $(MAIN)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN)

tgz: clean
	-mkdir -p /tmp/$(USER)/$(ENTREGA)
	chmod 0700 /tmp/$(USER)/$(ENTREGA)
	cp *.c *.h makefile /tmp/$(USER)/$(ENTREGA)
	tar czvf $(ENTREGA).tgz -C /tmp/$(USER) $(ENTREGA)
	rm -rf /tmp/$(USER)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"

clean:
	rm -f *~ $(OBJ) $(MAIN).o $(MAIN) /tmp/$(USER)/$(ENTREGA) $(ENTREGA).tgz