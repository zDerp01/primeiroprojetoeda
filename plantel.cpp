#include <fstream>
#include <iostream>
#include <random>
#include "plantel.h"

#include <iomanip>

using namespace std;

int numJornada=1, numPontos=0;

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

void passarJornada(jogador* &plantel, int &numJogadores, jogador* &lesionados, int &numLesionados, jogador* &castigados, int &numCastigados, jogador* &transferencias, int &numTransferencias, string* adversarios, int numAdversarios) {
    system("cls");

    // Sorteia o adversário UMA VEZ para os dois jogos da jornada
    int indiceAdversario = rand() % numAdversarios;
    string nomeAdversario = adversarios[indiceAdversario];

    // CICLO PARA FAZER DOIS JOGOS CONTRA A MESMA EQUIPA
    for (int jogoNum = 1; jogoNum <= 2; jogoNum++) {

        int totalGolos = rand() % 9;
        int resultadoEquipaA = (totalGolos == 0) ? 0 : rand() % (totalGolos + 1); // Eda
        int resultadoEquipaB = totalGolos - resultadoEquipaA;

        cout << "=====================================================" << endl;
        cout << "            JORNADA " << numJornada << " - JOGO " << jogoNum << "/2" << endl;
        cout << "            EDA FC vs " << nomeAdversario << endl;
        cout << "=====================================================" << endl;

        system("pause");
        system("cls");

        jogador* titulares = new jogador[11];
        jogador* suplentes = new jogador[6];
        bool escolhido[100] = {false}; // array pa marcar quem já foi selecionado (assumindo max 100 jogadores)

        string posicoes[4] = {"GR", "DEF", "MED", "AVA"};
        int limiteTitulares[4] = {1, 4, 4, 2};
        int locTitulares = 0;

        // pa escolher os titulares
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < limiteTitulares[i]; j++) {
                int maxQualidade = -1;
                int ind = -1;
                for (int k = 0; k < numJogadores; k++) {
                    if (!escolhido[k] && plantel[k].pos == posicoes[i] && plantel[k].qualidade > maxQualidade) {
                        maxQualidade = plantel[k].qualidade;
                        ind = k;
                    }
                }
                if (ind != -1) {
                    titulares[locTitulares++] = plantel[ind];
                    escolhido[ind] = true;
                }
            }
        }

        // pa escolher suplentes
        int limiteSuplentes[4] = {1, 2, 2, 1};
        int locSuplentes = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < limiteSuplentes[i]; j++) {
                int maxQualidade = -1;
                int ind = -1;
                for (int k = 0; k < numJogadores; k++) {
                    if (!escolhido[k] && plantel[k].pos == posicoes[i] && plantel[k].qualidade > maxQualidade) {
                        maxQualidade = plantel[k].qualidade;
                        ind = k;
                    }
                }
                if (ind != -1) {
                    suplentes[locSuplentes++] = plantel[ind];
                    escolhido[ind] = true;
                }
            }
        }

        // ----- lesoes e substituicoes -----
        int substituicoesFeitas = 0;
        string substituicoesTexto[3];

        for (int i = 0; i < locTitulares; i++) {
            if (rand() % 100 < titulares[i].prob_lesao) {
                titulares[i].dias_treino = rand() % 10 + 1;
                if (substituicoesFeitas < 3) {
                    int idxSup = -1;
                    for (int s = 0; s < locSuplentes; s++) {
                        if (suplentes[s].pos == titulares[i].pos) { idxSup = s; break; }
                    }
                    if (idxSup == -1 && locSuplentes > 0) idxSup = 0;

                    if (idxSup != -1) {
                        substituicoesTexto[substituicoesFeitas++] = titulares[i].nome + " -> " + suplentes[idxSup].nome;
                        jogador suplenteSelecionado = suplentes[idxSup];
                        for (int s = idxSup; s < locSuplentes - 1; s++) suplentes[s] = suplentes[s + 1];
                        locSuplentes--;
                        adicionarJogador(lesionados, numLesionados, titulares[i]);
                        removerJogador(plantel, numJogadores, titulares[i]);
                        titulares[i] = suplenteSelecionado;
                    } else {
                        adicionarJogador(lesionados, numLesionados, titulares[i]);
                        removerJogador(plantel, numJogadores, titulares[i]);
                    }
                } else {
                    adicionarJogador(lesionados, numLesionados, titulares[i]);
                    removerJogador(plantel, numJogadores, titulares[i]);
                }
            }
        }

        // ----- castigos -----
        for (int i = 0; i < locTitulares; i++) {
            if (rand() % 100 < titulares[i].prob_castigo) {
                titulares[i].dias_treino = rand() % 10 + 1;
                adicionarJogador(castigados, numCastigados, titulares[i]);
                removerJogador(plantel, numJogadores, titulares[i]);
            }
        }

        if (resultadoEquipaA == resultadoEquipaB) numPontos++;
        else if (resultadoEquipaA > resultadoEquipaB) numPontos+=3;

        cout << "************************************" << endl;
        cout << "* EDA FC - JOGO " << jogoNum << " - " << numPontos << " pontos acumulados. *" << endl;
        cout << "************************************" << endl;
        cout << "Resultado : EDA FC:" << resultadoEquipaA << " - " << nomeAdversario << ":" << resultadoEquipaB << endl;

        // --- TABELAS DETALHADAS ---
        cout << "\n11 Inicial" << endl;
        cout << left << setw(26) << "Nome" << " | " << setw(2)  << "Num" << " | " << setw(7)  << "Posicao" << " | " << setw(5)  << "Idade" << " | " << setw(9)  << "ProbLesao" << " | " << setw(11) << "ProbCastigo" << " | " << "Qualidade" << endl;
        cout << "-----------------------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < locTitulares; i++) {
            cout << left << setw(26) << titulares[i].nome << " | " << setw(2)  << titulares[i].num << " | " << setw(7)  << titulares[i].pos << " | " << setw(5)  << titulares[i].idade << " | " << setw(8)  << titulares[i].prob_lesao << "%" << " | " << setw(10) << titulares[i].prob_castigo << "%" << " | " << titulares[i].qualidade << endl;
        }

        cout << "\nCastigados:" << endl;
        cout << left << setw(26) << "Nome" << " | " << setw(2) << "Num" << " | " << setw(7) << "Posicao" << " | " << setw(5) << "Idade" << " | " << setw(9) << "ProbLesao" << " | " << setw(11) << "ProbCastigo" << " | " << setw(9) << "Qualidade" << " | JogosCastigo" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < numCastigados; i++) {
            cout << left << setw(26) << castigados[i].nome << " | " << setw(2) << castigados[i].num << " | " << setw(7) << castigados[i].pos << " | " << setw(5) << castigados[i].idade << " | " << setw(8) << castigados[i].prob_lesao << "%" << " | " << setw(10) << castigados[i].prob_castigo << "%" << " | " << setw(9) << castigados[i].qualidade << " | " << castigados[i].dias_treino << endl;
        }

        cout << "\nLesionados:" << endl;
        cout << left << setw(26) << "Nome" << " | " << setw(2) << "Num" << " | " << setw(7) << "Posicao" << " | " << setw(5) << "Idade" << " | " << setw(9) << "ProbLesao" << " | " << setw(11) << "ProbCastigo" << " | " << setw(9) << "Qualidade" << " | JogosLesao" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < numLesionados; i++) {
            cout << left << setw(26) << lesionados[i].nome << " | " << setw(2) << lesionados[i].num << " | " << setw(7) << lesionados[i].pos << " | " << setw(5) << lesionados[i].idade << " | " << setw(8) << lesionados[i].prob_lesao << "%" << " | " << setw(10) << lesionados[i].prob_castigo << "%" << " | " << setw(9) << lesionados[i].qualidade << " | " << lesionados[i].dias_treino << endl;
        }

        cout << "\nSubstituicoes:" << endl;
        if (substituicoesFeitas == 0) cout << "Sem substituicoes neste jogo." << endl;
        else {
            for (int i = 0; i < substituicoesFeitas; i++) cout << "  " << substituicoesTexto[i] << endl;
        }

        delete[] titulares;
        delete[] suplentes;

        if (jogoNum == 1) {
            cout << "\nFim do primeiro jogo." << endl;
            system("pause");
            system("cls");
        }
    }

    // ----- FINAL DA JORNADA (Processado após os 2 jogos) -----
    for (int i = numLesionados - 1; i >= 0; i--) {
        lesionados[i].dias_treino--;
        if (lesionados[i].dias_treino <= 0) {
            lesionados[i].dias_treino = 0;
            adicionarJogador(plantel, numJogadores, lesionados[i]);
            removerJogador(lesionados, numLesionados, lesionados[i]);
        }
    }

    for (int i = numCastigados - 1; i >= 0; i--) {
        castigados[i].dias_treino--;
        if (castigados[i].dias_treino <= 0) {
            castigados[i].dias_treino = 0;
            adicionarJogador(plantel, numJogadores, castigados[i]);
            removerJogador(castigados, numCastigados, castigados[i]);
        }
    }

    int totalNomesTransf = 0;
    string* nomesTransf = geraNomes("nomes.txt", totalNomesTransf);
    string posicoes4[4] = {"GR", "DEF", "MED", "AVA"};
    for (int k = 0; k < 2; k++) {
        jogador novo;
        novo.nome = nomesTransf[rand() % totalNomesTransf]; novo.pos = posicoes4[rand() % 4];
        novo.num = rand() % 99 + 1; novo.idade = rand() % 18 + 18;
        novo.prob_lesao = rand() % 16; novo.prob_castigo = rand() % 21;
        novo.qualidade = rand() % 101; novo.dias_treino = 0;
        adicionarJogador(transferencias, numTransferencias, novo);
    }
    delete[] nomesTransf;

    numJornada++;
    system("pause");
    system("cls");

    mostrarPlantel(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, false);
    exibirMenu(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios, false);
}

