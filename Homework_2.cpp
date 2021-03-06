#include <iostream>
#include <string>
#include <exception>
using namespace std;

class Assignment3Exception : public exception {

};


//a fidelity card class that records the number of points that a clietn will get for each payment
//clasa Card Fidelitate ce inregistreaza numarul de puncte castigate de client de fiecare data cand efectueaza o plata
class FidelityCard {
public:
	const int id;			//constant attribute - generated based on noCards value
private:	
	char owner[50];
	string cardType;		//the service that provides the card (ex. Rompetrol, Mega Image, etc)
	
	int* points=NULL;			//points accumulated each time the client buys something
	int noPayments=0;			//number of payments done by the client

	static int noCards;		//incremented for each created card
public:
	const static int MIN_POINTS_FOR_PREMIUM;		//init with 1000 - the minimum points for becoming a premium member
	
public:
	/*
	
		//constructors
		//constructori
	
	*/

	FidelityCard() :id(noCards++) {
		this->cardType="None";
		strcpy(this->owner, "John Doe");

	}			//sets name to John Doe and cardType to "None" | initializeaza numele cu John Doe si tipul cardului cu "None"
	FidelityCard(const char* name, string cardName) :id(noCards++)  {
		this->cardType = cardName;
		strcpy(this->owner, name);
		

	};
	FidelityCard(const char* name, string cardName, int* existingPoints, int noPoints) :id(noCards++){
		this->cardType = cardName;
		strcpy(this->owner, name);
		
		this->points = new int[noPoints];
		for (int i = 0; i < noPoints; i++)
			this->points[i] = existingPoints[i];
		this->noPayments = noPoints;
		
	}

	//copy constructor
	//TO DO
	FidelityCard(FidelityCard& c) :id(c.noCards++) {
		strcpy(this->owner, c.owner);
		this->cardType = c.cardType;
		this->noPayments = c.noPayments;
		if(c.points){
		this->points = new int[noPayments];
		for (int i = 0; i < noPayments; i++)
			this->points[i] = c.points[i];
		
		}

	}

	//destructor
	//TO DO
	~FidelityCard() {
		cout << endl<<"Apel destructor ";
		if (this->points != NULL)
			delete[] this->points;
	}


	/*

	//public interface
	//interfata publica

	*/

	//computes total points
	//determina numarul total de puncte
	
	int getTotalPoints() {
		double s = 0;
		if (this->points != NULL)
		{
			for (int i = 0; i < noPayments; i++)
				s += this->points[i];
			return s;
		}
		else
			return 0;
	}
	

	//returns the owner name
	//returneaza numele de pe card
	
	char* getName() {
		return this->owner;
	}

	//returns number of payments/points
	//returneaza numarul de puncte
	
	int getNoPayments() {
		return this->noPayments;
	}

	//returns a specific payment
	//if the index is wrong the function shoud throw a new Assignment3Exception with "throw new Assignment3Exception();"

	//returneaza punctele asociate cu o anumita plata
	//daca indexul primit este gresit (nu se afla intre limitele 0 si numarPuncte -1 ) atunci se arunca o exceptie de tip Assignment3Exception cu "throw new Assignment3Exception();"

	int getPayment(int index) {
		if (index >= 0 && index < noPayments)
		{
			for (int i = 0; i < noPayments; i++)
				return this->points[index];
		}
		else
			throw new Assignment3Exception();
	}

	//returns the card name
	//returneaza tipul cardului
	
	string getCardType() {
		return this->cardType;
	}


	//checks is the client is a premium one - if it has more than MIN_POINTS_FOR_PREMIUM
	//verifica daca clientul este unul premium - suma punctelor depaseste MIN_POINTS_FOR_PREMIUM
	
	bool isPremiumClient() {
		if (this->getTotalPoints() >= FidelityCard::MIN_POINTS_FOR_PREMIUM)
			return true;
		else
			return false;
	}

	//allow you to change a specific entry in the points array
	//if the index is wrong or the value is a negative one the function shoud throw a new Assignment3Exception with "throw new Assignment3Exception();"

	//permite modificarea numarului de puncte de la o pozitie data
	//daca indexul primit este gresit (nu se afla intre limitele 0 si numarPuncte -1 ) si valoarea este negativa atunci se arunca o exceptie de tip Assignment3Exception cu "throw new Assignment3Exception();"
	
	void changePoints(int index, int value) {
		if (index >= 0 && index < this->noPayments && value>0)
		{
			for (int i = 0; i < this->noPayments; i++)
				this->points[index] = value;
		}
		else
			throw new Assignment3Exception();
	}


	//allow you to change the owner name
	//if newOwnerName has less than 3 chars and more than 49 the function shoud throw a new Assignment3Exception

