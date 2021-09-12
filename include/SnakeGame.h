#ifndef SnakeGame_h
#define SnakeGame_h
#include <iostream>
#include <vector>

#include "Level.h"
#include "Utils.h"
#include "Snake.h"

using namespace std;

class SnakeGame
{
private:
    //<! atributos adicione outros se quiser
    vector<Level> maps;                 //<! vector contendo os mapas
    int current_map;                    //<! usado para especificar qual é o mapa mostrado
    string choice;                      //<! usado na função process_actions para guardar a escolha do usuário
    GameStates state;                   //<! guarda o estado do jogo
    vector<pair<int, int>> solution;    //<! vector com a solução do mapa
    int current_sol_pos_index;          //<! inteiro indicando a posição da soluçao
    bool has_solution;                  //<! booleano indicando se existe solução
    Snake snake;                        //<! Objeto Snake que contem a posição e a orientação da cobra

public:
    /**
        * @brief construtor padrão, fique à vontade para adicionar parâmetros se desejar
        **/
    SnakeGame(string filePath);

    /**
        * @brief chamado no main, este loop executa o jogo indefinidamente até que o usuário escolha terminar!
        */
    void loop();

private:
    /**
        * @brief realiza a inicialização geral do jogo, fique à vontade para adicionar parâmetros se achar que deve
        **/
    void initialize_game(string filePath);

    /**
        * @brief atualiza o estado do jogo, basicamente movendo os objetos, sorteando novas posições de comida
        **/
    void update();

    /**
        * @brief processa as entradas do jogador
        **/
    void process_actions();

    /**
        * @brief testa o estado do jogo e desenha a tela correspondente
        **/
    void render();

    /**
        * @brief é chamada quando o jogo termina a fim de destruir/resetar elementos do estado do jogo
        **/
    void game_over();
};

#endif //SnakeGame_h