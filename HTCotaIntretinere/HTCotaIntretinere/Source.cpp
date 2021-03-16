#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct CotaIntretinere {
	char* adresa;
	int nrAp;
	int nrPers;
	int anul;
	int luna;
	float valoare;
};

CotaIntretinere initializareCota(const char* adresa, int nrAp, int nrPers, int anul, int luna, float valoare)
{
	CotaIntretinere c;
	c.adresa = (char*)malloc((strlen(adresa) + 1) * sizeof(char));
	strcpy(c.adresa, adresa);
	c.nrAp = nrAp;
	c.nrPers = nrPers;
	c.anul = anul;
	c.luna = luna;
	c.valoare = valoare;
	return c;
}

void afisareCota(CotaIntretinere c)
{
	printf("\nAdresa: %s, nr ap: %d, nr pers: %d, anul: %d, luna: %d, valoare: %5.2f", c.adresa, c.nrAp, c.nrPers, c.anul, c.luna, c.valoare);
}

struct Nod {
	CotaIntretinere info;
	Nod*next;
};

Nod* inserareNod(Nod* p, CotaIntretinere c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = p;
	return nou;
}

int functiaHash(int nrAp, int size)
{
	return nrAp % size;
}

void inserareHash(Nod**hashT, CotaIntretinere c,int size)
{
	int k = functiaHash(c.nrAp, size);
	hashT[k] = inserareNod(hashT[k], c);
}
void afisareHash(Nod**hashT, int size)
{
	for(int i=0;i<size;i++)
		if (hashT[i])
		{
			Nod*temp = hashT[i];
			while (temp)
			{
				printf("\nAdresa: %s, nr ap: %d, nr pers: %d, anul: %d, luna: %d, valoare: %5.2f", temp->info.adresa, temp->info.nrAp, temp->info.nrPers, temp->info.anul, temp->info.luna, temp->info.valoare);
				temp = temp->next;
			}
		}
}

float valoareTotalaAnuala(Nod**hashT, int size, int nrAp, int anul, const char* adresa)
{
	float sum = 0;
	int k = functiaHash(nrAp, size);
	if (hashT[k])
	{
		Nod* temp = hashT[k];
		while (temp)
		{
			if (temp->info.anul == anul && (strcmp(temp->info.adresa, adresa) == 0))
				sum += temp->info.valoare;
			temp = temp->next;
		}
	}
	return sum;
}

int numarCote(Nod** hashT, int size, float prag)
{
	int numar = 0;
	for(int i=0;i<size;i++)
		if (hashT[i])
		{
			Nod* temp = hashT[i];
			while (temp)
			{
				if (temp->info.valoare > prag)
					numar++;
				temp = temp->next;
			}
		}
	return numar;
}

void stergereHash(Nod **hashT, int size, int nrAp,const char* adresa)
{
	int k = functiaHash(nrAp, size);
	Nod*temp = hashT[k];
	if (strcmp(temp->info.adresa, adresa) == 0)
	{
		hashT[k] = temp->next;
		free(temp->info.adresa);
		free(temp);
	}
	else
	{
		while (temp->next)
		{
			if (strcmp(temp->next->info.adresa, adresa) == 0)
			{
				Nod*aux = temp->next;
				temp->next = aux->next;
				free(aux->info.adresa);
				free(aux); 
				return;
			}
			temp = temp->next;
		}
	}
}

void main()
{
	Nod**hashT;
	int size = 5;
	hashT = (Nod**)malloc(sizeof(Nod*)*size);
	for (int i = 0; i < size; i++)
		hashT[i] = 0;
	inserareHash(hashT, initializareCota(" garii, 701",45,2,2018,03,1200), size);
	inserareHash(hashT, initializareCota(" mocani, 250", 40, 3, 2018, 01, 1500), size);
	inserareHash(hashT, initializareCota(" florilor, 505", 23, 1, 2018, 06, 960), size);
	inserareHash(hashT, initializareCota(" garii, 701", 45, 2, 2018, 10, 1100), size);
	inserareHash(hashT, initializareCota(" liceului, 506", 20, 3, 2018, 12, 1250), size);
	afisareHash(hashT, size);

	printf("\n\nValoare totala: %5.2f", valoareTotalaAnuala(hashT, size, 45, 2018, " garii, 701"));
	printf("\n\nNumar cote care depasesc valoarea aleasa: %d", numarCote(hashT, size, 1200));

	stergereHash(hashT, size, 20, " liceului, 506");
	printf("\n\nDupa stergere: ");
	afisareHash(hashT, size);
}