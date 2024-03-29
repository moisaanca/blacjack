#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;
float sumapariu;
int primacarte;
void afisreInstructiuni()
{

	cout <<" -----------------------------------------------------------------------------------------" << endl;
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

void sumaPariata()
{
    cout<<"Suma pariata este:"<<endl;
    cin>>sumapariu;
}

void permitInstructiuni()
{
    int aprobare;
    cout << "						   BLACKJACK										" << endl;
	cout << endl;
	cout << "Doriti sa cititi instructiunile?"<< endl;
	cout << "DA - 1 si NU - 2"<<endl;
    cin>> aprobare;
    if(aprobare==1)
        {
            afisreInstructiuni();
            sumaPariata();
        }
    if(aprobare==2)
        sumaPariata();

    if(aprobare!=1 && aprobare!= 2)
    {
        cout<< "EROARE. Alegeti un raspuns valid(1 sau 2)";
        permitInstructiuni();
    }
}



void creareCarti(int carti[])
{
    int index, inima, romb, frunza, trefla;
    inima=101;
    romb=201;
    frunza=301;
    trefla=401;
    for(index=0;index<=13;index++)
        carti[index]=inima++;
    for(index=13;index<=26;index++)
        carti[index]=romb++;
    for(index=26;index<=39;index++)
        carti[index]=frunza++;
    for(index=39;index<=51;index++)
        carti[index]=trefla++;
}

void afisareCarte(int carteJoc)
{
char tipCarte;
   if(carteJoc==0)
        cout<<"";
   else
    switch (carteJoc % 100)
   {
   case 1:
    cout<<"A";
    break;
   case 11 :
    cout<<"J";
    break;
   case 12 :
    cout<<"Q";
    break;
   case 13 :
    cout<<"K";
    break;;
   case 14 :
    cout<<"A";
    break;

   default:
    cout<< carteJoc % 100;
   }

   if(carteJoc == 0)
    cout<<"";
   else
    {
       if(carteJoc>=101 && carteJoc<=114)
        {
            tipCarte=3;
            cout<<tipCarte;
        }
        if(carteJoc>=201 && carteJoc<=214)
        {
            tipCarte=4;
            cout<<tipCarte;
        }
        if(carteJoc>=301 && carteJoc<=314)
        {
            tipCarte=6;
            cout<<tipCarte;
        }
        if(carteJoc>=401 && carteJoc<=414)
        {
            tipCarte=5;
            cout<<tipCarte;
        }
    }

}

void afisareCartiJoc(int carti[], int nrCarti, bool ascundePrimaParte)
{
    int index;
    if(ascundePrimaParte==true)
        cout<<"**";
    else
    {
        afisareCarte(carti[0]);
        cout<<" ";
    }

    for(index=1;index<nrCarti;index++)
        if(carti[index] != 0)
    {
        afisareCarte(carti[index]);
        cout<<" ";
    }
    else
        cout<<"";
}

int valoareaCartii(int carteJoc)
{
    int valoarecarte;
    switch (carteJoc % 100)
    {
    case 1 :
        valoarecarte=11;
        break;
    case 11 :
    case 12 :
    case 13 :
        valoarecarte=10;
        break;
    case 14 :
        valoarecarte=1;
        break;
    default :
        valoarecarte=carteJoc % 100;
    }

    return valoarecarte;
}

void numarOarecare(int minim, int maxim)
{
    bool inceput=true;
    int nr;
    if(inceput != false)
    {
        srand( static_cast<unsigned int>(time(NULL)) );
        inceput=false;
    }
    nr=rand() % (maxim-minim + 1) + minim;
    return nr;
}

void amestecCarti( int carti[], int marime)
{
    int index, primaCarte, aDouaCarte, aTreiaCarte;
    for(index=0;index<350;index++)
    {
        primaCarte=0;
        aDouaCarte=numarOarecare(0, marime);
        aTreiaCarte=numarOarecare(0, marime);
        primaCarte=carti[aDouaCarte];
        carti[aDouaCarte]=carti[aTreiaCarte];
        carti[aTreiaCarte]=primaCarte;
    }
}

int primaCarte(int carti[])
{
    int index;
    for(index=0;index<51;index++)
        if(carti[index] != 0)
    {
        primacarte=carti[index];
        carti[index]=0;
        return primacarte;
    }
}

void adaugaCarte (int pachet[], int carte)
{
    int index;
    for(index=0;index<9;index++)
        if(pachet[index]==0)
    {
        pachet[index]=carte;
        break;
    }
}
 int main()
{
    permitInstructiuni();
    return 0;
}
