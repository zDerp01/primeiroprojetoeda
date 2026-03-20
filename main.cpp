#include <iostream>
#include "plantel.h"
#include <stdlib.h>
#include <list>
#include <time.h>

using namespace std;

int main() {
    srand (time(NULL));
    list<jogador> jogadores;
    jogadores = gerarLista(jogadores);


    for (const auto& j : jogadores) {
        cout << j.id << " | " << j.nome << " | " << j.pos << " | " << j.num << endl;
    }

    return 0;
}