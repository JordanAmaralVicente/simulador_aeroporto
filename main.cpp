// Aeroporto.cpp : define o ponto de entrada para o aplicativo do console.
//DeclaraÃ§Ãµes

#include<stdio.h>
#include<windows.h>
#include<ctype.h>
#include<time.h>

typedef struct aviao {
    int fuel;
    int ID;
    struct aviao *prox;
}aviao;

typedef struct pista {
    aviao *f1, *f2, *f3;
    int qtd1, qtd2, qtd3;
}pista;

typedef struct {
    int atualPar, atualImpar;
}Estatistica;

int geracaoFuel();
int geracaoAviao();
int verifica_fila(pista *p);
pista * remove_fila(int f, pista *p);
aviao *gerar_Aviao(bool tipo);
pista *Insere_Aviao(pista *alvo, bool tipo);
int Escolhe_pista(pista *p1, pista *p2);
void imprimeFila(pista *alvo);
pista * geraPista(pista *p);
pista * removeCombustivel(pista *p);
pista * Remove_Aviao_Pista(pista *alvo);
pista *procuraVoid(pista *alvo);
pista *remove_comeco(pista *alvo);

Estatistica estatistica;

int main() {
    estatistica.atualImpar = 1;
    estatistica.atualPar = 0;
	
	
    bool tipo;
    int tempo = 100, escolha, sorteioPouso, sorteioDecolagem, tira1, tira2;

    pista * pista1 = NULL;
    pista1 = geraPista(pista1);
    pista * pista2 = NULL;
    pista2 = geraPista(pista1);
    pista * pista3 = NULL;
    pista3 = geraPista(pista1);

    srand(time(NULL));
    while (tempo != 0) {
		
		
        sorteioPouso = geracaoAviao();
        
        tipo = false;
		printf("Chegaram %02d avioes para pouso e ", sorteioPouso);
        for (int x = 0; x < sorteioPouso; x++) {
            escolha = Escolhe_pista(pista1, pista2);
            if (escolha == 1)
                pista1 = Insere_Aviao(pista1, tipo);
            else
                pista2 = Insere_Aviao(pista2, tipo);
        }

        sorteioDecolagem = geracaoAviao();
        tipo = true;
        printf("Chegaram %02d avioes para decolagem\n", sorteioDecolagem);
        for (int x = 0; x < sorteioDecolagem; x++)
            pista3 = Insere_Aviao(pista3, tipo);

        /*
        Se de todas as 4 filas de pouso, um aviao estiver na reserva, este irÃ¡ pousar na pista 3, portanto nesta rodada nÃ£o haveram decolagens.
        Se mais de um aviao em alguma das 4 filas estiver na reserva, estes deveram pousar nas duas 2 pistas.
        */

        //2 na fila 1,   1 na fila dois,  4 na fila 3,  

        printf("Pista 1\n\n");
        imprimeFila(pista1);
        printf("Pista 2\n\n");
        imprimeFila(pista2);
        printf("Pista 3\n\n");
        imprimeFila(pista3);


        //Funcoes para remover avioes com 0 de combustivel	
        pista1 = procuraVoid(pista1);
        pista2 = procuraVoid(pista2);

        pista3 = remove_comeco(pista3);

        removeCombustivel(pista1);
        removeCombustivel(pista2);

        tempo--;
        tira1 = verifica_fila(pista1);
		tira2 = verifica_fila(pista2);
        printf("%d ***** %d\n", tira1, tira2);
		pista1 = remove_fila(tira1, pista1);
        pista2 = remove_fila(tira2, pista2);
		system("pause");
        system("cls");
    }
    printf("%d\t%d\t%d\n", pista1->qtd1, pista1->qtd2, pista1->qtd3);
    printf("%d\t%d\t%d\n", pista2->qtd1, pista2->qtd2, pista2->qtd3);
    printf("%d\t%d\t%d\n", pista3->qtd1, pista3->qtd2, pista3->qtd3);
}



