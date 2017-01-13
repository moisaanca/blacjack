#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <fstream>


using namespace std;

ofstream fout("blackjack.txt");
void nivelDificultate();
void sumaPariata();
void permitInstructiuni();
void joacaUnJoc();
void creareCarti(int carti[]);
void afisareCarte(int carteJoc);
void afisareCartiJoc(int carti[], int nrCarti, bool ascundePrimaParte);
int valoareaCartii(int carteJoc);
int valoareaMainii(int carti[]);
int numarOarecare(int minim, int maxim);
void amestecCarti(int carti[], int marime);
int primaCarte(int carti[]);
void adaugaCarte(int pachet[], int carte);
void valoareAs(int jucator[]);
void as1sau11(int dealer[], int jucator[]);
void oprirePartida(int dealer[], int carti[], int jucator[]);
bool joacaAltaMana(char& raspuns);
bool carteNoua(char& raspuns);
void afisarePunctaj(int jucator[], int dealer[]);
void verificareCastigator(int jucator[], int dealer[]);
void blackjacksimplu(int jucator[], int dealer[], char joaca);
void blackjack(int jucator[], int dealer[], char joaca);
void verificareEliminare(int jucator[], int dealer[], char joaca);
bool continuareJoc(char& raspuns);
void afiseazaValoare(int carti[], int dimensiune);
void utilizator();


int nivel;
int primacarte;
int sumapariu;
int sumaTotala;

void afisreInstructiuni()
{
	
	cout << " -----------------------------------------------------------------------------------------" << endl;
	cout << "	Blackjack este un joc de cazinou foarte popular si este destul de usor de invatat.	 " << endl;
	cout << " Obiectivul de baza al jocului de blackjack este sa se obtina un total al cartilor	 	 " << endl;
	cout << " cat mai aproape posibil de numarul 21, insa daca numarul cumulat al mainii depaseste   " << endl;
	cout << " 21, atunci jucatorul pierde.															 " << endl;
	cout << "	Aspecte de retinut cu privire la regulile de blackjack:								 " << endl;
	cout << "  *Probabil cel mai important lucru de retinut in blackjack este acela ca totalul		 " << endl;
	cout << " cartilor dintr-o mana nu poate depasi 21. 											 " << endl;
	cout << "  *Trebuie sa se ia in considerare faptul ca, daca dealerul are un total al cartilor	 " << endl;
	cout << " mai mic decat 16, atunci trebuie impartita inca o carte.								 " << endl;
	cout << "  *In cazul in care totalul cartilor dealerului depaseste 17, atunci dealerul nu va	 " << endl;
	cout << " mai primi carti suplimentare.															 " << endl;
	cout << "  *Jucatorii trebuie sa retina ca, in jocul de blackjack, un as poate fi calculat ca 1  " << endl;
	cout << " sau ca 11.																			 " << endl;
	cout << "  *Trebuie sa se retina ca, in acest joc, cartile cu figuri si cartea cu numarul 10     " << endl;
	cout << " sunt calculate fiecare la 10 puncte.													 " << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;

}

void nivelDificultate()
{
	cout << "Nivelul de dificultate ales este: " << endl;
	cout << "Usor(1) sau Greu(2)" << endl;
	cin >> nivel;
	if (nivel != 1 && nivel != 2)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "EROARE. Alegeti nivelul de dificultate folosind doar 1 sau 2." << endl;
		nivelDificultate();
	}
}

void utilizator()
{
	char nume[100];
	cout << "Nume utilizator: " << endl;
	cin >> nume;
	fout << "Nume utilizator: " ;
	fout << nume;
}
void sumaPariata()
{
	
	cout << "Suma pariata este:" << endl;
	cin >> sumapariu;
	fout << endl << "Suma pariata este: " << sumapariu << endl;
	
}

void permitInstructiuni()
{
	char aprobare;
	cout << endl;
	cout << "Doriti sa cititi instructiunile?" << endl;
	cout << "DA - 1 si NU - 2" << endl;
	cin >> aprobare;
	if (aprobare == '1')
	{
		afisreInstructiuni();
		sumaPariata();
		nivelDificultate();
	}
	if (aprobare == '2')
	{
		sumaPariata();
		nivelDificultate();
	}

	if (aprobare != '1' && aprobare != '2')
	{
		cout << "EROARE. Alegeti un raspuns valid(1 sau 2)";
		permitInstructiuni();
	}
}

