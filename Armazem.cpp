#include "Armazem.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <ctime>



#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemoryLeak"
using namespace std;

string* conteudoMarcas = leFicheirosMarcas();
string* conteudoCategorias = leFicheirosCategorias();
string alfabeto = criaAlfabeto();
string* categoriasEscolhidas = escolheCategoria(conteudoCategorias);
bool removerDaListaDeChegadaChamada = false;
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
    seccao.vendaTotal = 0;

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

string* escolheCategoria(string* conteudoCatregoria){
    srand(time(0));
    string* categoriasEscolhidas = new string [10];//Linha com erro
    int conta = 0;
    while(conta < 10){
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
    Peca* listaChegada = new Peca[11];
    for (int i = 0; i < tamanho ; i++) {
        int numlinhaM = rand() % 73;// Cria linha aleatória da marca
        string marca = conteudoMarcas[numlinhaM];// Marca aleatória
        string categoria;
        do {
            int numlinhaC = rand() % 9;// Cria linha aleatória da categoria
            categoria = categoriasEscolhidas[numlinhaC];// Categoria aleatória
        } while (categoria.empty()); // Se a categoria for vazia, escolhe outra
        int probVenda = rand()%46 +5;// Probabilidade de venda entre 5 e 50
        int preco = (rand()%179+2)*5;// Preço entre 10 e 900
        int numSerie = rand() % 9000+1000;// Numero de serie entre 1000 e 9999
        iniciarPecasLC(listaChegada[i],marca, categoria, probVenda, preco, numSerie);// Inicializa a peça
    }
    return listaChegada;
}

seccoes* criaSeccoes(int numSecoes){
    seccoes* secoes = new seccoes[10];// Alocar dinamicamente o array de secções
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




void imprimeSecLis(int ciclos, seccoes* secoes, Peca* listaChegada,  int tamanho, int numSecoes){
    int tamanhoLista = tamanho;
    int novoTamanhoLista;
    int tamanhoLista2;



    // Imprime as seções
    if (ciclos != 0) {
        if(ciclos == 1) {
            cout << setw(60) << "******************************************************" << endl;
            cout << setw(48) << "********** Armazem EDA | Faturcao total = " << secoes->vendaTotal << " **********"<< endl;
            cout << setw(60) << "******************************************************" << endl;
            for (int i = 0; i < numSecoes; i++) {
                for (int j = 0; j < tamanhoLista; j++) {
                    // Adiciona novas peças à seção e imprime
                    if (tamanhoLista == 0) {
                        break;
                    }
                    if (listaChegada[j].categorias == secoes[i].categoria &&
                        secoes[i].quantidade < secoes[i].capacidade) {
                        secoes[i].inventario[secoes[i].quantidade].marcas = listaChegada[j].marcas;
                        secoes[i].inventario[secoes[i].quantidade].categorias = listaChegada[j].categorias;
                        secoes[i].inventario[secoes[i].quantidade].numSerie = listaChegada[j].numSerie;
                        secoes[i].inventario[secoes[i].quantidade].preco = listaChegada[j].preco;
                        secoes[i].inventario[secoes[i].quantidade].probVenda = listaChegada[j].probVenda;
                        secoes[i].quantidade += 1;
                    }
                }
                cout << "Seccao " << secoes[i].id << " | " << "Categoria: " << secoes[i].categoria << " | "
                     << " Capacidade = "
                     << secoes[i].capacidade << " | " << "Quantidade = " << secoes[i].quantidade << " | "
                     << "Faturacao = " << secoes[i].vendaTotal << endl;

                for (int k = 0; k < secoes[i].quantidade; k++) {
                    cout << "        " << secoes[i].inventario[k].marcas << " | "
                         << secoes[i].inventario[k].categorias
                         << " | " << "Numero de Serie: " << secoes[i].inventario[k].numSerie << " | "
                         << "Preco = " << secoes[i].inventario[k].preco << "$" << endl;
                }
            }
            cout << "*************************************************" << endl;
            cout << "       *****   Lista de Chegada   *****" << endl;
            for (int i = 0; i < 5; i++) {
                cout << setw(10) << listaChegada[i].marcas << " | " << setw(15) << listaChegada[i].categorias
                     << " | " << listaChegada[i].numSerie << " |" << listaChegada[i].preco << "$" << "\n";
            }
            cout << "*************************************************" << endl;
        }else if (ciclos > 1) {
            if (ciclos > 1) {
                for (int i = 0; i < numSecoes; i++) {
                    for (int j = 0; j < tamanhoLista; j++) {
                        // Adiciona novas peças à seção e imprime
                        if (tamanhoLista == 0) {
                            break;
                        }
                        if (listaChegada[j].categorias == secoes[i].categoria &&
                            secoes[i].quantidade < secoes[i].capacidade) {
                            secoes[i].inventario[secoes[i].quantidade].marcas = listaChegada[j].marcas;
                            secoes[i].inventario[secoes[i].quantidade].categorias = listaChegada[j].categorias;
                            secoes[i].inventario[secoes[i].quantidade].numSerie = listaChegada[j].numSerie;
                            secoes[i].inventario[secoes[i].quantidade].preco = listaChegada[j].preco;
                            secoes[i].inventario[secoes[i].quantidade].probVenda = listaChegada[j].probVenda;
                            secoes[i].quantidade += 1;
                        }
                    }
                    for (int j = 0; j < secoes[i].quantidade; j++) {
                        for (int k = j + 1; k < secoes[i].quantidade; k++) {
                            if (secoes[i].inventario[j].numSerie == secoes[i].inventario[k].numSerie) {
                                removePecaDuplicada(secoes, i, k);
                                break;
                            }
                        }
                    }
                    cout << "Seccao " << secoes[i].id << " | " << "Categoria: " << secoes[i].categoria << " | "
                         << " Capacidade = "
                         << secoes[i].capacidade << " | " << "Quantidade = " << secoes[i].quantidade << " | "
                         << "Faturacao = " << secoes[i].vendaTotal << endl;

                    for (int k = 0; k < secoes[i].quantidade; k++) {
                        cout << "        " << secoes[i].inventario[k].marcas << " | "
                             << secoes[i].inventario[k].categorias
                             << " | " << "Numero de Serie: " << secoes[i].inventario[k].numSerie << " | "
                             << "Preco = " << secoes[i].inventario[k].preco << "$" << endl;
                    }
                }

            }
            tamanhoLista2 = removerDaListaDeChegada(secoes, listaChegada, numSecoes, tamanhoLista);
            cout << tamanhoLista2 << endl;
            cout << "*************************************************" << endl;
            cout << "       *****   Lista de Chegada   *****" << endl;
            for (int i = 0; i < 5+tamanhoLista2; i++) {
                cout << setw(10) << listaChegada[i].marcas << " | " << setw(15) << listaChegada[i].categorias
                     << " | " << listaChegada[i].numSerie << " |" << listaChegada[i].preco << "$" << "\n";
            }
            cout << "*************************************************" << endl;
        }
    } else if (ciclos == 0) {

        cout << setw(60)<< "******************************************************" << endl;
        cout << setw(60)<< "********** Armazem EDA | Faturcao total = 0 **********" << endl;
        cout << setw(60)<< "******************************************************" << endl;

        for (int i = 0; i < numSecoes; i++) {
            cout << "Seccao " << secoes[i].id << " | " << "Categoria: " << secoes[i].categoria << " | "
                 << " Capacidade = "
                 << secoes[i].capacidade << " | " << "Quantidade = " << secoes[i].quantidade << endl;

        }
        cout << "*************************************************" << endl;
        cout << "       *****   Lista de Chegada   *****" << endl;
        for (int i = 0; i < 10; i++) {
            cout << setw(10) << listaChegada[i].marcas << " | " << setw(15) << listaChegada[i].categorias
                 << " | " << listaChegada[i].numSerie << " |" << listaChegada[i].preco << "$" << "\n";
        }
        cout << "*************************************************" << endl;

    }


    // Imprime a lista de chegada


}

bool removerDaListaDeChegadaUsado(){
    return removerDaListaDeChegadaChamada;
}

void apagarMemoria(seccoes* secoes, Peca* peca){
    delete[] secoes;
    delete[] peca;
}

int removerDaListaDeChegada(seccoes* secoes,Peca* listaChegada, int numSecoes,int tamanhoLista){
    removerDaListaDeChegadaChamada = true;
    int novoTamanho = tamanhoLista - 1; // O novo tamanho será um elemento a menos
    Peca* novaLista = new Peca[novoTamanho];

    int novaListaIndex = 0; // Índice para a nova lista

    for (int k = 0; k < tamanhoLista; k++) {
        bool encontrado = false;

        // Verificar se o número de série do elemento atual de listaChegada existe no inventário de qualquer seção
        for (int i = 0; i < numSecoes && !encontrado; i++) {
            for (int j = 0; j < secoes[i].quantidade && !encontrado; j++) {
                if (secoes[i].inventario[j].numSerie == listaChegada[k].numSerie) {
                    // Elemento encontrado, não adicionamos na nova lista
                    encontrado = true;
                }
            }
        }

        // Se o elemento não foi encontrado no inventário de nenhuma seção, copiamos para a nova lista
        if (!encontrado) {
            novaLista[novaListaIndex] = listaChegada[k];
            novaListaIndex++;
        }
    }

    // Liberar a memória da lista antiga
    delete[] listaChegada;

    // Apontar listaChegada para a nova lista
    listaChegada = new Peca[novaListaIndex];
    for (int i = 0; i < novaListaIndex; ++i) {
        listaChegada[i] = novaLista[i];
    }



    return novaListaIndex;

}
void VendaManual(seccoes* secoes, int numSecoes, Peca* listaChegada, int& tamanhoLista) {
    string secao;
    string produto;

    cout << "Digite o nome da secao: ";
    cin >> secao;

    cout << "Digite o nome do produto: ";
    cin >> produto;

    bool encontrado = false;

    for (int i = 0; i < numSecoes; ++i) {
        if (secoes[i].id == secao[0]) {
            for (int j = 0; j < secoes[i].quantidade; ++j) {
                if (secoes[i].inventario[j].marcas == produto) {
                    cout << "Produto encontrado na secao " << secao << endl;
                    cout << "Preco do produto: $" << secoes[i].inventario[j].preco << endl;

                    // Adiciona o preco da venda aos registros de faturacao do armazem e da secao
                    secoes[i].vendaTotal += secoes[i].inventario[j].preco;

                    // Remove o produto vendido da secao
                    for (int k = j; k < secoes[i].quantidade - 1; ++k) {
                        secoes[i].inventario[k] = secoes[i].inventario[k + 1];
                    }
                    secoes[i].quantidade--;

                    // Remove uma peca da lista de chegada (se existir)
                    if (tamanhoLista > 0) {
                        for (int k = 0; k < tamanhoLista - 1; ++k) {
                            listaChegada[k] = listaChegada[k + 1];
                        }
                        tamanhoLista--;
                    }

                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                cout << "Produto nao encontrado na secao " << secao << endl;
            }
            break;
        }
    }
    if (!encontrado) {
        cout << "Secao nao encontrada." << endl;
    }
}


void Promocao(seccoes* secoes, int numSecoes) {
    char secao;
    int duracaoPromocao;
    double descontoPercentual;

    cout << "Digite o nome da secao para adicionar promocao: ";
    cin >> secao;

    cout << "Digite a duracao da promocao em dias (ciclos): ";
    cin >> duracaoPromocao;

    cout << "Digite a porcentagem de desconto a ser aplicada (%): ";
    cin >> descontoPercentual;

    bool secaoEncontrada = false;
    for (int i = 0; i < numSecoes; ++i) {
        if (secoes[i].id == secao) {
            secaoEncontrada = true;

            // Aplicar desconto a todas as peças na seção
            for (int j = 0; j < secoes[i].quantidade; ++j) {
                secoes[i].inventario[j].preco -= secoes[i].inventario[j].preco * (descontoPercentual / 100);
                // Aumentar a probabilidade de venda em 15%
                secoes[i].inventario[j].probVenda += 15;
                if (secoes[i].inventario[j].probVenda > 100) {
                    secoes[i].inventario[j].probVenda = 100; // Limite superior da probabilidade de venda a 100%
                }
            }

            // Adicionar informações da promoção à seção
            secoes[i].vendaTotal += duracaoPromocao;
            cout << "Promocao adicionada com sucesso para a secao " << secao << ". Desconto de " << descontoPercentual << "% aplicado durante " << duracaoPromocao << " dias." << endl;

            break;
        }
    }

    if (!secaoEncontrada) {
        cout << "Secao nao encontrada." << endl;
    }
}


void alterarCategoria(seccoes* secoes, int numSecoes, string novaCategoria) {
    char secao;

    cout << "Digite o nome da secao para alterar a categoria: ";
    cin >> secao;
    cout << "Escolha uma categoria :";
    cin >> novaCategoria;

    bool secaoEncontrada = false;
    for (int i = 0; i < numSecoes; ++i) {
        if (secoes[i].id == secao) {
            secaoEncontrada = true;

            // Remover todos os produtos da seção
            delete[] secoes[i].inventario;
            secoes[i].quantidade = 0;

            // Atualizar a categoria da seção
            secoes[i].categoria = novaCategoria;

            cout << "Categoria da secao " << secao << " alterada para: " << novaCategoria << endl;
            break;
        }
    }

    if (!secaoEncontrada) {
        cout << "Secao nao encontrada." << endl;
    }
}


void adicionarSecao(seccoes*& secoes, int& numSecoes) {
    char id;
    int capacidade;
    string categoria;

    // Solicitar ao usuário os dados para a nova seção
    cout << "Digite o ID único para a nova secao: ";
    cin >> id;

    cout << "Digite a capacidade máxima para a nova secao: ";
    cin >> capacidade;

    cout << "Digite a categoria para a nova secao: ";
    cin >> categoria;

    // Alocar espaço para a nova seção e copiar os dados fornecidos pelo usuário
    seccoes* novaSecao = new seccoes[numSecoes + 1];
    for (int i = 0; i < numSecoes; ++i) {
        novaSecao[i] = secoes[i];
    }

    // Adicionar a nova seção ao final do vetor de seções
    novaSecao[numSecoes].id = id;
    novaSecao[numSecoes].capacidade = capacidade;
    novaSecao[numSecoes].categoria = categoria;
    novaSecao[numSecoes].quantidade = 0; // Inicializa a quantidade de produtos na nova seção
    novaSecao[numSecoes].vendaTotal = 0; // Inicializa a venda total da nova seção
    novaSecao[numSecoes].inventario = new Peca[capacidade]; // Aloca memória para o inventário da nova seção

    // Liberar memória alocada para o vetor de seções anterior
    delete[] secoes;

    // Atualiza o ponteiro de seções para apontar para o novo vetor de seções
    secoes = novaSecao;

    // Atualizar o número total de seções
    numSecoes++;

    cout << "Nova secao adicionada com sucesso!" << endl;
}


void gravarArmazem(seccoes* secoes, int numSecoes, Peca* listaChegada, int tamanho, int ciclos, bool carregarArmazemUsado) {
    // Salvar dados das seções do armazém em um arquivo
    ofstream arquivoSecoes("secoes.txt");
    if (arquivoSecoes.is_open()) {
        for (int i = 0; i < numSecoes; ++i) {
            arquivoSecoes <<  secoes[i].id << "," << secoes[i].categoria << ","
                          << secoes[i].capacidade << "," << secoes[i].quantidade << endl;
        }
        arquivoSecoes.close();
        cout << "Dados das secoes do armazem foram gravados com sucesso." << endl;
    } else {
        cout << "Erro ao abrir o arquivo para gravar os dados das secoes do armazem." << endl;
    }

    // Salvar dados das peças em um arquivo
    bool resultadoRemoverDaListaDeChegada = removerDaListaDeChegadaUsado();
    if(resultadoRemoverDaListaDeChegada == true){
        tamanho = removerDaListaDeChegada(secoes, listaChegada, numSecoes, tamanho);
    }
     // Atualiza o tamanho da lista de chegada
    ofstream arquivoPecas("pecas.txt");
    if (arquivoPecas.is_open()) {
        for (int i = 0; i < tamanho; ++i) {
            arquivoPecas <<listaChegada[i].marcas << "," << listaChegada[i].categorias
                         << "," << listaChegada[i].numSerie << "," << listaChegada[i].preco
                         << "," << listaChegada[i].probVenda << endl;
        }
        arquivoPecas.close();
        cout << "Dados das pecas do armazem foram gravados com sucesso." << endl;
    } else {
        cout << "Erro ao abrir o arquivo para gravar os dados das pecas do armazem." << endl;
    }

    // Salvar o número de ciclos em um arquivo
    ofstream arquivoCiclos("ciclos.txt");
    if (arquivoCiclos.is_open()) {
        arquivoCiclos << "Ciclos: " << ciclos << endl;
        arquivoCiclos.close();
        cout << "Numero de ciclos foi gravado com sucesso." << endl;
    } else {
        cout << "Erro ao abrir o arquivo para gravar o numero de ciclos." << endl;
    }

    ofstream arquivoPecasArmazem("pecasArmazem.txt");
    if (arquivoPecasArmazem.is_open()) {
        for (int i = 0; i < numSecoes; ++i) {
            arquivoPecasArmazem << secoes[i].id << endl;
            for (int j = 0; j < secoes[i].quantidade; ++j) {
                arquivoPecasArmazem << setw(15) <<secoes[i].inventario[j].marcas << ","
                << secoes[i].inventario[j].categorias<< ","
                << secoes[i].inventario[j].numSerie << ","
                << secoes[i].inventario[j].preco << ","
                << secoes[i].inventario[j].probVenda << endl;
            }

        }
        arquivoPecas.close();
        cout << "Dados das pecas do armazem foram gravados com sucesso." << endl;
    } else {
        cout << "Erro ao abrir o arquivo para gravar os dados das pecas do armazem." << endl;
    }
}

int novaPeca(Peca* listaChegada, int tamanho){
    int novoTamanho = tamanho +5;
    Peca* novaLista = new Peca[novoTamanho];

    for (int i = 0; i < tamanho; i++) {
        novaLista[i] = listaChegada[i];
    }

    for (int i = tamanho; i < novoTamanho ; i++) {
        novaLista[i].marcas = conteudoMarcas[rand() % 73];
        novaLista[i].categorias = categoriasEscolhidas[rand() % 9];
        novaLista[i].preco = (rand() % 179 + 2) * 5;
        novaLista[i].numSerie = rand() % 9000 + 1000;
        novaLista[i].probVenda = rand() % 46 + 5;
    }

    delete[] listaChegada;

    listaChegada = new Peca[novoTamanho];
    for (int i = 0; i < novoTamanho; i++) {
        listaChegada[i] = novaLista[i];
    }

    //delete[] novaLista;

    return novoTamanho;

}

int contarLinhas(string nomeFicheiro) {
    ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return -1;
    }

    int numLinhas = 0;
    string linha;
    while (getline(ficheiro, linha)) {
        numLinhas++;
    }

    ficheiro.close();
    return numLinhas;
}

seccoes* leFicheiroSeccoes(string nomeFicheiro){
    seccoes* secoes2 = new seccoes[10];
    char id;
    string categoria;
    int capacidade;
    int quantidade;
    ifstream ficheiroSeccoes(nomeFicheiro);
    if(ficheiroSeccoes.is_open()) {
        int i = 0;
        string temp;
        while (getline(ficheiroSeccoes, temp, ',') && i < 10) {
            id = temp[0];
            getline(ficheiroSeccoes, categoria, ',');
            ficheiroSeccoes >> capacidade;
            getline(ficheiroSeccoes, temp, ',');
            ficheiroSeccoes >> quantidade;
            getline(ficheiroSeccoes, temp);
            secoes2[i].id = id;
            secoes2[i].categoria = categoria;
            secoes2[i].capacidade = capacidade;
            secoes2[i].quantidade = quantidade;
            i++;
        }
        ficheiroSeccoes.close();
    } else {
        cout << "Erro ao abrir o arquivo para carregar os dados das secoes do armazem." << endl;
    }
    return secoes2;
}

Peca* leFicheiroPeca(string nomeFicheiro) {
    Peca* listaChegada2 = new Peca[50];
    string marca;
    string categoria;
    int capacidade;
    int quantidade;
    ifstream ficheiroPecas(nomeFicheiro);
    if(ficheiroPecas.is_open()) {
        int i = 0;
        string temp;
        while (getline(ficheiroPecas, marca, ',') && i < 50) {
            getline(ficheiroPecas, categoria, ',');
            ficheiroPecas >> capacidade;
            getline(ficheiroPecas, temp, ',');
            ficheiroPecas >> quantidade;
            getline(ficheiroPecas, temp);
            listaChegada2[i].marcas = marca;
            listaChegada2[i].categorias = categoria;
            listaChegada2[i].numSerie = capacidade;
            listaChegada2[i].preco = quantidade;
            i++;
        }
        ficheiroPecas.close();
    } else {
        cout << "Erro ao abrir o arquivo para carregar os dados das pecas do armazem." << endl;
    }
    return listaChegada2;
}

int leFicheiroCiclos(string nomeFicheiro) {
    int ciclos2;
    ifstream ficheiroCiclos(nomeFicheiro);
    if(ficheiroCiclos.is_open()) {
        ficheiroCiclos >> ciclos2;
        ficheiroCiclos.close();
    } else {
        cout << "Erro ao abrir o arquivo para carregar o numero de ciclos." << endl;
    }
    return ciclos2;
}

void carregarArmazem(int argc, const char* argv[], int numSecoes, int tamanholista){
    string ficheiroSeccoes;
    string ficheiroPecas;
    string ficheiroCiclos;
    string ficheiroSeccoes2;
    string ficheiroPecas2;
    string ficheiroCiclos2;
    cout << "Escolheu Carregar Armazem" << endl;
    if(argc == 1){
        cout<< "Qual o nome que contem as seccoes?";
        cin >> ficheiroSeccoes;
        cout<< "Qual o nome que contem as pecas?";
        cin >> ficheiroPecas;
        cout<< "Qual o nome que contem os ciclos?";
        cin >> ficheiroCiclos;
        seccoes* secoes2 = leFicheiroSeccoes(ficheiroSeccoes);
        Peca* listaChegada2 = leFicheiroPeca(ficheiroPecas);
        int ciclos2 = leFicheiroCiclos(ficheiroCiclos);
        int numSecoes2 = contarLinhas(ficheiroSeccoes);
        int tamanholista2 = contarLinhas(ficheiroPecas);
        imprimeSecLis(ciclos2, secoes2, listaChegada2, tamanholista2, numSecoes2);
    }else{
        ficheiroSeccoes2 = argv[1];
        ficheiroPecas2 = argv[2];
        ficheiroCiclos2 = argv[3];
        seccoes* secoes2 = leFicheiroSeccoes(ficheiroSeccoes2);
        Peca* listaChegada2 = leFicheiroPeca(ficheiroPecas2);
        int ciclos2 = leFicheiroCiclos(ficheiroCiclos2);
        int numSecoes2 = contarLinhas(ficheiroSeccoes2);
        int tamanholista2 = contarLinhas(ficheiroPecas2);
        imprimeSecLis(ciclos2, secoes2, listaChegada2, tamanholista2, numSecoes2);
    }
}

void ordenarPorPreco(Peca* listaChegada, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho-1; j++) {
            if (listaChegada[j].preco < listaChegada[j+1].preco){
                swap(listaChegada[j], listaChegada[j+1]);
            }
        }
    }
    // Imprime as peças ordenadas por preço
    for (int i = 0; i < tamanho; i++) {
        cout << "Marca: "  << listaChegada[i].marcas << " | " <<"Categoria: " << listaChegada[i].categorias<< " | " << "Numero de Serie: " << listaChegada[i].numSerie << " | "<< "Preco:" << listaChegada[i].preco << endl;
    }
}

