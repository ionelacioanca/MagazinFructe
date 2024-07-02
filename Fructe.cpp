#include <iostream>
#include <list>
using namespace std;

class data_culegerii
{
private:
	int zi, luna, an;

public:
	data_culegerii(int zi, int luna, int an)
	{
		this->zi = zi;
		this->luna = luna;
		this->an = an;
	}

	void afisare_data()
	{
		cout << zi << "/" << luna << "/" << an << endl;
	}
};
class fruct
{
protected:
	int cantitate;
	string nume;
	float pret;
	int valabilitate;

	fruct(string nume, float pret, int cantitate, int valabilitate)
	{
		this->nume = nume;
		this->pret = pret;
		this->cantitate = cantitate;
		this->valabilitate = valabilitate;
	}

public:
	virtual void afisare_fruct()
	{
		cout << "- nume: " << nume << endl;
		cout << "- pret: " << pret << endl;
		cout << "- cantitate: " << cantitate << endl;
		cout << "- valabilitate (in zile): " << valabilitate << endl; 
	}

	virtual int getCantitate()
	{
		return cantitate;
	}

	virtual string getNume()
	{
		return nume;
	}

	virtual int getValabilitate()
	{
		return valabilitate;
	}

	virtual float getPret()
	{
		return pret;
	}
};

class fruct_autohton : private fruct
{
private:
	string judet, producator;
	data_culegerii* data;

public:
	fruct_autohton(string nume, float pret, int cantitate, int valabilitate, string judet, string producator, data_culegerii* data) : fruct(nume, pret, cantitate, valabilitate)
	{
		this->judet = judet;
		this->producator = producator;
		this->data = data;
	}

	void afisare_fruct()
		override
	{
		fruct::afisare_fruct();
		cout << "- judetul de provenienta: " << judet << endl;
		cout << "- producator: " << producator << endl;
		cout << "- data la care au fost culese fructele: "; data->afisare_data();
	}

	int getCantitate()
		override
	{
		return fruct::cantitate;
	}

	string getNume()
		override
	{
		return nume;
	}

	int getValabilitate()
		override
	{
		return valabilitate;
	}

	float getPret()
		override
	{
		return pret;
	}
};

class fruct_importat : private fruct
{
private:
	string tara, importator;

public:
	fruct_importat(string nume, float pret, int cantitate, int valabilitate, string tara, string importator) : fruct(nume, pret, cantitate, valabilitate)
	{
		this->tara = tara;
		this->importator = importator;
	}

	void afisare_fruct()
		override
	{
		fruct::afisare_fruct();
		cout << "- tara de provenineta: " << tara << endl;
		cout << "- importator: " << importator << endl;
	}

	int getCantitate()
		override
	{
		return fruct::cantitate;
	}

	string getNume()
		override
	{
		return nume;
	}

	int getValabilitate()
		override
	{
		return valabilitate;
	}

	float getPret()
		override
	{
		return pret;
	}
};

istream& operator >>(istream& in, fruct_autohton*& fa)
{
	string nume, judet, producator;
	float pret;
	int cantitate, valabilitate, zi, luna, an; 
	data_culegerii* data;

	cout << "nume: ";
	cin >> nume;
	cout << "cantitate: ";
	cin >> cantitate;
	cout << "pret: ";
	cin >> pret;
	cout << "valabilitate: ";
	cin >> valabilitate;
	cout << "judetul de provenienta: ";
	cin >> judet;
	cout << "producator: ";
	cin >> producator;
	cout << "data la care au fost culese fructele: "; 
	cin >> zi >> luna >> an;
	data = new data_culegerii(zi, luna, an);
	fa = new fruct_autohton(nume, pret, cantitate, valabilitate, judet, producator, data);
	return in;
}

istream& operator >>(istream& in, fruct_importat*& fi)
{
	string nume, tara, importator;
	float pret;
	int cantitate, valabilitate;

	cout << "nume: ";
	cin >> nume;
	cout << "cantitate: ";
	cin >> cantitate;
	cout << "pret: ";
	cin >> pret;
	cout << "valabilitate: ";
	cin >> valabilitate;
	cout << "tara de proveninenta: ";
	cin >> tara;
	cout << "importator: ";
	cin >> importator;
	fi = new fruct_importat(nume, pret, cantitate, valabilitate, tara, importator);
	return in;
}

int main()
{
	int optiune, optiune2, valabilitate_cautata, cantitate_fruct_cautata;
	int cantitate_ref;
	float max = -1;
	string nume_fruct_cautat;
	list<fruct*>fructe;
	list<fruct_autohton*>autohtone;
	list<fruct_importat*>importate;
	fruct* f;
	fruct_autohton* fa;
	fruct_importat* fi;
	while (true)
	{
		cout << "1. Adaugare fructe in stoc" << endl;
		cout << "2. Modificarea cantitatii daca s-a vandut din cea initiatala si stergerea fructului care nu se mai afla in stoc" << endl;
		cout << "3. Sortarea fructelor dupa nume" << endl;
		cout << "4. Cautarea si afisarea unui fruct dupa valabilitate" << endl;
		cout << "5. Afisarea intregului stoc" << endl;
		cout << "6. Afisarea fructelor de import care au cel mai mare pret" << endl;
		cout << "Introduceti optiunea dorita: ";
		cin >> optiune; 
		
		switch (optiune)
		{
		case 1:
			cout << "Ce fel de fructe doriti sa adaugati in stoc?" << endl;
			cout << "1. Fructe autohtone" << endl;
			cout << "2. Fructe importate" << endl;
			cin >> optiune2;

			switch (optiune2)
			{
			case 1:
				cin >> fa;
				autohtone.push_back(fa);
				f = (fruct*)fa;
				fructe.push_back(f);
				break;
			case 2:
				cin >> fi;
				importate.push_back(fi);
				f = (fruct*)fi;
				fructe.push_back(f);
				break;
			default:
				cout << "Optiunea introdusa nu este valida!";
				break;
			}
			break;
		case 2:
			cout << "Introduceti numele fructului pentru care ati avut vanzari azi: ";
			cin >> nume_fruct_cautat;
			cout << "Introduceti cantitatea de fruct vanduta: ";
			cin >> cantitate_fruct_cautata;
			for (fruct* x : fructe)
			{
				if (x->getNume() == nume_fruct_cautat)
				{
					cantitate_ref = x->getCantitate();
					cantitate_ref -= cantitate_fruct_cautata;
					if (x->getCantitate() == 0)
					{
						fructe.remove(x);
						autohtone.remove(dynamic_cast<fruct_autohton*>(x));
						importate.remove(dynamic_cast<fruct_importat*>(x));
						delete(x);
					}
					break;
				}
			}
			break;
		case 3:
			fructe.sort([](fruct* stanga, fruct* dreapta) { return stanga->getNume() < dreapta->getNume(); });
			for (fruct* x : fructe)
			{
				x->afisare_fruct();
				cout << endl;
			}
			break;
		case 4:
			cout << "Introduceti valabilitatea in functie de care cautati un anumit fruct: ";
			cin >> valabilitate_cautata;
			for (fruct* x : fructe)
			{
				if (x->getValabilitate() == valabilitate_cautata)
				{
					x->afisare_fruct();
				}
			}
			break;
		case 5:
			for (fruct* x : fructe)
			{
				x->afisare_fruct();
				cout << endl;
			}
			break;
		case 6:
			for (fruct_importat* i : importate)
			{
				if (max < i->getPret())
				{
					max = i->getPret();
				}
			}
			for (fruct_importat* i : importate)
			{
				if (max == i->getPret())
				{
					i->afisare_fruct();
				}
			}
			break;
		default:
			cout << "Optiunea introdusa nu este valida!";
			break;
		}
	}
	return 0;
}