void joacaUnJoc()
{
	char play = 'N';
	do
	{
		char retragere = 'D';
		int carti[52];
		creareCarti(carti);
		amestecCarti(carti, 51);
		int jucator[10] = { 0 };
		int dealer[10] = { 0 };
		adaugaCarte(jucator, primaCarte(carti));
		adaugaCarte(dealer, primaCarte(carti));
		adaugaCarte(jucator, primaCarte(carti));
		adaugaCarte(dealer, primaCarte(carti));
		cout << "________________________________________________________________________" << endl;
		cout << "Dealerul a impartit cartile si ti-a dat doua carti" << endl;
		blackjacksimplu(jucator, dealer, 'd');
		blackjack(jucator, dealer, 'D');
		cout << "Cartile tale: " << endl;
		afisareCartiJoc(jucator, 10, false);
		cout<<endl << "Cartile dealerului: " << endl;
		afisareCartiJoc(dealer, 10, true);
		valoareAs(jucator);
		while (carteNoua(retragere))
		{
			adaugaCarte(jucator, primaCarte(carti));
			cout << "Dealerul ti-a mai dat o carte" << endl;
			cout << "Cartile tale: " << endl;
			afisareCartiJoc(jucator, 10, false);
			valoareAs(jucator);
			verificareEliminare(jucator, dealer, 'd');
			blackjack(jucator, dealer, 'D');
		}
		oprirePartida(dealer, carti, jucator);
		cout << endl;
		verificareEliminare(jucator, dealer, 'D');
		blackjack(jucator, dealer, 'D');
		verificareCastigator(jucator, dealer);
		cout << endl;
		cout << "Suma castigata: " << sumapariu << endl;
	} while (joacaAltaMana(play));
}

void creareCarti(int carti[])
{
	int index, inima, romb, frunza, trefla;
	inima = 101;
	romb = 201;
	frunza = 301;
	trefla = 401;
	for (index = 0; index <= 13; index++)
		carti[index] = inima++;
	for (index = 13; index <= 26; index++)
		carti[index] = romb++;
	for (index = 26; index <= 39; index++)
		carti[index] = frunza++;
	for (index = 39; index <= 51; index++)
		carti[index] = trefla++;
}

void afisareCarte(int carteJoc)
{
	char tipCarte;
	if (carteJoc == 0)
		cout << "";
	else
		switch (carteJoc % 100)
	{
		case 1:
			cout << "A";
			break;
		case 11:
			cout << "J";
			break;
		case 12:
			cout << "Q";
			break;
		case 13:
			cout << "K";
			break;;
		case 14:
			cout << "A";
			break;

		default:
			cout << carteJoc % 100;
	}

	if (carteJoc == 0)
		cout << "";
	else
	{
		if (carteJoc >= 101 && carteJoc <= 114)
		{
			tipCarte = 3;
			cout << tipCarte;
		}
		if (carteJoc >= 201 && carteJoc <= 214)
		{
			tipCarte = 4;
			cout << tipCarte;
		}
		if (carteJoc >= 301 && carteJoc <= 314)
		{
			
			tipCarte = 6;
			cout << tipCarte;
			
		}
		if (carteJoc >= 401 && carteJoc <= 414)
		{
			
			tipCarte = 5;
			cout << tipCarte;
			
		}
	}

}

void afisareCartiJoc(int carti[], int nrCarti, bool ascundePrimaParte)
{
	int index;
	if (ascundePrimaParte == true)
		cout << "**";
	else
	{
		afisareCarte(carti[0]);
		cout << " ";
	}

	for (index = 1; index<nrCarti; index++)
	if (carti[index] != 0)
	{
		afisareCarte(carti[index]);
		cout << " ";
	}
	else
		cout << "";
}

int valoareaCartii(int carteJoc)
{
	int valoarecarte;
	switch (carteJoc % 100)
	{
	case 1:
		valoarecarte = 11;
		break;
	case 11:
	case 12:
	case 13:
		valoarecarte = 10;
		break;
	case 14:
		valoarecarte = 1;
		break;
	default:
		valoarecarte = carteJoc % 100;
	}

	return valoarecarte;
}

int valoareaMainii(int carti[])
{
	int index, valoare = 0;
	for (index = 0; index < 9; index++)
		valoare = valoare + valoareaCartii(carti[index]);
	return valoare;
}

int numarOarecare(int minim, int maxim)
{
	static bool inceput = true;
	int nr;
	if (inceput)
	{
		srand(static_cast<unsigned int>(time(NULL)));
		inceput = false;
	}
	nr = rand() % (maxim - minim + 1) + minim;
	return nr;
}

void amestecCarti(int carti[], int marime)
{
	int index, primaCarte, aDouaCarte, aTreiaCarte;
	for (index = 0; index<500; index++)
	{
		primaCarte = 0;
		aDouaCarte = numarOarecare(0, marime);
		aTreiaCarte = numarOarecare(0, marime);
		primaCarte = carti[aDouaCarte];
		carti[aDouaCarte] = carti[aTreiaCarte];
		carti[aTreiaCarte] = primaCarte;
	}
}

