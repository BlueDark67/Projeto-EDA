#include "Armazem.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>



using namespace std;

int numSecoes = rand() % 4+7;

string* conteudoMarcas = leFicheirosMarcas();
string* conteudoCategorias = leFicheirosCategorias();;
string* categoriasEscolhidas = escolheCategoria(conteudoCategorias, numSecoes);
string alfabeto = criaAlfabeto();




/**
 *Função que inicializa a lista de chegada
 * @param lista
 * @param marca
 * @param categoria
 * @return lista de chegada
 */
void iniciarListadChegada(listaDeChegada& lista, string marca, string categoria){
    lista.categoria = categoria;
    lista.marca = marca;
}

/**
 * Função que inicializa a seccao
 * @param seccao
 * @param id
 * @param categoria
 * @param capacidade
 * @return seccoes
 */
void iniciarSeccao(seccoes& seccao,char id,  string categoria, int capacidade, int quantidade) {
    seccao.id = id;
    seccao.capacidade = capacidade;
    seccao.categoria = categoria;
    seccao.quantidade = quantidade;
}

/**
 * Função que inicializa a peça
 * @param pecas
 * @param marca
 * @param categoria
 * @param probVenda
 * @param preco
 * @param numSerie
 * @return pecas
 */
void iniciarPecasLC( Peca& pecas, string marca, string categoria,  int probVenda, int preco, int numSerie){
    pecas.marcas = marca;
    pecas.categorias = categoria ;
    pecas.preco = preco;
    pecas.numSerie= numSerie;
    pecas.probVenda = probVenda;

}

/**
 *
 * @param max_linhas
 * @param linhaM
 * @param textoM
 * @return conteudoMarcas
  * Esta função abre o ficheiro marcas.txt e tranforma o seu conteudo em um array textoM.
 */
string* leFicheirosMarcas(){

    const int max_linha = 100;
    string* conteudoMarcas = new string[max_linha];
    int linhaM =0;
    string textoM;
    ifstream ficheiroMarcas("marcas.txt");
    while (getline (ficheiroMarcas, textoM) && linhaM < max_linha) {
        conteudoMarcas[linhaM] =textoM;
        linhaM++;
    }
    ficheiroMarcas.close();
    return conteudoMarcas;
}

/**
 * @param max_linha
 * @param linhaC
 * @param max_linha
 * @param ficheiroCategorias
 * @param textoC
 * @return conteudoCategorias
 * esta funcao abre o ficheiro categorais.txt transforma o conteudo em uma array textoC
 * no fim deste procedimento fecha o ficheiro
 */
string* leFicheirosCategorias(){

    const int max_linha = 100;
    string* conteudoCategorias = new string[max_linha];
    int linhaC =0;
    string textoC;
    ifstream ficheiroCategorias("categorias.txt");
    while (getline (ficheiroCategorias, textoC) && linhaC < max_linha) {
        conteudoCategorias[linhaC] = textoC;
        linhaC++;
    }
    ficheiroCategorias.close();
    return conteudoCategorias;
}

/**
 * @param tamanho alfabeto
 * @return alfabeto
 * esta funcao gera o alfabeto usado posteriormente para nomear cada seccao, por exe: seccao A , seccao B, etc.
 */
string criaAlfabeto(){
    const int tamanhoAlfabeto = 26;
    char alfabeto[tamanhoAlfabeto];
    for (int i = 0; i < tamanhoAlfabeto; ++i) {
        alfabeto[i] = 'A' + i;
    }
    return alfabeto;
}

string* escolheCategoria(string* conteudoCatregoria, int numSecoes){
    string* categoriasEscolhidas = new string [numSecoes];
    int conta = 0;
    while(conta < numSecoes){
        int numCategoria = rand()%22;
        bool duplicado = false;
        for (int i = 0; i < conta; i++) {
            if (conteudoCatregoria[numCategoria] == categoriasEscolhidas[i]){
                duplicado = true;
                break;
            }
        }
        if(!duplicado){
            categoriasEscolhidas[conta] = conteudoCatregoria[numCategoria];
            conta++;
        }

    }
    return categoriasEscolhidas;
}


Peca* criaPecas(int tamanho, int numSecoes){
    Peca* peca = new Peca[tamanho];
    for (int i = 0; i < tamanho ; i++) {
        int numlinhaM = rand() % 73;// Cria linha aleatória da marca

        int numlinhaC = rand() % 10;// Cria linha aleatória da categoria
        string marca = conteudoMarcas[numlinhaM];// Marca aleatória
        string categoria = categoriasEscolhidas[numlinhaC];// Categoria aleatória
        int probVenda = rand()%46 +5;// Probabilidade de venda entre 5 e 50
        int preco = (rand()%179+2)*5;// Preço entre 10 e 900
        int numSerie = rand() % 9000+1000;// Numero de serie entre 1000 e 9999
        iniciarPecasLC(peca[i],marca, categoria, probVenda, preco, numSerie);// Inicializa a peça
    }
    return peca;
}


listaDeChegada* criaListaChegada(Peca* peca, int tamanho){
    listaDeChegada* listaDeChegadaArray = new listaDeChegada[tamanho];
    for (int i = 0; i < tamanho ; i++) {
        string marca = peca[i].marcas;// Marca aleatória
        string categoria = peca[i].categorias;// Categoria aleatória
        iniciarListadChegada(listaDeChegadaArray[i], marca, categoria);// Inicializa a lista de chegada
    }

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < 9; j++) {
            if (listaDeChegadaArray[j].marca > listaDeChegadaArray[j+1].marca){
                swap(listaDeChegadaArray[j], listaDeChegadaArray[j+1]);
            }
        }
    }

    return listaDeChegadaArray;
}