void ordenarPorMarca(Peca* listaChegada, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho-1; j++) {
            if (listaChegada[j].marcas > listaChegada[j+1].marcas){
                swap(listaChegada[j], listaChegada[j+1]);
            }
        }
    }

    for (int i = 0; i < tamanho; i++) {
        cout << "Marca: "  << listaChegada[i].marcas << " | " <<"Categoria: " << listaChegada[i].categorias<< " | " << "Numero de Serie: " << listaChegada[i].numSerie << " | "<< "Preco:" << listaChegada[i].preco << endl;
    }
}

void imprimirArmazem(Peca* listaChegada, int tamanho) {
    bool sair = false;// Variável para sair do ciclo
    do {// Ciclo para escolher a opção
        char opcao;// Opção escolhida
            cout << "Escolha uma opcao: \n";
            cout << "1 - ordem por preco" << endl;
            cout << "2 - ordem alfabetica(marca)" << endl;
            cout << "0 - Sair" << endl;
            cin >> opcao;
            cout << endl;
            switch (opcao) {
                case '1':
                    ordenarPorPreco(listaChegada, tamanho) ;
                    break;
                case '2':
                    ordenarPorMarca(listaChegada, tamanho);
                    break;
                case '0':
                    cout << "Escolheu a opcao Sair. Adeus!" << endl;
                    sair = true;
                    break;
                default:
                    cout << "Escolha uma opcao valida." << endl;
            }
    }while (!sair);
}