int primaCarte(int carti[])
{
	int index;
	for (index = 0; index<51; index++)
	if (carti[index] != 0)
	{
		primacarte = carti[index];
		carti[index] = 0;
		return primacarte;
	}
}

void adaugaCarte(int pachet[], int carte)
{
	int index;
	for (index = 0; index<9; index++)
	if (pachet[index] == 0)
	{
		pachet[index] = carte;
		break;
	}
}

void valoareAs(int jucator[])
{
	int index, valoare, asul1sau11;
	for (index = 0; index < 9; index++)
	{
		valoare = valoareaCartii(jucator[index]);
		if (valoare == 11 || valoare == 1)
		{
			cout<<endl << "Asul poate fi punctat fie cu 1 punct, fie cu 11 puncte. Ce alegeti?";
			cout << endl;
			cin >> asul1sau11;
			if (asul1sau11 == 1)
				if (valoare == 11)
					jucator[index] += 13;
			else
				if (asul1sau11 == 11)
					if (valoare == 1)
						jucator[index] -= 13;
			//else
			if (asul1sau11 != 1 && asul1sau11 != 11)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "EROARE. Alegeti una din valorile 1 sau 11";
				valoareAs(jucator);
			}

		}
	}
}

void as1sau11(int dealer[], int jucator[])
{
	int index;
	for (index = 0; index < 9; index++)
	{
		if (valoareaCartii(dealer[index]) == 11 || valoareaCartii(dealer[index])== 1)
		if (valoareaCartii(dealer[index])==11)
		if (valoareaMainii(dealer) - valoareaCartii(dealer[index]) + 1 > valoareaMainii(jucator))
		if (valoareaMainii(dealer) - valoareaCartii(dealer[index]) + 1 < 22)
			dealer[index] += 13;
		else
		if (valoareaMainii(dealer) > 21)
			dealer[index] += 13;
		else
		if (valoareaMainii(dealer) - valoareaCartii(dealer[index]) + 11 > valoareaMainii(jucator))
		if (valoareaMainii(dealer) - valoareaCartii(dealer[index]) + 11 < 22)
			dealer[index] -= 13;
	}
}

void oprirePartida(int dealer[], int carti[], int jucator[])
{
	int index;
	for (index = 0; index < 9; index++)
	{
		if (valoareaMainii(dealer) < 17)
		if (nivel == 1)
			adaugaCarte(dealer, primaCarte(carti));
		else
		if (nivel == 2)
		{
			adaugaCarte(dealer, primaCarte(carti));
			as1sau11(dealer, jucator);
		}
		else
		if (index == 0)
		{
			cout << "Dealerul se opreste" << endl;
			break;
		}
		else
		if (index == 1)
		{
			cout << "Dealerul mai ia o carte si se opreste" << endl;
			break;
		}
		else
		{
			cout << "Dealerul mai ia " << index << "carti si se opreste." << endl;
			break;
		}
		if (nivel == 2)
			as1sau11(dealer, jucator);
	}
}


bool joacaAltaMana(char& raspuns)
{
	cout << endl << "Jucati inca o tura? (D / N)" << endl;
	cin >> raspuns;
	cout << endl;
	if (raspuns == 'D' || raspuns == 'd')
	{
		system("cls");

		cout << "Suma pariata: " << endl;
		cin >> sumapariu;
		fout << "Suma pariata : " << sumapariu<<endl;
		joacaUnJoc();
		return true;
	}
	if (raspuns == 'N' || raspuns == 'n')
	{
		cout << "Jocul s-a terminat." << endl;
		exit(0);
	}
	if (raspuns != 'd' && raspuns != 'D' && raspuns != 'n' && raspuns != 'N')
	{
		cout <<endl<< "EROARE! Alegeti un raspuns valid( D sau N)." << endl;
		joacaAltaMana(raspuns);
	}
}

bool carteNoua(char& raspuns)
{
	cout << endl << "Doriti o alta carte? (D / N)" << endl;
	cin >> raspuns;
	if (raspuns == 'D' || raspuns == 'd')
		return true;
	//else
	if (raspuns == 'n' || raspuns == 'N')
		return false;
	if (raspuns != 'D' && raspuns != 'd ' && raspuns != 'n' && raspuns != 'N')
	{
		cout << "EROARE! Alegeti un raspuns valid ( D / N).";
		carteNoua(raspuns);
		
	}
}

void afisarePunctaj(int jucator[], int dealer[])
{
	cout << "Cartile jucatorului: ";
	afisareCartiJoc(jucator, 10, false);
	cout << "( " << valoareaMainii(jucator) << " puncte)" << endl;
	cout << "V.S." << endl;
	cout << "Cartile dealerului: ";
	afisareCartiJoc(dealer, 10, false);
	cout << "( " << valoareaMainii(dealer) << " puncte)" << endl;
}

