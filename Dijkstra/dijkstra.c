#include <stdio.h>

void imprime_matriz(unsigned int n, unsigned int X[n][n])
{
	int i,j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d\t", X[i][j]);
		}
		printf("\n");
	}
}

void matriz_de_arquivo(unsigned int n, unsigned int adjacencias[n][n], char* caminho)
{
	int i, j;
	
	FILE *f;
  	f = fopen(caminho, "r");
	
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n; j++)
		{
			if (!fscanf(f, "%d", &adjacencias[i][j])) 
           		break;
		}	
	}

	fclose(f);

}

void busca_em_largura(unsigned int n, unsigned int adjacencias[n][n], unsigned int raiz)
{
	
  int verificado[n];
  int vetor[n];
  int i, j = 0;
  
  for (i = 0; i < n; i++){

    vetor[i] = -1;
    verificado[i] = 0;

  }

  vetor[0] = raiz;
  verificado[raiz] = 1;
  j++;
  
  for(i = 0; i < n; i++){
  	
    if(vetor[i] == -1){
	
		break;
	
	}

    raiz = vetor[i];
    int x;
    for(x = 0; x < n; x++){
    	
    	if(adjacencias[x][raiz] != 0 && (verificado[raiz] == 0 || verificado[x] == 0)){

	      vetor[j] = x;
	      verificado[x] = 1;
	      j++;
	
	    }
    	
	}
    

  }
  
  if (j == 1){
    
    printf("Busca em Largura: ");
  	printf("%d", raiz);
  	return;
  
  }

  printf("Busca em Largura: ");	
  for(i = 0; i < n; i++){
  
  	printf("%d ", vetor[i]);
  
  }
}

void busca_em_profundidade(unsigned int n, unsigned int adjacencias[n][n], unsigned int raiz)
{
	printf("imprime vertices usando busca em profundidade, a partir do vertice raiz\n");
}

void push(unsigned int n, unsigned int* cabeca, unsigned int* cauda, unsigned int fila[n], unsigned int valor)
{
	// caso da fila cheia
	if ( (*cauda - *cabeca) == (n - 1) )
	{
		printf("Fila cheia!\n");
	} else
	{
		// caso da fila vazia
		if (*cabeca > *cauda)
		{
			*cabeca = 0;
			*cauda = 0;
		} else 
		{
			*cauda = *cauda + 1;		
		}
		fila[*cauda % n] = valor;
	}
	
}

int pop(unsigned int n, unsigned int* cabeca, unsigned int* cauda, unsigned int fila[n])
{
	unsigned int retorno;
	
	if (*cabeca > *cauda)
	{
		printf("Fila vazia!\n");
		return -1;
	}
	
	retorno = fila[*cabeca % n];
	*cabeca = *cabeca + 1;
	return retorno;
}

void testaPesos(unsigned int n, unsigned int raiz, unsigned int matriz[n][n], int pesosNos[n]){
	
	int i;
	for (i = 0; i < n; i++){
	
		if(matriz[raiz][i] != 0 && matriz[raiz][i] + pesosNos[raiz]  < pesosNos[i]){
		
			pesosNos[i] = matriz[raiz][i] + pesosNos[raiz];
					
		}		
	
	}
	
	return;

}

void menorCaminho(unsigned int n, unsigned int raiz, unsigned int matriz[n][n], unsigned int destino, unsigned int caminho[n]){

	int visitados[n];
	int pesosSomar[n];
	
	int i;
	for (i = 0; i < n; i++){
	
		visitados[i] = 0;
	
	}
		
	int pesosNos[n];
	
	for (i = 0; i < n; i++){
		
		if (i == raiz){
		
			pesosNos[i] = 0;
		
		} else {
		
			pesosNos[i] = 999999;
		
		}		
	
	}
	
	int posicaoAtual = raiz;
	
	i = -1;
	while (posicaoAtual != destino){
	
		i++;
		testaPesos(n, raiz, matriz, pesosNos);
		
		int menor = 999999;
		int indice;
		
		int j;
		for(j = 0; j < n; j++){
			
			if (pesosNos[j] < menor && visitados[j] == 0){
				
				menor = pesosNos[j];
				indice = j;
				
			}
			
		}		
		
		int indice_visitado = raiz;
		visitados[indice_visitado] = 1;
		
		pesosSomar[i] = menor;
		
		raiz = indice;
		caminho[i] = indice;
		
		posicaoAtual = raiz;
		
	
	}
	
	return;	

}

int main()
{
	
	unsigned int n = 5;
	unsigned int adjacencias[n][n];
	
	matriz_de_arquivo(n, adjacencias, "grafoGerado.txt");
	
	imprime_matriz(n, adjacencias);
	
	unsigned int vetorCaminho[n];
	menorCaminho(n, 1, adjacencias, 3, vetorCaminho);
	 
	int i;
	for(i = 0; i < n; i++){
		
		printf("| %d |", vetorCaminho[i]);
		
	}
	
	//busca_em_largura(n, adjacencias, 3);
	//busca_em_profundidade(n, adjacencias, 3);
	
	//unsigned int cabeca = 0;
	//unsigned int cauda = -1;
	//unsigned int fila[n];
	
	// teste da fila
	/* 
	push(n, &cabeca, &cauda, fila, 7);
	push(n, &cabeca, &cauda, fila, 2);
	push(n, &cabeca, &cauda, fila, 9);
	push(n, &cabeca, &cauda, fila, 8);
	push(n, &cabeca, &cauda, fila, 5);
	push(n, &cabeca, &cauda, fila, 11);
	push(n, &cabeca, &cauda, fila, 22);
	
	printf("%d\n", pop(n, &cabeca, &cauda, fila));
	printf("%d\n", pop(n, &cabeca, &cauda, fila));
	printf("%d\n", pop(n, &cabeca, &cauda, fila));
	printf("%d\n", pop(n, &cabeca, &cauda, fila));
	printf("%d\n", pop(n, &cabeca, &cauda, fila));
	printf("%d\n", pop(n, &cabeca, &cauda, fila));
	
	push(n, &cabeca, &cauda, fila, 11);
	push(n, &cabeca, &cauda, fila, 22);
	
	printf("%d\n", pop(n, &cabeca, &cauda, fila));
	printf("%d\n", pop(n, &cabeca, &cauda, fila)); */
		
	return 0;
}
