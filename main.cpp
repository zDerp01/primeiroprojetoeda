#include <iomanip>
#include <iostream>
#include "plantel.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
    srand (time(NULL));

    // ------ cria o plantel inicial, listas de lesionados, castigados, transferencias e lista de adversarios ------
    int numJogadoresSort = 0;
    jogador* plantel = gerarPlantel(numJogadoresSort);
    int numLesionados = 0;
    jogador* lesionados = nullptr;
    int numCastigados = 0;
    jogador* castigados = nullptr;
    int numTransferencias = 0;
    jogador* transferencias = nullptr;
    int numAdversarios = 0;
    string* adversarios = geraNomes("equipas.txt", numAdversarios);


    //adicionarJogador(lesionados, numLesionados, plantel[0]);
    //removerJogador(plantel, numJogadoresSort, plantel[0]);

    mostrarPlantel(plantel, numJogadoresSort, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, false);
    exibirMenu(plantel, numJogadoresSort, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios, false);

    delete[] plantel;
    delete[] lesionados;
    delete[] castigados;
    delete[] transferencias;
    delete[] adversarios;

    //system("cls");
    system("pause");
}