extern Estatistica estatistica;
extern int pouso;

pista * geraPista(pista *p) {

    p = (pista*)malloc(sizeof(pista));
    p->f1 = (aviao*)malloc(sizeof(aviao));
    p->f1 = NULL;
    p->f2 = (aviao*)malloc(sizeof(aviao));
    p->f2 = NULL;
    p->f3 = (aviao*)malloc(sizeof(aviao));
    p->f3 = NULL;

    p->qtd1 = 0;
    p->qtd2 = 0;
    p->qtd3 = 0;

    return p;
}

pista * removeCombustivel(pista *p) {
    aviao *aux1 = p->f1;
    aviao *aux2 = p->f2;

    while (aux1 != NULL) {
        aux1->fuel--;
        aux1 = aux1->prox;
    }
    while (aux2 != NULL) {
        aux2->fuel--;
        aux2 = aux2->prox;
    }
    return p;
}

aviao *gerar_Aviao(bool tipo) {
    aviao *novo = (aviao*)malloc(sizeof(aviao));
    novo->prox = NULL;

    if (tipo) {
        novo->ID = estatistica.atualImpar;
        estatistica.atualImpar += 2;
        novo->fuel = 24;
    }
    else {
        novo->ID = estatistica.atualPar;
        estatistica.atualPar += 2;
        novo->fuel = geracaoFuel();
    }

    return novo;
}

pista *Insere_Aviao(pista *alvo, bool tipo) {
    aviao *novo = gerar_Aviao(tipo);
    aviao *aux = NULL, *ant = NULL;
    int indicadorFila; //se i = 1 (f1) se i = 2 (f2) se i = 3 (f3)

                       //	printf("ID: %d FUEL: %d\n",novo->ID,novo->fuel);

    if (!tipo) {
        if (alvo->qtd1 <= alvo->qtd2) {
            aux = alvo->f1;
            indicadorFila = 1;
            alvo->qtd1 += 1;
        }
        else {
            aux = alvo->f2;
            indicadorFila = 2;
            alvo->qtd2 += 1;
        }
    }
    else {
        aux = alvo->f3;
        indicadorFila = 3;
        alvo->qtd3 += 1;
    }

    if (alvo->f1 == NULL && indicadorFila == 1) {
        alvo->f1 = novo;
        return alvo;
    }
    else if (alvo->f2 == NULL && indicadorFila == 2) {
        alvo->f2 = novo;
        return alvo;
    }
    else if (alvo->f3 == NULL && indicadorFila == 3) {
        alvo->f3 = novo;
        return alvo;
    }

    while (aux != NULL) {
        ant = aux;
        aux = aux->prox;
    }

    ant->prox = novo;

    return alvo;
}

pista *remove_comeco(pista *alvo) {
    aviao *aux = alvo->f3;

    if (aux == NULL)
        return alvo;

    alvo->f3 = aux->prox;
    free(aux);

    alvo->qtd3--;

    return alvo;
}

aviao *remove_aviao(aviao *alvo, int id) {
    aviao *ant = NULL;
    aviao *aux = alvo;

    if (alvo == NULL)
        return alvo;


    while (aux != NULL && aux->ID != id) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux != NULL) {
        if (ant == NULL)
            alvo = aux->prox;
        else
            ant->prox = aux->prox;

        free(aux);
    }

    return alvo;
}

