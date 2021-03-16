#include<string.h>
#include<malloc.h>
#include<stdio.h>

struct Magazin
{
	int idMagazin;
	char* denumire;
	char* localitate;
	float suprafata;
	int nrAngajati;
};
Magazin creareMagazin(int idMagazin, char* denumire, char*localitate, float suprafata, int nrAngajati)
{
	Magazin m;
	m.idMagazin = idMagazin;
	m.denumire = (char*)malloc(sizeof(char)*(strlen(denumire )+ 1));
	strcpy(m.denumire, denumire);
	m.localitate = (char*)malloc(sizeof(char)*(strlen(localitate) + 1));
	strcpy(m.localitate, localitate);
	m.suprafata = suprafata;
	m.nrAngajati = nrAngajati;
	return m;
}

void afisareMagazin(Magazin m)
{
	printf("\nIdMagazin: %d", m.idMagazin);
	printf("\nDenumire: %s", m.denumire);
	printf("\nLocalitate: %s", m.localitate);
	printf("\nSuprafata: %5.2f", m.suprafata);
	printf("\nNrAngajati: %d", m.nrAngajati);
}
struct NodLS;
struct NodLP
{
	Magazin info;
	NodLP* next;
	NodLS* vecini;
};
struct NodLS
{
	Magazin nodAdiacent;
	int pondere;
	NodLS* next;
};
NodLP* inserareLP(NodLP* l, Magazin m)
{
	
	NodLP* nou = (NodLP*)malloc(sizeof(NodLP));
	nou->next = NULL;
	nou->info = creareMagazin(m.idMagazin, m.denumire, m.localitate, m.suprafata, m.nrAngajati);
	nou->vecini = NULL;
	if (l)
	{NodLP* temp = l;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = nou;
		return l;
	}
	else return nou;
}
NodLS* inserareLS(NodLS*l, Magazin m,int pondere)
{
	NodLS* nou = (NodLS*)malloc(sizeof(NodLS));
	nou->next = NULL;
	nou->pondere = pondere;
	nou->nodAdiacent = creareMagazin(m.idMagazin, m.denumire, m.localitate, m.suprafata, m.nrAngajati);
	if (l)
	{
		NodLS* temp = l;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = nou;
		return l;
	}
	else return nou;

}

NodLP* cautareNod(NodLP* l, int cod)
{
	NodLP* temp = l;
	while (temp)
	{
		if (temp->info.idMagazin == cod)
		{
			return temp;

		}
		temp = temp->next;
	}
}

void inserareArcInGraf(NodLP* graf, Magazin start, Magazin stop,int pondere)
{
	NodLP* nodStart = cautareNod(graf, start.idMagazin);
	NodLP* nodStop = cautareNod(graf, stop.idMagazin);
	if (nodStart != NULL && nodStop != NULL)
	{
		nodStart->vecini = inserareLS(nodStart->vecini, nodStop->info, pondere);
		nodStop->vecini = inserareLS(nodStop->vecini, nodStart->info, pondere);
	}
}
void afisareLS(NodLS* l)
{
	if (l)
	{
		NodLS* temp = l;
		while (temp)
		{
			printf(" %d",temp->nodAdiacent.idMagazin);
			printf(" ponderea %d", temp->pondere);
			temp = temp->next;
		}
	}
}
void afisareLP(NodLP* l)
{
	if (l)
	{
		NodLP* tmp = l;
		while (tmp)
		{
			NodLS* temp = tmp->vecini;
			while (temp)
			{printf("\n\nNodul %d", tmp->info.idMagazin);
			printf(" are vecinul ");
				printf(" %d", temp->nodAdiacent.idMagazin);
				printf(" ponderea %d", temp->pondere);
				temp = temp->next;
			}
			tmp = tmp->next;
		}
			
			
				
		}
	}

float suprafataTotala(NodLP* graf)
{float sum = 0.0f;
	if (graf)
	{
		
		NodLP* temp = graf;
		while (temp)
		{
			sum = sum + temp->info.suprafata;
			temp = temp->next;
		}
	}
	return sum;
}
float* totalPlata(NodLP* graf,int& nrMag)
{
	nrMag = 0;
	NodLP* temp = graf;
	while (temp)
	{
		nrMag++;
		temp = temp->next;
	}
	float* total = (float*)malloc(sizeof(float)*nrMag);
	NodLP* aux = graf;
	int i = 0;
	while (aux)
	{
		total[i] = aux->info.suprafata * 9;
		i++;
		aux = aux->next;
	}
	return total;
}
NodLP* modificareAngajati(NodLP* &graf, int id,int nrAngNou)
{
	NodLP* temp = graf;
	while (temp)
	{
		if (temp->info.idMagazin == id)
			temp->info.nrAngajati = nrAngNou;
		temp = temp->next;
	}
	return graf;

}
void afisareLP2(NodLP* graf)
{
	NodLP* temp = graf;
	while (temp)
	{
		afisareMagazin(temp->info);
		temp = temp->next;
	}
}
int nrNoduri(NodLP* graf)
{
	int nr = 0;
	NodLP* temp = graf;
	while (temp)
	{
		nr++;
		temp = temp->next;
	}
	return nr;
}
struct Nod
{
	int info;
	Nod* next;
};
Nod* push(Nod* s, int f)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = f;
	nou->next = s;
	return nou;
}
Nod* pop(Nod*s,int&varf)
{
	Nod* aux = s;
	s = s->next;
	varf = aux->info;
	free(aux);
	return s;
}
Nod* set(Nod* c, int m)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = m;
	nou->next = NULL;
	if (c)
	{

		Nod* temp = c;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = nou;
		return c;
	}
	else return nou;
}

