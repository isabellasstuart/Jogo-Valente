CC      = gcc
CFLAGS  = -Wall -g -std=c99 $(shell pkg-config allegro_dialog-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_ttf-5 allegro_font-5 allegro_image-5 allegro-5 allegro_font-5 --cflags)
LDLIBS  = $(shell pkg-config allegro_dialog-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_ttf-5 allegro_font-5 allegro_image-5 allegro-5 allegro_font-5 --libs)
MAIN    = main
ENTREGA = $(MAIN)

# lista de arquivos de cabeçalho (a completar)
HDR = tela_inicial.h tela_jogo.h personagem.h

# lista de arquivos-objeto (a completar)
OBJ = tela_inicial.o tela_jogo.o personagem.o

# construir o executável
$(MAIN): $(MAIN).o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# construir os arquivos-objeto (a completar)
$(MAIN).o: $(MAIN).c $(HDR)

tela_inicial.o: tela_inicial.c tela_inicial.h
tela_jogo.o: tela_jogo.c tela_jogo.h
personagem.o: personagem.c personagem.h

# executar
run: $(MAIN)
	./$(MAIN)

# testar no Valgrind
valgrind: $(MAIN)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN)

# gerar arquivo TGZ para entregar
tgz: clean
	-mkdir -p /tmp/$(USER)/$(ENTREGA)
	chmod 0700 /tmp/$(USER)/$(ENTREGA)
	cp *.c *.h makefile /tmp/$(USER)/$(ENTREGA)
	tar czvf $(ENTREGA).tgz -C /tmp/$(USER) $(ENTREGA)
	rm -rf /tmp/$(USER)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"

# limpar arquivos temporários
clean:
	rm -f *~ $(OBJ) $(MAIN).o $(MAIN) /tmp/$(USER)/$(ENTREGA) $(ENTREGA).tgz