void verificareCastigator(int jucator[], int dealer[])
{
	int punctajJucator, punctajDealer;
	punctajJucator = valoareaMainii(jucator);
	punctajDealer = valoareaMainii(dealer);
	afisarePunctaj(jucator, dealer);
	if ((punctajJucator < 22 && punctajJucator>punctajDealer) || (punctajDealer > 21 && punctajJucator < 22))
	{
		cout << endl;
		cout << "Ai castigat! Felicitari!" << endl;
		sumapariu += sumapariu;
	}
	else
	if (punctajJucator == punctajDealer)
	{
		cout << endl;
		cout << "Push in favoarea dealerului. 0:1 recompensa";
	}
	else
	{
		cout << endl;
		cout << "Ai pierdut." << endl;
		sumapariu -= sumapariu;
		fout << "Suma castigata: " << sumapariu << endl;
	}
}

void blackjacksimplu(int jucator[], int dealer[], char joaca)
{
	int punctajJucator, punctajDealer;
	punctajJucator = valoareaMainii(jucator);
	punctajDealer = valoareaMainii(dealer);
	if (punctajDealer != 21 && punctajJucator == 21)
	{
		afisarePunctaj(jucator, dealer);
		cout << endl << "BLACKJACK! Ai castigat! Primesti o recompensa de 3:2";
		sumapariu += 3 * sumapariu / 2;
		cout << "Suma castigata: " << sumapariu << endl;
		fout << "Suma castigata: " << sumapariu << endl;
		sumaTotala += sumapariu;
		joacaAltaMana(joaca);
	}
}

void blackjack(int jucator[], int dealer[], char joaca)
{
	int punctajJucator, punctajDealer;
	punctajJucator = valoareaMainii(jucator);
	punctajDealer = valoareaMainii(dealer);
	if (punctajDealer == 21 && punctajJucator == 21)
	{
		afisarePunctaj(jucator, dealer);
		cout << endl << "Blackjack atat pentru tine cat si pentru dealer. Push in favoarea ta cu o recompensa de 1:1" << endl;
		sumapariu += sumapariu;
		cout << "Suma castigata: " << sumapariu << endl;
		fout << "Suma castigata: " << sumapariu << endl;
		sumaTotala += sumapariu;
		joacaAltaMana(joaca);
	}
	if (punctajJucator == 21 && punctajDealer != 21)
	{
		cout << endl;
		afisarePunctaj(jucator, dealer);
		cout << endl << "BLACKJACK! Ai castigat o recompensa de 3:2" << endl;
		sumapariu = 3 * sumapariu / 2;
		cout << "Suma castigata: " << sumapariu << endl;
		fout << "Suma castigata: " << sumapariu << endl;
		sumaTotala += sumapariu;
		joacaAltaMana(joaca);
	}
}

void verificareEliminare(int jucator[], int dealer[], char joaca)
{
	int punctajJucator, punctajDealer;
	punctajJucator = valoareaMainii(jucator);
	punctajDealer = valoareaMainii(dealer);
	if (punctajJucator >= 22)
	{
		cout << "Ai pierdut! esti eliminat cu: " << punctajJucator << "puncte." << endl;
		sumapariu -= sumapariu;
		cout << "Suma castigata: " << sumapariu << endl;
		fout << "Suma castigata: " << sumapariu << endl;
		sumaTotala += sumapariu;
		joacaAltaMana(joaca);
	}
	if (punctajDealer >= 22)
	{
		afisarePunctaj(jucator, dealer);
		cout << endl << "Dealerul a pierdut. Ai castigat!" << endl;
		sumapariu += sumapariu;
		cout << "Suma castigata: " << sumapariu << endl;
		fout << "Suma castigata: " << sumapariu << endl;
		sumaTotala+=sumapariu;
		joacaAltaMana(joaca);
	}
}

bool continuareJoc(char& raspuns)
{
	cout << endl << "Doresti inca o carte? (D / N)" << endl;
	cin >> raspuns;
	if (raspuns == 'd' || raspuns == 'D')
		return true;
	else
	if (raspuns == 'n' || raspuns == 'N')
		return false;
	else
	{
		cout << "EROARE! Alegeti una din valorile D sau N"<<endl;
		continuareJoc(raspuns);
	}
}
void afiseazaValoare(int carti[], int dimensiune)
{
	int index;
	for (index = 0; index < dimensiune; index++)
		cout << index + 1 << ".)" << carti[index] << endl;
}

int main()
{
	system("color FC"); 
	cout << "                         BLACKJACK                      " << endl;
	utilizator();
	permitInstructiuni();
	//nivelDificultate();
	joacaUnJoc();

	return 1;
}