pista *procuraVoid(pista *alvo) {
    aviao *aux1 = alvo->f1;
    aviao *aux2 = alvo->f2;
    int *remocaoF1 = NULL, *remocaoF2 = NULL, auxiliarRemocao1 = 0, auxiliarRemocao2 = 0;

    while (aux1 != NULL) {
        if (aux1->fuel == 0) {
            remocaoF1 = (int *)realloc(remocaoF1, (auxiliarRemocao1 + 1) * sizeof(int));
            remocaoF1[auxiliarRemocao1] = aux1->ID;
            auxiliarRemocao1++;
        }
        aux1 = aux1->prox;
    }

    while (aux2 != NULL) {
        if (aux2->fuel == 0) {
            remocaoF2 = (int *)realloc(remocaoF2, (auxiliarRemocao2 + 1) * sizeof(int));
            remocaoF2[auxiliarRemocao2] = aux2->ID;
            auxiliarRemocao2++;
        }
        aux2 = aux2->prox;
    }


    for (int i = 0; i < auxiliarRemocao1; i++) {
        alvo->f1 = remove_aviao(alvo->f1, remocaoF1[i]);
        alvo->qtd1--;
    }

    for (int x = 0; x < auxiliarRemocao2; x++) {
        alvo->f2 = remove_aviao(alvo->f2, remocaoF2[x]);
        alvo->qtd2--;
    }

    free(remocaoF1);
    free(remocaoF2);

    return alvo;
}

int geracaoFuel() {
    int newFuel = rand() % 20 + 1;
    return newFuel;
}

int geracaoAviao() {
    int newAviao = rand() % 3;
    return newAviao;
}

int Escolhe_pista(pista *p1, pista *p2) {
    if ((p1->qtd1 + p1->qtd2) == (p2->qtd1 + p2->qtd2)) {
        return 1;
    }
    else if ((p1->qtd1 + p1->qtd2)<(p2->qtd1 + p2->qtd2)) {
        return 1;
    }
    else if ((p1->qtd1 + p1->qtd2)>(p2->qtd1 + p2->qtd2)) {
        return 2;
    }
    return 0;
}

void imprimeFila(pista *alvo) {
    aviao *aux1 = alvo->f1;
    aviao *aux2 = alvo->f2;
    aviao *aux3 = alvo->f3;

    puts("Fila 1: ");
    while (aux1 != NULL) {
		printf("ID: %d  FUEL: %d\n", aux1->ID, aux1->fuel);
        aux1 = aux1->prox;
    }
    printf("\n");
	
    puts("Fila 2: ");
    while (aux2 != NULL) {
		printf("ID: %d  FUEL: %d\n", aux2->ID, aux2->fuel);
        aux2 = aux2->prox;
    }
    printf("\n");

    puts("Fila 3: ");
    while (aux3 != NULL) {
		printf("ID: %d\n", aux3->ID);
        aux3 = aux3->prox;
    }
    printf("\n");
}

