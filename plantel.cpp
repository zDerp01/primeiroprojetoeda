#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>
#include "plantel.h"
#include <list>

using namespace std;

list<jogador> gerarLista(list<jogador> lista) {
    int numJogadores = rand()%11+20;

    ifstream file("nomes.txt");
    string linha;
    int totalNomes = 0;
    while (getline(file, linha))
        if (linha != "") totalNomes++;

    for (int i = 0; i < numJogadores; i++) {
        jogador j;
        j.id = i + 1;

        int escolha = rand() % totalNomes;
        int contador = 0;
        ifstream file2("nomes.txt");
        while (getline(file2, linha)) {
            if (linha.empty()) continue;
            if (contador == escolha) break;
            contador++;
        }
        j.nome = linha;

        string posicoes[] = {"GR", "DEF", "MED", "AVA"};
        j.pos = posicoes[rand() % 4];

        j.num = rand() % 99 + 1;

        lista.push_back(j);
    }

    return lista;
}
