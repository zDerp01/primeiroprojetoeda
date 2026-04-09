#include <fstream>
#include <iostream>
#include <random>
#include "plantel.h"

#include <iomanip>

using namespace std;

int numJornada=1, numPontos=0;
int taticaAtual[4] = {1, 4, 4, 2};

/**
* Função auxiliar que atribui um valor numerico a cada posicao para facilitar a ordenacao.
* @param pos - string que recebe uma posicao e retorna um numero que a identifica.
*/
int valorPosicao(string pos) {
    if (pos == "GR") return 1;
    if (pos == "DEF") return 2;
    if (pos == "MED") return 3;
    if (pos == "AVA") return 4;
    return 5;
}

/**
* Função que reordena o plantel pela sua posicao.
* @param plantel - plantel.
* @param numJogadores - numero de jogadores.
*/
void ordenarPorPosicao(jogador* plantel, int numJogadores) {
    for (int i = 0; i < numJogadores - 1; i++) {
        for (int j = 0; j < numJogadores - i - 1; j++) {
            if (valorPosicao(plantel[j].pos) > valorPosicao(plantel[j + 1].pos)) {
                jogador temp = plantel[j];
                plantel[j] = plantel[j + 1];
                plantel[j + 1] = temp;
            }
        }
    }
}

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

    ordenarPorPosicao(lista, numJogadores);
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

/**
* Função que avança as jornadas e apresenta o resultado dos jogos.
* Esta função calcula tudo o que é necessário para a realização dos 2 jogos (resultados / adversário / titulares e suplentes)
* Afeta também o plantel através de lesões, substituições e castigos.
* @param plantel - o plantel.
* @param numJogadores - numero de jogadores do plantel.
* @param lesionados - a lista de lesionados.
* @param numLesionados - numero de jogadores lesionados.
* @param castigados - a lista de castigados.
* @param numCastigados - numero de jogadores castigados.
* @param transferencias - a lista de transferencias.
* @param numTransferencias - numero de jogadores nas transferencias.
* @param adversarios - lista de adversarios.
* @param numAdversarios - numero de adversarios.
*/
void passarJornada(jogador* &plantel, int &numJogadores, jogador* &lesionados, int &numLesionados, jogador* &castigados, int &numCastigados, jogador* &transferencias, int &numTransferencias, string* adversarios, int numAdversarios) {
    system("cls");

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
        int limiteTitulares[4] = {taticaAtual[0], taticaAtual[1], taticaAtual[2], taticaAtual[3]};
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
        cout << "* EDA FC - JOGO " << jogoNum << " - " << numPontos << " pontos. *" << endl;
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
            system("pause");
            system("cls");
        }
        else {
            // ----- treino -----
            for (int i = 0; i < numJogadores; i++) {
                if (plantel[i].dias_treino > 0) {
                    plantel[i].dias_treino--;
                    if (plantel[i].qualidade + 5 <= 100)
                        plantel[i].qualidade += 5;
                    else
                        plantel[i].qualidade = 100;
                }
            }
        }
    }

    // ----- dps de 2 jogos -----
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