void treinarJogador(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios,bool aposJornada){
    char opcTreino;
    system("cls");
    cout << "1-Mudar a posição de um jogador:" << endl;
    cout << "2-Melhorar a qualidade de um jogador:" << endl;
    switch (opcTreino) {
        case '1':
            mostrarPlantel(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, aposJornada);
            break;

        case '2':
            break;

        default :
            cout <<"Comando inválido!";
            break;
    }
}

void exibirMenu(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios,bool aposJornada) {
    char opc;

    cout << "===========================================================================================" << endl;
    cout << "Pressione [S] + [ENTER] para avancar uma jornada ou [O] + [ENTER] para aceder ao menu de gestao do plantel." << endl << endl << ">>> ";
    cin >> opc;

    switch (opc) {
        case 'S':
        case 's':
            passarJornada(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            break;

        case 'O':
        case 'o':
            treinarJogador(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios,aposJornada);
            system("pause");
            system("cls");
            mostrarPlantel(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, aposJornada);
            exibirMenu(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios,aposJornada);
            break;

        default :
            cout << endl << "Operacao invalida!" << endl;
            system("pause");
            system("cls");
            mostrarPlantel(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, aposJornada);
            exibirMenu(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios,aposJornada);
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

void mostrarPlantel(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, bool aposJornada) {
    system("cls");
    if (!aposJornada) {
        cout << "************************************" << endl;
        cout << "* EDA FC - " << numJornada << "a Jornada - " << numPontos << " pontos. *" << endl;
        cout << "************************************" << endl;
    }

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
             << " | " << setw(11)  << plantel[i].prob_lesao << "%"
             << " | " << setw(12)  << plantel[i].prob_castigo << "%"
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
                 << " | " << setw(11)  << lesionados[i].prob_lesao << "%"
                 << " | " << setw(12)  << lesionados[i].prob_castigo << "%"
                 << " | " << setw(9)  << lesionados[i].qualidade
                 << " | " << lesionados[i].dias_treino << endl;

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

        for (int i = 0; i < numCastigados; i++) {
            if (i > 0 && castigados[i].pos != ultimaPosicaoCastigo) {
                cout << endl;
            }
            ultimaPosicaoCastigo = castigados[i].pos;

            cout << left << setw(26) << castigados[i].nome
                 << " | " << setw(4)  << castigados[i].num
                 << " | " << setw(7)  << castigados[i].pos
                 << " | " << setw(6)  << castigados[i].idade
                 << " | " << setw(11)  << castigados[i].prob_lesao << "%"
                 << " | " << setw(12)  << castigados[i].prob_castigo << "%"
                 << " | " << setw(9)  << castigados[i].qualidade
                 << " | " << castigados[i].dias_treino<< endl;
        }
    }
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "****************************************************************************" << endl;
    cout << "\nTransferencias:" << endl;

    cout << left << setw(26) << "Nome"
         << " | " << setw(4)  << "Num"
         << " | " << setw(7)  << "Posicao"
         << " | " << setw(6)  << "Idade"
         << " | " << setw(12) << "ProbLesao"
         << " | " << setw(13) << "ProbCastigo"
         << " | " << setw(8)  << "Qualidade" << endl;

    cout << "-----------------------------------------------------------------------------------------------" << endl;

    if (numTransferencias == 0) {
        cout << "Nao existem transferencias." << endl;
    }
    else {
        string ultimaPosicaoTransferencias = "";

        for (int i = 0; i < numTransferencias; i++) {
            if (i > 0 && transferencias[i].pos != ultimaPosicaoTransferencias) {
                cout << endl;
            }
            ultimaPosicaoTransferencias = transferencias[i].pos;

            cout << left << setw(26) << transferencias[i].nome
                 << " | " << setw(4)  << transferencias[i].num
                 << " | " << setw(7)  << transferencias[i].pos
                 << " | " << setw(6)  << transferencias[i].idade
                 << " | " << setw(11)  << transferencias[i].prob_lesao << "%"
                 << " | " << setw(12)  << transferencias[i].prob_castigo << "%"
                 << " | " << setw(9)  << transferencias[i].qualidade << endl;
        }
    }
    cout << "-----------------------------------------------------------------------------------------------" << endl << endl;
}