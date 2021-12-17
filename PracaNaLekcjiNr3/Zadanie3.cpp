#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<ctime>
using namespace std;

class Szyfr																	//tworzenie klasy szyfrow
{
public:
	char text[1000];
	int dlugosc, klucz;
	int liczbypierwsze[19] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79 };
	int n, d, e;

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

	int Euler(int a, int b)
	{
		while (a != b)
		{
			if (a < b)
				b -= a;
			else
				a -= b;
		}
		return a;
	}

	void generujRSA()														//funkcja generujaca klucze
	{
		srand(time(NULL));
		int x = rand() % 17;
		int p = liczbypierwsze[x];
		int q = liczbypierwsze[x + 1];
		int n = p * q;
		int tocjent = (p - 1) * (q - 1);
		int e = 2;
		int d = 2;
		while (e < tocjent)
		{
			if (Euler(e, tocjent) == 1)
				break;
			else
				e++;
		}
		while (d * e % tocjent != 1)
		{
			d++;
		}
		this->n = n;
		this->d = d;
		this->e = e;
	}

	void wypiszRSA()																	//funkcja wypisujaca klucze
	{
		cout << "klucz publiczny: " << "n: " << n << " " << "e: " << e << endl;
		cout << "klucz prywatny: " << "n: " << n << " " << "d: " << d << endl;
	}

	int powMod(int t, int w, int n)
	{
		int pow, wyn, q;

		pow = t;
		wyn = 1;

		for (q = w; q > 0; q /= 2)
		{
			if (q % 2) wyn = (wyn * pow) % n;
			pow = (pow * pow) % n;
		}

		return wyn;
	}

	void kodRSA()			//funkcja kodowania przy uzyciu RSA
	{
		int msg, e, n;
		cout << "Podaj liczbe do zakodowania: ";
		cin >> msg;
		cout << "Podaj e: ";
		cin >> e;
		cout << "Podaj n: ";
		cin >> n;
		cout << "Zakodowana wiadomosc: " << powMod(msg, e, n) << endl;
	}

	void odkodRSA()			//funkcja odkodowania przy uzyciu RSA
	{
		int msg, d, n;
		cout << "Podaj liczbe do odkodowania: ";
		cin >> msg;
		cout << "Podaj d: ";
		cin >> d;
		cout << "Podaj n: ";
		cin >> n;
		cout << "Odkodowana wiadomosc: " << int(pow(msg, d)) % n;
	}
};

int main()
{
	int wybor;
	Szyfr obj;
	obj.wczytaj();															//wczytanie wiadomosci

	cout << "Jaka operacje wykonac \n";
	cout << "1. Zaszyfruj kodem cezara \n";
	cout << "2. Zaszyfruj lub odszyfruj kodem przestawieniowym \n";			//wybor funkcji
	cout << "3. Zaszyfruj oboma kodami \n";
	cout << "4. Odszyfruj kodem cezara \n";
	cout << "5. Wygeneruj klucz RSA \n";
	cout << "6. Zakoduj widomosc korzystajac z RSA (liczba)\n";
	cout << "7. Odkoduj widomosc korzystajac z RSA (liczba)\n";
	cin >> wybor;

	switch (wybor) {															//wykonanie wybranej funkcji
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
	case 5:
		obj.generujRSA();
		obj.wypiszRSA();
		break;
	case 6:
		obj.generujRSA();
		obj.wypiszRSA();
		obj.kodRSA();
		break;
	case 7:
		obj.odkodRSA();
		break;
	default:
		cout << "Niepoprawna liczba\n";
		return 0;
	}
}
