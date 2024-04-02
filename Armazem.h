

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

void iniciarSeccao( seccoes& seccao, char id,  string categoria, int capacidade, int quantidade);
string* leFicheirosMarcas();
string* leFicheirosCategorias();
string criaAlfabeto();
string* escolheCategoria(string* conteudoCatregoria);

void iniciarPecasLC(Peca& pecas, string marca, string categoria  ,int probVenda, int preco, int numSerie);
//void iniciarListadChegada(listaDeChegada& lista, string marca, string categoria);



Peca* criaPecas(int tamanh, int numSecoes);

//listaDeChegada* criaListaChegada(Peca* peca, int tamanho);

seccoes* criaSeccoes(int numSecoes);

void imprimeSecLis(int ciclos, seccoes* secoes, Peca* listaChegada, int tamanho,  int numSecoes);

void apagarMemoria(seccoes* secoes, Peca* peca);

extern string* conteudoMarcas;
extern string* conteudoCategorias;
extern string* categoriasEscolhidas;
extern string alfabeto;

bool removerDaListaDeChegadaUsado();
int removerDaListaDeChegada(seccoes* secoes,Peca* listaChegada,int numSecoes, int tamanhoLista);
void VendaManual(seccoes*secoes,int numSecoes, Peca* listaChegada, int & tamanholista);
void Promocao(seccoes* secoes, int numSecoes);
void alterarCategoria(seccoes* secoes, int numSecoes, string novaCategoria);
void adicionarSecao(seccoes*& secoes, int& numSecoes);
void gravarArmazem(seccoes* secoes, int numSecoes, Peca* peca, int tamanho, int ciclos, bool carregarArmazemUsado);
int novaPeca(Peca* listaChegada, int tamanho);
void carregarArmazem(int argc, const char* argv[], int numSecoes, int tamanholista);
void ordenarPorPreco(Peca* listaChegada,int tamanho);
void ordenarPorMarca(Peca* listaChegada, int tamanho);
void imprimirArmazem(Peca* listaChegada, int tamanho);
int leFicheiroCiclos(string nomeFicheiro);
Peca* leFicheiroPeca(string nomeFicheiro);
seccoes* leFicheiroSeccoes(string nomeFicheiro);
int contarLinhas(string nomeFicheiro);
void vendaPeca(seccoes* seccoes,int numSecoes);
void removePecaVenda(seccoes* secoes, int id,int numSecoes, int numSerie);
void removePecaDuplicada(seccoes* secoes, int secaoIndex, int pecaIndex);

#endif //PROJETO_EDA_ARMAZEM_H