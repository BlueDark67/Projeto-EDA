

#ifndef PROJETO_EDA_ARMAZEM_H
#define PROJETO_EDA_ARMAZEM_H
#include <iostream>
#include <string>

using namespace std;


struct Peca{
    string marcas;
    string categorias;
    int probVenda;
    int preco;
    int numSerie;
};

struct seccoes{
    char id;
    string categoria;
    int capacidade;
    int vendaTotal;
    int quantidade;
    Peca* inventario;
};

struct listaDeChegada{
    string  marca;
    string  categoria;
};

void iniciarSeccao( seccoes& seccao, char id,  string categoria, int capacidade, int quantidade);
string* leFicheirosMarcas();
string* leFicheirosCategorias();
string criaAlfabeto();
string* escolheCategoria(string* conteudoCatregoria, int numSecoes);

void iniciarPecasLC(Peca& pecas, string marca, string categoria  ,int probVenda, int preco, int numSerie);
void iniciarListadChegada(listaDeChegada& lista, string marca, string categoria);



Peca* criaPecas(int tamanh, int numSecoes);

listaDeChegada* criaListaChegada(Peca* peca, int tamanho);

seccoes* criaSeccoes(int numSecoes);

void imprimeSecLis(int ciclos, seccoes* secoes, Peca* peca, listaDeChegada* listaDeChegadaArray, int tamanho, int &indice);

void apagarMemoria(seccoes* secoes, Peca* peca, listaDeChegada* listaChegada, int numSecoes);


extern string* conteudoMarcas;
extern string* conteudoCategorias;
extern string alfabeto;

void venderPeca(seccoes* secoes, Peca* peca);

void removerDaListaDeChegada(Peca* peca ,listaDeChegada* listaDeChegadaArray, int indiceRemover, int tamanhoLista);

#endif //PROJETO_EDA_ARMAZEM_H