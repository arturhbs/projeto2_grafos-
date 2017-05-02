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
	float creditos;
	float dificuldade;
	int quantidade_materias_loop;
	list<int> lista_materias;
	list<float> lista_valorAresta;
	

}t_materia;
/*variaveis globais --------------------------------------------------------------*/
t_materia materia[52];
t_materia materia_copia[52];
list<int> grauzero;	/*lista para gravar a ordem topologica utilizando Khan*/
/* ------------------------------------------------------------------------------*/
void CriarGrafo(){
	string	line;
	ifstream fp("materias.txt");
	int i=0, j;
	int valor;
	float valorAresta;
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
	for(i=0;i<52;i++){
		if(materia[i].quantidade_materias_loop != 0){ /*verificar apenas as materias que o grau é diferente de zero*/
			for (list<int>::iterator it=materia[i].lista_materias.begin(); it != materia[i].lista_materias.end(); ++it){/* pesquisar na lista de cada um se há a materia como pre-requisito*/
				valor =	*it;
				for(int k=0; k<52;k++){	/*fazer um loop nas materias já cadastradas para verificar com as da lista */
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

void PegarGrauZero(){
	int codigo_materia, i=0, j;
	bool ja_existe;

	while(i !=52 ){
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

				for(j=0;j<52; j ++){
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
	for(i=0;i<52;i++){
		cout <<"Codigo  = " <<materia[i].codigo ;
		if(!materia[i].lista_materias.empty()){		/* verifica se a lista de materias está vazia, ja que se estiver a de valor de aresta tambem estara*/
			cout << " Pre-requisito(s) = ";		
			list<int>::iterator it;
			list<float>::iterator it_aux;
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
		for(int i=0;i<52;i++){
			if(*it == materia[i].codigo){
				cout << " == " << materia[i].nome<<endl; ;
				break;
			}
		}
	}
}
typedef struct {
	list<int> lista;
}t_lista;
void CaminhoCritico(){
	int i , codigo_aux,code,  primeiro, j, contador, k, m , tamanho_lista, save, tamanho_listaAtual, acabou, entrou;

	list<int> lista_CaminhoCritico;
	t_lista lista_caminhos[34];
	for(i=0; i<52; i++){ /*percorre todas as materias */

		if(!materia_copia[i].lista_materias.empty()){ /* verifica qual delas tem pre requisito e coloca em uma lista*/
			codigo_aux = materia_copia[i].codigo;
			lista_CaminhoCritico.push_back(codigo_aux);
		}
	};

	m=0;
		i=1;
	for(list<int>::iterator it = lista_CaminhoCritico.begin(); it != lista_CaminhoCritico.end(); it ++){
		acabou =0;
		while(i<52 && acabou != 1){
			if(*it == materia_copia[i].codigo){

				primeiro = materia_copia[i].lista_valorAresta.front();
				if(materia_copia[i].lista_valorAresta.size() > 1){/*para caso tenha mais de uma aresta ligada*/
					j=0;/*percorre a lista das arestas para achar a com o peso maior*/
					for(list<float>::iterator it_listaAresta = materia_copia[i].lista_valorAresta.begin();it_listaAresta != materia_copia[i].lista_valorAresta.end(); it_listaAresta++){
						if(*it_listaAresta > primeiro){
							contador = j;
							primeiro = *it_listaAresta;
						}
						j++;
					}
					/*percorre a lista de materias para achar a materia que é a mesma do maior peso*/
					list<int>::iterator it_listaMateria;
					it_listaMateria = materia_copia[i].lista_materias.begin();
					tamanho_lista = materia_copia[i].lista_materias.size();
				 	k=0;
					while(k != tamanho_lista){
						if(k == contador){
							lista_caminhos[m].lista.push_back(*it_listaMateria);
							code = *it_listaMateria;
						}
						it_listaMateria++;
						k++;
					}
					
				}
				else{/*para caso tenha uma aresta ligada*/
			

					list<int>::iterator it_listaMateria;
					it_listaMateria = materia_copia[i].lista_materias.begin();
					lista_caminhos[m].lista.push_back(*it_listaMateria);
					code = *it_listaMateria;
					
				}
				for(int n=0;i<52;n++){ /*procura o codigo ligado e verifica se ele ainda tem pre-requisitos*/
					if(code == materia_copia[n].codigo){
						if(materia_copia[n].lista_materias.size() == 0){ /*se n tiver pre requisitos e acha e já sai do loop*/
							acabou =1;
	
						}
						else{
							acabou= 0;
							*it = code;
							entrou =1;
						}
						break;
					}

				}
			}
			if(entrou == 1){ /*tera de fazer outra procura na struct para achar o indice da nova materia*/
				i =0;
			}
			else{
				i++;
			}
			entrou=0;
		}
		m++;
	}
	i=0;

	int tamanho_final = lista_caminhos[i].lista.size();

	while(i!= 34){	
		tamanho_listaAtual = lista_caminhos[i].lista.size();
		if( tamanho_listaAtual > tamanho_final ){
			save = i;
			tamanho_final = tamanho_listaAtual;
		}
		i++;
	}
	for(list<int>::iterator la = lista_caminhos[save].lista.begin();la != lista_caminhos[save].lista.end(); la++){
		for(i=0;i<52;i++){
			if(*la == materia_copia[i].codigo){
				cout << " " << materia_copia[i].nome ;
				
			}
		}
	}
	cout << "\n Maior lista eh : " << tamanho_final << endl;


}

int main(){
	int escolha, aux, j=0;

	CriarGrafo();
	for(int i=0;i<52;i++){ /*fazer uma copia do grafo atual para poder modificar salvando o grafo original*/

		materia_copia[i].codigo = materia[i].codigo;
		materia_copia[i].nome = materia[i].nome;
		materia_copia[i].creditos = materia[i].creditos;
		materia_copia[i].dificuldade = materia[i].dificuldade;
		materia_copia[i].quantidade_materias_loop = materia[i].quantidade_materias_loop;
		for(list<int>::iterator it = materia[i].lista_materias.begin(); it!= materia[i].lista_materias.end();it++){
			aux = *it;
			materia_copia[i].lista_materias.push_back(aux);
			
		}
		for(list<float>::iterator it1 = materia[i].lista_valorAresta.begin(); it1!= materia[i].lista_valorAresta.end();it1++){
			aux = *it1;
			materia_copia[i].lista_valorAresta.push_back(aux);
			j++;
		}
	}
	PegarGrauZero();
	cout << "Escolha a opcao que deseja : \n 1- Printar grafo \n 2- Printar grafo em ordem topologica\n 3- CaminhoCritico\n ";

	cin >> escolha;

	switch(escolha){
		case 1 :  PrintarGrafo();
		break;
		case 2 :  PrintarOrdemTopologica();
		break;		
		case 3 :  CaminhoCritico();
	}	




	return 0; 	
}
