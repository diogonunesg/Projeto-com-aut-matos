#include <math.h>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <map>
#define fore(i,n) for(int i = 0; i < n; i++)
#define TAM 7


/*
Tarefa em andamento:
    AFNDG

Tarefas concluídas:
	Classe AFND, AFD e Autômatos, Reinaldo
	Criar nova classe AFNDG (Com um novo estado inicial e um estado final fixo) ou criar método que transforma de AFND em AFNDG - Reinaldo

Tarefas a serem feitas:

	1) Funções de busca

		Interessante usarmos sobrecarga de método aqui.

		Sch(qi,a,qj,M0) = {(qi,a,qj) : (qi,a,qj) ? ?} (1.8)

		Sch(qi,qj,M0) = {(qi,a,qj) : (qi,a,qj) ? ?} (1.9)

		Sch(qi,M0) = {(qi,a,q00) : (qi,a,q00) ? ?} (1.10)

		Sch(qj,M0) = {(q0,a,qj) : (q0,a,qj) ? ?} (1.11)

		Sch(qi,a,M0) = {(qi,a,q00) : qi,a,q00) ? ?} (1.12)

		Sch(qj,a,M0) = {(q0,a,qj) : (q0,a,qj) ? ?} (1.13)

		Sch(a,M0) = {(q0,a,q00) : (q0,a,q00) ? ?} (1.14)
	2) Função de inserção
	3) Função de remoção
	4) Sequência positiva e sequência negativa
	5) Criar um par ordenado tal que (Sequência positiva, sequência negativa)


Recados:

Galera se sintam a vontade para modificar ou para tomar iniciativas.
Não precisamos nos limitar ao ponto de estabelecer uma liderança para a parte de implementação e sim cada um tomando a iniciativa quando achar conveniente.

Conforme forem concluindo nossas metas coloquem elas na parte de metas concluídas e que foi você que fez para que saibamos com quem falar como exemplifiquei.
Detalhes sobre a implementação e discursões sobre a engenharia de software acho legal fazer no face para se tornar mais dinâmico.



Ex de entrada:

2
0 1
3
q1 q2 q3
7
q1 0 q2
q1 1 q2
q2 1 q2
q2 0 q1
q2 1 q3
q3 0 q2
q3 u q1
1
q1
1
q2
AFND 1

*/

using namespace std;

class Automato
{

protected:
    vector< vector< bitset<TAM> > > tabelaDeTransicoes;

public:
    string nome;
    map <string, int> Alfabeto,
    Estados,
    estadosIniciais,
    estadosFinais;

    Automato(string nome2, map <string, int> A, map <string, int> B, vector< vector< bitset<TAM> > > C, map <string, int> D, map <string, int> E)
    {
        nome = nome2;
        Alfabeto = A;
        Estados = B;
        tabelaDeTransicoes = C;
        estadosIniciais = D;
        estadosFinais = E;
        toANFDG();
    }
    void toANFDG(){

        vector< bitset<TAM> > aux(Alfabeto.size());
        //vector< vector< bitset<TAM> > > aux(1, vector< bitset<TAM> >(Alfabeto.size()));
        tabelaDeTransicoes.push_back(aux);
        tabelaDeTransicoes.push_back(aux);
        int posicaoInicial = Estados.size();
        pair <string, int> estadoInicial ("Inicial", posicaoInicial);
        Estados.insert(estadoInicial);
        int posicaoFinal = Estados.size();
        pair <string, int> estadoFinal ("Final", posicaoFinal);
        Estados.insert(estadoFinal);

        map <string, int> :: iterator it;
        it = estadosIniciais.begin();
        bitset <TAM> auxInicial;
        for(it ; it != estadosIniciais.end(); it++){
            auxInicial[it->second] = 1;
        }
        tabelaDeTransicoes[posicaoInicial][Alfabeto.size() - 1] = auxInicial;

        it = estadosFinais.begin();

        bitset <TAM> auxFinal;
        for(it ; it != estadosFinais.end(); it++){
            auxFinal[it->second] = 1;
        }

        tabelaDeTransicoes[posicaoFinal][Alfabeto.size() - 1] = auxFinal;

        estadosIniciais.clear();
        estadosFinais.clear();
        estadosIniciais.insert(estadoInicial);
        estadosFinais.insert(estadoFinal);



    }

