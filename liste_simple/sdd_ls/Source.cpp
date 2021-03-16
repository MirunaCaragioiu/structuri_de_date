#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct Carte {
	int id;
	char *titlu;
};

struct Nod {
	Carte book;
	Nod * next;
};

Carte createCarte(int id,const char* titlu)
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

Nod* inserareNod(Nod* l, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->book = c;
	//nou->book.titlu = (char*)malloc((strlen(c.titlu) + 1) * sizeof(char));
	//strcy_s(nou->book.titlu, (strlen(c.titlu) + 1), c.titlu);
	nou->next = l;
	return nou;
}

Nod* InserareSfarsit(Nod* l, Carte c)
{
	Nod* nou = inserareNod(NULL,c);
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
			nodNou->next =l;
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

void afisareLista(Nod* l)
{
	while (l)
	{
		printf("Id carte:%d , titlu carte:%s\n", l->book.id, l->book.titlu);
		l = l->next;
	}
}

Nod* dezalocareLista(Nod* l)
{
	while (l)
	{
		Nod* t = l; 
		l = l->next; 
		free(t->book.titlu); 
		free(t); 
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
	//Carte c = createCarte(21,"Acasa");
	//Nod* nod = inserareNod(NULL,c);
	Nod* l = NULL;

	l = InserareSfarsit(l, createCarte(12, "Iarna"));
	l = InserareSfarsit(l, createCarte(45, "Acasa"));
	l = InserareSfarsit(l, createCarte(5, "Toamna"));
	l = InserareSfarsit(l, createCarte(47, "Ulita"));
	l = InserareSfarsit(l, createCarte(52, "Ion"));
	l = inserareNod(l, createCarte(41, "Vara"));
	//l = inserareNod(l,citireCarte());
	

	l = sortareBubble(l);
	l = inserareSortata(l, createCarte(3, "Soare"));
	afisareLista(l);

	stergereNodPoz(l,6);
	printf("\nDupa stergere:\n");
	afisareLista(l);

	stergereNodVal(l, 12);
	printf("\nDupa stergere:\n");
	afisareLista(l);
}