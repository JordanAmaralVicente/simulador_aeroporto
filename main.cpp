#include<stdio.h>
#include<windows.h>
#include<ctype.h>
#include<time.h>

//define a estrutura aviao, uma lista encadeada com id e combustivel
typedef struct aviao{
	int id;
	int combustivel;
	struct aviao *prox; //aponta para o proximo que vira uma lista 
}aviao;

//define a estrutura pista, composta por duas filas de avioes
typedef struct pista{
	aviao *fila_1;
	aviao *fila_2;
	aviao *fila_3;
}pista;

//declaracoes
aviao * geraAviaoPar(void);
aviao * geraAviaoImPar(void);
pista * inserePista(pista *p, aviao *av);
int verificaFila(aviao *fila);
int verificaPista(pista *p);
aviao * insereLista(aviao *lista, aviao* av);
pista * geraPista(pista *p);
pista * removeCombustivel(pista *p);

int main(){
	pista *pista_1 = geraPista(pista_1), *pista_2 = geraPista(pista_2), *pista_3 = geraPista(pista_3);
	int qtdPouso_1, qtdPouso_2, qtdDecolagem_1, qtdDecolagem_2, qtdDecolagem_3;
	
	int tempo = 10;
	while(tempo != 0){
		
		pista_1 = removeCombustivel(pista_1);
		pista_2 = removeCombustivel(pista_2);
		pista_3 = removeCombustivel(pista_3);
		//gera os avioes aleatorios
		aviao * av1 = geraAviaoPar(); //para pouso
		aviao * av2 = geraAviaoPar(); //para pouso
		aviao * av3 = geraAviaoPar(); //para pouso
		aviao * av4 = geraAviaoImPar(); //para decolagem
		aviao * av5 = geraAviaoImPar(); //para decolagem
		aviao * av6 = geraAviaoImPar(); //para decolagem
			
		// verifica qual das duas pistas de pouso está menor 
		qtdPouso_1 = verificaPista(pista_1);
		qtdPouso_2 = verificaPista(pista_2);
		// verifica qual das pistas de decolagem está menor
		qtdDecolagem_1 = verificaFila(pista_1->fila_3);
		qtdDecolagem_2 = verificaFila(pista_1->fila_2);
		//
		
		tempo--;
	}
	return 0;
}

//funcoes 
pista * geraPista(pista *p){

	p = (pista*)malloc(sizeof(pista));
	p->fila_1 =(aviao*)malloc(sizeof(aviao));
	p->fila_1 = NULL;
	p->fila_2 =(aviao*)malloc(sizeof(aviao));
	p->fila_2 = NULL;
	p->fila_3 =(aviao*)malloc(sizeof(aviao));
	p->fila_3 = NULL;

	return p;
}
//gera o aviao completo
aviao * geraAviaoPar(void){

	aviao *novo = (aviao*)malloc(sizeof(aviao)); //aloca
	novo->combustivel = rand() % 20 + 1 ; //atribui um combustivel
	novo->id = ((rand() % 9999) * 2) + 1; //id que define pouso ou decolagem
	novo->prox = NULL;
	
	return novo;
}

aviao * geraAviaoImPar(void){
	aviao *novo = (aviao*)malloc(sizeof(aviao)); //aloca
	novo->combustivel = rand() % 20 + 1 ; //atribui um combustivel
	novo->id = (rand() % 9999) * 2; //id que define pouso ou decolagem
	novo->prox = NULL;
	
	return novo;
}

pista * inserePista(pista *p, aviao *av){

	aviao * auxFila_1 = p->fila_1; 
	aviao * auxFila_2 = p->fila_2; 
	
	// verifica a quantidade de avioes em cada fila 
	int aux1 = verificaFila(auxFila_1); 
	int aux2 = verificaFila(auxFila_2); 
	
	if(aux1 < aux2){
		p->fila_1 = insereLista(p->fila_1, av);
	}
	else if(aux2 < aux1){
		p->fila_2 = insereLista(p->fila_2, av);
	}
	
	return p;
}

aviao *insereLista(aviao * lista, aviao * av){ 
	
	if(lista == NULL){
		return av;
	}
	
	if (lista != NULL){
		aviao *p = lista;
		aviao *ant = NULL;
		
		while(p!=NULL){
			ant = p;
			p = p->prox;
		}
		ant->prox = av;
		
		return lista;
	}
}

//verifica qual pista está menor, porém so contando as pistas de pouso ////////////////////////////////////
int verificaPista(pista *p){
	if(p == NULL){
		return 0;
	}
	else{
		int aux1 = verificaFila(p->fila_1);
		int aux2 = verificaFila(p->fila_2);
		return aux1 + aux2;
	}
}
 // verifica qualquer lista/////////////////////////////////////////////////////////////////
int verificaFila(aviao *fila){
	
	int qtd = 0;
	if(fila != NULL){
		aviao *aux = fila;
		
		while(aux != NULL){
			qtd++;
			aux = aux->prox;			
		}
		
		return qtd;
	}else
		return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// Pronta e adequada
pista * removeCombustivel(pista *p){
	aviao *aux1  = p->fila_1;
	aviao *aux2  = p->fila_2;
	aviao *aux3  = p->fila_3;
	
	while(aux1 != NULL){
		aux1->combustivel--;
		aux1 = aux1->prox;
	}
	while(aux2 != NULL){
		aux2->combustivel--;
		aux2 = aux2->prox;
	}
	while(aux3 != NULL){
		aux3->combustivel--;
		aux3 = aux3->prox;
	}
	return p;
}
