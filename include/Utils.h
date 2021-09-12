#ifndef Utils_h
#define Utils_h
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Enum para os objetos de um mapa
enum LevelObjects
{
    WALL,                          //<! Indica objeto parede do mapa
    INVISIBLE_WALL,                //<! Indica objeto parede invisível do mapa
    SNAKE_INITIAL_POSITION,        //<! Indica objeto cobra do mapa
    FRUIT,                         //<! Indica objeto fruta do mapa
    FREE_SPACE,                    //<! Indica espaço livre do mapa
};

//Enum para os estados do jogo
enum GameStates
{
    RUNNING,                        //<! quando o jogo está executando o estado é RUNNING
    GAME_OVER,                      //<! quando o jogo deve terminar o estado é GAME_OVER
    WAITING_USER,                   //<! quando o jogo deve esperar por uma entrada do usuário o estado é WAITING_USER
    WAITING_SOLUTION                //<! quando o jogo deve esperar por uma solução do mapa o estado é WAITING_USER
};

//Enum para as direções da cobra
enum SnakeDirections
{
    NORTH,                          //<! quando a cobra está virada com a cabeça para cima o estado é NORTH
    SOUTH,                          //<! quando a cobra está virada com a cabeça para baixo o estado é SOUTH
    EAST,                           //<! quando a cobra está virada com a cabeça para direita o estado é EAST
    WEST                            //<! quando a cobra está virada com a cabeça para esquerda o estado é WEST
};

//Função backtracking que retorna false caso não tenha achado solução e true caso tenha
bool solveMap(vector<vector<char>> map, pair<int, int> snake_pos, SnakeDirections snake_dir, vector<pair<int, int>> sol, vector<pair<int, int>> &real_solution_vec, pair<int, int> fruit);

#endif //Utils_h