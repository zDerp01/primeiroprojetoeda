#include <iomanip>
#include <iostream>
#include "plantel.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char* argv[]) {
    srand (time(NULL));

    // ------ cria o plantel inicial, listas de lesionados, castigados, transferencias e lista de adversarios ------
    int numJogadoresSort = 0;
    int numLesionados = 0;
    int numCastigados = 0;
    int numTransferencias = 0;
    int numAdversarios = 0;

    // Inicializamos a nullptr para evitar erros no delete[] final caso o ficheiro não carregue
    jogador* plantel = nullptr;
    jogador* lesionados = nullptr;
    jogador* castigados = nullptr;
    jogador* transferencias = nullptr;
    string* adversarios = geraNomes("equipas.txt", numAdversarios);

    // Verificamos se foi passado um ficheiro por argumento
    if (argc > 1) {
        carregarEquipa(plantel, numJogadoresSort, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios, argv[1]);
    }
    else {
        // Se não houver argumento, gera o plantel novo normalmente
        plantel = gerarPlantel(numJogadoresSort);

        //adicionarJogador(lesionados, numLesionados, plantel[0]);
        //removerJogador(plantel, numJogadoresSort, plantel[0]);

        mostrarPlantel(plantel, numJogadoresSort, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, false);
        exibirMenu(plantel, numJogadoresSort, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios, false);
    }

    delete[] plantel;
    delete[] lesionados;
    delete[] castigados;
    delete[] transferencias;
    delete[] adversarios;

    //system("cls");
    //system("pause");

    return 0;
}