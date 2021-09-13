#include "Utils.h"

using namespace std;

//Função backtracking que retorna false caso não tenha achado solução e true caso tenha
bool solveMap(vector<vector<char>> map, pair<int, int> snake_pos, SnakeDirections snake_dir, vector<pair<int, int>> sol, vector<pair<int, int>> &real_solution_vec, pair<int, int> fruit)
{
    //Inicializa posição auxiliar da cobra
    pair<int, int> snake_pos_aux;

    //Caso a cobra tenha chegado à fruta, é setado a solução ao vetor da solução real e retornado true
    if (
        snake_pos.first == fruit.first && snake_pos.second == fruit.second)
    {
        sol.push_back(snake_pos);
        real_solution_vec = sol;
        return true;
    }

    //Caso a posição atual seja um espaço livre ou a posição inicial da cobra e não seja parte da solução, ele entra para checar a próxima posição
    if ((map[snake_pos.first][snake_pos.second] == ' ' || map[snake_pos.first][snake_pos.second] == '*') && find(sol.begin(), sol.end(), snake_pos) == sol.end())
    {
        sol.push_back(snake_pos); //Adiciona a posição atual à solução

        //Checa se a direção da cobra possibilita o movimento para o SUL
        if (snake_dir == SOUTH || snake_dir == EAST || snake_dir == WEST)
        {
            snake_pos_aux.first = snake_pos.first + 1; //Adiciona 1 ao Y da cobra
            snake_pos_aux.second = snake_pos.second;   //Mantém o valor de X da cobra

            //Checa se é possível se mover para essa posição e retorna true se for possível
            if (solveMap(map, snake_pos_aux, SOUTH, sol, real_solution_vec, fruit) == true)
                return true;
        }

        //Checa se a direção da cobra possibilita o movimento para o NORTE
        if (snake_dir == NORTH || snake_dir == EAST || snake_dir == WEST)
        {
            snake_pos_aux.first = snake_pos.first - 1; //Subtrai 1 do Y da cobra
            snake_pos_aux.second = snake_pos.second;   //Mantém o valor de X da cobra

            //Checa se é possível se mover para essa posição e retorna true se for possível
            if (solveMap(map, snake_pos_aux, NORTH, sol, real_solution_vec, fruit) == true)
                return true;
        }

        //Checa se a direção da cobra possibilita o movimento para o LESTE
        if (snake_dir == EAST || snake_dir == NORTH || snake_dir == SOUTH)
        {
            snake_pos_aux.first = snake_pos.first;       //Mantém o valor de Y da cobra
            snake_pos_aux.second = snake_pos.second + 1; //Adiciona 1 ao X da cobra
            if (solveMap(map, snake_pos_aux, EAST, sol, real_solution_vec, fruit) == true)
                return true;
        }

        //Checa se a direção da cobra possibilita o movimento para o OESTE
        if (snake_dir == WEST || snake_dir == NORTH || snake_dir == SOUTH)
        {
            /* movendo para leste */
            snake_pos_aux.first = snake_pos.first;       //Mantém o valor de Y da cobra
            snake_pos_aux.second = snake_pos.second - 1; //Subtrai 1 do X da cobra
            if (solveMap(map, snake_pos_aux, WEST, sol, real_solution_vec, fruit) == true)
                return true;
        }
    }

    //Retorna false se não for uma posição inválida do mapa ou se já fizer parte da solução
    return false;
}