int verifica_fila(pista *p){

	aviao *p1 = p->f1;
	aviao *p2 = p->f2;
	aviao *p3 = p->f3;
	
	
	int cont1=0, cont2=0, cont3=0;
	
	if(p1 != NULL && p2 != NULL && p3 != NULL){
		if(p1->fuel == 1){
			return 1;
		}
		else if(p2->fuel == 1){
			return 2;
		}
		else if(p3->fuel == 1){
			return 3;
		}
		else{
			for(p1 = p->f1; p1 != NULL; p1 = p1->prox){
				cont1 += p1->fuel;
			}
			
			for(p2 = p->f2; p2 != NULL; p2 = p2->prox){
				cont2 += p2->fuel;
			}
			for(p3 = p->f3; p3 != NULL; p3 = p3->prox){
				cont3 += p3->fuel;
			}
			
			if((cont1<cont2)&&(cont1<cont3)){
				return 1;
			}else if((cont1<cont2)&&(cont1>cont3)){
				return 3;
			}else if((cont1>cont2)&&(cont1>cont3)){
				if(cont3>cont2){
					return 2;
				}else if(cont2>cont3){
					return 3;
				}else{
					return 2;
				}
			}else{
				p1 = p->f1;
				p2 = p->f2;
				p3 = p->f3;
				
			printf("1\n");
			system("PAUSE");
				if((p1->fuel<p2->fuel)&&(p1->fuel<p3->fuel)){
					return 1;
				}else if((p1->fuel<p2->fuel)&&(p1->fuel>p3->fuel)){
					return 3;
				}else if((p1->fuel>p2->fuel)&&(p1->fuel>p3->fuel)){
					if(p3->fuel>p2->fuel){
						return 2;
					}else if(p2->fuel>p3->fuel){
						return 3;
					}else{
						return 2;
					}
				}
			}
		}
	}else if(p1!= NULL && p2!= NULL && p3 == NULL){
		if(p1->fuel == 1){
			return 1;
		}
		else if(p2->fuel == 1){
			return 2;
		}
		for(p1 = p->f1; p1 != NULL; p1 = p1->prox){
			cont1 += p1->fuel;
		}
	    for(p2 = p->f2; p2 != NULL; p2 = p2->prox){
			cont2 += p2->fuel;
		}
		if(cont1<cont2){
			return 1;
		}
		else if(cont1>cont2){
			return 2;
		}else{
			p2 = p->f2;
			p1 = p->f1;
			int comb1 = p1->fuel;
			int comb2 = p2->fuel;
			if(comb2 < comb1){
				return 2;
			}else if(comb2 > comb1){
				return 1;
			}else{
				return 2;
			}
		}
	}else if(p1!= NULL && p2 == NULL && p3 != NULL){	
		if(p1->fuel == 1){
			return 1;
		}
		else if(p3->fuel == 1){
			return 3;
		}
		for(p1 = p->f1; p1 != NULL; p1 = p1->prox){
			cont1 += p1->fuel;
		}
	    for(p3 = p->f3; p3 != NULL; p3 = p3->prox){
			cont3 += p3->fuel;
		}
		
		if(cont1<cont3){
			return 1;
		}
		else if(cont1<cont3){
			return 3;
		}else{
			p1 = p->f1;
			p3 = p->f3;
			if(p1->fuel < p3->fuel){
				return 1;
			}else if(p1->fuel > p3->fuel){
				return 3;
			}else{
				return 1;
			}
		}
	}else if(p1 == NULL && p2!= NULL && p3 != NULL){
		if(p2->fuel == 1){
			return 2;
		}
		else if(p3->fuel == 1){
			return 3;
		}
		for(p2 = p->f2; p2 != NULL; p2 = p2->prox){
			cont2 += p2->fuel;
		}
	    for(p3 = p->f3; p3 != NULL; p3 = p3->prox){
			cont3 += p3->fuel;
		}
		
		if(cont2<cont3){
			return 2;
		}
		else if(cont2<cont3){
			return 3;
		}else{
			printf("ULTIMO\n");
			system("PAUSE");
			p2 = p->f2;
			p3 = p->f3;
			printf("p2: %d , p3: %d",p2->fuel, p3->fuel );
			if(p2->fuel < p3->fuel){
				return 2;
			}else if(p2->fuel > p3->fuel){
				return 3;
			}else{
				return 2;
			}
		}
	}
	if(p1!= NULL && p2 == NULL & p3 == NULL){
		return 1;
	}
	if(p1== NULL && p2 != NULL & p3 == NULL){
		return 2;
	}
	if(p1== NULL && p2 == NULL & p3 != NULL){
		return 3;
	}
	if(p == NULL){
		return 0;
	}
}

pista * remove_fila(int f, pista *p){
	if(f ==1){
		aviao *ant = p->f1;
		aviao *aux = ant->prox;
		free(p->f1);
		p->f1 = aux;
		return p;
	} if(f ==2){
		aviao *ant = p->f2;
		aviao *aux = ant->prox;
		free(p->f2);
		p->f2 = aux;
		return p;
	}if(f ==3){
		if(p->f3->prox == NULL){
			free(p->f3);
			p->f3 = NULL;
			return p;
		}
		aviao *ant = p->f3;
		aviao *aux = ant->prox;
		free(p->f3);
		p->f3 = aux;
		return p;
	}
	
	return p;
}
