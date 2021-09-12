#include "Snake.h"

using namespace std;

//Método para setar a posição e a orientação inicial da cobra
void Snake::set_snake_pos(pair<int, int> initial_pos, SnakeDirections new_orient) {
    pos = initial_pos; //Seta a posição
    orient = new_orient; //Seta a orientação
}

//Método para atualizar a posição e a orientação da cobra
void Snake::update_snake_pos(pair<int, int> new_pos) {
    if (new_pos.first < pos.first) {
        orient = NORTH; //Caso o Y da nova posição seja menor que o atual, então a cobra está virada para o NORTE
    } else if (new_pos.first > pos.first) {
        orient = SOUTH; //Caso o Y da nova posição seja maior que o atual, então a cobra está virada para o SUL
    } else if (new_pos.second < pos.second) {
        orient = WEST; //Caso o X da nova posição seja menor que o atual, então a cobra está virada para o OESTE
    } else if (new_pos.second > pos.second) {
        orient = EAST; //Caso o X da nova posição seja maior que o atual, então a cobra está virada para o LESTE
    }

    pos = new_pos; //Por fim, atualiza a nova posição
}

//Método que retorna a posição da cobra
pair<int, int> Snake::get_pos() {
    return pos; //Retorna a posição atual da cobra
}

//Método que retorna o char da cabeça da cobra de acordo com a direção
char Snake::get_snake_char() {
    if (orient == NORTH) {
        return 'v'; //Caso a cobra esteja virada para o NORTE, sua cabeça é representada por 'v'
    } else if (orient == EAST) {
        return '<'; //Caso a cobra esteja virada para o LESTE, sua cabeça é representada por '<'
    } else if (orient == WEST) {
        return '>'; //Caso a cobra esteja virada para o OESTE, sua cabeça é representada por '>'
    }

    return '^'; //Caso a cobra esteja virada para o SUL, sua cabeça é representada por '^'
}

//Método que retorna a orientação da cobra
SnakeDirections Snake::get_orient() {
    return orient; //Retorna a orientação atual
}