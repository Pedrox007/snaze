#include <iostream>
#include "../include/SnakeGame.h"

using namespace std;

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        cout << "[ E ]: Forneca o caminho completo do arquivo por meio do parametro." << endl;
        exit(EXIT_FAILURE);
    }

    FILE *arquivo = fopen(argv[1], "r");

    if (arquivo == NULL)
    {
        cout << "[ E ]: FArquivo nao encontrado." << endl;
        exit(EXIT_FAILURE);
    }

    fclose(arquivo);

    SnakeGame game;

    game.loop(); //bloqueia aqui e só saí quando o jogo termina

    return 0;
}