	//permite modificarea numelui proprietarului
	//daca newOwnerName are mai putin de 3 caractere si mai mult de 49 se arunca o exceptie de tip Assignment3Exception cu "throw new Assignment3Exception();"
	void changeOwner(const char* newOwnerName) {
		if (strlen(newOwnerName ) >= 3 || strlen(newOwnerName ) < 49)
			 strcpy(this->owner, newOwnerName);
		else
			throw new Assignment3Exception();

	}

	//adds (concatenates) the newPoints array to the existing one; if the existing one is NULL then it's created and takes the values
	// if newPoints is NULL then throw a new Assignment3Exception
	
	//adauga (concateneaza) vectorul newPoints la cel existent; daca cel existent este NULL, atunci este creat si ia valorile
	//daca newPoints este NULL atunci arunca o exceptie Assignment3Exception
	//without | fara MEMORY LEAKS
	
	void transferPoints(int* newPoints, int noPoints);
		
		
	
	//the function allows clients to use the points to buy bew services/products
	//the function will remove the first n values from the points array wich sum are >= amount
	//if amount is <= 0 or > than the points sum then throw a new Assignment3Exception

	// functia permite clientilor sa utilizeze punctele pentru a cumpara servicii / produse noi 
	// functia va elimina primele n valori din vectorul de puncte, a caror suma este >= cu amount
	// daca amount este <= 0 sau > suma tuturor punctelor se arunca o exceptie Assignment3Exception
	void usePoints(int amount);
		
		
		
	void afisare() {
		cout << endl << "-----------------------------------";
		cout << endl << this->id << " " << this->owner;
		cout << endl << this->cardType << endl;
		if (this->points != NULL)
		{ 
			cout << "Punctele sunt: ";
			for (int i = 0; i < noPayments; i++)
				cout << this->points[i] << " | ";
		}
	}

	/*
	
		//operators
		//operatori
	
	*/
	FidelityCard operator=(const FidelityCard& c) {
		if (this->points)
			delete[] this->points;
		
		strcpy(this->owner, c.owner);
		this->cardType = c.cardType;
		this->noPayments = c.noPayments;
		if (c.points) {
			this->points = new int[noPayments];
			for (int i = 0; i < noPayments; i++)
				this->points[i] = c.points[i];
			
		}
		
		return *this;
	}
	bool operator<(FidelityCard& c)
	{
		if (this->getTotalPoints() < c.getTotalPoints())
			return true;
		else
			return false;
	}
	bool operator>(FidelityCard& c)
	{
		if (this->getTotalPoints() > c.getTotalPoints())
			return true;
		else
			return false;
	}
	bool operator==(FidelityCard& c)
	{
		if (this->getTotalPoints() == c.getTotalPoints())
			return true;
		else
			return false;
	}
	bool operator>=(FidelityCard& c)
	{
		if (this->getTotalPoints() >= c.getTotalPoints())
			return true;
		else
			return false;
	}
	explicit operator int() {
		return this->getTotalPoints();
	}
	FidelityCard operator++(int j) {
		FidelityCard aux= *this;
		int* puncte;
		puncte = new int[noPayments + 1];
		for (int i = 0; i < noPayments; i++)
			puncte[i] = points[i];
		puncte[noPayments] = 10;
		noPayments++;
		delete[] this->points;
		this->points = puncte;
		
		return aux;
		
	}
	FidelityCard operator++()
	{
		
		int* puncte;
		puncte = new int[noPayments + 1];
		for (int i = 0; i < noPayments; i++)
			puncte[i] = points[i];
		puncte[noPayments] = 10;
		noPayments++;
		delete[] this->points;
		this->points = puncte;
		
		return *this;
		
	}
	FidelityCard operator--(int i)
	{
		FidelityCard aux = *this;
		int* puncte;
		puncte = new int[noPayments- 1];
		for (int i = 0; i < noPayments-1; i++)
			puncte[i] = points[i];
		
		noPayments--;
		delete[] this->points;
		this->points = puncte;
		
		return aux;
		
	}
	FidelityCard operator--()
	{
		
		int* puncte;
		puncte = new int[noPayments - 1];
		for (int i = 0; i < noPayments - 1; i++)
			puncte[i] = points[i];

		noPayments--;
		delete[] this->points;
		this->points = puncte;


		return *this;

	}
	
	//TO DO
	//implement the required operators as class member functions or global functions so the examples from main will work
	//implementeaza operatorii indicati in main ca functii membre in clasa sau functii globale, astfel �ncat exemplele din main vor rula
	
