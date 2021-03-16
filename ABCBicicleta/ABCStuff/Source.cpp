#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct Bicicleta {
	int id;
	int durataUtilizare;
	int idStatie;
	int nrUtilizariPeZi;
	char* nume;

};

struct Nod {
	Bicicleta info;
	Nod* st, *dr;
};

Nod* initializareNod(Bicicleta b, Nod*st, Nod*dr)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = b;
	nou->st = st;
	nou->dr = dr;
	return nou;
}

Nod* inserare(Nod* rad, Bicicleta b)
{
	if (rad)
	{
		if (rad->info.durataUtilizare > b.durataUtilizare)
			rad->st = inserare(rad->st, b);
		else
			rad->dr = inserare(rad->dr, b);
		return rad;
	}
	else
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = b;
		nou -> st = NULL;
		nou->dr = NULL;
		rad = nou;
		return rad;
	}
}

void ParseABC(Nod*rad)
{
	if (rad)
	{
		ParseABC(rad->st);
		printf("\nId: %d,durata: %d, id statoe: %d, nr utilizari: %d, nume: %s", rad->info.id, rad->info.durataUtilizare, rad->info.idStatie, rad->info.nrUtilizariPeZi, rad->info.nume);
		ParseABC(rad->dr);
	}
}

int durataUtilizare(Nod* rad)
{
	int sum = 0;
	if (rad)
	{
		sum += rad->info.durataUtilizare + durataUtilizare(rad->st) + durataUtilizare(rad->dr);
	}
	return sum;
}

int valoare(Nod* rad)
{
	int val = 0;
	if (rad)
	{
		val += (rad->info.durataUtilizare * 2 - (10 * rad->info.nrUtilizariPeZi))+valoare(rad->st)+valoare(rad->dr);
	}
	return val;
}


void main()
{
	Bicicleta b;
	FILE* f;
	char buffer[150];
	Nod* rad=NULL;

	f = fopen("biciclete.txt","r");
	fgets(buffer, sizeof(buffer), f);
	while (!feof(f))
	{
		b.id = atoi(buffer);
		fgets(buffer, sizeof(buffer), f);
		b.durataUtilizare = atoi(buffer);
		fgets(buffer, sizeof(buffer), f);
		b.idStatie = atoi(buffer);
		fgets(buffer, sizeof(buffer), f);
		b.nrUtilizariPeZi = atoi(buffer);
		fgets(buffer, sizeof(buffer), f);
		b.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(b.nume, buffer);

		rad = inserare(rad, b);

		fgets(buffer, sizeof(buffer), f);
	}

	ParseABC(rad);

	printf("\n\nDurata totala: %d", durataUtilizare(rad));
	printf("\n\Valoare totala: %d", valoare(rad));
}