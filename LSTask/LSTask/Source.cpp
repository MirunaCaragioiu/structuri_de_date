#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Task {
	int id;
	char* dataCreare;
	char* dataAsignare;
	char*inginerAsignat;
	int prioritate;
	char* stareTask;
};

Task createTask(int id, const char* dataCreare, const char*dataAsignare, const char*inginerAsignat, int prioritate, const char*stareTask)
{
	Task t;
	t.id = id;
	t.dataCreare = (char*)malloc((strlen(dataCreare) + 1) * sizeof(char));
	strcpy(t.dataCreare, dataCreare);
	t.dataAsignare = (char*)malloc((strlen(dataAsignare) + 1) * sizeof(char));
	strcpy(t.dataAsignare, dataAsignare);
	t.inginerAsignat = (char*)malloc((strlen(inginerAsignat) + 1) * sizeof(char));
	strcpy(t.inginerAsignat, inginerAsignat);
	t.prioritate = prioritate;
	t.stareTask = (char*)malloc((strlen(stareTask) + 1) * sizeof(char));
	strcpy(t.stareTask, stareTask);
	return t;
}

struct Nod {
	Task info;
	Nod*next;
};

Nod*inserareNod(Nod*l, Task t)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = t;
	nou->next = l;
	return nou;
}

Nod* inserareSfarsit(Nod*l, Task t)
{
	Nod*nou = inserareNod(NULL, t);
	if (l)
	{
		Nod*p = l;
		while (p->next)
			p = p->next;
		p->next = nou;
	}
	else
		l = nou;
	return l;
}

void afisareLista(Nod* l)
{
	while (l)
	{
		printf("\n\nId: %d, data creare: %s, data asignare: %s, inginer asignat: %s, prioritate: %d, stare task: %s", l->info.id, l->info.dataCreare, l->info.dataAsignare, l->info.inginerAsignat, l->info.prioritate, l->info.stareTask);
		l = l->next;
	}
}

int numarTask(Nod* l)
{
	int nr = 0;
	if (l)
	{
		Nod*p = l;
		while (p)
		{
			if ((strcmp(p->info.stareTask, "nou") == 0) || ((strcmp(p->info.stareTask,"deschis")==0)))
				nr++;
			p = p->next;
		}
	}
	return nr;
}


char** multime(Nod*l, const char* data, int&dim, char**&vector)
{
	if (l)
	{
		Nod*p = l;
		char** v = (char**)malloc(sizeof(char*)*(dim + 1));
		for (int i = 0; i < dim; i++)
			v[i] = vector[i];
		while (p)
		{
			if (strcmp(p->info.dataAsignare, data) == 0)
			{
				v[dim] = p->info.inginerAsignat;
				dim++;
				vector = v;
			}
			p = p->next;
		}
	}
	return vector;
}

void asigmTask(Nod* l, int id, const char*inginer)
{
	if (l)
	{
		Nod*p = l;
		while (p)
		{
			if (p->info.id == id)
			{
				strcpy(p->info.inginerAsignat ,inginer);
				if (strcmp(p->info.stareTask, "nou") == 0)
					strcpy(p->info.stareTask,"deschid");
			}
			p = p->next;
		}
	}
}

void main()
{
	Nod* l = NULL;
	l = inserareSfarsit(l, createTask(12, "12/04/2018", "12/05/2018", "Marian", 3, "nou"));
	l = inserareSfarsit(l, createTask(25, "14/07/2018", "21/08/2018", "Ionut", 4, "in lucru"));
	l = inserareSfarsit(l, createTask(41, "13/01/2018", "12/05/2018", "Cristina", 2, "inchis"));
	l = inserareSfarsit(l, createTask(32, "21/10/2018", "08/12/2018", "Ioana", 1, "rezolvat"));
	l = inserareSfarsit(l, createTask(70, "25/06/2018", "14/09/2018", "Laurentiu", 4, "nou"));
	afisareLista(l);

	printf("\n\nNr taskuri la care nu s a inceput lucrul: %d", numarTask(l));

	char**vector;
	int dim = 0;
	char**v = multime(l, "12/05/2018", dim, vector);
	printf("\n\nVector de ingineri cu data de asignare 12/05/2018: ");
	for (int i = 0; i < dim; i++)
		printf("%s ", v[i]);

	asigmTask(l, 70, "Mioara");
	printf("\n\nDupa schimbare inginer: ");
	afisareLista(l);

}