    void getEstados()
    {
        cout << nome << endl << "Estados: " << endl;
        map <string, int> :: iterator it = Estados.begin();

        for(it; it != Estados.end(); it++)
        {
            cout << it->first << " " << it->second << endl;
        }
    }

    void getEstadosIniciais()
    {
        cout << nome << endl << "Estados Iniciais: " << endl;
        map <string, int> :: iterator it = estadosIniciais.begin();

        for(it; it != estadosIniciais.end(); it++)
        {
            cout << it->first << " " << it->second << endl;
        }

    }

    void getEstadosFinais()
    {
        cout << nome << endl << "Estados Finais: " << endl;
        map <string, int> :: iterator it = estadosFinais.begin();

        for(it; it != estadosFinais.end(); it++)
        {
            cout << it->first << " " << it->second << endl;
        }

    }


    void getTabelaTransicao()
    {
        cout << nome << endl << "Tabela de Transicao: " << endl;
        fore(i, tabelaDeTransicoes.size())
        {
            cout << i << " ";
            fore(j, tabelaDeTransicoes[i].size())
            {
                cout << tabelaDeTransicoes[i][j] << " ";
            }
            cout << endl;
        }
    }

    string imprimeBIT(bitset<TAM> &vetor)
    {
        string saida = "";
        fore(i, vetor.size())
        {
            if(vetor[i])
            {
                string estado;
                map <string, int> :: iterator it = Estados.begin();
                for(it; it != Estados.end(); it++)
                {
                    if(it->second == i)
                    {
                        saida += it-> first;
                        saida += " ";
                    }
                }
            }
        }
        return saida;
    }



};

class AFD: public Automato
{
public:
    AFD(string nome, map <string, int> A, map <string, int> B, vector< vector< bitset<TAM> > > C, map <string, int> D, map <string, int> E): Automato(nome, A, B, C, D, E)
    {
    }
};

class AFND: public Automato
{
public:

    AFND(string nome, map <string, int> A, map <string, int> B, vector< vector< bitset<TAM> > > C, map <string, int> D, map <string, int> E ): Automato(nome, A, B, C, D, E)
    {
    }


    //Funcao que converte de não determinístico para determinístico
    AFD AFND2FND()
    {
        map <string, int> a;
        bitset <TAM> estados;


        //Gerando o conjunto das partes
        int N = pow(2,Estados.size());  //Quantidade de estados do FND

        int contador = 0;

        conjuntoDasPartes.insert(pair<string,int> (estados.to_string(), contador++));
        fore(i, N - 1)
        {
            buildEstadosFND(estados, N, conjuntoDasPartes, contador);
        }
        map <string, int> :: iterator it = conjuntoDasPartes.begin();

        string nomeFND = nome + " FND";
        int qtdAlfabeto = Alfabeto.size();
        int qtdEstados = conjuntoDasPartes.size();

        vector< bitset<TAM> > estadosAFD;

        it = conjuntoDasPartes.begin();

        //Colocando em uma map por questão de padronização
        for(it; it != conjuntoDasPartes.end(); it++)
        {
            bitset<TAM> aux (it->first);
            estadosAFD.push_back(aux);
        }


        it = conjuntoDasPartes.begin();


        //Gerando a Tabela de Transiação do FND
        vector< vector< bitset<TAM> > > tabTransicaoFND(estadosAFD.size(), vector< bitset<TAM> >(qtdAlfabeto));
        fore(i, estadosAFD.size())
        {

            vector<int> setados = checarSetados(estadosAFD[i], qtdEstados);
            fore(j, qtdAlfabeto)
            {
                bitset<TAM> alf;
                alf.set(); //seta todo mundo para 1.
                fore(k, setados.size())
                {
                    alf = alf & tabelaDeTransicoes[setados[k]][j];
                }
                tabTransicaoFND[i][j] = alf;
            }
        }

        map <string, int> estadosFinaisAFD;
        it = estadosFinais.begin();

        for(it; it != estadosFinais.end(); it++){
                int posFinal = it->second;
                map <string, int> :: iterator it2 = conjuntoDasPartes.begin();
                for(it2; it2 != conjuntoDasPartes.end(); it2++){
                    string aux = it2->first;
                    bitset <TAM> aux2 (aux);
                    if(aux2[posFinal]){
                        pair <string, int> x (it2->first, it2->second);
                        estadosFinaisAFD.insert(x);
                    }

                }

        }

        AFD AFD2 = AFD(nomeFND, Alfabeto, conjuntoDasPartes, tabTransicaoFND, estadosIniciais, estadosFinaisAFD);
        return AFD2;
    }

private:

    map <string, int> conjuntoDasPartes;


    //Método para construir o conjunto das partes
    void buildEstadosFND(bitset <TAM> &estados, int n, map <string, int> &vetor, int &contador)
    {

        int i = 0;
        while( i < n )
        {
            if(estados[i])
            {
                estados.flip(i++);
            }
            else
            {
                estados.flip(i);
                break;
            }

        }

        if(i == n)
        {
            cout << "Overflow" << endl;
        }
        else
        {
            vetor.insert(pair <string, int>(estados.to_string<char,std::string::traits_type,std::string::allocator_type>(), contador++));
        }
    }

    vector<int> checarSetados(bitset<TAM> set, int qtdEstados)
    {

        vector<int> resp;

        fore(i, qtdEstados)
        {
            if(set[i]) resp.push_back(i);
        }

        return resp;

    }


};
void trataVazio2(vector< vector< bitset<TAM> > > &transicoes, int i, bitset<TAM> cEstado, int vazio)
{

    int qtdEstados = transicoes.size();
    int qtdSimbolos = transicoes[0].size();
    vector<bool> mark(qtdEstados, false);
    queue<int> fila;

    for(int j=0; j<TAM; j++)
    {
        if(cEstado[j])
        {
            fila.push(j);
            mark[j] = true;
        }
    }

    while(!fila.empty())
    {
        int e = fila.front();
        fila.pop();
        bitset<TAM> aux = transicoes[e][vazio];
        for(int j=0; j<TAM; j++)
        {
            if(aux[j])
            {
                if(!mark[j])
                {
                    mark[j] = true;
                    fila.push(j);
                }
            }
        }
    }

    for(int j=0; j<qtdEstados; j++)
    {
        if(mark[j])
        {
            for(int p=0; p<qtdSimbolos; p++)
            {
                transicoes[i][p] = transicoes[i][p] | transicoes[j][p];
            }
        }
    }



}