seccoes* criaSeccoes(int numSecoes){
    seccoes* secoes = new seccoes[numSecoes];// Alocar dinamicamente o array de secções
    for (int i = 0; i < numSecoes; ++i) {
        char id = alfabeto[i]; // ID conforme a posição no alfabeto
        int capacidade = rand() % 4  + 3; // Capacidade entre 3 e 6
        string categoria = categoriasEscolhidas[i];// Categoria aleatória
        int quantidade = 0;//quantidade de pecas na seccao
        iniciarSeccao(secoes[i], id, categoria,capacidade, quantidade); // Inicializa a seção
        secoes[i].inventario = new Peca[capacidade]; // Alocação de memória para o inventário
    }

    return secoes;

}




void imprimeSecLis(int ciclos, seccoes* secoes, Peca* peca, listaDeChegada* listaDeChegadaArray, int tamanho, int &indice){
    int numSecoes = rand() % 4 + 7;  // Numero de seções entre 7 e 10
    int tamanhoLista = tamanho;

    // Imprime as seções
    if (ciclos != 0) {
        for (int i = 0; i < numSecoes; i++) {
            cout << "Seccao " << secoes[i].id << " | " << "Categoria: " << secoes[i].categoria << " | "
                 << " Capacidade = "
                 << secoes[i].capacidade << " | " << "Quantidade = " << secoes[i].quantidade << endl;
            for (int j = 0; j < tamanhoLista; j++) {


                // Adiciona novas peças à seção e imprime
                if (listaDeChegadaArray[j].categoria == secoes[i].categoria &&
                    secoes[i].quantidade < secoes[i].capacidade) {
                    secoes[i].inventario[secoes[i].quantidade].marcas = listaDeChegadaArray[j].marca;
                    secoes[i].inventario[secoes[i].quantidade].categorias = listaDeChegadaArray[j].categoria;
                    secoes[i].inventario[secoes[i].quantidade].numSerie = peca[j].numSerie;
                    secoes[i].inventario[secoes[i].quantidade].preco = peca[j].preco;
                    secoes[i].inventario[secoes[i].quantidade].probVenda = peca[j].probVenda;
                    for (int k = 0; k < secoes[i].quantidade; k++) {
                        cout << "        " << secoes[i].inventario[k].marcas << " | " << secoes[i].inventario[k].categorias
                             << " | " << "Numero de Serie: " << secoes[i].inventario[k].numSerie << " | " << "Preco = "
                             << secoes[i].inventario[k].preco
                             << "$" << endl;
                    }
                    /*cout << "        " << secoes[i].inventario[secoes[i].quantidade].marcas << " | " << secoes[i].inventario[secoes[i].quantidade].categorias
                         << " | " << "Numero de Serie: " << secoes[i].inventario[secoes[i].quantidade].numSerie << " | " << "Preco = "
                         << secoes[i].inventario[secoes[i].quantidade].preco
                         << "$" << endl;*/
                    secoes[i].quantidade += 1;


                    removerDaListaDeChegada(peca, listaDeChegadaArray, j, tamanhoLista);
                    indice++;
                    tamanhoLista--;
                }
            }

        }
        cout << "Tamanho da lista de chegada: " << tamanhoLista << endl;
        cout << "*************************************************" << endl;
    } else {
        for (int i = 0; i < numSecoes; i++) {
            cout << "Seccao " << secoes[i].id << " | " << "Categoria: " << secoes[i].categoria << " | "
                 << " Capacidade = "
                 << secoes[i].capacidade << " | " << "Quantidade = " << secoes[i].quantidade << endl;
        }
    }

    // Imprime a lista de chegada
    cout << "*************************************************" << endl;
    cout << "       *****   Lista de Chegada   *****" << endl;
    for (int i = 0; i < tamanhoLista; i++) {
        cout << setw(10) << listaDeChegadaArray[i].marca << " | " << setw(15) << listaDeChegadaArray[i].categoria
             << " | " << peca[i].numSerie << " |" << peca[i].preco << "$" << "\n";
    }
    cout << "*************************************************" << endl;

}


void apagarMemoria(seccoes* secoes, Peca* peca, listaDeChegada* listaChegada, int numSecoes){
    delete[] secoes;
    delete[] peca;
    delete[] listaChegada;
    for (int i = 0; i < numSecoes; i++) {
        delete[] secoes[i].inventario; // Liberação de memória para o inventário
    }
}

void venderPeca(seccoes* secoes, Peca* peca){
    int resposta;
    cout << "Qual é o numero de serie da peca que quer vender?" << endl;
    cin >> resposta;
    for (int i = 0; i < 10; i++) {
        if (peca[i].numSerie == resposta) {
            for (int j = 0; j < 10; j++) {

                }
            }
        }
    }


void removerDaListaDeChegada(Peca* peca ,listaDeChegada* listaDeChegadaArray, int indiceRemover,int tamanhoLista){

    if (indiceRemover < 0 || indiceRemover >= tamanhoLista) {
        cout << "Indice de remocao invalido." << endl;
        return;
    }

    // Move os elementos para preencher a lacuna deixada pela remocao
    for (int i = indiceRemover; i < tamanhoLista - 1; i++) {
        listaDeChegadaArray[i] = listaDeChegadaArray[i + 1];
        peca[i] = peca[i + 1];
    }

    // Atualiza o tamanho da lista
    tamanhoLista--;

}