	FidelityCard operator+(int valoare) {
		
		int *puncte;
		puncte = new int[noPayments + 1];
		for (int i = 0; i < noPayments; i++)
			puncte[i] = points[i];
		puncte[noPayments] = valoare;
		noPayments++;
		delete[] this->points;
		this->points = puncte;
		return *this;
	}
	FidelityCard operator+=(int valoare) {
		int *puncte;
		puncte = new int[noPayments + 1];
		for (int i = 0; i < noPayments; i++)
			puncte[i] = points[i];
		puncte[noPayments] = valoare;
		noPayments++;
		delete[] this->points;
		this->points = puncte;
		return *this;
	}

		int operator()(int indexStart, int indexFinal) {
			if (indexStart >= 0 && indexStart < noPayments && indexFinal>=0 && indexFinal < noPayments && indexStart<=indexFinal)
			{
				int suma = 0;
				for (int i = indexStart; i <= indexFinal; i++)
					suma += points[i];
				return suma;

			}
			else throw new Assignment3Exception();
		}
		int operator[](int index) {
			if(index>=0 && index<noPayments)
			return this->points[index];
		}
		FidelityCard operator!() {
			FidelityCard aux = *this;
			int* puncte=NULL;
			puncte = new int[aux.noPayments];
			for (int i = 0; i <= aux.noPayments; i++)
			{
				puncte[i] = aux.points[i];
				aux.noPayments--;
                
			}
			puncte[aux.noPayments] = aux.points[aux.noPayments];
			aux.noPayments--;
			delete[] aux.points;
			aux.points = puncte;
			return aux;
		}
		FidelityCard operator*(int valoare) {
			if(valoare>0){
			for(int i=0;i<noPayments;i++)
			    points[i] = valoare*points[i];
			return *this;
			}
			else throw new Assignment3Exception();
		}
		
	friend ostream& operator<<(ostream&, FidelityCard&);
	friend istream& operator>>(istream&, FidelityCard&);
	friend FidelityCard operator+(int, FidelityCard);
};

int FidelityCard::noCards = 0;
const int FidelityCard::MIN_POINTS_FOR_PREMIUM = 1000;
ostream& operator<<(ostream& out, FidelityCard& c)
{
	out << endl<<"**************************************"<< endl;
	out << "Id:" << c.id << " Nume:" << c.owner << endl;
	out << c.cardType<<endl;
	if (c.points)
	{
		for (int i = 0; i < c.noPayments; i++)
			out << c.points[i] << " ";
	}
	else
		out << endl << "Nu exista puncte";
	return out;

			
}

