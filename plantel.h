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

string* geraNomes(string nomeFicheiro, int &totalNomes);
jogador* gerarPlantel(int &totalNomes);
void adicionarJogador(jogador* &lista, int &numJogadores, jogador novoJogador);
void removerJogador(jogador* &lista, int &numJogadores, jogador jogadorRemovido);
void transferir(jogador* &plantel, int &numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* &transferencias, int &numTransferencias, string* adversarios, int numAdversarios);
void passarJornada(jogador* &plantel, int &numJogadores, jogador* &lesionados, int &numLesionados, jogador* &castigados, int &numCastigados, jogador* &transferencias, int &numTransferencias, string* adversarios, int numAdversarios);
void exibirGestao(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios);
void treinarJogador(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias);
void exibirMenu(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios, bool aposJornada);
void mostrarPlantel(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, bool aposJornada);