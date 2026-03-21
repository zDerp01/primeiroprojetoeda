#include <iomanip>
#include <iostream>
#include "plantel.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
    srand (time(NULL));

    // cria o plantel inicial
    int numJogadoresSort = 0;
    jogador* plantel = gerarPlantel(numJogadoresSort);

    // cria listas de lesionados, castigados e transferencias
    int numLesionados = 0;
    jogador* lesionados = nullptr;

    int numCastigados = 0;
    jogador* castigados = nullptr;

    int numTransferencias = 0;
    jogador* transferencias = nullptr;

    adicionarJogador(lesionados, numLesionados, plantel[0]);
    removerJogador(plantel, numJogadoresSort, plantel[0]);

    mostrarPlantel(plantel, numJogadoresSort, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias);


    delete[] plantel;
    delete[] lesionados;
    delete[] castigados;
    delete[] transferencias;

    //system("cls");
    system("pause");
}