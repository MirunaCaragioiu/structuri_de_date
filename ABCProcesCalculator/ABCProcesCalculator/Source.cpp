#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct ProcesCalculator {
	int idPC;
	char* denumire;
	char* descriere;
	int memOcupata;
	char* user;
};

ProcesCalculator initializareProces(int id, const char*denumire, const char* descriere, int memOcupata, const char*user)
{
	ProcesCalculator pc;
	pc.idPC = id;
	pc.denumire = (char*)malloc((strlen(denumire)+1)*sizeof(char));
	strcpy(pc.denumire, denumire);
	pc.descriere = (char*)malloc((strlen(descriere) + 1) * sizeof(char));
	strcpy(pc.descriere, descriere);
	pc.memOcupata = memOcupata;
	pc.user = (char*)malloc((strlen(user) + 1) * sizeof(char));
	strcpy(pc.user, user);
	return pc;
}

void afisareProces(ProcesCalculator pc)
{
	printf("\nId: %d, denumire: %s, descriere: %s, memorie: %d, user: %s", pc.idPC, pc.denumire, pc.descriere, pc.memOcupata, pc.user);
}

struct Nod {
	ProcesCalculator info;
	Nod* st, *dr;
};

Nod* initializareNod(ProcesCalculator pc, Nod*st, Nod*dr)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = pc;
	nou->st = st;
	nou->dr = dr;
	return nou;
}

Nod* inserareABC(Nod* rad,ProcesCalculator p)
{

	if (rad == NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = p;
		nou->dr = NULL;
		nou->st = NULL;
		rad = nou;
	}
	else
	{
		if (p.idPC < rad->info.idPC)
			rad->st = inserareABC(rad->st, p);
		else if (p.idPC > rad->info.idPC)
			rad->dr = inserareABC(rad->dr, p);

		return rad;
	}
}

void parseABC(Nod* rad)
{
	if (rad)
	{
		parseABC(rad->st);
		printf("\nId: %d, denumire: %s, descriere: %s, memorie: %d, user: %s",rad->info.idPC,rad->info.denumire,rad->info.descriere,rad->info.memOcupata,rad->info.user);
		parseABC(rad->dr);
	}
}

void numarProcese(Nod*rad, const char* user,int*nr)
{
	if (rad)
	{
		if (strcmp(rad->info.user, user)==0)
			(*nr)++;
		numarProcese(rad->st, user,nr);
		numarProcese(rad->dr, user,nr);
	}
}

void afisareProcesDupaNivel(Nod* root, int nivel)
{
	if (root)
	{
		if (nivel == 1)
		{
			afisareProces(root->info);

		}
		else
		{
			nivel--;
			afisareProcesDupaNivel(root->st, nivel);
			afisareProcesDupaNivel(root->dr, nivel);
		}
	}

}

void numarPeNivel(Nod*rad, int nivelCautat, int nivelCurent,int *nr)
{
	if (rad)
	{
		if (nivelCautat == nivelCurent)
			(*nr)++;
		else
		{
			numarPeNivel(rad->st, nivelCautat, nivelCurent + 1,nr);
			numarPeNivel(rad->dr, nivelCautat, nivelCurent + 1,nr);
		}
	}
}

void modificaMemorie(Nod* rad, int id, int newMemorie)
{
	if (rad)
	{
		if (rad->info.idPC == id)
			rad->info.memOcupata = newMemorie;
		modificaMemorie(rad->st, id, newMemorie);
		modificaMemorie(rad->dr, id, newMemorie);
	}
}

int* multimeProcese(Nod* rad, int&dim, int *&vector, int memorie)
{
	if (rad)
	{
		multimeProcese(rad->st, dim, vector, memorie);
		if (rad->info.memOcupata < memorie)
		{
			int*temp = (int*)malloc(sizeof(int)*(dim + 1));
			for (int i = 0; i < dim; i++)
				temp[i] = vector[i];
			temp[dim] = rad->info.idPC;
			dim++;
			vector = temp;
			return vector;
		}
		multimeProcese(rad->dr, dim, vector, memorie);
	}
}

void main()
{
	Nod* rad = NULL;
	rad = inserareABC(rad, initializareProces(12, "a", "f", 45, "ana"));
	rad = inserareABC(rad, initializareProces(52, "b", "g", 10, "maria"));
	rad = inserareABC(rad, initializareProces(45, "c", "h", 23, "ana"));
	rad = inserareABC(rad, initializareProces(10, "d", "i", 25, "alex"));
	rad = inserareABC(rad, initializareProces(32, "e", "j", 45, "ana"));
	parseABC(rad);

	int nr = 0;
	numarProcese(rad, "ana", &nr);
	printf("\n\nNumar procese ale userului cerut: %d", nr);



	int nr1 = 0;
	numarPeNivel(rad, 2, 1, &nr1);
	printf("\n\nNumar noduri pe un nivel: %d", nr1);

	//modificaMemorie(rad, 52, 100);
	//printf("\n\nDupa modificare memorie: ");
	//parseABC(rad);

	//printf("\n\n");
	//afisareProcesDupaNivel(rad, 2);


	int*vector;
	int dim = 0;
	int* m = multimeProcese(rad, dim, vector, 45);
	printf("\n\nPC cu memoria sub mem aleasa: ");
	for (int i = 0; i < dim; i++)
		printf("%d ", m[i]);


	printf("\n\n\n");
	afisareProcesDupaNivel(rad,4);
}