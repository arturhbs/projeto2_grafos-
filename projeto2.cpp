/*Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao

Teroria e aplicação de grafos - 01/2017

Alunos(a): Artur Henrique Brandao de Souza	- 15/0118783 
		   Marcos Paulo Batalha Bispo - 15O154208
							
Versão do compilador: gcc(GCC) 4.8.1

Descricao:	Projeto2 = 
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
	

}t_materia;

t_materia materia[50];

void CriarGrafo(){
	string	line;
	ifstream fp("materias.txt");
	int i=0, j;
	int valor;
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
}

void PegarGrauZero(){
	list<int> grauzero;	/*lista para gravar a ordem topologica utilizando Khan*/
	int codigo_materia, i, j;
	

	for(i=0; i<35; i++ ){

		if(materia[i].quantidade_materias_loop == 0){ /*gravar os vertices que contem grau zero na lista 'grauzero' */
			codigo_materia = materia[i].codigo;
			grauzero.push_back(codigo_materia);
			
					 /*	for(int k=0;k<35; k++){	 TESTE MEU PARA VER OQ ESTÁ PRINTANDO
					 		if(materia[k].codigo == codigo_materia){
					 			cout << "Materia = "<<materia[k].nome << endl;
					 			break;
					 		}
					 	}
					 	getchar();*/
			for(j=0;j<35; j ++){
				if(materia[j].quantidade_materias_loop != 0){ /*verificar apenas as materias que o grau é diferente de zero*/
					for (list<int>::iterator it1=materia[j].lista_materias.begin(); it1 != materia[j].lista_materias.end(); ++it1){/* pesquisar na lista de cada um se há a materia como pre-requisito*/
					 	if(*it1 == codigo_materia){
					 		materia[j].quantidade_materias_loop = materia[j].quantidade_materias_loop -1;/*diminui o contador da materia*/	
					 		cout << "materia = " << materia[j].nome<< endl;
					 	}	
					}
				}	
			}
		} 

	}
	for (list<int>::iterator it=grauzero.begin(); it != grauzero.end(); ++it){/* printar lista de cada um*/
	 	cout << ' ' << *it << ' ';
		getchar();
	}

}


int main(){
	CriarGrafo();
	PegarGrauZero();


	return 0; 	
}
