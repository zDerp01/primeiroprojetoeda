#include <fstream>
#include <iostream>
#include <random>
#include "plantel.h"

#include <iomanip>

using namespace std;

int numJornada=1;

/**
* Função que recebe o nome de um ficheiro e referencia o totalNomes (para
* assim alterar o argumento usado para esse total de nomes), que retorna a lista com todos os nomes do ficheiro.
* @param nomeFicheiro - string nome do ficheiro.
* @param totalNomes - referencia que altera o numero de nomes consoantes os do ficheiro.
* @return - lista com os nomes todos do ficheiros.
*/
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


/**
* Função que recebe o numero total atual de jogadores no plantel que vai ser alterado consoante a geracao feita
* pelo inteiro local numJogadores e gera um plantel com cada jogador criado com todos os seus atributos preenchidos.
* @param totalPlantel - inteiro com a variavel que vai conter o numero de jogadores no plantel.
* @return - plantel.
*/
jogador* gerarPlantel(int &totalPlantel) {
    int numJogadores = rand() % 11 + 20;

    int quantNomesNoFicheiro = 0;

    string* listaNomes = geraNomes("nomes.txt", quantNomesNoFicheiro); // isto muda o valor de quantNomesNoFicheiro

    int GR=2, DEF=7, MED=7, AVA=4;
    int extras = numJogadores - 20;

    //for (extras; extras > 0; extras--) {
        //int sorteio = rand() % 4;
        //if (sorteio == 0 && GR < 3) GR++;
        //else if (sorteio == 1 && DEF < 10) DEF++;
        //else if (sorteio == 2 && MED < 10) MED++;
        //else if (sorteio == 3 && AVA < 7) AVA++;
    //}

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

/**
* Função que recebe uma lista (plantel, suspensos, lesionados ou transferencias) e adiciona um jogador ja existente a essa lista.
* @param lista - lista em que o jogador vai ser adicionado.
* @param numJogadores - numero de jogadores dessa lista (que vai ser atualizado).
* @param novoJogador - o jogador a adicionar.
*/
void adicionarJogador(jogador* &lista, int &numJogadores, jogador novoJogador) {
    jogador* novaLista = new jogador[numJogadores + 1];
    for (int i = 0; i < numJogadores; i++) {
        novaLista[i] = lista[i];
    }

    novaLista[numJogadores] = novoJogador;

    delete[] lista;

    lista = novaLista;
    numJogadores++;
}

/**
* Função que recebe uma lista (plantel, suspensos, lesionados ou transferencias) e remove um jogador especifico dessa lista.
* @param lista - lista em que o jogador vai ser removido.
* @param numJogadores - numero de jogadores dessa lista (que vai ser atualizado).
* @param jogadorRemovido - o jogador a remover.
*/
void removerJogador(jogador* &lista, int &numJogadores, jogador jogadorRemovido) {
    if (numJogadores != 0 || lista != nullptr) {
        jogador* novaLista = new jogador[numJogadores - 1];
        int j = 0;
        bool encontrou = false;
        for (int i = 0; i < numJogadores; i++) {
            if (!encontrou && lista[i].nome == jogadorRemovido.nome && lista[i].num == jogadorRemovido.num) {
                encontrou = true;
            }
            else {
                if (j < numJogadores - 1) {
                    novaLista[j] = lista[i];
                    j++;
                }
            }
        }

        if (!encontrou) {
            delete[] novaLista;
            return;
        }

        delete[] lista;

        lista = novaLista;
        numJogadores--;
    }
}

void passarJornada() {
    system("cls");
    numJornada++;
    

    // trabalha joao rodrigo sff
}

void exibirMenu(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias) {
    char opc;

    cout << "===========================================================================================" << endl;
    cout << "Pressione [S] + [ENTER] para avancar uma jornada ou [O] + [ENTER] para aceder ao menu de gestao do plantel." << endl << endl << ">>> ";
    cin >> opc;

    switch (opc) {
        case 'S':
        case 's':
            passarJornada();
            break;

        case 'O':
        case 'o':
            cout << endl << "Menu a ser feito!" << endl;
            system("pause");
            system("cls");
            mostrarPlantel(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias);
            exibirMenu(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias);
            break;

        default :
            cout << endl << "Operacao invalida!" << endl;
            system("pause");
            system("cls");
            mostrarPlantel(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias);
            exibirMenu(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias);
            break;
    }
}

/**
* Função que recebe todas as listas e os seus tamanhos e mostra de forma organizada o plantel.
* @param plantel - o plantel.
* @param numJogadores - numero de jogadores do plantel.
* @param lesionados - a lista de lesionados.
* @param numLesionados - numero de jogadores lesionados.
* @param castigados - a lista de castigados.
* @param numCastigados - numero de jogadores castigados.
* @param transferencias - a lista de transferencias.
* @param numTransferencias - numero de jogadores nas transferencias.
*/
void mostrarPlantel(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias) {
    cout << "************************************" << endl;
    cout << "* EDA FC - " << numJornada << "a Jornada - " << "(num pontos)" << " pontos. *" << endl;
    cout << "************************************" << endl;
    cout << "\n***************************** Plantel Disponivel: *****************************" << endl;

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
             << " | " << setw(9)  << plantel[i].qualidade
             << " | " << plantel[i].dias_treino << endl;
    }

    cout << "-----------------------------------------------------------------------------------------------" << endl;

    cout << "\nLesionados:" << endl;

    cout << left << setw(26) << "Nome"
         << " | " << setw(4)  << "Num"
         << " | " << setw(7)  << "Posicao"
         << " | " << setw(6)  << "Idade"
         << " | " << setw(12) << "ProbLesao"
         << " | " << setw(13) << "ProbCastigo"
         << " | " << setw(8)  << "Qualidade"
         << " | " << "Dias-Restantes" << endl;

    cout << "-----------------------------------------------------------------------------------------------" << endl;

    if (numLesionados == 0) {
        cout << "Nao existem jogadores lesionados." << endl;
    }
    else {
        string ultimaPosicaoLesao = "";

        for (int i = 0; i < numLesionados; i++) {
            if (i > 0 && lesionados[i].pos != ultimaPosicaoLesao) {
                cout << endl;
            }
            ultimaPosicaoLesao = lesionados[i].pos;

            cout << left << setw(26) << lesionados[i].nome
                 << " | " << setw(4)  << lesionados[i].num
                 << " | " << setw(7)  << lesionados[i].pos
                 << " | " << setw(6)  << lesionados[i].idade
                 << " | " << setw(3)  << lesionados[i].prob_lesao << "%" << setw(8) << ""
                 << " | " << setw(3)  << lesionados[i].prob_castigo << "%" << setw(9) << ""
                 << " | " << setw(9)  << lesionados[i].qualidade << endl;
        }
    }
    cout << "-----------------------------------------------------------------------------------------------" << endl;

    cout << "\nCastigados:" << endl;

    cout << left << setw(26) << "Nome"
         << " | " << setw(4)  << "Num"
         << " | " << setw(7)  << "Posicao"
         << " | " << setw(6)  << "Idade"
         << " | " << setw(12) << "ProbLesao"
         << " | " << setw(13) << "ProbCastigo"
         << " | " << setw(8)  << "Qualidade"
         << " | " << "Dias-Restantes" << endl;

    cout << "-----------------------------------------------------------------------------------------------" << endl;

    if (numCastigados == 0) {
        cout << "Nao existem jogadores castigados." << endl;
    }
    else {
        string ultimaPosicaoCastigo = "";

        for (int i = 0; i < numLesionados; i++) {
            if (i > 0 && castigados[i].pos != ultimaPosicaoCastigo) {
                cout << endl;
            }
            ultimaPosicaoCastigo = castigados[i].pos;

            cout << left << setw(26) << castigados[i].nome
                 << " | " << setw(4)  << castigados[i].num
                 << " | " << setw(7)  << castigados[i].pos
                 << " | " << setw(6)  << castigados[i].idade
                 << " | " << setw(3)  << castigados[i].prob_lesao << "%" << setw(8) << ""
                 << " | " << setw(3)  << castigados[i].prob_castigo << "%" << setw(9) << ""
                 << " | " << setw(9)  << castigados[i].qualidade << endl;
        }
    }
    cout << "-----------------------------------------------------------------------------------------------" << endl;
}