/**
* Função que gere as transferências de jogadores, verificando os limites maximos e mínimos do plantel.
* Caso os limites sejam atingidos, obriga à troca de um jogador do plantel por um da lista de transferências.
* @param plantel - o plantel atual.
* @param numJogadores - numero de jogadores do plantel.
* @param transferencias - a lista de transferencias.
* @param numTransferencias - numero de jogadores nas transferencias.
* @param lesionados - a lista de lesionados.
* @param numLesionados - numero de jogadores lesionados.
* @param castigados - a lista de castigados.
* @param numCastigados - numero de jogadores castigados.
* @param adversarios - lista de adversarios.
* @param numAdversarios - numero de jogadores adversario.
*/
void transferir(jogador* &plantel, int &numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* &transferencias, int &numTransferencias, string* adversarios, int numAdversarios) {
    if (numTransferencias == 0) {
        cout << "\nNao ha jogadores na lista de transferencias" << endl;
        system("pause");
        exibirGestao(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
    }
    else {
        system("cls");
        cout << "********************* MERCADO DE TRANSFERENCIAS *********************" << endl;
        for (int i = 0; i < numTransferencias; i++) {
            cout << i + 1 << " - " << transferencias[i].nome
                 << " | Pos: " << transferencias[i].pos
                 << " | Qualidade: " << transferencias[i].qualidade
                 << " | Idade: " << transferencias[i].idade << endl;
        }
        cout << "0 - Cancelar" << endl;
        cout << "*********************************************************************" << endl;

        int escolhaTransf;
        cout << "Escolha o jogador a contratar (numero da lista): ";
        cin >> escolhaTransf;

        if (escolhaTransf <= 0 || escolhaTransf > numTransferencias) exibirGestao(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);

        jogador jogadorDesejado = transferencias[escolhaTransf - 1];

        // contagem por posicao dos jogadores atuais ---
        int countGR = 0, countDEF = 0, countMED = 0, countAVA = 0;
        for (int i = 0; i < numJogadores; i++) {
            if (plantel[i].pos == "GR") countGR++;
            else if (plantel[i].pos == "DEF") countDEF++;
            else if (plantel[i].pos == "MED") countMED++;
            else if (plantel[i].pos == "AVA") countAVA++;
        }

        // confirmar os limites ----
        bool limiteGeral = numJogadores >= 30;
        bool limitePosicao = false;
        if (jogadorDesejado.pos == "GR" && countGR >= 3) limitePosicao = true;
        if (jogadorDesejado.pos == "DEF" && countDEF >= 10) limitePosicao = true;
        if (jogadorDesejado.pos == "MED" && countMED >= 10) limitePosicao = true;
        if (jogadorDesejado.pos == "AVA" && countAVA >= 7) limitePosicao = true;

        if (limiteGeral || limitePosicao) {
            cout << "\n[AVISO] Limite do plantel ou da posicao atingido!" << endl;
            cout << "Para contratar este jogador, tera de fazer uma troca." << endl;
            system("pause");

            system("cls");
            cout << "--- Escolhe um jogador para dispensar ---" << endl;
            for (int i = 0; i < numJogadores; i++) {
                cout << i + 1 << " - " << plantel[i].nome << " (" << plantel[i].pos << ")" << endl;
            }

            int opc;
            cout << "Opcao: ";
            cin >> opc;

            if (opc <= 0 || opc > numJogadores) {
                cout << "Transferencia cancelada." << endl;
                system("pause");
                exibirGestao(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            }

            jogador jogadorSaindo = plantel[opc - 1];

            // limites minimos ---
            if (jogadorSaindo.pos != jogadorDesejado.pos) {
                if (jogadorSaindo.pos == "GR" && countGR <= 2) { cout << "Erro: Minimo de GR e 2. Troca cancelada!" << endl; system("pause"); exibirGestao(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);; }
                if (jogadorSaindo.pos == "DEF" && countDEF <= 7) { cout << "Erro: Minimo de DEF e 7. Troca cancelada!" << endl; system("pause"); exibirGestao(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);; }
                if (jogadorSaindo.pos == "MED" && countMED <= 7) { cout << "Erro: Minimo de MED e 7. Troca cancelada!" << endl; system("pause"); exibirGestao(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);; }
                if (jogadorSaindo.pos == "AVA" && countAVA <= 4) { cout << "Erro: Minimo de AVA e 4. Troca cancelada!" << endl; system("pause"); exibirGestao(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);; }
            }

            removerJogador(transferencias, numTransferencias, jogadorDesejado);
            removerJogador(plantel, numJogadores, jogadorSaindo);

            adicionarJogador(plantel, numJogadores, jogadorDesejado);
            adicionarJogador(transferencias, numTransferencias, jogadorSaindo);

            cout << "\nTroca realizada com sucesso: Sai " << jogadorSaindo.nome << " e entra " << jogadorDesejado.nome << "!" << endl;
        } else {
            removerJogador(transferencias, numTransferencias, jogadorDesejado);
            adicionarJogador(plantel, numJogadores, jogadorDesejado);
            cout << "\nTransferencia realizada com sucesso! " << jogadorDesejado.nome << " e o novo reforco do EDA FC." << endl;
        }

        system("pause");

        mostrarPlantel(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, false);
        exibirMenu(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios,false);
    }
}

/**
* Função que permite alterar a tatica da equipa, validando os maximos e minimos.
* @param plantel - o plantel atual.
* @param numJogadores - numero de jogadores do plantel.
* @param lesionados - a lista de lesionados.
* @param numLesionados - numero de jogadores lesionados.
* @param castigados - a lista de castigados.
* @param numCastigados - numero de jogadores castigados.
* @param transferencias - a lista de transferencias.
* @param numTransferencias - numero de jogadores nas transferencias.
* @param adversarios - lista de adversarios.
* @param numAdversarios - numero de adversarios.
*/
void alterarTatica(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios) {
    system("cls");
    cout << "*********************** ALTERACAO TATICA ***********************" << endl;
    cout << "Tatica atual: " << taticaAtual[0] << "-" << taticaAtual[1] << "-" << taticaAtual[2] << "-" << taticaAtual[3] << endl;
    cout << "Regras: Total = 11 | Minimos: 1 GR, 3 DEF, 2 MED, 1 AVA" << endl;
    cout << "****************************************************************" << endl;

    int def, med, ava;
    cout << "Numero de Defesas (Min 3): "; cin >> def;
    cout << "Numero de Medios (Min 2): "; cin >> med;
    cout << "Numero de Avancados (Min 1): "; cin >> ava;

    if ((1 + def + med + ava == 11) && def >= 3 && med >= 2 && ava >= 1) {
        taticaAtual[1] = def;
        taticaAtual[2] = med;
        taticaAtual[3] = ava;
        cout << "\nTatica alterada com sucesso para 1-" << def << "-" << med << "-" << ava << "!" << endl;
    }
    else {
        cout << "\nTatica Invalida! Nao cumpre o total de 11 jogadores ou os minimos exigidos." << endl;
    }

    system("pause");

    mostrarPlantel(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, false);
    exibirMenu(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios, false);
}

/**
* Função que permite aplicar ou reduzir lesões e castigos aos jogadores, movendo-os entre listas.
* @param plantel - o plantel atual.
* @param numJogadores - numero de jogadores do plantel.
* @param lesionados - a lista de lesionados.
* @param numLesionados - numero de jogadores lesionados.
* @param castigados - a lista de castigados.
* @param numCastigados - numero de jogadores castigados.
* @param transferencias - a lista de transferencias.
* @param numTransferencias - numero de jogadores nas transferencias.
* @param adversarios - lista de adversarios.
* @param numAdversarios - numero de adversarios.
*/
void gerirFisicaDisciplina(jogador* &plantel, int &numJogadores, jogador* &lesionados, int &numLesionados, jogador* &castigados, int &numCastigados, jogador* &transferencias, int &numTransferencias, string* adversarios, int numAdversarios) {
    char opc;
    system("cls");
    cout << "****************** GESTAO FISICA E DISCIPLINAR *****************" << endl;
    cout << "1 - Aplicar Lesao a um jogador do Plantel" << endl;
    cout << "2 - Reduzir/Remover Lesao de um jogador" << endl;
    cout << "3 - Aplicar Castigo a um jogador do Plantel" << endl;
    cout << "4 - Reduzir/Remover Castigo de um jogador" << endl;
    cout << "0 - Voltar" << endl;
    cout << "****************************************************************" << endl << ">>> ";
    cin >> opc;

    if (opc == '0') {
        exibirGestao(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
    }
    else if (opc == '1' || opc == '3') {
        if (numJogadores == 0) {
            cout << "O plantel esta vazio!" << endl;
            system("pause");
            gerirFisicaDisciplina(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
        }
        else {
            system("cls");
            cout << "--- Jogadores Disponiveis ---" << endl;
            for (int i = 0; i < numJogadores; i++) cout << i + 1 << " - " << plantel[i].nome << " (" << plantel[i].pos << ")" << endl;

            int escolha, jornadas;
            cout << "Escolha o jogador (numero): "; cin >> escolha;

            if (escolha > 0 && escolha <= numJogadores) {
                cout << "Quantas jornadas de indisponibilidade (Max 10)? "; cin >> jornadas;
                if (jornadas > 10) jornadas = 10;

                jogador afetado = plantel[escolha-1];
                afetado.dias_treino = jornadas;
                removerJogador(plantel, numJogadores, afetado);

                if (opc == '1') {
                    adicionarJogador(lesionados, numLesionados, afetado);
                    cout << "\n" << afetado.nome << " lesionou-se por " << jornadas << " jornadas!" << endl;
                } else {
                    adicionarJogador(castigados, numCastigados, afetado);
                    cout << "\n" << afetado.nome << " foi suspenso por " << jornadas << " jornadas!" << endl;
                }
                system("pause");
                gerirFisicaDisciplina(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            } else {
                cout << "\nOpcao invalida!" << endl;
                system("pause");
                gerirFisicaDisciplina(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            }
        }
    }
    else if (opc == '2' || opc == '4') {
        bool isLesao = (opc == '2');
        int qtdLista = isLesao ? numLesionados : numCastigados;
        jogador* listaAlvo = isLesao ? lesionados : castigados;

        if (qtdLista == 0) {
            cout << "\nNao ha jogadores nesta lista!" << endl;
            system("pause");
            gerirFisicaDisciplina(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
        }
        else {
            system("cls");
            cout << "--- Jogadores Indisponiveis ---" << endl;
            for (int i = 0; i < qtdLista; i++) cout << i + 1 << " - " << listaAlvo[i].nome << " (" << listaAlvo[i].pos << ") - Faltam " << listaAlvo[i].dias_treino << " jornadas" << endl;

            int escolha, reducao;
            cout << "Escolha o jogador (numero): "; cin >> escolha;

            if (escolha > 0 && escolha <= qtdLista) {
                cout << "Quantas jornadas pretende reduzir? "; cin >> reducao;

                listaAlvo[escolha - 1].dias_treino -= reducao;

                if (listaAlvo[escolha - 1].dias_treino <= 0) {
                    jogador recuperado = listaAlvo[escolha - 1];
                    recuperado.dias_treino = 0;

                    if (isLesao) removerJogador(lesionados, numLesionados, recuperado);
                    else removerJogador(castigados, numCastigados, recuperado);

                    adicionarJogador(plantel, numJogadores, recuperado);
                    cout << "\n" << recuperado.nome << " esta novamente apto e regressou ao plantel!" << endl;
                } else {
                    cout << "\nPena reduzida. Faltam " << listaAlvo[escolha - 1].dias_treino << " jornadas para o " << listaAlvo[escolha - 1].nome << " voltar." << endl;
                }
                system("pause");
                gerirFisicaDisciplina(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            } else {
                cout << "\nOpcao invalida!" << endl;
                system("pause");
                gerirFisicaDisciplina(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            }
        }
    }
    else {
        cout << "\nOpcao invalida!" << endl;
        system("pause");
        gerirFisicaDisciplina(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
    }
}

/**
* Função auxiliar que permite escrever no ficheiro uma lista.
* @param f - o ficheiro.
* @param lista - a lista em questao.
* @param qtd - a capacidade da lista.
*/
void escreverLista(ofstream &f, jogador* lista, int qtd) {
    f << qtd << endl;
    for (int i = 0; i < qtd; i++) {
        jogador &j = lista[i];

        f << j.nome << endl;
        f << j.pos << " " << j.num << " " << j.idade << " "
          << j.prob_lesao << " " << j.prob_castigo << " "
          << j.qualidade << " " << j.dias_treino << endl;
    }
}

/**
* Função que permite gravar o estado atual do EDA FC num ficheiro de texto.
* Guarda a jornada, pontuação, tática e todos os jogadores (plantel, lesionados, castigados e transferências).
* @param plantel - o plantel atual.
* @param numJogadores - numero de jogadores do plantel.
* @param lesionados - a lista de lesionados.
* @param numLesionados - numero de jogadores lesionados.
* @param castigados - a lista de castigados.
* @param numCastigados - numero de jogadores castigados.
* @param transferencias - a lista de transferencias.
* @param numTransferencias - numero de jogadores nas transferencias.
* @param adversarios - lista de adversarios.
* @param numAdversarios - numero de adversarios.
*/
void gravarEquipa(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios) {
    ofstream f("savegame.txt");

    if (!f.is_open()) {
        cout << "\n[ERRO] Nao foi possivel criar o ficheiro" << endl;
    }
    else {
        f << numJornada << " " << numPontos << endl;
        f << taticaAtual[0] << " " << taticaAtual[1] << " " << taticaAtual[2] << " " << taticaAtual[3] << endl;

        // Função para gravar cada lista (Plantel, Lesionados, etc.)

        escreverLista(f, plantel, numJogadores);
        escreverLista(f, lesionados, numLesionados);
        escreverLista(f, castigados, numCastigados);
        escreverLista(f, transferencias, numTransferencias);

        f.close();
        cout << "\n[SUCESSO] Jogo guardado!" << endl;
    }
    system("pause");
    exibirGestao(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
}

/**
* Função auxiliar que permite ler no ficheiro uma lista.
* @param f - o ficheiro.
* @param lista - a lista em questao.
* @param qtd - a capacidade da lista.
*/
void lerLista(ifstream &f, jogador* &lista, int &qtd) {
    f >> qtd;
    if (qtd > 0) {
        lista = new jogador[qtd];
        for (int i = 0; i < qtd; i++) {
            f.ignore();

            jogador &j = lista[i];

            getline(f, j.nome);

            f >> j.pos >> j.num >> j.idade
              >> j.prob_lesao >> j.prob_castigo
              >> j.qualidade >> j.dias_treino;
        }
    }
    else {
        lista = nullptr;
    }
}

/**
* Função que permite carregar um estado do campeonato e do clube a partir de um ficheiro.
* @param plantel - referencia para o plantel atual (será reinicializado).
* @param numJogadores - referencia para o numero de jogadores (será atualizado).
* @param lesionados - referencia para a lista de lesionados (será reinicializado).
* @param numLesionados - referencia para o numero de lesionados (será atualizado).
* @param castigados - referencia para a lista de castigados (será reinicializado).
* @param numCastigados - referencia para o numero de castigados (será atualizado).
* @param transferencias - referencia para a lista de transferencias (será reinicializado).
* @param numTransferencias - referencia para o numero de transferencias (será atualizado).
* @param adversarios - lista de adversarios.
* @param numAdversarios - numero de adversarios.
* @param nomeFicheiro - string com o caminho/nome do ficheiro a carregar.
*/
void carregarEquipa(jogador* &plantel, int &numJogadores, jogador* &lesionados, int &numLesionados, jogador* &castigados, int &numCastigados, jogador* &transferencias, int &numTransferencias, string* adversarios, int numAdversarios, string nomeFicheiro) {
    ifstream f(nomeFicheiro);

    if (!f.is_open()) {
        cout << "\n[ERRO] O ficheiro nao existe!" << endl;
        system("pause");
    } else {
        delete[] plantel;
        delete[] lesionados;
        delete[] castigados;
        delete[] transferencias;

        f >> numJornada >> numPontos;
        f >> taticaAtual[0] >> taticaAtual[1] >> taticaAtual[2] >> taticaAtual[3];

        lerLista(f, plantel, numJogadores);
        lerLista(f, lesionados, numLesionados);
        lerLista(f, castigados, numCastigados);
        lerLista(f, transferencias, numTransferencias);

        f.close();
        cout << "\n[SUCESSO] Jogo carregado!" << endl;
        system("pause");
    }
    mostrarPlantel(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, false);
    exibirMenu(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios, false);
}

/**
* Função que permite mudar a posicao de um jogador confirmando todos os limites das mesmas.
* @param plantel - referencia para o plantel atual (será reinicializado).
* @param numJogadores - referencia para o numero de jogadores (será atualizado).
* @param lesionados - referencia para a lista de lesionados (será reinicializado).
* @param numLesionados - referencia para o numero de lesionados (será atualizado).
* @param castigados - referencia para a lista de castigados (será reinicializado).
* @param numCastigados - referencia para o numero de castigados (será atualizado).
* @param transferencias - referencia para a lista de transferencias (será reinicializado).
* @param numTransferencias - referencia para o numero de transferencias (será atualizado).
* @param adversarios - lista de adversarios.
* @param numAdversarios - numero de adversarios.
*/
void mudarPos(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios) {
    system("cls");
    cout << "Jogadores disponíveis:" << endl;
    cout << "----------------------" << endl;
    for (int i = 0; i < numJogadores; i++) {
        cout << i + 1 << ". " << plantel[i].nome << " (" << plantel[i].pos << ")" << endl;
    }

    int escolha;
    cout << "\nIntroduza o numero do jogador: ";
    cin >> escolha;

    if (escolha < 1 || escolha > numJogadores) {
        cout << "Numero invalido!" << endl;
        system("pause");
        treinarJogador(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
    }

    string novaPosicao;
    cout << "Introduza a nova posicao (GR, DEF, MED, AVA): ";
    cin >> novaPosicao;

    if (novaPosicao != "GR" && novaPosicao != "DEF" && novaPosicao != "MED" && novaPosicao != "AVA") {
        cout << "Posicao invalida!" << endl;
        system("pause");
        treinarJogador(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
    }

    int contPos = 0;
    for (int i = 0; i < numJogadores; i++) {
        if (plantel[i].pos == novaPosicao) contPos++;
    }

    int maxPos = 0;
    if (novaPosicao == "GR")  maxPos = 3;
    else if (novaPosicao == "DEF") maxPos = 10;
    else if (novaPosicao == "MED") maxPos = 10;
    else if (novaPosicao == "AVA") maxPos = 7;

    if (contPos >= maxPos) {
        cout << "Capacidade insuficiente para essa posicao!" << endl;
        system("pause");
        treinarJogador(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
    }

    plantel[escolha - 1].pos = novaPosicao;
    ordenarPorPosicao(plantel, numJogadores);
    cout << "Posicao alterada com sucesso!" << endl;
    system("pause");
    treinarJogador(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
}

/**
* Função que coloca um jogador em treino, melhorando a sua qualidade ao longo das jornadas.
* @param plantel - o plantel.
* @param numJogadores - numero de jogadores do plantel.
* @param lesionados - a lista de lesionados.
* @param numLesionados - numero de jogadores lesionados.
* @param castigados - a lista de castigados.
* @param numCastigados - numero de jogadores castigados.
* @param transferencias - a lista de transferencias.
* @param numTransferencias - numero de jogadores nas transferencias.
* @param adversarios - lista de adversarios.
* @param numAdversarios - numero de adversarios.
*/
void melhorarQualidade(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios) {
    system("cls");
    cout << "Jogadores disponíveis:" << endl;
    cout << "----------------------" << endl;
    for (int i = 0; i < numJogadores; i++) {
        cout << i + 1 << ". " << plantel[i].nome << " (" << plantel[i].pos << ")" << endl;
    }

    int escolha;
    cout << "\nIntroduza o numero do jogador: ";
    cin >> escolha;

    if (escolha < 1 || escolha > numJogadores) {
        cout << "Numero invalido!" << endl;
        system("pause");
        treinarJogador(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
    }

    bool estaLesionado = false;
    for (int i = 0; i < numLesionados; i++) {
        if (lesionados[i].nome == plantel[escolha - 1].nome && lesionados[i].num == plantel[escolha - 1].num) {
            cout << "Jogador lesionado nao pode treinar" << endl;
            system("pause");
            treinarJogador(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
        }
    }

    int semanas;
    cout << "Introduza o numero de semanas de treino (1-5): ";
    cin >> semanas;

    if (semanas < 1 || semanas > 5) {
        cout << "Numero de semanas invalido" << endl;
        system("pause");
        treinarJogador(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
    }

    plantel[escolha - 1].dias_treino = semanas;
    cout << plantel[escolha - 1].nome << " vai treinar durante " << semanas << " jornada(s)!" << endl;
    system("pause");
    treinarJogador(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
}

/**
* Função que mostra o menu de treino individual.
* @param plantel - o plantel.
* @param numJogadores - numero de jogadores do plantel.
* @param lesionados - a lista de lesionados.
* @param numLesionados - numero de jogadores lesionados.
* @param castigados - a lista de castigados.
* @param numCastigados - numero de jogadores castigados.
* @param transferencias - a lista de transferencias.
* @param numTransferencias - numero de jogadores nas transferencias.
*/
void treinarJogador(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios){
    char opcTreino;
    system("cls");
    cout << "\n***************************** Menu de Treino: *****************************" << endl;
    cout << "1 - Mudar Posicao" << endl;
    cout << "2 - Melhorar Qualidade" << endl;
    cout << "0 - Voltar" << endl;
    cout << "\n***************************************************************************" << endl << ">>> ";
    cin >> opcTreino;
    switch (opcTreino) {
        case '1':
            mudarPos(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            break;

        case '2':
            melhorarQualidade(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            break;

        case '0':
            exibirGestao(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            break;

        default :
            cout << endl << "Operacao invalida!" << endl;
            system("pause");
            treinarJogador(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            break;
    }
}

/**
* Função que mostra o menu de gestao de equipa.
* @param plantel - o plantel.
* @param numJogadores - numero de jogadores do plantel.
* @param lesionados - a lista de lesionados.
* @param numLesionados - numero de jogadores lesionados.
* @param castigados - a lista de castigados.
* @param numCastigados - numero de jogadores castigados.
* @param transferencias - a lista de transferencias.
* @param numTransferencias - numero de jogadores nas transferencias.
* @param adversarios - lista de adversarios.
* @param numAdversarios - numero de adversarios.
*/
void exibirGestao(jogador* plantel, int numJogadores, jogador* lesionados, int numLesionados, jogador* castigados, int numCastigados, jogador* transferencias, int numTransferencias, string* adversarios, int numAdversarios){
    char opcTreino;
    system("cls");
    cout << "\n***************************** Menu de Gestao: *****************************" << endl;
    cout << "1 - Treino Especifico" << endl;
    cout << "2 - Transferencias" << endl;
    cout << "3 - Alteracao Tatica" << endl;
    cout << "4 - Gestao Fisica e Disciplinar" << endl;
    cout << "5 - Gravar Equipa" << endl;
    cout << "6 - Carregar Equipa" << endl;
    cout << "0 - Voltar" << endl;
    cout << "\n***************************************************************************" << endl << ">>> ";
    cin >> opcTreino;
    switch (opcTreino) {
        case '1':
            treinarJogador(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            break;

        case '2':
            transferir(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            break;

        case '3':
            alterarTatica(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            break;

        case '4':
            gerirFisicaDisciplina(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            break;

        case '5':
            gravarEquipa(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            break;

        case '6':
            carregarEquipa(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios, "savegame.txt");
            break;

        case '0':
            mostrarPlantel(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, false);
            exibirMenu(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios,false);
            break;

        default :
            cout << endl << "Operacao invalida!" << endl;
            system("pause");
            exibirGestao(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
            break;
    }
}

/**
* Função que exibe as opcoes disponiveis e lê o que o utilizador meter.
* @param plantel - o plantel.
* @param numJogadores - numero de jogadores do plantel.
* @param lesionados - a lista de lesionados.
* @param numLesionados - numero de jogadores lesionados.
* @param castigados - a lista de castigados.
* @param numCastigados - numero de jogadores castigados.
* @param transferencias - a lista de transferencias.
* @param numTransferencias - numero de jogadores nas transferencias.
* @param adversarios - a lista de adversarios.
* @param numAdversarios - numero de equipas adversarias.
* @param aposJornada - booleano que influencia na exibicao do metodo mostrarPlantel.
*/
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
            exibirGestao(plantel, numJogadores, lesionados, numLesionados, castigados, numCastigados, transferencias, numTransferencias, adversarios, numAdversarios);
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
* @param aposJornada - booleano que influencia na exibicao.
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