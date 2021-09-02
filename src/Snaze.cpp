#include <iostream>
#include "../include/SnakeGame.h"

using namespace std;

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        fprintf(stderr, "[ E ]: Forneca o caminho completo do arquivo por meio do parametro. \n");
        exit(EXIT_FAILURE);
    }

    FILE *arquivo = fopen(argv[1], "r");

    if (arquivo == NULL)
    {
        fprintf(stderr, "[ E ]: Arquivo nao encontrado. \n");
        exit(EXIT_FAILURE);
    }

    fclose(arquivo);
    printf("[I]: Sucesso. \n");
    return EXIT_SUCCESS;
    SnakeGame game;

    game.loop(); //bloqueia aqui e só saí quando o jogo termina

    return 0;
}