#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Tara {
	char* nume;
	int nrLoc;
	float suprafata;
};

struct Nod {
	Tara inf;
	Nod* next;
	Nod* prev;
};

struct ListaD{
	Nod* primNod;
	Nod* ultimNod;
};

Tara createTara(const char* nume, int nrLoc, float suprafata)
{
	Tara t;
	t.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(t.nume, nume);
	t.nrLoc = nrLoc;
	t.suprafata = suprafata;
	return t;
}

Nod* initializareNod(Tara t, Nod* next, Nod* prev)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = t;
	nou->next = next;
	nou->prev = prev;
	return nou;
}

ListaD inseraraInceput(ListaD l, Tara t)
{
	Nod* nou = initializareNod(t, NULL, NULL);
	if (l.primNod == NULL)
	{
		l.primNod=nou;
		l.ultimNod = nou;
	}
	else {
		nou->next = l.primNod;
		l.primNod->prev = nou;
		l.primNod = nou;
	}
	return l;
}

ListaD inserareSfarsit(ListaD l, Tara t) 
{
	Nod* nou = initializareNod(t, NULL, NULL);
    if (l.ultimNod == NULL) 
	{
		l.primNod = nou;
		l.ultimNod = nou;
	}
	else {
		nou->prev = l.ultimNod;
		l.ultimNod->next = nou;
		l.ultimNod = nou;
	}
	return l;
}

ListaD inserareSortata(ListaD l, Tara t) {
	Nod*p = l.primNod;
	/*Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = createTara(t.nume, t.nrLoc,t.suprafata);*/
	Nod* nou = initializareNod(t, NULL, NULL);
	if (p) {
		if (p->next && p->inf.nrLoc > t.nrLoc)
		{
			nou->next = p;
			p->prev = nou;
			l.primNod = nou;
			return l;
		}
		while (p->next && p->inf.nrLoc < t.nrLoc) {
			p = p->next;
		}

		if (p->inf.nrLoc > t.nrLoc) {
			nou->prev = p->prev;
			p->prev->next = nou;
			nou->next = p;
			p->prev = nou;
		}
		else {
			nou->next = NULL;
			nou->prev= p;
			p->next = nou;
			nou = l.ultimNod;
		}
		return l;
	}
	else {
		l.primNod = l.ultimNod = nou;
		return l;
	}
}

ListaD stergereListaDubla(ListaD l) 
{
	while (l.primNod)
	{
		Nod* temp = l.primNod;
		free(l.primNod->inf.nume);	
		l.primNod = l.primNod->next;
		free(temp);
	}
	l.primNod= NULL;
	l.ultimNod = NULL;
	return l;
}

void afisareTara(Tara t) 
{
	printf("Tara %s are %d locuitori si o suprafata de %5.2f.\n", t.nume, t.nrLoc, t.suprafata);
}
	
void afisareLista(ListaD l) 
{
	while (l.primNod) {
		afisareTara(l.primNod->inf);
		l.primNod = l.primNod->next;
	}
}

void afisareListaInvers(ListaD l)
{
	while (l.ultimNod)
	{
		afisareTara(l.ultimNod->inf);
		l.ultimNod = l.ultimNod->prev;
	}
}

Nod* cautarePozitie(ListaD l, int poz)
{
	int i = 0;
	while (l.primNod != NULL && i < poz)
	{
		l.primNod = l.primNod->next;
		i++;
	}
	if (i == poz)
		return l.primNod;
}

void stergereNodPoz(ListaD l, int poz)
{
	if (poz == 0)
	{
		Nod* s = l.primNod;
		l.primNod = l.primNod->next;
		l.primNod->prev = NULL;
		delete s;
	}
	else {
		Nod*s = cautarePozitie(l, poz);
		if (s->next)
		{
			s->prev->next = s->prev->next->next;
			s->next->prev = s->next->prev->prev;
			delete s;
		}
		else
		{
			s->prev->next = NULL;
			delete s;
		}
	}
}

Nod* cautareValoare(ListaD l, int val)
{
	int i = 0;
	while (l.primNod != NULL && l.primNod->inf.nrLoc != val)
	{
		l.primNod = l.primNod->next;
		i++;
	}
	if (l.primNod->inf.nrLoc == val)
		return l.primNod;
}

void stergereNodVal(ListaD l, int val)
{
	if (l.primNod == NULL) return;
	if (l.primNod->inf.nrLoc == val)
	{
		Nod* s = l.primNod;
		l.primNod = l.primNod->next;
		l.primNod->prev = NULL;
		delete s;
	}
	Nod* s = cautareValoare(l,val);
	if (s->next)
	{
		s->prev->next = s->prev->next->next;
		s->next->prev = s->next->prev->prev;
		delete s;
	}
	else
	{
		s->prev->next = NULL;
		delete s;
	}
}

ListaD interschimbAdiacente(Nod *t, ListaD l) {
	Nod *q, *r, *s;
	if (t == l.primNod) {
		// t este primul nod in lista dubla
		r = t->next;
		s = r->next;
		t->next = s;
		t->prev = r;
		r->next = t;
		r->prev = NULL; // r devine primul nod

		if (s) {
			// lista contine cel putin 3 noduri
			s->prev = t;
		}
		else {
			// s = NULL; lista are doar 2 noduri care se interschimba
			l.ultimNod = t;
		}
		l.primNod = r;
	}
	else {
		// t in interiorul listei duble
		q = t->prev;
		r = t->next;
		s = r->next;
		if (t->next == l.ultimNod) {
			// t este penultimul nod
			l.ultimNod = t;
		}
		else {
			// exista s nod
			s->prev = t;
		}
		t->next = s;
		t->prev = r;
		r->next = t;
		r->prev = q;
		q->next = r;
	}
	return l;
}

ListaD sortBubble(ListaD l) {
	if (!l.primNod || !l.primNod->next) // lista nu are cel putin 2 noduri
		return l;
	char vb; // boolean pentru interschimb de noduri adiacente
	do {
		vb = 0;
		Nod *t = l.primNod;
		while (t && t->next) { // parsare lista de la primul la ultimul nod
			if (t->inf.nrLoc > t->next->inf.nrLoc) { // sortare crescatoare dupa id carte
				l = interschimbAdiacente(t, l);
				vb = 1;
			}
			else {
				t = t->next;
			}
		}

	} while (vb);
	return l;
}

void main()
{
	ListaD lista;
	lista.primNod = lista.ultimNod = NULL;
	lista = inserareSfarsit(lista, createTara("Ungaria", 2000, 300));
	lista = inserareSfarsit(lista, createTara("Bulgaria", 4000, 200));
	lista = inserareSfarsit(lista, createTara("Serbia", 6000, 100));
	lista = inserareSortata(lista, createTara("Romania", 3000, 200));
	afisareLista(lista);

	printf("\nInvers:\n");
	afisareListaInvers(lista);

	/*stergereNodPoz(lista, 1);
	printf("\nLista dupa stergere nod poz:\n");
	afisareLista(lista);*/

	/*stergereNodVal(lista, 6000);
	printf("\nLista dupa stergere nod val:\n");
	afisareLista(lista);*/

	lista = stergereListaDubla(lista);
	printf("\n Dupa dezalocare:");
	afisareLista(lista);
}