/*Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao

Teroria e aplicação de grafos - 01/2017

Alunos(a): Artur Henrique Brandao de Souza	- 15/0118783 
		   Marcos Paulo Batalha Bispo - 15O154208
							
Versão do compilador: gcc(GCC) 4.8.1

Descricao:	Projeto2 = 
*/


#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;

typedef  struct materias{
	int *codigo;
	string nome;
	int *creditos;
	int *dificuldade;
	string adjacentes;
	list<materias> lista_materias;


}t_materia;

t_materia materia[50];

void CriarGrafo(){
	string line; 

	ifstream fp("materias.txt");
	if(fp.is_open()){	/*verifica se existe o arquivo, se ele realmente foi aberto*/
		while(!fp.eof()){
			getline(fp, line);
			cout << line << endl;
			getchar();
			scanf(%[^|])
			cin >>	
		}
	}
	else{
		cout << "Nao existe arquivo" << endl;
	}
	fp.close();
}

int main(){

	CriarGrafo();	


	return 0; 	
}
