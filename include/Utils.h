#ifndef Utils_h
#define Utils_h
#include <iostream>

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
    RUNNING,     //<! quando o jogo está executando o estado é RUNNING
    GAME_OVER,   //<! quando o jogo deve terminar o estado é GAME_OVER
    WAITING_USER //<! quando o jogo deve esperar por uma entrada do usuário o estado é WAITING_USER
};

#endif //Utils_h