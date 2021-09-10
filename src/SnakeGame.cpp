#include "SnakeGame.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctype.h>

#include <chrono> //por causa do sleep
#include <thread> //por causa do sleep

using namespace std;

SnakeGame::SnakeGame(string filePath)
{
    choice = "";
    frameCount = 0;
    current_map = 0;
    initialize_game(filePath);
}

void SnakeGame::initialize_game(string filePath)
{
    //carrega as variáveis auxiliares para a inicialização do jogo
    ifstream levelFile(filePath);
    int linesCount, colsCount, fruits;
    string line;
    vector<string> map;
    if (levelFile.is_open())
    {
        while (getline(levelFile, line))
        {
            //Se o primeiro digito da linha seja um número, é pra ser carregado um novo mapa e salva o anterior
            if (isdigit(line[0]))
            {
                //Caso o vector com as linhas do mapa não esteja vazio
                if (map.size() > 0) {
                    //Adiciona um novo objeto LEvel com o mapa em maps
                    maps.push_back(Level(linesCount, colsCount, map, fruits));
                }

                istringstream line_stream(line);

                //Salva os valores do arquivo com relação ao mapa
                line_stream >> linesCount >> colsCount >> fruits;
                map.clear();

                continue;
            }
            //Adiciona a string da linha ao vetor do mapa
            map.push_back(line);
        }
    }

    //Caso ao final não seja carrgado nenhuma linha do mapa, é retornado um erro
    if (map.size() == 0) {
        cout << "[ E ]: Erro ao ler mapas do arquivo." << endl;
        exit(EXIT_FAILURE);
    }
    maps.push_back(Level(linesCount, colsCount, map, fruits));//Adiciona o último mapa do arquivo a lista de mapas

    state = RUNNING;
}

void SnakeGame::process_actions()
{
    //processa as entradas do jogador de acordo com o estado do jogo
    //nesse exemplo o jogo tem 3 estados, WAITING_USER, RUNNING e GAME_OVER.
    //no caso deste trabalho temos 2 tipos de entrada, uma que vem da classe Player, como resultado do processamento da IA
    //outra vem do próprio usuário na forma de uma entrada do teclado.
    switch (state)
    {
    case WAITING_USER: //o jogo bloqueia aqui esperando o usuário digitar a escolha dele
        cin >> std::ws >> choice;
        break;
    default:
        //nada pra fazer aqui
        break;
    }
}

void SnakeGame::update()
{
    //atualiza o estado do jogo de acordo com o resultado da chamada de "process_input"
    switch (state)
    {
    case RUNNING:
        if (frameCount > 0 && frameCount % 10 == 0) //depois de 10 frames o jogo pergunta se o usuário quer continuar
            state = WAITING_USER;
        break;
    case WAITING_USER: //se o jogo estava esperando pelo usuário então ele testa qual a escolha que foi feita
        if (choice == "n")
        {
            state = GAME_OVER;
            game_over();
        }
        else
        {
            //pode fazer alguma coisa antes de fazer isso aqui
            state = RUNNING;
        }
        break;
    default:
        //nada pra fazer aqui
        break;
    }
}

/**
 * @brief função auxiliar para fazer o programa esperar por alguns milisegundos
 * @param ms a quantidade de segundos que o programa deve esperar
 */
void wait(int ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}

/**
 * @brief função auxiliar para limpar o terminal
 */
void clearScreen()
{
//some C++ voodoo here ;D
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined(__APPLE__)
    system("clear");
#endif
}

void SnakeGame::render()
{
    clearScreen();
    //Iniciar as variaveis contendo mapa e posição da fruta
    pair<int, int> fruit_pos = maps[current_map].get_current_fruit();
    vector<vector<char>> map = maps[current_map].get_map();
    char el;
    switch (state)
    {
    case RUNNING:
        //Lendo linhas do mapa
        for (int lines_i = 0; lines_i < map.size(); lines_i++)
        {
            //Lendo colunas do mapa
            for (int cols_i = 0; cols_i < map[lines_i].size(); cols_i++) {
                el = map[lines_i][cols_i];
                //Caso o elemento do mapa seja a posição inicial da cobra, é pra printar o espaço vazio
                if (el == '*') {
                    cout << " ";
                    continue;
                }

                //Caso seja a posição da fruta, é para printa-la
                if (lines_i == fruit_pos.first && cols_i == fruit_pos.second) {
                    cout << "@";
                    continue;
                }

                //Printa o elemento do mapa
                cout << el;
            }
            //Pula a linha
            cout << endl;
        }
        break;
    case WAITING_USER:
        cout << "Você quer continuar com o jogo? (s/n)" << endl;
        break;
    case GAME_OVER:
        cout << "O jogo terminou!" << endl;
        break;
    }
    frameCount++;
}

void SnakeGame::game_over()
{
}

void SnakeGame::loop()
{
    while (state != GAME_OVER)
    {
        process_actions();
        update();
        render();
        wait(1000); // espera 1 segundo entre cada frame
    }
}
