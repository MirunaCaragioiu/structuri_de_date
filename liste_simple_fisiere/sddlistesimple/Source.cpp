#include <stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

struct Carte {
	int id;
	char nrAutori;
	char **Autori;
	char* titlu;
};

struct Nod {
	Carte book;
	Nod* next;
};

void parseList(Nod* l)
{
	while (l)
	{
		printf("Id carte: %d\n", l->book.id);
		printf("Titlu carte: %s\n", l->book.titlu);
		for (char i = 0; i < l->book.nrAutori; i++)
			printf("\t%s\n", l->book.Autori[i]);
		l = l->next;
	}
}

Carte createCarte(int id, const char* titlu)
{
	Carte c;
	c.id = id;
	c.titlu = (char*)malloc((strlen(titlu) + 1) * sizeof(char));
	strcpy(c.titlu, titlu);

	return c;
}

Carte citireCarte()
{
	Carte c;
	char buffer[50];
	printf("Titlu carte:");
	scanf("%s", buffer);
	c.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy_s(c.titlu, (strlen(buffer) + 1), buffer);
	printf("Id carte: ");
	scanf("%d", &c.id);
	return c;
}

Nod* inserareNodLista(Nod* l, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->book = c;
	nou->next = l;
	return nou;
}

Nod* inserareSfarsitLista(Nod* l, Carte c) 
{
	Nod* nou = inserareNodLista(NULL, c);
	if (l)
	{
		Nod* p = l;
		while (p->next)
			p = p->next;
		p->next = nou;
	}
	else {
		l = nou;
	}
	return l;
}

Nod* inserareSortata(Nod* l, Carte c) {
	Nod* p = l;
	Nod* pred;
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->book = createCarte(c.id, c.titlu);
	if (p) {
		if (p->next && p->book.id > c.id)
		{
			nodNou->next = l;
			return nodNou;
		}
		while (p->next && p->book.id < c.id) {
			pred = p;
			p = p->next;
		}

		if (p->book.id > c.id) {
			nodNou->next = p;
			pred->next = nodNou;
		}
		else {
			nodNou->next = NULL;
			p->next = nodNou;
		}

		return l;
	}
	else {
		nodNou->next = NULL;
		return nodNou;
	}
}

Nod* sortareBubble(Nod* l)
{
	if (!l || !l->next)
		return l;

	char vb = 1;
	Nod* p, *q, *r, *s;
	while (vb)
	{
		vb = 0;

		if (l->book.id > l->next->book.id)
		{
			p = l->next;
			q = p->next;
			l->next = q;
			p->next = l;
			l = p;
			vb = 1;
		}
		Nod* t = l;
		while (t->next->next) 
		{
			p = t->next;  
			q = p->next; 
			if (p->book.id > q->book.id)
			{
				r = q->next; 
				t->next = q;
				p->next = r;
				q->next = p;
				vb = 1;
			}
			t = t->next;
		}
	}
	return l;
}

Nod* dezalocareLista(Nod* l)
{
	while (l)
	{
		Nod* t = l; //nodul care se dezaloca
		l = l->next; //noul inceput de lista
		for (char i = 0; i < t->book.nrAutori; i++)
			free(t->book.Autori[i]); //dezalocare linie i din matricea de char (nume autori)
		free(t->book.Autori);

		free(t->book.titlu); //dezalocare heap seg pentru titlu carte
		free(t); //dezalocare nod
	}
	return l;
}

Nod* cautarePozitie(Nod*l, int poz)
{
	int i = 0;
	while (l != NULL && i < poz)
	{
		l = l->next;
		i++;
	}
	if (i == poz)
		return l;
	else
		return NULL;
}

void stergereNodPoz(Nod*l, int poz)
{
	if (poz == 0)
	{
		Nod* s = l;
		l = l->next;
		delete s;
	}
	else
	{
		Nod*pred = cautarePozitie(l, poz - 1);
		Nod* s = pred->next;
		if (pred->next->next)
		{
			pred->next = pred->next->next;
			delete s;
		}
		else
		{
			pred->next = NULL;
			delete s;
		}
	}
}

Nod* cautareValoare(Nod* l, int val)
{
	while (l != NULL && l->book.id != val)
		l = l->next;
	if (l->book.id == val)
		return l;
	else return NULL;
}

void stergereNodVal(Nod* &l, int val)
{
	if (l == NULL) return;
	if (l->book.id == val)
	{
		Nod* s = l;
		l = l->next;
		delete s;
	}
	Nod* s = cautareValoare(l, val);
	Nod* pred = l;
	while (pred->next != NULL && pred->next->book.id != val)
		pred = pred->next;
	if (pred->next->next)
	{
		pred->next = pred->next->next;
		delete s;
	}
	else
	{
		pred->next = NULL;
		delete s;
	}
}

void main()
{
	Carte temp;
	FILE *f;
	char buffer[150];
	Nod* list = NULL;

	f = fopen("Text.txt","r");
	fgets(buffer, sizeof(buffer), f);
	while (!feof(f))
	{
		temp.id = atoi(buffer);
		fgets(buffer, sizeof(buffer), f);
		temp.nrAutori = atoi(buffer);
		
		temp.Autori = (char**)malloc(temp.nrAutori * sizeof(char*));
		for (char i = 0; i < temp.nrAutori; i++)
		{
			fgets(buffer, sizeof(buffer), f);
			temp.Autori[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char*));
			strcpy(temp.Autori[i], buffer);
		}

		fgets(buffer, sizeof(buffer), f);
		temp.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(temp.titlu, buffer);

		list = inserareNodLista(list, temp);
		

		fgets(buffer, sizeof(buffer), f);
	}

	list = inserareSfarsitLista(list, createCarte(12,"Ana"));

	//parseList(list);

	list = sortareBubble(list);
	/*printf("\nlista dupa sortare:\n\n");
	parseList(list);*/

	list = inserareSortata(list, createCarte(48, "Buna"));
	printf("\nlista dupa sortare:\n\n");
	parseList(list);

	/*list = dezalocareLista(list);
	printf("\nLista dupa dezalocare:\n\n");*/
	//parseList(list);

	fclose(f);

	
}