void trataVazio(vector< vector< bitset<TAM> > > &transicoes, int vazio, int qtdEstados, int qtdAlfabeto)
{

     vector<bool> mark(qtdEstados, false);

    /* Tratar partindo com vazio */
    fore(i, transicoes.size())
    {
        if (transicoes[i][vazio].count())  /* Se o estado i receber algum símbolo vazio */
        {
            mark[i] = true;
            bitset<TAM> cEstado = transicoes[i][vazio]; //Seleciona todos os estados em que o estado i se liga através do vazio.
            trataVazio2(transicoes, i, cEstado, vazio);
        }
    }


    /* Tratar chegando com vazio */
    fore(i, transicoes.size()){
      fore(j, qtdAlfabeto-1){
         fore(k, mark.size()){
            if(mark[k] && transicoes[i][j][k]){
              transicoes[i][j] = transicoes[i][j] | transicoes[k][qtdAlfabeto-1];
            }
         }
      }
    }

    /* Imprime o AFND depois de ajeitar os vazios */
    cout<<"Tabela AFND: "<<endl;
    for(int i=0; i<transicoes.size(); i++)
    {
        for(int j=0; j<transicoes[i].size()-1; j++)
        {
            cout<<transicoes[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

}


int main()
{
    map <string, int> Alfabeto;
    map <string,int> Estados;


    //Quantidade de símbolos no alfabeto
    int qtdAlfabeto, qtdEstados, qtdTransicoes;
    cin >> qtdAlfabeto;

    //Entrada de símbolos no alfabeto
    fore(i, qtdAlfabeto)
    {
        string simbolo;
        cin >> simbolo;
        Alfabeto.insert(pair <string,int> (simbolo, i));
    }
    // Inserindo o -1 que irá representa o símbolo vazio
    Alfabeto.insert(pair <string,int> ("-1", qtdAlfabeto));
    qtdAlfabeto++;

    //Quantidade de estados
    cin >> qtdEstados;

    //Leitura dos estados
    fore(i,qtdEstados)
    {
        string estado;
        cin >> estado;
        Estados.insert(pair <string,int> (estado, i));
    }

    vector< vector< bitset<TAM> > > grafo(qtdEstados, vector< bitset<TAM> >(qtdAlfabeto));
    //Quantidade de Transições
    cin >> qtdTransicoes;
    //Ler as transições
    fore(i,qtdTransicoes)
    {
        string origem, simbolo, destino;
        cin >> origem >> simbolo >> destino;
        if(Alfabeto.find(simbolo) == Alfabeto.end())  /* Caso seja o símbolo vazio */
        {
            simbolo = "-1";
        }
        int origemid = (Estados.find(origem))->second;
        int destinoid = (Estados.find(destino))->second;
        int simboloid = (Alfabeto.find(simbolo))->second;
        grafo[origemid][simboloid].set(destinoid); /* Se estiver no estado origemid e chegar o símboloid então vai para o estado destinoid. */
    }
    //Quantidade de estados iniciais
    int qtdEstadosIniciais;
    cin >> qtdEstadosIniciais;
    map <string, int> estadosIniciais, estadosFinais;

    //Leitura dos estados iniciais
    fore(i, qtdEstadosIniciais)
    {
        string estadoInicial;
        cin >> estadoInicial;
        map <string, int> :: iterator it;
        int auxFinal;
        it = Estados.begin();
        for(it ; it != Estados.end(); it++){
            if(it->first == estadoInicial) auxFinal = it->second;
        }
        estadosIniciais.insert(pair<string,int> (estadoInicial, i));
    }

    //Quantidade de estados finais
    int qtdEstadosFinais;
    cin >> qtdEstadosFinais;

    //Leitura dos estados finais
    fore(i, qtdEstadosFinais)
    {
        string estadoFinal;
        cin >> estadoFinal;
        int auxFinal;
        map <string, int> :: iterator it;
        it = Estados.begin();
        for(it ; it != Estados.end(); it++){
            if(it->first == estadoFinal) auxFinal = it->second;
        }
        estadosFinais.insert(pair<string,int> (estadoFinal, auxFinal));

    }
    //Um nome para o autômato
    string nome;
    cin >> nome; /* Nome do Autômato Finito Não-Determinístico */

 //Tratar o vazio
    string simbolo = "-1";
    int simboloid = (Alfabeto.find(simbolo))->second;
    //trataVazio(grafo, simboloid, qtdEstados, qtdAlfabeto);

    AFND novo = AFND(nome, Alfabeto, Estados, grafo,estadosIniciais, estadosFinais);

    //Transformando um AFND em AFD
    novo.getEstados();
    novo.getEstadosFinais();
    novo.getTabelaTransicao();

    /*   */
}
