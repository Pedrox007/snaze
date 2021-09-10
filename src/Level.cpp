#include "Level.h"

//Construtor
Level::Level(int linesCount, int colsCount, vector<string> map_lines, int fruits_number) {
    //Seta alguns atributos do objeto como as dimensões
    current_fruit = 0;
    dimensions.first = linesCount;
    dimensions.second = colsCount;

    define_map(map_lines); //Chama o método de definir o mapa passando a mtriz de linhas recebida

    generate_fruits(fruits_number); //Chama o método para gerar as frutas passando a quantidade de frutas recebidas
}

//Método para gerar aleatoriamente as frutas
void Level::generate_fruits(int fruits_number) {
    srand(time(NULL)); //Configura a seed da função rand

    //Declara algumas variáveis auxiliares
    vector<pair<int, int>> positions_checked;
    pair<int, int> new_fruit_pos;
    int count = 0;

    //Loop que só para quando o count de frutas geradas chega ao limite
    while (count < fruits_number) {
        //Gera aleatoriamente a posição da fruta de acordo com as dimensões do mapa
        new_fruit_pos.first = rand() % dimensions.first;
        new_fruit_pos.second = rand() % dimensions.second;

        //Checa se a posição gerada está livre para ser posicionada a fruta além de checar se essa posição já foi checada
        if (
            get_map_object(new_fruit_pos) != FREE_SPACE || 
            find(positions_checked.begin(), positions_checked.end(), new_fruit_pos) != positions_checked.end()
            ) 
        {
            positions_checked.push_back(new_fruit_pos); //Caso Não seja possível possicionar a fruta na posição, ela é armazenada para ser checada mais facilmente caso seja gerada novamente
            continue;
        }

        //Adiciona a fruta a lista de frutas do objeto e incrementa o count de frutas geradas
        fruits.push_back(new_fruit_pos);
        count++;
    }

}

//Método para incrementar o index da fruta sendo mostrada
bool Level::pass_fruit() {
    current_fruit++; //Incrementa o index da fruta atual

    if (current_fruit >= fruits.size()) return false; //Retorna falso caso o index ultrapasse o número de frutas do mapa

    return true; //Retorna verdadeiro caso o index esteja dentro do limite da quantidade de frutas
}

//Método para definir a estrutura do mapa
void Level::define_map(vector<string> map_lines) {
    //Declara vetor auxiliar
    vector<char> line_vec;

    for (auto line : map_lines) {
        copy(line.begin(), line.end(), back_inserter(line_vec)); //Copia cada char da linha para o vetor de linhas

        map.push_back(line_vec); //Adiciona o vetor ao mapa

        line_vec.clear(); //Reseta os valore do vetor de chars
    }
}

//Método para retornar o mapa
vector<vector<char>> Level::get_map() {
    return map; //Retorna o mapa
}

//Método para retornar qual tipo de objeto está em uma posição passada
LevelObjects Level::get_map_object(pair<int, int> pos) {
    if (map[pos.first][pos.second] == '#') //Caso seja uma parede
    {
        return WALL;
    } else if (map[pos.first][pos.second] == '.') //Caso seja uma parede invisivel
    {
        return INVISIBLE_WALL;
    } else if (map[pos.first][pos.second] == '*') //Caso seja a posição inicial da cobra
    {
        return SNAKE_INITIAL_POSITION;
    } else {
        for (auto fruit : fruits) {
            if (fruit == pos) //Caso seja a posição de uma fruta
            {
                return FRUIT; 
            }
        }
    }
    
    return FREE_SPACE; //Caso seja um espaço livre
}

//Método para retornar a posição da fruta atual
pair<int, int> Level::get_current_fruit() {
    return fruits[current_fruit]; //Retorna a posição da fruta atual
}