Nod* get(Nod* c, int&varf)
{
	
		Nod* temp = c;
		c = c->next;
		varf = temp->info;
		free(temp);
		return c;
}
int* parcurgereBF(NodLP* graf, int start)
{
	int k = 0;
	int* flags = (int*)malloc(sizeof(int)*nrNoduri(graf));
	for (int i = 0; i < nrNoduri(graf); i++)
		flags[i] = 0;
	int* output = (int*)malloc(sizeof(int)*nrNoduri(graf));
	Nod* coada = NULL;
	coada = set(coada, start);
	flags[start - 1] = 1;
	while (coada)
	{
		int varf;
		coada = get(coada, varf);
		output[k] = varf;
		k=k+1;
		NodLP* temp = cautareNod(graf, varf);
		NodLS* tms = temp->vecini;
		while (tms)
		{
			if (flags[tms->nodAdiacent.idMagazin - 1] == 0)
			
				coada = set(coada, tms->nodAdiacent.idMagazin);
				flags[tms->nodAdiacent.idMagazin - 1] = 1;
			
			tms=tms->next;
		}
	}
	//free(flags);
	return output;
}
NodLP* stergereNod(NodLP* graf, int id)
{
	NodLP* aux = graf;
	if (aux->info.idMagazin == id)
	{
		graf = aux->next;
		free(aux->info.denumire);
		free(aux->info.localitate);
	}
	else while (aux->next)
	{
		if (aux->next->info.idMagazin == id)
		{
			NodLP* tmp = aux->next;
			aux->next = tmp->next;
			free(tmp->info.denumire);
			free(tmp->info.localitate);
			free(tmp);
			return graf;
		}
		 aux = aux->next;
	}
	return graf;
}

int* parcurgereDF(NodLP* graf, int idStart)
{
	int k = 0;
	int* flags = (int*)malloc(sizeof(int)*nrNoduri(graf));
	for (int i = 0; i < nrNoduri(graf); i++)
		flags[i] = 0;
	int* output = (int*)malloc(sizeof(int)*nrNoduri(graf));
	Nod* stiva = NULL;
	stiva = push(stiva, idStart);
	flags[idStart - 1] = 1;
	while (stiva)
	{
		int varf;
		stiva = pop(stiva, varf);
		output[k] = varf;
		k++;
		NodLP* tmp = cautareNod(graf, varf);
		NodLS* tms = tmp->vecini;
		while (tms)
		{
			if (flags[tms->nodAdiacent.idMagazin - 1] == 0)
				stiva = push(stiva, tms->nodAdiacent.idMagazin);
			flags[tms->nodAdiacent.idMagazin - 1] = 1;
			tms = tms->next;
		}
	}
	free(flags);
	return output;

}
void main()
{
	Magazin m1 = creareMagazin(1, "Magazin 1", "Barlad", 25.5f, 12);
	Magazin m2 = creareMagazin(2, "Magazin 2", "Bucuresti", 20.5f, 10);
	Magazin m3 = creareMagazin(3, "Magazin 3", "Targu-Jiu", 27.5f, 9);
	Magazin m4 = creareMagazin(4, "Magazin 4", "Targoviste", 29.5f, 15);
	Magazin m5 = creareMagazin(5, "Magazin 5", "Suceava", 35.5f, 20);
	NodLP* graf = NULL;
	graf = inserareLP(graf, m1);
	 graf = inserareLP(graf, m2);
	 graf = inserareLP(graf, m3);
	 graf = inserareLP(graf, m4);
	 graf = inserareLP(graf, m5);
	 inserareArcInGraf(graf, m1, m2, 5);
	 inserareArcInGraf(graf, m1, m3, 10);
	 inserareArcInGraf(graf, m1, m4, 7);
	 inserareArcInGraf(graf, m4, m5, 20);
	 inserareArcInGraf(graf, m5, m3, 5);
	afisareLP(graf);
	float suprafata = suprafataTotala(graf);
	printf("\n\nSuprafata totala este: %5.2f", suprafata);
	int nrM;
	float * total = totalPlata(graf, nrM);
	printf("\n\nChirii: ");
	for (int i = 0; i < nrM; i++)
	{
		printf(" %5.2f", total[i]);
	}
	printf("\n\nGraful dupa modificare: ");
	graf=modificareAngajati(graf, 3, 50);
	afisareLP2(graf);
	//parcurgere in adancime
	printf("\n\nParcurgere in adancime");
	int* output = parcurgereDF(graf, 1);
	for (int i = 0; i < nrNoduri(graf); i++)
	{
		printf(" %d", output[i]);
	}
	printf("\n\nGraf dupa stergere");
	graf = stergereNod(graf, 3);
	afisareLP(graf);
	printf("\n\nParcurgere in latime: ");
	int* output2 = parcurgereBF(graf, 1);
	for (int i = 0; i < nrNoduri(graf); i++)
	{
		printf(" %d", output2[i]);
	}
}