void vendaPeca(seccoes* seccoes,int numSecoes){
    int probAleatoria = rand()%5+60;
    for (int i = 0; i < numSecoes; i++) {
        for (int j = 0; j < seccoes[i].quantidade; ++j) {
            if(seccoes[i].inventario[j].probVenda > probAleatoria){
                cout << "Venda efetuada com sucesso!" << endl;
                cout << "Produto vendido: " << seccoes[i].inventario[j].marcas << " | " << seccoes[i].inventario[j].categorias << " | " << "Numero de Serie: " << seccoes[i].inventario[j].numSerie << " | " << "Preco: " << seccoes[i].inventario[j].preco << endl;
                seccoes[i].vendaTotal += seccoes[i].inventario[j].preco;
                removePecaVenda(seccoes,seccoes[i].id,numSecoes,seccoes[i].inventario[j].numSerie);
                seccoes[i].quantidade--;
                break;
            }
        }
    }

}

void removePecaVenda(seccoes* secoes, int id,int numSecoes, int numSerie){
    int novoTamanho = secoes[id].quantidade - 1; // O novo tamanho será um elemento a menos
    Peca* novoInventario = new Peca[novoTamanho];

    int novaListaIndex = 0; // Índice para a nova lista

    for (int i = 0; i < numSecoes; ++i) {
        for (int j = 0; j < secoes[i].quantidade; ++j) {
            if (secoes[i].inventario[j].numSerie == numSerie) {
                // Ignorar a peça a ser removida
                continue;
            }
            novoInventario[novaListaIndex] = secoes[i].inventario[j];
            novaListaIndex++;
        }
    }

    // Liberar a memória do inventário antigo da seção
    delete[] secoes[id].inventario;

    // Apontar o inventário para o novo inventário
    secoes[id].inventario = new Peca[novoTamanho];
    for (int i = 0; i < novoTamanho; ++i) {
        secoes[id].inventario[i] = novoInventario[i];
    }

    // Atualizar o tamanho do inventário da seção
    secoes[id].quantidade = novoTamanho;

    // Liberar a memória do novo inventário
    delete[] novoInventario;

}
void removePecaDuplicada(seccoes* secoes, int secaoIndex, int pecaIndex) {
    // Cria um novo inventário com um tamanho menor
    int novoTamanho = secoes[secaoIndex].quantidade - 1;
    Peca* novoInventario = new Peca[novoTamanho];

    // Copia todas as peças do inventário antigo para o novo, exceto a peça duplicada
    int j = 0;
    for (int i = 0; i < secoes[secaoIndex].quantidade; i++) {
        if (i != pecaIndex) {
            novoInventario[j] = secoes[secaoIndex].inventario[i];
            j++;
        }
    }

    // Libera a memória do inventário antigo
    delete[] secoes[secaoIndex].inventario;

    // Atualiza o inventário e a quantidade da seção
    secoes[secaoIndex].inventario = novoInventario;
    secoes[secaoIndex].quantidade = novoTamanho;
}


//corrigir a criação das 5 novas pecas
//fazer a venda aleatoria
//rever numSecoes?

#pragma clang diagnostic pop