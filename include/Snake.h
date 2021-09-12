#ifndef Snake_h
#define Snake_h
#include <iostream>
#include <vector>
#include "Utils.h"

using namespace std;

class Snake
{
public:
    void set_snake_pos(pair<int, int> initial_pos, SnakeDirections new_orient); //Método para setar a posição e a orientação inicial da cobra

    void update_snake_pos(pair<int, int> new_pos); //Método para atualizar a posição e a orientação da cobra

    pair<int, int> get_pos(); //Método que retorna a posição da cobra

    char get_snake_char(); //Método que retorna o char da cabeça da cobra de acordo com a direção

    SnakeDirections get_orient(); //Método que retorna a orientação da cobra
private:
    pair<int, int> pos;         //Atributo para armazenar a posição da cobra
    SnakeDirections orient;     //Atributo para armazenar a orientação da cobra
};

#endif //Snake_h