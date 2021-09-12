#ifndef Level_h
#define Level_h
#include <iostream>
#include <vector>
#include <algorithm>
#include "Utils.h"

using namespace std;

//Classe do mapa
class Level
{
public:
    Level(int linesCount, int colsCount, vector<string> map_lines, int fruits_number); //Construtor

    bool pass_fruit(); //Método para incrementar o index da fruta sendo mostrada

    vector<vector<char>> get_map(); //Método para retornar o mapa

    pair<int, int> get_current_fruit(); //Método para retornar a posição da fruta atual

    pair<int, int> get_snake_initial_pos(); //Método para retornar posição inicial da cobra no mapa

    LevelObjects get_map_object(pair<int, int> pos); //Método para retornar qual tipo de objeto está em uma posição passada

private:
    vector<vector<char>> map; //Matriz do mapa
    vector<pair<int, int>> fruits; //Vetor de posições para as frutas
    int current_fruit; //Inteiro que indica o index do vetor da fruta atual
    pair<int, int> dimensions; //Dimensões da mtriz do mapa

    void define_map(vector<string> map_lines); //Método para definir a estrutura do mapa

    void generate_fruits(int fruits_number); //Método para gerar aleatoriamente as frutas
};

#endif //Level_h