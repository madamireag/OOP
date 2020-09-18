#include "assignment2.h"
#include<iostream>
using namespace std;
//aici se implementeaza metodele
int numarElementeMaiMari(int* valori, int nrValori, int valoarePrag)
{
	int nrElementeMaiMari = 0;
	for (int i = 0; i < nrValori; i++)
		if (valori[i] >= valoarePrag)
			nrElementeMaiMari++;
	return nrElementeMaiMari;
}

int* filtrareElementeMaiMari(int* valori, int nrValori, int valoarePrag)
{
	int nrElementeMaiMari=0;
	int* valoriMaiMari;
	int i,k = 0;
	for (i = 0; i < nrValori; i++)
		if (valori[i] > valoarePrag)
			nrElementeMaiMari++;

	if (nrElementeMaiMari != 0)
	{
		valoriMaiMari = new int[nrElementeMaiMari];
		for ( i = 0; i < nrValori; i++)
		if (valori[i] >= valoarePrag)
			{
				valoriMaiMari[k] = valori[i];
				k++;

			}
	}
	else
			valoriMaiMari = NULL;

	return valoriMaiMari;
	delete[] valoriMaiMari;
}
void filtrareElementeMaiMari2(int* valori, int nrValori, int valoarePrag, int** valoriMaiMari)
{
	int nrElementeMaiMari = 0,indice=0;

	for (int i = 0; i < nrValori; i++)
		if (valori[i] > valoarePrag)
			nrElementeMaiMari++;
	if (nrElementeMaiMari != 0)
	{
		*valoriMaiMari = new int[nrElementeMaiMari];
		for (int i = 0; i < nrValori; i++)
			if (valori[i] >= valoarePrag)
			{
				(*valoriMaiMari)[indice] = valori[i];
				indice++;

			}
	}
	else
		*valoriMaiMari = NULL;


}


int getElement(int* valori, int nrValori, int index)
{
	if (index >= 0 && index < nrValori)
	{
		for (int i = 0; i < nrValori; i++)
			if (i == index)
				return valori[i];
	}
	else throw new ExceptieAssignment2();
}
int* slice(int* valori, int nrValori, int indexStart, int indexFinal, int& dimensiuneSubvector)
{
	int *subvector;
	if (indexStart == indexFinal && indexStart>=0 &&indexFinal<nrValori)
	{
		dimensiuneSubvector = 1;
		subvector = new int[1];
		subvector[0] = valori[indexStart];
	}
	else
	if (indexStart >= 0 && indexStart<nrValori && indexFinal>=0 && indexFinal <= nrValori)
	{
		dimensiuneSubvector = indexFinal - indexStart + 1;
		int nrElemente = dimensiuneSubvector;
			int	j = 0;
				subvector = new int[nrElemente];
				for (int i = indexStart; i <= indexFinal; i++)
				subvector[j++] = valori[i];
			}
	else throw new ExceptieAssignment2();
	if(indexStart>indexFinal)
		throw new ExceptieAssignment2();

	return subvector;}

int main()
{
	int vectorInitial[] = { 23,67,89,102,560,1000 }, nrElemente = 6, prag, dim;
	cout << "Testarea primei functii: " << endl<<"Test normal: "<<endl;
	prag = 100;
	cout << numarElementeMaiMari(vectorInitial, nrElemente, prag);
	cout <<endl<< "Test limita: "<<endl;
	prag = 102;
	cout << numarElementeMaiMari(vectorInitial, nrElemente, prag);
	cout << endl << "Test out: " << endl;
	prag = 2000;
	cout << numarElementeMaiMari(vectorInitial, nrElemente, prag);

	cout << endl << " Testarea functiei filtrareElementeMaiMari:";
	int* filtrate;
	prag = 60;
	filtrate = new int[nrElemente];
	cout << endl << "Test normal:" << endl;
	filtrate = filtrareElementeMaiMari(vectorInitial, nrElemente, prag);
	for (int i =0 ; i < nrElemente; i++)
		cout << Filtrate[i]<<" ";
	cout << endl << "Test valoare prag necorespunzatoare:" << endl;
	int* filtrate2;
	prag = 2000;
	filtrate2 = new int[nrElemente];
	filtrate2 = filtrareElementeMaiMari(vectorInitial, nrElemente, prag);
	cout << filtrate2 << " ";

	cout << endl << "Testarea functiei filtrareElementeMaiMari2:" << endl;
	cout << "Test normal:" << endl;
	int* vectorTest;
	prag = 100;
	vectorTest = new int[nrElemente];
	filtrareElementeMaiMari2(vectorInitial, nrElemente, prag, &vectorTest);
	for (int i = 0; i < nrElemente; i++)
		cout << vectorTest[i] << " ";
	cout <<endl<< "Test cand valoare prag prea mare(test null):" << endl;
	int* vectorTest2;
	prag = 2000;
	vectorTest2 = new int[nrElemente];
	filtrareElementeMaiMari2(vectorInitial, nrElemente, prag, &vectorTest2);
	cout << vectorTest2;

	cout << endl << "Testarea functiei getElement: " << endl << "Test normal:" << endl;
	cout << getElement(vectorInitial, nrElemente, 1);
	cout << endl<<"Test Index Negativ:" << endl;
	cout << getElement(vectorInitial, nrElemente, -1);
	cout << "Test Index Limita:" << endl;
	cout << getElement(vectorInitial, nrElemente, nrElemente);
	cout << "Test index prea mare:" << endl;
    cout << getElement(vectorInitial, nrElemente, 1000);

cout << endl << "Testarea functiei slice:" << endl;
cout << "Test normal:";
int indexStart, indexFinal;
int* subvector;
indexStart = 2;
indexFinal = 4;
int nrElementeSlice = indexFinal - indexStart + 1;
subvector = new int[nrElementeSlice];
subvector = slice(vectorInitial, nrElemente, indexStart, indexFinal, dim);
for (int i = 0; i < nrElementeSlice; i++)
	cout << subvector[i] << " ";
delete[] subvector;
cout << endl << "Test index egal:" << endl;
indexStart = 2; indexFinal = 2;
nrElementeSlice = indexFinal - indexStart + 1;
subvector = new int[nrElementeSlice];
subvector = slice(vectorInitial, nrElemente, indexStart, indexFinal, dim);
for (int i = 0; i < nrElementeSlice; i++)
	cout << subvector[i] << " ";
cout << endl << "Test index start negativ:" << endl;
indexStart = -2; indexFinal = 4;
nrElementeSlice = indexFinal - indexStart + 1;
subvector = new int[nrElementeSlice];
cout<<slice(vectorInitial, nrElemente, indexStart, indexFinal, dim);
cout<<endl<<"Test index final negativ:"
indexStart = 2; indexFinal = -4;
cout << slice(vectorInitial, nrElemente, indexStart, indexFinal, dim);
cout << endl << "Test index final prea mare:"<<endl;
indexStart = 2; indexFinal = 30;
cout << slice(vectorInitial, nrElemente, indexStart, indexFinal, dim);
cout << "Test index start > index final:"<<endl;
indexStart = 2; indexFinal = 1;
cout << slice(vectorInitial, nrElemente, indexStart, indexFinal, dim);

}



