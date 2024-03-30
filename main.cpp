#include <iostream>
#include "Armazem.h"
#include <stdlib.h>
#include <string>


using namespace std;

int main() {
    srand(time(0));// Seed para gerar numeros aleatórios
    int numSecoes = rand() % 4+7;// Numero de seções entre 7 e 10
    int indice = 0;// Indice
    int ciclos = 0;// Ciclo
    int tamanho = 10;// Tamanho da lista de chegada
    Peca* peca = criaPecas(tamanho, numSecoes);// Cria as peças
    listaDeChegada* listaDeChegadaArray = criaListaChegada(peca, tamanho);// Cria a lista de chegada*/
    seccoes* secoes = criaSeccoes(numSecoes);// Cria as secções

    imprimeSecLis(ciclos, secoes, peca, listaDeChegadaArray, tamanho, indice);// Imprime as secções e a lista de chegada

    string resposta;// Resposta do utilizador
    do{
        cout << "Escolha uma opcao: \n";
        cout << "Dia (s)eguinte *********** (g)estao";
        cin >> resposta;
        if (resposta == "g") {// Se a resposta for g
            bool sair = false;// Variável para sair do ciclo
            char opcao;// Opção escolhida
            do {// Ciclo para escolher a opção
                cout << "\n*****Bem Vindo ao Gestor*****\n";
                cout << "1 - Venda Manual" << endl;
                cout << "2 - Promocao" << endl;
                cout << "3 - Alterar categoria" << endl;
                cout << "4 - Adicionar seccao" << endl;
                cout << "5 - Gravar Armazem" << endl;
                cout << "6 - Carregar Armazem" << endl;
                cout << "7 - Imprimir Armazem" << endl;
                cout << "0 - Sair" << endl;
                cin >> opcao;
                cout << endl;
                switch (opcao) {// Escolhe a opção
                    case '1':
                        cout << "Escolheu Venda Manual" << endl;

                        break;
                    case '2':
                        cout << "Escolheu Promocao" << endl;

                        break;
                    case '3':
                        cout << "Escolheu Alterar categoria" << endl;

                        break;
                    case '4':
                        cout << "Escolheu Gravar Armazem" << endl;

                        break;
                    case '6':
                        cout << "Escolheu Carregar Armazem" << endl;

                        break;
                    case '7':
                        cout << "Escolheu Imprimir Armazem" << endl;

                        break;
                    case '0':
                        cout << "Escolheu a opcao Sair. Adeus!" << endl;
                        sair = true;
                        break;
                    default:
                        cout << "Escolha uma opcao valida." << endl;
                }
            } while (!sair);// Enquanto não sair
        } else if (resposta == "s" || resposta == "S") {// Se a resposta for s
            if (tamanho + 5 > 50) {
                cout << "Não é possível adicionar mais peças, a lista de chegada está cheia." << endl;
                continue;
            }else{
                ciclos++;// Ciclo
                int conta = 0;
                int i= 0;
                while(!listaDeChegadaArray[i].marca.empty()){
                    conta++;
                    i++;
                }

                tamanho = conta;
                tamanho+=5;// Tamanho da lista de chegada
                Peca* novasPecas = criaPecas(5, numSecoes);  // Cria 5 novas peças
                listaDeChegada* novaListaChegada = criaListaChegada(novasPecas, 5);  // Cria uma nova lista de chegada para as novas peças

                // Adiciona as novas peças e a nova lista de chegada às existentes
                for (int i = 0; i < 5; i++) {
                    peca[tamanho  + i].marcas = novasPecas[i].marcas;
                    peca[tamanho  + i].categorias = novasPecas[i].categorias;
                    peca[tamanho  + i].numSerie = novasPecas[i].numSerie;
                    peca[tamanho  + i].preco = novasPecas[i].preco;
                    peca[tamanho  + i].probVenda = novasPecas[i].probVenda;
                    listaDeChegadaArray[tamanho  + i].marca = peca[tamanho + i].marcas;
                    listaDeChegadaArray[tamanho  + i].categoria = peca[tamanho + i].categorias;
                }

                // Libera a memória alocada para as novas peças e a nova lista de chegada
                delete[] novasPecas;
                delete[] novaListaChegada;
                cout << "Tamanho da lista de chegada: " << tamanho << endl;
                cout << "Escolheu Dia Seguinte " << ciclos << endl;
                imprimeSecLis(ciclos, secoes, peca, listaDeChegadaArray, tamanho, indice);// Imprime as secções e a lista de chegada

            }

        } else {// Se a resposta for diferente de s ou g
            cout << "Escolha a opcao sair." << endl;
        }
    }while (resposta != "0");// Enquanto a resposta for diferente de 0

    // Libera a memória alocada
    apagarMemoria(secoes, peca, listaDeChegadaArray, numSecoes);
    return 0;
}