istream& operator>>(istream& in, FidelityCard& c) {
	cout << "Introduceti numele: ";
	in >> c.owner;
	cout << "Tipul cardului: ";
	in >> c.cardType;
	if (c.points)
		delete[] c.points;
	cout << "Numarul de puncte: ";
	in >> c.noPayments;
	c.points = new int[c.noPayments];
	cout << "Punctele sunt:";
	for (int i = 0; i < c.noPayments; i++)
		in >> c.points[i];
	return in;
}
FidelityCard operator+(int valoare,FidelityCard c) {
	
	int *puncte;
	if (valoare > 0) {
		puncte = new int[c.noPayments + 1];
		for (int i = 0; i < c.noPayments; i++)
			puncte[i] = c.points[i];
		puncte[c.noPayments] = valoare;
		c.noPayments++;
		delete[] c.points;
		c.points = puncte;
		return c;
	}
	else throw "Valoare negativa";
}
void main() {

	//test class functions
	cout << endl << "Testarea functiei getTotalPoints:" << endl;
	int puncte[] = { 15,5,10,30 };
	FidelityCard card("Andra", "Sephora", puncte, 4);
	cout << "Numarul de puncte este: "<<card.getTotalPoints();
	cout << endl << "Testarea functiilor changePoints si changeOwner: " << endl;
	cout << "Initial cardul este:" << endl;
	card.afisare();
	card.changePoints(1, 15);
	card.changeOwner("Ana");
	cout <<endl<< "Dupa modificari: " << endl;
	card.afisare();
	cout<<"Test exceptii:"<<endl;
	card.changeOwner("An");
	card.changePoints(-1,10);
	cout << endl << "Testarea functiei getName:" << endl;
	cout<<card.getName();
	cout << endl << "Testarea functiei getCardType:" << endl;
	cout << card.getCardType()<<endl;
	cout << "Testarea functiei isPremiumClient:" << endl;
	cout << "Testarea functiei getPayment:" << endl;
	cout<<card.getPayment(1);
	cout << "Test exceptii:" << endl;
	cout << card.getPayment(6);

	int pct[] = { 500,300,300 };
	FidelityCard cardTest("Ion", "Mega Image", pct, 3);
	if (cardTest.isPremiumClient())
		cout <<cardTest.getName()<< " este client premium :)"<<endl;
	cout << cardTest;
	//test destructor

	//test constructor de copiere
	FidelityCard card10(cardTest);
	//cout << card10;

	////operators section
	FidelityCard card1("No Name", "Blank");
	FidelityCard card2 = card1;
	cout << card1;
	 cout << card2;
	cin >> card1;
	cout << card1;
	

	int somePoints[] = { 15,5,10,30 };
	int noPoints = 4;
	FidelityCard card3("John", "ACME Inc", somePoints, noPoints);
	FidelityCard card4 = card3;
	
	//operator =
	//without MEMORY LEAKS
	cout << endl << "--------------------------------------" << endl << "Operator =" << endl;
	card2 = card1;			//copy data to card 1 from card 2 | copiaza datele cardului 1 in cardul 2
	cout << card2;

	cout << endl << "--------------------------------------" << endl << "Operatori + si +=" << endl;
	card1 = card3 + 15; //adds new points | adauga puncte noi
	card1 = 20 + card1; //adds new points | adauga puncte noi
	card1 += 10;		//adds new points | adauga puncte noi

	cout << card1;

	FidelityCard card5("No Name", "Blank");
	//card5 = card1 - 20;		//spends 20 points | utilizeaza 20 de puncte de pe card
	//card5 -= 10;			//spends 10 more points | utilizeaza inca 10 de puncte de pe card
	cout << endl << "--------------------------------------" << endl << "Operator *" << endl;
	//card5 = card5 * 2;			//doubles all existing points | dubleaza toate punctele existente
	//cout << card5;
	cardTest = cardTest * 2;
	cout << cardTest;
	FidelityCard card6("No Name", "Blank");
	cout << endl << "--------------------------------------" << endl << "Operator postincrement" << endl;
	//postincrement
	card6 = card3++;		// adds 10 more points | adauga inca 10 puncte
	cout << card6;
	cout << card3;

	cout << endl << "-------------------------------------" << endl << "Operator preincrement" << endl;
	//preincrement
	card6 = ++card3;		// adds 10 more points | adauga inca 10 puncte
	cout << card6;
	cout << card3;
	cout << endl << "-------------------------------------" << endl << "Operator postdecrement" << endl;
	//postdecrement
	card6 = card3--;		// removes the last entry in the points array
	cout << card6;
	cout << card3;

	cout << endl << "-------------------------------------" << endl << "Operator predecrement" << endl;
	//predecrement
	card6 = --card3;		// removes the last entry in the points array
	cout << card6;
	cout << card3;

	cout << endl << "--------------------------------------" << endl << "Operator >" << endl;
	if (card6 > card2) {
		cout << endl << card6.getName() << " has more points than " << card2.getName();
	}
	if (cardTest > card) {
		cout << endl << cardTest.getName() << " has more points than " << card.getName();
	}
	cout << endl << "--------------------------------------" << endl << "Operator < " << endl;
	if (card6 < card2) {
		cout << endl << card6.getName() << " has less points than " << card2.getName();
	}
	if (card < cardTest) {
		cout << endl << card.getName() << " has less points than " << cardTest.getName();
	}
	cout << endl << "--------------------------------------" << endl << "Operator ==" << endl;
	if (card6 == card2) {
		cout << endl << card6.getName() << " has the same amount of points as " << card2.getName();
	}
	if (card10 == cardTest) {
		cout << endl << card10.getName() << " has the same amount of points as " << cardTest.getName();
	}
	cout << endl << "--------------------------------------" << endl << "Operator >=" << endl;
	if (card6 >= card2) {
		cout << endl << card6.getName() << " has more or equal points than " << card2.getName();
	}
	if (card6 >= card2) {
		cout << endl << card6.getName() << " has more or equal points than " << card2.getName();
	}


	//explicit cast
	cout << endl <<"-------------------------------------"<<endl<< "Explicit cast:" << endl;
	//int totalPoints = (int)card3;		//get total points on the card | determina numarul total de puncte
	//cout <<endl<< totalPoints;
	cout << endl << "-------------------------------------" << endl << "Operator [ ]" << endl;
int somePoints2 = card3[1];//returns the number of points from the array on index 1 | intoarce numarul de puncte de pe pozitia 1 din vectorul de puncte
cout << somePoints2<<" ";
//	card3[0] = 25;						//allows you to change the points value at index 0 in the array | iti permite sa modifici numarul de puncte de la index 0 in vectorul de puncte					
cout << endl << "-------------------------------------" << endl << "Operator ( )" << endl;
	int partialSum = card3(1, 3);			//determines the sum of points from index 1 to 3 (including 3) | determina numarul de puncte de la indexul 1 pana la 3 (inclusiv)
	cout << partialSum;
	cout << endl << "--------------------------------------" << endl << "Operator !" << endl;
	card6 = !card3;						//returns a copy of card with 0 points | returneaza o copie a cardului 3 fara a pastra punctele
	cout << card6;

}