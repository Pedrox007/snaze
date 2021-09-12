#include "SnakeGame.h"

#include <iostream>
#include <fstream>

#include <sstream> //Define vários modelos de classe que suportam operações iostreams em sequências armazenadas em um objeto de matriz alocada.
#include <ctype.h> //Define classes para trabalhar com caracteres e fazer conversões.

#include <chrono> //Por causa do sleep
#include <thread> //Por causa do sleep

using namespace std;

//Construtor
SnakeGame::SnakeGame(string filePath)
{
    choice = "";
    current_map = 0;
    initialize_game(filePath);
}

//Realiza a inicialização geral do jogo
void SnakeGame::initialize_game(string filePath)
{
    //Carrega as variáveis auxiliares para a inicialização do jogo

    //Abre o arquivo apenas para leitura
    ifstream levelFile(filePath);

    int linesCount, colsCount, fruits;
    string line;
    vector<string> map;

    //Caso consiga abrir o arquivo
    if (levelFile.is_open())
    {
        //Até chegar ao final do arquivo a função getline lê o caractere e o descarta,e armazena o mesmo na variável line.
        while (getline(levelFile, line))
        {
            //Se o primeiro digito da linha for um número, é carregado um novo mapa e salva o anterior.
            if (isdigit(line[0]))
            {
                //Caso o vector com as linhas do mapa não esteja vazio
                if ((int)map.size() > 0)
                {
                    //Adiciona um novo objeto Level com o mapa em maps
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
    if ((int)map.size() == 0)
    {
        cout << "[ E ]: Erro ao ler mapas do arquivo." << endl;
        //Encerra o programa indicando falha no programa.
        exit(EXIT_FAILURE);
    }
    maps.push_back(Level(linesCount, colsCount, map, fruits)); //Adiciona o último mapa do arquivo a lista de mapas

    snake.set_snake_pos(maps[current_map].get_snake_initial_pos(), NORTH); //Seta a posição inicial da cobra com o valor passado pelo Level

    state = WAITING_SOLUTION; //Seta state para WAITING_SOLUTION para procurar a solução para a primeira fruta
}

void SnakeGame::process_actions()
{
    vector<pair<int, int>> sol;
    //processa as entradas do jogador de acordo com o estado do jogo
    //nesse exemplo o jogo tem 3 estados, WAITING_USER, RUNNING e GAME_OVER.
    //no caso deste trabalho temos 2 tipos de entrada, uma que vem da classe Player, como resultado do processamento da IA
    //outra vem do próprio usuário na forma de uma entrada do teclado.
    switch (state)
    {
    case WAITING_USER: //o jogo bloqueia aqui esperando o usuário digitar a escolha dele
        cin >> std::ws >> choice;
        break;
    case WAITING_SOLUTION: //o jogo bloqueia aqui esperando a solução ser gerada
        //Chama a função que faz o backtracking para procurar uma solução
        has_solution = solveMap(maps[current_map].get_map(), snake.get_pos(), snake.get_orient(), sol, solution, maps[current_map].get_current_fruit());
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
        current_sol_pos_index++; //Incrementa o index de posições da solução

        //Caso o index de posições da solução passe do tamanho do vetor
        if (current_sol_pos_index >= (int)solution.size())
        {
            //Caso haja frutas no mapa
            if (maps[current_map].pass_fruit())
            {
                state = WAITING_SOLUTION; //Seta state para WAITING_SOLUTION afim de procurar solução para a nova fruta do mapa
            }
            else
            {
                current_map++; //Passa para o próximo mapa caso não haja mais frutas

                //Caso não exista mais mapas
                if (current_map >= (int)maps.size())
                {
                    //Finaliza o jogo e o programa
                    state = GAME_OVER;
                    game_over();
                }
                else
                {
                    state = WAITING_USER; //Seta o state para WAITING_USER caso haja mais mapas para ele decidir se continua
                }
            }
        }
        else
        {
            snake.update_snake_pos(solution[current_sol_pos_index]); //Caso ainda haja posições a ser feitas da solução, a posição da cobra é atualizada com a posição da solução
        }
        break;
    case WAITING_USER: //se o jogo estava esperando pelo usuário então ele testa qual a escolha que foi feita
        //Caso a escolha seja finalizar o jogo, assim é feito, o jogo termina
        if (choice == "n")
        {
            state = GAME_OVER;
            game_over();
        }
        else
        {
            snake.set_snake_pos(maps[current_map].get_snake_initial_pos(), NORTH); //Caso seja continuar, é reiniciado a posição e a direção da cobra para o novo mapa
            state = WAITING_SOLUTION;                                              //Seta o state para WAITING_SOLUTION para procurar uma nova solução
        }
        break;
    case WAITING_SOLUTION:
        //Caso não haja solução
        if (!has_solution)
        {
            //Caso haja frutas no mapa
            if (maps[current_map].pass_fruit())
            {
                state = WAITING_SOLUTION; //Seta state para WAITING_SOLUTION afim de procurar solução para a nova fruta do mapa
            }
            else
            {
                current_map++; //Passa para o próximo mapa caso não haja mais frutas

                //Caso não exista mais mapas
                if (current_map >= (int)maps.size())
                {
                    //Finaliza o jogo e o programa
                    state = GAME_OVER;
                    game_over();
                }
                else
                {
                    state = WAITING_USER; //Seta o state para WAITING_USER caso haja mais mapas para ele decidir se continua
                }
            }
        }
        else
        {
            current_sol_pos_index = 0; //Seta o atributo que define o index de posição da solução
            state = RUNNING;
        }
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
    //Iniciar as variaveis contendo mapa, posição da fruta, posição da cobra
    pair<int, int> fruit_pos = maps[current_map].get_current_fruit();
    pair<int, int> snake_pos = snake.get_pos();
    vector<vector<char>> map = maps[current_map].get_map();
    char el;
    switch (state)
    {
    case WAITING_SOLUTION:
    case RUNNING:
        //Lendo linhas do mapa
        for (int lines_i = 0; lines_i < (int)map.size(); lines_i++)
        {
            //Lendo colunas do mapa
            for (int cols_i = 0; cols_i < (int)map[lines_i].size(); cols_i++)
            {
                el = map[lines_i][cols_i];
                //Caso o elemento do mapa seja a posição inicial da cobra, é pra printar o espaço vazio ou a cobra na posição inicial
                if (el == '*')
                {
                    if (lines_i == snake_pos.first && cols_i == snake_pos.second)
                    {
                        cout << snake.get_snake_char();
                        continue;
                    }
                    else
                    {
                        cout << " ";
                        continue;
                    }
                }

                //Caso seja a posição da cobra, é para printa-la
                if (lines_i == snake_pos.first && cols_i == snake_pos.second)
                {
                    cout << snake.get_snake_char();
                    continue;
                }

                //Caso seja a posição da fruta, é para printa-la
                if (lines_i == fruit_pos.first && cols_i == fruit_pos.second)
                {
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
        //Caso não haja solução, é para mostrar um aviso relativo a isso e depois perguntar se deseja seguir o jogo
        if (!has_solution)
        {
            cout << "Não existe solução para chegar na fruta" << endl;
        }

        cout << "Você quer continuar com o jogo? (s/n)" << endl;
        break;
    case GAME_OVER:
        cout << "O jogo terminou!" << endl;
        break;
    }
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
        wait(500); // espera 1 segundo entre cada frame
    }
}
