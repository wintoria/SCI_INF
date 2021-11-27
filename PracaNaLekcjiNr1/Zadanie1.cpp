#include<iostream>
#include<cstring>
using namespace std;

class Szyfr																	//tworzenie klasy szyfrow
{
public:
	char text[1000];
	int dlugosc, klucz;

	void wczytaj()															//funkcja wczytywania wiadomosci
	{
		cout << "Podaj wiadomosc do zaszyfrowania: ";
		cin.getline(text, 1000);
		dlugosc = strlen(text);
	}

	void SzyfrCezar()														//funkcja szyfrowania kodem cezara
	{
		char znak;
		cout << "O ile przesunac: ";
		cin >> klucz;
		if (klucz <= 0 || klucz > 26)
		{
			cout << "Niepoprawna liczba\n";
			return;
		}

		for (int i = 0; i < dlugosc; i++)									//podstawianie znakow w wiadomosci
		{
			znak = text[i];
			if (znak >= 'a' && znak <= 'z')
			{
				znak = ((znak - 'a' + klucz) % 26) + 'a';
			}

			text[i] = znak;
		}
		printf("Zaszyfrowany tekst kodem cezara: %s \n", text);
	}

	void OdszyfrCezar()														//funkcja odszyfrowania kodem cezara
	{
		char znak;
		cout << "O ile przesunac: ";
		cin >> klucz;
		if (klucz <= 0 || klucz > 26)
		{
			cout << "Niepoprawna liczba\n";
			return;
		}

		for (int i = 0; i < dlugosc; i++)
		{
			znak = text[i];
			if (znak >= 'a' && znak <= 'z')
			{
				znak = ((znak - 'a' + (26 - klucz)) % 26) + 'a';
			}

			text[i] = znak;
		}
		printf("Odszyfrowany tekst kodem cezara: %s \n", text);
	}

	void Przestawienie()													//funkcja uzycia szyfru przestawieniowego
	{
		for (int i = 0; i < dlugosc - 1; i += 2)
		{
			char znak;
			znak = text[i];
			text[i] = text[i + 1];
			text[i + 1] = znak;

		}
		printf("Zaszyfrowany tekst kodem przestawieniowym: %s \n", text);
	}

};

int main()
{
	int wybor;
	Szyfr obj;
	obj.wczytaj();															//wczytanie wiadomosci

	cout << "Jaka operacje wykonac \n";
	cout << "1. Zaszyfruj kodem cezara \n";
	cout << "2. Zaszyfruj lub odszyfruj kodem przestawieniowym \n";			//wybor funkcji szyfrowania
	cout << "3. Zaszyfruj oboma kodami \n";
	cout << "4. Odszyfruj kodem cezara \n";
	cin >> wybor;

	switch (wybor){															//wykonanie wybranej funkcji
	case 1:
		obj.SzyfrCezar();
		break;
	case 2:
		obj.Przestawienie();
		break;
	case 3:
		obj.SzyfrCezar();
		obj.Przestawienie();
		break;
	case 4:
		obj.OdszyfrCezar();
		break;
	default:
		cout << "Niepoprawna liczba\n";
		return 0;
	}
}
