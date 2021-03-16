#include<stdio.h>
#include<string.h>
#include<malloc.h>

struct Rezervare {
	int idRezervare;
	char* denumire;
	unsigned int nrCamereRezervare;
	char* numeClient;
	char* dataRezervare;
	float sumaDePlata;
};

Rezervare initializareRezervare(int id, const char*denumire, unsigned int nrCamereRezervate, const char* numeClient, const char* dataRezervare, float sumaDePlata)
{
	Rezervare r;
	r.idRezervare = id;
	r.denumire = (char*)malloc((strlen(denumire) + 1) * sizeof(char));
	strcpy(r.denumire, denumire);
	r.nrCamereRezervare = nrCamereRezervate;
	r.numeClient = (char*)malloc((strlen(numeClient) + 1) * sizeof(char));
	strcpy(r.numeClient, numeClient);
	r.dataRezervare = (char*)malloc((strlen(dataRezervare) + 1) * sizeof(char));
	strcpy(r.dataRezervare, dataRezervare);
	r.sumaDePlata = sumaDePlata;
	return r;
}

void afisareRezervare(Rezervare r)
{
	printf("\nId: %d, denumire: %s, numar camere: %d, nume client: %s, data: %s, suma de plata: %5.2f ",r.idRezervare,r.denumire,r.nrCamereRezervare,r.numeClient,r.dataRezervare,r.sumaDePlata);
}


struct Nod {
	Rezervare info;
	Nod* next;
};

Nod* inserareNod(Nod* p, Rezervare r)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = p;
	nou->info = r;
	return nou;
}

int functiaHash(int idRezervare, int size)
{
	return idRezervare % size;
}

void inserareHash(Nod** hashT,Rezervare r, int size)
{
	int k = functiaHash(r.idRezervare, size);
	hashT[k] = inserareNod(hashT[k], r);
}

void parseHash(Nod**hashT,int size)
{
	for(int i=0;i<size;i++)
		if (hashT[i])
		{
			Nod*temp = hashT[i];
			while (temp)
			{
				printf("\nId: %d, denumire: %s, numar camere: %d, nume client: %s, data: %s, suma de plata: %5.2f ", temp->info.idRezervare, temp->info.denumire, temp->info.nrCamereRezervare, temp->info.numeClient, temp->info.dataRezervare, temp->info.sumaDePlata);;
				temp = temp->next;
			}
		}
}

int afisareNumar(Nod**hashT,int size, const char*dataCalendaristica)
{
	for(int i=0;i<size;i++)
		if (hashT[i])
		{
			Nod*temp = hashT[i];
			while (temp)
			{
				if (!(strcmp(temp->info.dataRezervare, dataCalendaristica)))
					return temp->info.nrCamereRezervare;
				temp = temp->next;
			}
		}
}

float afisareSumaTotalaDePlata(Nod**hashT, int size, const char*numeClient)
{
	float sum = 0;
	for (int i = 0; i < size; i++)
		if (hashT[i])
		{
			Nod*temp = hashT[i];
			while (temp)
			{
				if (!(strcmp(temp->info.numeClient, numeClient)))
					sum+= temp->info.sumaDePlata;
				temp = temp->next;
			}
		}
	return sum;
}

int* multime(Nod** hashT, int size, int &dim, int*&vector,int nivel)
{
	for(int i=0;i<size;i++)
		if (hashT[i])
		{
			Nod*temp = hashT[i];
			int*vec = (int*)malloc(sizeof(int)*(dim + 1));
			for (int i = 0; i < dim; i++)
				vec[i] = vector[i];
			while (temp)
			{
				if (temp->info.nrCamereRezervare > nivel)
				{
					vec[dim] = temp->info.idRezervare;
					dim++;
					vector = vec;
				}
				temp = temp->next;
			}
		}
	return vector;
}

void modificaData(Nod** hashT, int size, int idRezervare, char* newData)
{
	for(int i=0;i<size;i++)
		if (hashT[i])
		{
			Nod*temp = hashT[i];
			while (temp)
			{
				if (temp->info.idRezervare == idRezervare)
					temp->info.dataRezervare = newData;
				temp = temp->next;
			}
		}
}


void main()
{
	Nod** hashT;
	int size = 10;
	Rezervare r;
	hashT = (Nod**)malloc(sizeof(Nod*)*size);
	for (int i = 0; i < size; i++)
		hashT[i] = 0;

	inserareHash(hashT, initializareRezervare(12, "Maria", 2, "Ion", "12.02.2019", 532), size);
	inserareHash(hashT, initializareRezervare(45, "Acc", 1, "Gigel", "12.07.2019", 320), size);
	inserareHash(hashT, initializareRezervare(32, "Flo", 3, "Carmen", "14.12.2019", 452), size);
	inserareHash(hashT, initializareRezervare(20, "Vultur", 3, "Gigel", "12.09.2019", 102), size);

	parseHash(hashT, size);

	printf("\n\nNumar camere rezervate la data cautata: %d", afisareNumar(hashT, size, "14.12.2019"));
	printf("\n\nSuma de plata a clientului cautat: %5.3f", afisareSumaTotalaDePlata(hashT, size, "Gigel"));


	int *vector;
	int dim = 0;
	int*v = multime(hashT, size, dim, vector,2);
	printf("\n\nMultime de rezervari cu nr camere mai mare de 2: ");
	for (int i = 0; i < dim; i++)
		printf("%d ", v[i]);


	char newData[] = { "01.01.2019" };
	modificaData(hashT, size, 12,newData);
	printf("\n\nDupa modificarea datei: ");
	parseHash(hashT, size);

	
}