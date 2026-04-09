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

string* geraNomes(string nomeFicheiro, int &totalNomes);
jogador* gerarPlantel(int &totalNomes);
int valorPosicao(string pos);
void ordenarPorPosicao(jogador* plantel, int numJogadores);

void adicionarJogador(jogador* &lista, int &numJogadores, jogador novoJogador);
void removerJogador(jogador* &lista, int &numJogadores, jogador jogadorRemovido);
void alterarTatica(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios);
void gerirFisicaDisciplina(jogador* &plantel, int &numJogadores, jogador* &lesionados, int &numLesionados, jogador* &castigados, int &numCastigados, jogador* &transferencias, int &numTransferencias, string* adversarios, int numAdversarios);
void gravarEquipa(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios) ;
void carregarEquipa(jogador* &plantel, int &numJogadores, jogador* &lesionados, int &numLesionados, jogador* &castigados, int &numCastigados, jogador* &transferencias, int &numTransferencias, string* adversarios, int numAdversarios, string nomeFicheiro);
void transferir(jogador* &plantel, int &numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* &transferencias, int &numTransferencias, string* adversarios, int numAdversarios);
void passarJornada(jogador* &plantel, int &numJogadores, jogador* &lesionados, int &numLesionados, jogador* &castigados, int &numCastigados, jogador* &transferencias, int &numTransferencias, string* adversarios, int numAdversarios);
void exibirGestao(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios);
void mudarPos(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios);
void melhorarQualidade(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios);
void treinarJogador(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios);
void exibirMenu(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios, bool aposJornada);
void mostrarPlantel(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, bool aposJornada);