#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Depozit {
	int cod;
	char* locatie;
	int capacitate;
	int nrCategoriiCereale;
	char** denumireCereale;
};

Depozit createDepozit(int cod, const char* locatie, int capacitate,int nrCategoriiCereale ,const char** denumireCereale)
{
	Depozit d;
	d.cod = cod;
	d.locatie = (char*)malloc((strlen(locatie) + 1) * sizeof(char));
	strcpy(d.locatie, locatie);
	d.capacitate = capacitate;
	d.nrCategoriiCereale = nrCategoriiCereale;
	d.denumireCereale = (char**)malloc(sizeof(char*)*d.nrCategoriiCereale);
	for (int i = 0; i < nrCategoriiCereale; i++)
	{
		d.denumireCereale[i] = (char*)malloc((strlen(denumireCereale[i]) + 1) * sizeof(char));
	    strcpy(d.denumireCereale[i], denumireCereale[i]);
	}
	return d;
}

struct Nod {
	Depozit info;
	int GE;
	Nod* st, *dr;
};

int max(int a, int b)
{
	return a > b ? a : b;
}

int inaltimeArbore(Nod* rad)
{
	if (rad)
		return 1 + max(inaltimeArbore(rad->st), inaltimeArbore(rad->dr));
	else return 0;
}

void calculGE(Nod*rad)
{
	if (rad)
		rad->GE = inaltimeArbore(rad->dr) - inaltimeArbore(rad->st);
}

Nod * rotireSimplaSt(Nod*pivot, Nod* fiuDr)
{
	pivot->dr = fiuDr->st;
	calculGE(pivot);
	fiuDr->st = pivot;
	calculGE(fiuDr);
	return fiuDr;
}

Nod* rotireSimplaDr(Nod*pivot, Nod*fiuSt)
{
	pivot->st = fiuSt->dr;
	calculGE(pivot);
	fiuSt->dr = pivot;
	calculGE(fiuSt);
	return fiuSt;
}
Nod* rotireDublaStDr(Nod*pivot, Nod* fiuSt)
{
	pivot->st = rotireSimplaSt(fiuSt, fiuSt->dr);
	calculGE(pivot);
	fiuSt = pivot->st;
	fiuSt = rotireSimplaDr(pivot, fiuSt);
	return fiuSt;
}

Nod* rotireDublaDrSt(Nod*pivot, Nod*fiuDr)
{
	pivot->dr = rotireSimplaDr(fiuDr, fiuDr->st);
	calculGE(pivot);
	fiuDr = pivot->dr;
	fiuDr = rotireSimplaSt(pivot, fiuDr);
	return fiuDr;
}

Nod* inserareAVL(Nod* rad, Depozit f, int*err)
{
	if (rad)
	{
		if (rad->info.cod > f.cod)
			rad->st = inserareAVL(rad->st, f, err);
		else
			if (rad->info.cod < f.cod)
				rad->dr = inserareAVL(rad->dr, f, err);
			else
				*err = 1;
	}
	else
	{
		Nod *nou = (Nod*)malloc(sizeof(Nod));
		nou->info = f;
		nou->st = NULL;
		nou->dr = NULL;
		rad = nou;
	}
	calculGE(rad);
	if (rad->GE == 2)
	{
		if (rad->dr->GE == -1)
			rad = rotireDublaDrSt(rad, rad->dr);
		else
			rad = rotireSimplaSt(rad, rad->dr);
	}
	else {
		if (rad->GE == -2)
		{
			if (rad->st->GE == 1)
				rad = rotireDublaStDr(rad, rad->st);
			else
				rad = rotireSimplaDr(rad, rad->dr);
		}
	}
	return rad;
}

void parseInordineAVL(Nod*rad)
{
	if (rad)
	{
		parseInordineAVL(rad->st);
		printf("\nCod: %d, locatie: %s, capacitate: %d, numar categorii: %d ", rad->info.cod, rad->info.locatie, rad->info.capacitate, rad->info.nrCategoriiCereale);
		printf(" , denumire cereale: ");
		for (int i = 0; i < rad->info.nrCategoriiCereale; i++)
			printf(" %s, " ,rad->info.denumireCereale[i]);
		parseInordineAVL(rad->dr);
	}
}

void numarDepCuSecara(Nod* rad, int*nr)
{
	if (rad)
	{
		for (int i = 0; i < rad->info.nrCategoriiCereale; i++)
			if (!(strcmp("secara", rad->info.denumireCereale[i])))
				(*nr)++;
		numarDepCuSecara(rad->st,nr);
		numarDepCuSecara(rad->dr,nr);
	}
}

void adaugaCategorie(Nod* rad, int cod,const char* newCategorie)
{
	if (rad)
	{
		if (rad->info.cod == cod)
		{
			rad->info.nrCategoriiCereale += 1;
			rad->info.denumireCereale[rad->info.nrCategoriiCereale-1] = (char*)malloc((strlen(newCategorie)+1)*sizeof(char));
			strcpy(rad->info.denumireCereale[rad->info.nrCategoriiCereale-1] , newCategorie);
		}
		adaugaCategorie(rad->st, cod,newCategorie);
		adaugaCategorie(rad->dr, cod, newCategorie);

	}
}


void main()
{
	Depozit d;
	Nod*rad = NULL;
	int err;


	const char* dep1[3] = { "grau", "porumb", "secara" };
	const char* dep2[2] = { "floarea soarelui", "porumb" };
	const char* dep3[4] = { "grau", "rapita", "oraz","secara"};
	const char* dep4[3] = { "rapita", "porumb", "secara" };
	const char* dep5[2] = {  "porumb", "ovaz" };

	rad = inserareAVL(rad, createDepozit(45, "Buc", 120, 3,dep1), &err);
	rad = inserareAVL(rad, createDepozit(10, "Iasi", 200, 2, dep2), &err);
	rad = inserareAVL(rad, createDepozit(25, "Craiova", 145, 4, dep3), &err);
    rad = inserareAVL(rad, createDepozit(23, "Ploiesti", 300, 3, dep4), &err);
	rad = inserareAVL(rad, createDepozit(14, "Brasov", 200, 2, dep5), &err);

	parseInordineAVL(rad);


	int nr = 0;
	numarDepCuSecara(rad, &nr);
	printf("\n\nNumar depozite cu secara: %d", nr);

	printf("\n\nDupa adaugare categorie: ");
	adaugaCategorie(rad, 10, "grau");
	parseInordineAVL(rad);

}