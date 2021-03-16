#include<stdio.h>
#include<string>
#include<malloc.h>

struct Produs {
	char* denumire;
	int cantitate;
	char* unitateMasura;
};

struct Comanda {
	int id;
	char* denumire;
	int nrProdComandate;
	Produs* produs;
	char* dataLivrare;
};

Produs initializareProdus(const char* denumire, int cantitate, const char* unitateMasura)
{
	Produs p;
	p.denumire =(char*)malloc((strlen(denumire)+1)*sizeof(char));
	strcpy(p.denumire, denumire);
	p.cantitate = cantitate;
	p.unitateMasura = (char*)malloc((strlen(unitateMasura) + 1) * sizeof(char));
	strcpy(p.unitateMasura, unitateMasura);
	return p;
}

void afisareProdus(Produs p)
{
	printf("\n\t Produsul %s, cantitate: %d, u.m.: %s ", p.denumire,p.cantitate,p.unitateMasura);
}

Comanda initializareComanda(int id, const char* denumire, int nrProdComandate, Produs* produs, const char* dataLivrare)
{
	Comanda c;
	c.id = id;
	c.denumire = (char*)malloc((strlen(denumire) + 1) * sizeof(denumire));
	strcpy(c.denumire, denumire);
	c.nrProdComandate = nrProdComandate;
	c.produs = (Produs*)malloc(sizeof(Produs)*nrProdComandate);
	for (int i = 0; i < nrProdComandate; i++)
		c.produs[i] = initializareProdus(produs[i].denumire, produs[i].cantitate, produs[i].unitateMasura);
	c.dataLivrare = (char*)malloc((strlen(dataLivrare) + 1) * sizeof(char));
	strcpy(c.dataLivrare, dataLivrare);
	return c;
}

void afisareComanda(Comanda c){
	printf("\nComanda %d, denumire: %s,nr produse comandate: %d, data livrarre: %s produse: ", c.id, c.denumire, c.nrProdComandate, c.dataLivrare);
	for (int i = 0; i < c.nrProdComandate; i++)

		afisareProdus(c.produs[i]);
}

struct Nod {
	Comanda info;
	Nod* st;
	Nod*dr;
};

Nod* initializareNod(Comanda c, Nod*st, Nod*dr)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->st = st;
	nou->dr = dr;
	return nou;
}

void inordineABC(Nod* rad)
{
	if (rad)
	{
		inordineABC(rad->st);
		afisareComanda(rad->info);
		inordineABC(rad->dr);
	}
}

Nod* inserareABC(Nod* rad, Comanda c)
{
	if (rad)
	{
		if (rad->info.id > c.id)
			rad->st = inserareABC(rad->st, c);
		else
			rad->dr = inserareABC(rad->dr, c);
		return rad;
	}
	else
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = c;
		nou->st = NULL;
		nou->dr = NULL;
		return nou;
	}
}

int* idDupaData(Nod* rad, const char* data, int *&vector, int&dim)
{
	if (rad)
	{
		idDupaData(rad->st, data, vector, dim);
		if (strcmp(rad->info.dataLivrare, data) == 0)
		{
			int* temp = (int*)malloc(sizeof(int)*(dim + 1));
			for (int i = 0; i < dim; i++)
				temp[i] = vector[i];
			temp[dim] = rad->info.id;
			dim++;
			vector = temp;
			return vector;
		}
		idDupaData(rad->dr, data, vector, dim);
	}
}

void numarFrunze(Nod* rad, const char* numeClient, int*nr)
{
	if (rad)
	{
		if ( (strcmp(rad->info.denumire, numeClient) == 0) && (rad->st==NULL) &&(rad->dr==NULL) )
			(*nr)++;
		numarFrunze(rad->st, numeClient, nr);
		numarFrunze(rad->dr, numeClient, nr);
	}
}

void modificaProdus(Nod* rad, int idComanda,Produs* produs, int nrProduseComandate)
{
	if (rad)
	{
		if (rad->info.id == idComanda)
		{
			free(rad->info.produs);
			rad->info.nrProdComandate = nrProduseComandate;
			rad->info.produs = (Produs*)malloc(sizeof(Produs)*nrProduseComandate);
			for (int i = 0; i < nrProduseComandate; i++)
				rad->info.produs[i] = initializareProdus(produs[i].denumire, produs[i].cantitate, produs[i].unitateMasura);
		}
		modificaProdus(rad->st, idComanda, produs, nrProduseComandate);
		modificaProdus(rad->dr, idComanda, produs, nrProduseComandate);
	}
}

void afisarePeNivel(Nod*rad, int nivel)
{
	if (rad)
	{
		if (nivel == 1)
			afisareComanda(rad->info);
		else
		{
			nivel--;
			afisarePeNivel(rad->st, nivel);
			afisarePeNivel(rad->dr, nivel);
		}
	}
}

void main()
{
	Nod* rad = NULL;

	Produs* p1 = (Produs*)malloc(sizeof(Produs) * 2);
	p1[0] = initializareProdus("tableta", 1, "bucata");
    p1[1] = initializareProdus("telefon", 2, "bucati");

	Produs* p2 = (Produs*)malloc(sizeof(Produs) * 3);
	p2[0] = initializareProdus("cana", 6, "seturi");
	p2[1] = initializareProdus("carte", 2, "bucati");
	p2[2] = initializareProdus("vin", 3, "sticle");

	Produs* p3 = (Produs*)malloc(sizeof(Produs) * 2);
	p3[0] = initializareProdus("vinete", 5, "kg");
	p3[1] = initializareProdus("rosii", 3, "kg");

	Produs* p4 = (Produs*)malloc(sizeof(Produs) * 1);
	p4[0] = initializareProdus("tigai", 3, "bucata");

	Produs* p5 = (Produs*)malloc(sizeof(Produs) * 2);
	p5[0] = initializareProdus("apa", 12, "litrii");
	p5[1] = initializareProdus("suc", 8, "litrii");
	
	rad = inserareABC(rad, initializareComanda(12, "Miruna", 2, p1, "25.02.2019"));
	rad = inserareABC(rad, initializareComanda(45, "Razvan", 3, p2, "12.12.2019"));
	rad = inserareABC(rad, initializareComanda(32, "Diana", 2, p3, "08.05.2019"));
	rad = inserareABC(rad, initializareComanda(10, "Miruna", 1, p4, "12.12.2019"));
	rad = inserareABC(rad, initializareComanda(58, "Miruna", 2, p5, "30.06.2019"));

	inordineABC(rad);

	int* vector=NULL;
	int dim = 0;
	int* rezultat = idDupaData(rad,"12.12.2019",vector,dim);
	printf("\n\nPe data de 12.12.2019 vor fi livrate comenzile: ");
	for (int i = 0; i < dim; i++) {
		printf("%d ", rezultat[i]);
	}


	int numar = 0;
	numarFrunze(rad, "Miruna", &numar);
	printf("\n\nNumarul de comenzi ale clientului ales sunt: %d", numar);

	modificaProdus(rad, 45, p1, 2);
	printf("\n\nDupa modificare: ");
	inordineABC(rad);

	printf("\n\n\n");
	afisarePeNivel(rad, 3);
}
