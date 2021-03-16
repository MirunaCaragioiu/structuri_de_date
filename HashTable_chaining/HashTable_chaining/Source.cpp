#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct Telefon {
	char*serie;
	int memorie;
};

struct Nod {
	Telefon inf;
	Nod* next;
};

struct HashTable {
	Nod* *vector;
	int dim;
};

Telefon createTelefon(const char* serie, int memorie)
{
	Telefon t;
	t.memorie = memorie;
	t.serie = (char*)malloc((strlen(serie) + 1) * sizeof(char));
	strcpy(t.serie, serie);
	return t;
}

void afisareTelefon(Telefon t)
{
	printf("Telefonul seria %s are memoria= %d\n", t.serie, t.memorie);
}

Nod* inserareInceput(Nod* l, Telefon t)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = createTelefon(t.serie, t.memorie);
	nou->next = l;

	return nou;
}

int hashFunction(const char* serie, int dim)
{
	int suma = 0;
	for (int i = 0; i < strlen(serie); i++)
		suma += serie[i];
	return suma % dim;
}


HashTable createHashTable(int dim)
{
	HashTable ht;
	ht.dim = dim;
	ht.vector = (Nod**)malloc(sizeof(Nod*)*dim);
	for (int i = 0; i < dim; i++)
		ht.vector[i] = NULL;
	return ht;
}

int inserareHash(Telefon t, HashTable ht)
{
	if (ht.dim > 0)
	{
		int hash = hashFunction(t.serie, ht.dim);
		if (ht.vector[hash])
			ht.vector[hash] = inserareInceput(ht.vector[hash], t);
		else
			ht.vector[hash] = inserareInceput(ht.vector[hash], t);
		return hash;
	}
	else
	{
		return -1;
	}
}

void afisareHash(HashTable ht)
{
	for (int i = 0; i < ht.dim; i++)
		if (ht.vector[i])
		{
			Nod* p = ht.vector[i];
			while (p)
			{
				afisareTelefon(p->inf);
				p = p->next;
			}
		}
}

void stergereHash(HashTable * ht)
{
	for (int i = 0; i < ht->dim; i++)
	{
		Nod*p = ht->vector[i];
		while (p)
		{
			free(p->inf.serie);
			Nod*aux = p;
			p = p->next;
			free(aux);
		}
	}
	free(ht->vector);
	ht->dim = 0;
	ht->vector = NULL;
}

Telefon cautareDupaSerie(const char* serie, HashTable ht)
{
	if (ht.vector) {
		int pozitie = hashFunction(serie, ht.dim);
		Nod*p = ht.vector[pozitie];
		while (p&&strcmp(serie, p->inf.serie) != 0) {
			p = p->next;
		}
		if (p) {
			return p->inf;
		}
	}
	else {
		return createTelefon("", 0);
	}
}

void main()
{
	HashTable ht = createHashTable(5);
	inserareHash(createTelefon("RX23", 10), ht);
	inserareHash(createTelefon("UQU25", 6), ht);
	inserareHash(createTelefon("OPW54", 8), ht);
	inserareHash(createTelefon("ASD41", 2), ht);
	inserareHash(createTelefon("RX25", 100), ht);

	afisareHash(ht);

	Telefon cautat = cautareDupaSerie("ASD41", ht);
	if (cautat.serie)
	{
		printf("\nTelefonul cautat este: ");
		afisareTelefon(cautat);
	}
	else printf("\nNu s-a gasit teelfonul cautat");

	system("pause");
}
