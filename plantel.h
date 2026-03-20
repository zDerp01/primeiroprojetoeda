#include <iostream>
#include <list>
#include <string>

using namespace std;

struct jogador {
    string nome;
    string pos;
    int num;
    int idade;
    int prob_castigo;
    int prob_lesao;
    int dias_treino;
    int qualidade;
};

string* geraNomes(string nomeFicheiro, int &totalNomes);
jogador* gerarPlantel(int &totalNomes, int numJogadores);
void mostrarPlantel(jogador* plantel, int numJogadores);