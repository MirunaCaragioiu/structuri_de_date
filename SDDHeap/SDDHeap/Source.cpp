#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

struct CardAcces {
	int prioritate;
	char* cod;
	int durataValabilitate;
	float credit;
	float* istoricValidari;
};

struct Heap {
	CardAcces* vector;
	int dim;
};

void filtrare(Heap heap, int pozitie)
{
	int fiuSt = 2 * pozitie + 1;
	int fiuDr = 2 * pozitie + 2;
	int max = pozitie;
	if (fiuSt < heap.dim && heap.vector[max].prioritate < heap.vector[fiuSt].prioritate)
		max = fiuSt;
	if (fiuDr < heap.dim && heap.vector[max].prioritate < heap.vector[fiuDr].prioritate)
		max = fiuDr;
	if (max != pozitie)
	{
		CardAcces aux = heap.vector[max];
		heap.vector[max] = heap.vector[pozitie];
		heap.vector[pozitie] = aux;
		if (2 * max + 1 < heap.dim)
			filtrare(heap, max);
	}
}

CardAcces inserareHeap(Heap& heap, CardAcces ca)
{
	if (heap.dim >= 0)
	{
		CardAcces* temp = (CardAcces*)malloc(sizeof(CardAcces)*(heap.dim + 1));
		for (int i = 0; i < heap.dim; i++)
			temp[i] = heap.vector[i];
		temp[heap.dim] = ca;
		free(heap.vector);
		heap.vector = temp;
		heap.dim++;
		for (int i = (heap.dim - 1) / 2; i >= 0; i--)
			filtrare(heap, i);
	}
	return ca;
}

void afisareHeap(Heap heap)
{
	for (int i = 0; i < heap.dim; i++)
	{
		printf("\nprioritate: %d, cod: %s, durata: %d, credit: %5.2f", heap.vector->prioritate, heap.vector->cod, heap.vector->durataValabilitate, heap.vector->credit);
		for (int j = 0; heap.vector[i].istoricValidari[j] != NULL; j++)
			printf(" 5.2f ", heap.vector[i].istoricValidari[j]);
	}

}

void main()
{
	CardAcces ca;
	Heap heap;
	heap.dim = 3;
	heap.vector = (CardAcces*)malloc(sizeof(CardAcces)*heap.dim);
	FILE* f;
	char buffer[150];
	f = fopen("carduri.txt", "r");
	fgets(buffer, sizeof(buffer), f);
	while (!feof(f))
	{
		ca.prioritate = atoi(buffer);
		fgets(buffer, sizeof(buffer), f);
		ca.cod = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(ca.cod, buffer);
		fgets(buffer, sizeof(buffer), f);

		ca.durataValabilitate = atoi(buffer);
		fgets(buffer, sizeof(buffer), f);
		ca.credit = atof(buffer);

		for(int i=0;i<heap.dim;i++)
			heap.vector[i] = inserareHeap(heap, ca);

		fgets(buffer, sizeof(buffer), f);

	}

	afisareHeap(heap);
}