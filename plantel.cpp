#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>
#include "plantel.h"

using namespace std;

const int MAX_NOMES = 1000;

void gerarPlatel(const string & ficheiro) {
    ifstream file(ficheiro);

    if (!file.is_open()) {
        cerr << "Erro ao abrir ficheiro!\n";
        return;
    }

    string nomes[MAX_NOMES];
    int totalNomes = 0;

    while (getline(file, nomes[totalNomes]) && totalNomes < MAX_NOMES) {
        if (!nomes[totalNomes].empty()) {
            totalNomes++;
        }
    }

    file.close();

    random_device rd;
    mt19937 gen(rd());

    for (int i = totalNomes - 1; i > 0; i--) {
        uniform_int_distribution<> dist(0, i);
        int j = dist(gen);

        swap(nomes[i], nomes[j]);
    }

    uniform_int_distribution<> dist(20, 30);
    int totalJogadores = dist(gen);

    if (totalJogadores > totalNomes) {
        totalJogadores = totalNomes;
    }

    cout << "Plantel gerado:\n";
    for (int i = 0; i < totalJogadores; i++) {
        cout << "- " << nomes[i] << "\n";
    }
}