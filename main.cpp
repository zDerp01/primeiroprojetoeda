#include <iomanip>
#include <iostream>
#include "plantel.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
    srand (time(NULL));

    int numJogadoresSort = 0;
    jogador* plantel = gerarPlantel(numJogadoresSort,0);
    mostrarPlantel(plantel, numJogadoresSort);

    system("pause");
}