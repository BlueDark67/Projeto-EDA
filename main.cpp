#include <iostream>
#include "Armazem.h"
#include <stdlib.h>
#include <string>
#include <time.h>
#include <algorithm>



using namespace std;

int main(int argc, char const* argv[]) {
    srand((time(0)));// Seed para gerar numeros aleatórios
    int novoTamanho;
    int numSecoes = rand() % 4+7; //Numero de seções entre 7 e 10
    //int numSecoes2 = criaNumSecoes(); Numero de seções
    int ciclos = 0;// Ciclo
    int tamanho = 10;// Tamanho da lista de chegada
    Peca* listaChegada = criaPecas(tamanho, numSecoes);// Cria as peças
    seccoes* secoes = criaSeccoes(numSecoes);// Cria as secções
    imprimeSecLis(ciclos, secoes, listaChegada,  tamanho, numSecoes);// Imprime as secções e a lista de chegada



    string resposta;// Resposta do utilizador
    string novaCategoria;

    bool carregarArmazemUsado = false;

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
                        if(carregarArmazemUsado == true){
                            Peca* listaChegada2 = leFicheiroPeca("peca.txt");
                            seccoes* secoes2 = leFicheiroSeccoes("seccao.txt");
                            VendaManual(secoes2,numSecoes,listaChegada2, tamanho);
                        }else if (carregarArmazemUsado == false){
                            VendaManual(secoes,numSecoes,listaChegada, tamanho);
                        }
                        break;
                    case '2':
                        cout << "Escolheu Promocao" << endl;
                        Promocao(secoes,numSecoes);
                        if(carregarArmazemUsado == true){
                            seccoes* secoes2 = leFicheiroSeccoes("seccao.txt");
                            Promocao(secoes2,numSecoes);
                        }else if (carregarArmazemUsado == false){
                            Promocao(secoes,numSecoes);
                        }
                        break;
                    case '3':
                        cout << "Escolheu Alterar categoria" << endl;
                        if(carregarArmazemUsado == true){
                            seccoes* secoes2 = leFicheiroSeccoes("seccao.txt");
                            alterarCategoria( secoes2, numSecoes,novaCategoria);
                        }else if (carregarArmazemUsado == false){
                            alterarCategoria( secoes, numSecoes,novaCategoria);
                        }
                        break;
                    case '4':
                        cout << "Escolheu Adicionar Seccao" << endl;
                        if(carregarArmazemUsado == true){
                            seccoes* secoes2 = leFicheiroSeccoes("seccao.txt");
                            adicionarSecao(secoes2,numSecoes);
                        }else if (carregarArmazemUsado == false){
                            adicionarSecao(secoes,numSecoes);
                        }
                        break;
                    case '5':
                        cout << "Escolheu Gravar Armazem" << endl;
                        if(carregarArmazemUsado == true){
                            Peca* listaChegada2 = leFicheiroPeca("peca.txt");
                            seccoes* secoes2 = leFicheiroSeccoes("seccao.txt");
                            gravarArmazem(secoes2, numSecoes, listaChegada2, tamanho,ciclos, carregarArmazemUsado);
                        }else if (carregarArmazemUsado == false){
                            gravarArmazem(secoes, numSecoes, listaChegada, tamanho,ciclos, carregarArmazemUsado);
                        }
                        break;
                    case '6':
                        carregarArmazemUsado = true;
                        carregarArmazem(argc, argv, numSecoes,tamanho);

                        break;
                    case '7':
                        cout << "Escolheu Imprimir Armazem" << endl;
                        if(carregarArmazemUsado == true){
                            Peca* listaChegada2 = leFicheiroPeca("peca.txt");
                            imprimirArmazem(listaChegada2, tamanho);
                        }else if (carregarArmazemUsado == false){
                            imprimirArmazem(listaChegada, tamanho);
                        }
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
                ciclos++;// Ciclo
                cout << "Escolheu Dia Seguinte " << ciclos << endl;
                imprimeSecLis(ciclos, secoes, listaChegada, tamanho, numSecoes);// Imprime as secções e a lista de chegada


        } else {// Se a resposta for diferente de s ou g
            cout << "Escolha a opcao sair." << endl;
        }
    }while (resposta != "0");// Enquanto a resposta for diferente de 0

    // Libera a memória alocada
    delete[] conteudoMarcas;
    delete[] conteudoCategorias;
    delete[] categoriasEscolhidas;
    apagarMemoria(secoes, listaChegada);
    return 0;
}