#include <iostream>
#include "../include/SnakeGame.h"

using namespace std;

int main(int argc, char *argv[])
{
    //Caso o número de argumentos passados seja menor do que 2 ele exibe uma mensagem pedindo o caminho completo do arquivo.
    if (argc < 2)
    {
        cout << "[ E ]: Forneça o caminho completo do arquivo de nível." << endl;
        //Encerra o programa indicando falha no programa.
        exit(EXIT_FAILURE);
    }

    //Atribui a um ponteiro arquivo um arquivo real do computador cujo caminho é passado por linha de comando e é capturado pelo vetor argv na posição 1. O parâmetro r é passado para indiciar que o arquivo aberto será leitura.
    FILE *arquivo = fopen(argv[1], "r");

    //Caso a função fopen retorne NULL, significa que houve um erro, então é exibido a mensagem que o arquivo não foi encontrado.
    if (arquivo == NULL)
    {
        cout << "[ E ]: Arquivo não encontrado." << endl;
        //Encerra o programa indicando falha no programa.
        exit(EXIT_FAILURE);
    }

    //Fecha o arquivo aberto anteriormente.
    fclose(arquivo);

    //Exibe a mensagem que sucesso.
    cout << "[ I ]: Sucesso." << endl;

    //Instância um objeto game da classe SnakeGame passando o caminho do arquivo.
    SnakeGame game(argv[1]);

    game.loop(); //Bloqueia aqui e só saí quando o jogo termina

    return 0;
}