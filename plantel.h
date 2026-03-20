#include <iostream>
#include <list>
#include <string>

using namespace std;

struct jogador {
    int id;
    string nome;
    string pos;
    int num;
};

list<jogador> gerarLista(list<jogador> lista);