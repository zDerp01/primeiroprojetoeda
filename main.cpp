#include <iostream>
#include "plantel.h"
#include <stdlib.h>
#include <list>
#include <time.h>

using namespace std;

int main() {
    srand (time(NULL));
    int numJogadores = rand()%11+20;

    struct jogador {
        int id;
        string nome;
        string pos;
        int num;
    };

    list<jogador> jogadores;

    for (int i = 0; i < numJogadores; i++) {
        jogador j;

        j.id = i + 1;
        j.nome = "Jogador_" + to_string(i + 1);

        string posicoes[] = {"GR", "DEF", "MED", "AVA"};
        j.pos = posicoes[rand() % 4];

        j.num = rand() % 99 + 1;

        jogadores.push_back(j);
    }

    for (const auto& j : jogadores) {
        cout << j.id << " | " << j.nome << " | " << j.pos << " | " << j.num << endl;
    }

    return 0;
}