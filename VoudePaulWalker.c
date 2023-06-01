#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define N 100

typedef struct reg
{
    int conteudo;
    struct reg *prox;
} celula;

celula *LeInicio, *LeFim;
int vetor[N], Inicio, Fim;

void criaLista()
{
    Inicio = 0;
    Fim = -1;
}

void criaListaE()
{
    LeInicio = NULL;
    LeFim = NULL;
}

void insereLista(int valor)
{
    if (Fim == N - 1)
    {
        return;
    }
    Fim++;
    vetor[Fim] = valor;
}

celula *insereListaE(int valor, celula *fimAnterior)
{
    celula *novaCelula = (celula *)malloc(sizeof(celula));
    novaCelula->conteudo = valor;
    novaCelula->prox = NULL;

    if (fimAnterior != NULL)
        fimAnterior->prox = novaCelula;

    return novaCelula;
}

void imprimeListaE(celula *inicio)
{
    celula *aux = inicio;
    while (aux != NULL)
    {
    	
        printf("%d->", aux->conteudo);
        aux = aux->prox;
    }
}

int tamanhoListaE(celula *inicio)
{
    int tamanho = 0;
    celula *aux = inicio;
    while (aux != NULL)
    {
        tamanho++;
        aux = aux->prox;
    }
    return tamanho;
}

int statusListaVaziaE()
{
    return LeInicio == NULL;
}

void merge(int *vetor, int inicio, int meio, int fim)
{
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int *esquerda = (int *)malloc(n1 * sizeof(int));
    int *direita = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        esquerda[i] = vetor[inicio + i];
    for (int j = 0; j < n2; j++)
        direita[j] = vetor[meio + 1 + j];

    int i = 0;
    int j = 0;
    int k = inicio;

    while (i < n1 && j < n2){
        if (esquerda[i] <= direita[j])
        {
            vetor[k] = esquerda[i];
            i++;
        }
        else{
            vetor[k] = direita[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        vetor[k] = esquerda[i];
        i++;
        k++;
    }

    while (j < n2){
        vetor[k] = direita[j];
        j++;
        k++;
    }

    free(esquerda);
    free(direita);
}

void ordenaListaE(){
	
    celula *aux,*temp;
    int x;
    
for (aux=LeInicio; aux->prox != NULL; aux = aux->prox){
    	for(temp=LeInicio; temp->prox != NULL; temp = temp->prox){
        	if(temp->conteudo > temp->prox->conteudo)
        	{
        		x = temp->prox->conteudo;
            	temp ->prox->conteudo = temp->conteudo;
            	temp->conteudo = x;
        	}
    	}
	}
}

void imprimeLista()
{
    for (int i = Inicio; i <= Fim; i++)
    {
        printf(" %d->", vetor[i]);
    }
}

int statusListaVazia()
{
    return Inicio >= Fim;
}

celula *buscaRemoveListaE(int valor, celula *inicio)
{
    celula *anterior = NULL;
    celula *atual = inicio;

    while (atual != NULL)
    {
        if (atual->conteudo == valor)
        {
            if (anterior != NULL)
                anterior->prox = atual->prox;

            if (atual == LeInicio)
                LeInicio = atual->prox;

            if (atual == LeFim)
                LeFim = anterior;

            celula *proximo = atual->prox;
            free(atual);
            return proximo;
        }

        anterior = atual;
        atual = atual->prox;
    }

    return inicio;
}

int buscaPos(int p, int u, int Valor)
{
    if (p > u)
    {
        return p;
    }
    else
    {
        if (vetor[p] > Valor)
            return p;
        else
            buscaPos(p + 1, u, Valor);
    }
}

void insereLista2(int k, int Valor)
{
    for (int i = Fim; i >= k; --i){
        vetor[i + 1] = vetor[i];
    }
    vetor[k] = Valor;
    Fim++;
}

void insereLista2E(celula *LeInicio, int Valor)
{
	
	celula *nova = (celula *)malloc(sizeof(celula)), *aux=LeInicio;
	nova->conteudo = Valor;
	
	if(aux->prox == NULL){
		
		aux->prox = nova;
//		ordenaListaE();
	}else{
		if(aux->prox->conteudo < nova->conteudo){
			
				nova->prox = aux->prox;
				aux->prox = nova;
		}
		else insereLista2E(aux->prox, Valor);
	}
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int Senha, Pos;

    criaLista();
    criaListaE();

    do
    {
        printf("Informe senha de atendimento ou 0 para encerrar: ");
        scanf("%i", &Senha);

        insereLista(Senha);
        LeFim = insereListaE(Senha, LeFim);

        if (LeInicio == NULL)
            LeInicio = LeFim;

    } while (Senha != 0);

    Fim--;
    LeFim = buscaRemoveListaE(LeFim->conteudo, LeInicio);

    if (statusListaVaziaE() != 0)
        printf("Lista encadeada dinâmica vazia!\n");
    else
    {
        printf("\nA Lista encadeada dinâmica tem %d elementos:", tamanhoListaE(LeInicio));
        imprimeListaE(LeInicio);
    }

    if (statusListaVazia() != 0)
        printf("\nLista estática vazia!\n");
    else
    {
        printf("\nA Lista estática tem %d elementos:", Fim - Inicio + 1);
        imprimeLista();
        printf("\nOrganizando a lista dinamica em ordem crescente: ");
        ordenaListaE();
        imprimeListaE(LeInicio);
    }

    for (int i = 1; i < 4; i++)
    {
        if (statusListaVazia != 0)
        {
            insereLista2E(LeInicio, 10 * i);
        }
    }
    printf("\nA nova lista dinamica tem %d elementos:", Fim - Inicio + 1);
    imprimeListaE(LeInicio);

    return 0;
}
