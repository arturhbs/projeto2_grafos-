/*Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao

Teroria e aplicação de grafos - 01/2017

Alunos(a): Artur Henrique Brandao de Souza	- 15/0118783 
		   Marcos Paulo Batalha Bispo - 15/O154208
							
Versão do compilador: gcc(GCC) 4.8.1

Descricao:	Projeto2 = Criar um grafo valorado com as matérias do curso , fazendo uma ordenação topoçógica e o caminho crítico do mesmo.
*/

#include <sstream> 

#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;

typedef  struct materias{
	int codigo;
	string nome;
	int creditos;
	int dificuldade;
	int quantidade_materias_loop;
	list<int> lista_materias;
	list<int> lista_valorAresta;
	

}t_materia;

t_materia materia[50];

void CriarGrafo(){
	string	line;
	ifstream fp("materias.txt");
	int i=0, j;
	int valor;
	int valorAresta;
	while(!fp.eof()){
		getline(fp, line);/*pega uma linha inteira do .txt*/
		stringstream is(line);/* 'is' passa a ser um tipo de leitura para a string no arquivo*/
		is >> materia[i].codigo >> materia[i].nome >> materia[i].creditos >> materia[i].dificuldade >> materia[i].quantidade_materias_loop;/*faz leitura de cada termo no .txt*/

		j=0;
		while(j != materia[i].quantidade_materias_loop ){ /* colocar o valor das materias que estão direcionadas em uma lista */
			is >> valor;
			materia[i].lista_materias.push_back(valor);/*coloca no final da lista*/
			j++;
		}

		
		i++;
	}
	for(i=0;i<35;i++){
		if(materia[i].quantidade_materias_loop != 0){ /*verificar apenas as materias que o grau é diferente de zero*/
			for (list<int>::iterator it=materia[i].lista_materias.begin(); it != materia[i].lista_materias.end(); ++it){/* pesquisar na lista de cada um se há a materia como pre-requisito*/
				valor =	*it;
				for(int k=0; k<35;k++){	/*fazer um loop nas materias já cadastradas para verificar com as da lista */
					if(materia[k].codigo == valor){
						valorAresta = materia[k].creditos * materia[k].dificuldade;	/* Valor da aresta = Creditos * dificuldade*/
						materia[i].lista_valorAresta.push_back(valorAresta);/*colocar o valor final na lista*/
						break;
					}
				} 
			}
		}
	}

}

	list<int> grauzero;	/*lista para gravar a ordem topologica utilizando Khan*/
void PegarGrauZero(){
	int codigo_materia, i=0, j;
	bool ja_existe;

	while(i !=35 ){
		ja_existe = false;
		if(materia[i].quantidade_materias_loop == 0){ /*gravar os vertices que contem grau zero na lista 'grauzero' */
			for(list<int>::iterator it= grauzero.begin(); it!= grauzero.end(); it++){/*percorre a lista grauzero */
				if(materia[i].codigo == *it){/*verifica se a materia testada ja esta no arquivo*/
					ja_existe = true;/*se ja estiver no arquivo, ela marca que já está*/
					break;
				}
			}
			if(ja_existe == false){ /*caso a materia não esteja na lista como verificado antes, entra para ser colocado na lista*/

				codigo_materia = materia[i].codigo;
				grauzero.push_back(codigo_materia);/*coloca o codigo da materia no final da lista*/ 
				i=-1;/*ao ele colocar um novo elemento na lista grauzero , ele voltara nas materias e verificara se tem alguma materia que ficou para trás, caso o arquivo texto ja nao esteja em uma ordem topológica previamente*/

				for(j=0;j<35; j ++){
					if(materia[j].quantidade_materias_loop != 0){ /*verificar apenas as materias que o grau é diferente de zero*/
						for (list<int>::iterator it1=materia[j].lista_materias.begin(); it1 != materia[j].lista_materias.end(); ++it1){/* pesquisar na lista de cada um se há a materia como pre-requisito*/
						 	if(*it1 == codigo_materia){
						 		materia[j].quantidade_materias_loop = materia[j].quantidade_materias_loop -1;/*diminui o contador da materia*/	
						 	}	
						}
					}	
				}
			}
		} 
		i++;
	}
}

void PrintarGrafo(){

	int i;
	for(i=0;i<35;i++){
		cout <<"Codigo  = " <<materia[i].codigo ;
		if(!materia[i].lista_materias.empty()){		/* verifica se a lista de materias está vazia, ja que se estiver a de valor de aresta tambem estara*/
			cout << " Pre-requisito(s) = ";		
			list<int>::iterator it;
			list<int>::iterator it_aux;
			it = materia[i].lista_materias.begin();	/*pegar o primeiro elemento da lista de materias*/
			it_aux = materia[i].lista_valorAresta.begin(); /*pegar o primeiro elemento da lista dos valores das arestas*/
			while(it != materia[i].lista_materias.end()){
				cout << " <-- " << *it_aux << " -- " << *it; 
				it++;
				it_aux++;
			}
		}
		cout << "\n";
	}
}

void PrintarOrdemTopologica(){
	int j=1;	
	for(list<int>::iterator it= grauzero.begin(); it!= grauzero.end(); it++){
		cout << *it ;
		for(int i=0;i<35;i++){
			if(*it == materia[i].codigo){
				cout << " == " << materia[i].nome<<endl; ;
				break;
			}
		}
		j++;
	}
	cout << " j == " << j << endl;	
}


int main(){
	int escolha;

	CriarGrafo();
	PegarGrauZero();

	cout << "Escolha a opcao que deseja : \n 1- Printar grafo \n 2- Printar grafo em ordem topológica\n ";

	cin >> escolha;

	switch(escolha){
		case 1 :  PrintarGrafo();
		break;
		case 2 :  PrintarOrdemTopologica();
		break;		
		
	}	




	return 0; 	
}
