#include <iostream>
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

struct equipa {
    string nome;
};

jogador* gerarPlantel(int &totalNomes);
void adicionarJogador(jogador* &lista, int &numJogadores, jogador novoJogador);
void removerJogador(jogador* &lista, int &numJogadores, jogador jogadorRemovido);
void passarJornada();
void mostrarPlantel(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias);