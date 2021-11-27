#include<iostream>
#include<cstring>
using namespace std;

class Szyfr																	//tworzenie klasy szyfrow
{
public:
	char text[1000];
	int dlugosc, klucz;
	int liczbypierwsze[19] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67 };
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

	void generujRSA()
	{
		srand(time(NULL));
		int x = rand() % 24;
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
	
	void wypiszRSA()
	{
		cout << "klucz publiczny: " << "n: " << n << " " << "e: " << e << endl;
		cout << "klucz prywatny: " << "n: " << n << " " << "d: " << d << endl;
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
	default:
		cout << "Niepoprawna liczba\n";
		return 0;
	}
}
