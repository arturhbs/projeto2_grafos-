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
	string adjacentes;
	list<int> lista_materias;


}t_materia;

t_materia materia[50];

void CriarGrafo(){
	string	line;
	ifstream fp("materias.txt");
	int i=0, j;
	int valor, quantidade_materias_loop;
	while(!fp.eof()){
		getline(fp, line);
		stringstream is(line);
		is >> materia[i].codigo >> materia[i].nome >> materia[i].creditos >> materia[i].dificuldade >> quantidade_materias_loop;
		cout << materia[i].codigo << " " << materia[i].nome << " " << materia[i].creditos  << endl;
		j=0;
		while(j != quantidade_materias_loop ){
			is >> valor;
			materia[i].lista_materias.push_back(valor);
			getchar();
			j++;
		}
		/*for(auto v : materia[i].lista_materias){
			
		}*/

		i++;
		getchar();
	}
}


int main(){

	CriarGrafo();	


	return 0; 	
}
