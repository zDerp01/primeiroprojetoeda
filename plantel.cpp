#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>
#include "plantel.h"

#include <iomanip>

using namespace std;

string* geraNomes(string nomeFicheiro, int &totalNomes) {
    ifstream file(nomeFicheiro);
    string linha;
    totalNomes = 0;

    while (getline(file, linha)) {
        if (linha != "") totalNomes++;
    }

    file.clear();
    file.seekg(0);

    string* nomesEscolhidos = new string[totalNomes];
    int i = 0;
    while (getline(file, linha)) {
        if (linha != "") {
            nomesEscolhidos[i] = linha;
            i++;
        }
    }
    file.close();
    return nomesEscolhidos;
}

jogador* gerarPlantel(int &totalPlantel, int numJogadores) {
    numJogadores = rand() % 11 + 20;

    int quantNomesNoFicheiro = 0;

    string* listaNomes = geraNomes("nomes.txt", quantNomesNoFicheiro); // isto muda o valor de quantNomesNoFicheiro

    int GR=2, DEF=7, MED=7, AVA=4;
    int extras = numJogadores - 20;

    while (extras > 0) {
        int sorteio = rand() % 4;
        if (sorteio == 0 && GR < 3) { GR++; extras--; }
        else if (sorteio == 1 && DEF < 10) { DEF++; extras--; }
        else if (sorteio == 2 && MED < 10) { MED++; extras--; }
        else if (sorteio == 3 && AVA < 7) { AVA++; extras--; }
    }

    jogador* plantel = new jogador[numJogadores];
    int locarray = 0;
    string posicoes[4] = {"GR", "DEF", "MED", "AVA"};
    int qtt[4] = {GR, DEF, MED, AVA};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < qtt[i]; j++) {
            if (locarray < numJogadores) {
                int indiceSorteado = rand() % quantNomesNoFicheiro;
                plantel[locarray].nome = listaNomes[indiceSorteado];

                plantel[locarray].pos = posicoes[i];
                plantel[locarray].idade = rand() % 18 + 18;
                plantel[locarray].num = rand() % 99 + 1;
                plantel[locarray].prob_castigo = rand() % 21;
                plantel[locarray].prob_lesao = rand() % 16;
                plantel[locarray].qualidade = rand() % 101;
                plantel[locarray].dias_treino = 0;
                locarray++;
            }
        }
    }

    delete[] listaNomes;

    totalPlantel = numJogadores;
    return plantel;
}

void mostrarPlantel(jogador* plantel, int numJogadores) {
    // Cabeçalho Principal
    cout << "\n***************************** Plantel Disponivel: *****************************" << endl;

    // Cabeçalho das Colunas
    cout << left << setw(26) << "Nome"
         << " | " << setw(4)  << "Num"
         << " | " << setw(7)  << "Posicao"
         << " | " << setw(6)  << "Idade"
         << " | " << setw(12) << "ProbLesao"
         << " | " << setw(13) << "ProbCastigo"
         << " | " << setw(8)  << "Qualidade"
         << " | " << "Dias-Treino" << endl;

    cout << "-----------------------------------------------------------------------------------------------" << endl;

    string ultimaPosicao = "";

    for (int i = 0; i < numJogadores; i++) {
        // pa ter espaço entre as diferentes posicoes
        if (i > 0 && plantel[i].pos != ultimaPosicao) {
            cout << endl;
        }
        ultimaPosicao = plantel[i].pos;

        cout << left << setw(26) << plantel[i].nome
             << " | " << setw(4)  << plantel[i].num
             << " | " << setw(7)  << plantel[i].pos
             << " | " << setw(6)  << plantel[i].idade
             << " | " << setw(3)  << plantel[i].prob_lesao << "%" << setw(8) << ""
             << " | " << setw(3)  << plantel[i].prob_castigo << "%" << setw(9) << ""
             << " | " << setw(8)  << plantel[i].qualidade
             << " | " << plantel[i].dias_treino << endl;
    }

    cout << "-----------------------------------------------------------------------------------------------" << endl;
}