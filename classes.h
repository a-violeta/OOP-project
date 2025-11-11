#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <iomanip>
#include <list>
#include <tuple>

/*
class MyException1 : public std::exception {
public:
	const char* what() const noexcept override {
		return "My exception 1\n";
	}
};
*/

class MyException2 : public std::exception {
private:
	std::string message;

public:
	MyException2(const std::string& s) : message("My exception 2: " + s) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};

class Decor //era interesant si cu asta abstracta dar implica schimbari multe
{
protected:
	long int cantitate;
	double pret_per_kg;

public:
	Decor(long int c = 0, double p = 0);
	virtual ~Decor();
	Decor(const Decor& g);
	Decor& operator=(const Decor& i);

	virtual long int get_cantitate() const { return this->cantitate; }
	virtual double get_pret_per_kg() const { return this->pret_per_kg; }

	void set_cantitate(long int c) { this->cantitate=c; }
	void set_pret_per_kg(double p) { this->pret_per_kg=p; }

	virtual bool operator==(const Decor& g) const;
	virtual bool operator!=(const Decor& p) const;

	friend void operator*(Decor& g, double k);

	friend std::ostream& operator<<(std::ostream& os, const Decor& p);
	friend std::istream& operator>>(std::istream& is, Decor& p);

	virtual void actualizare_cantitate(int procent);

	//virtual std::string gust() = 0;
};

Decor::Decor(long int c, double p){
	this->cantitate = c;
	this->pret_per_kg = p;
}

Decor::~Decor(){}

Decor::Decor(const Decor& g) {
	this->cantitate = g.cantitate;
	this->pret_per_kg = g.pret_per_kg;
}

Decor& Decor::operator=(const Decor& i) {
	if (this != &i) {
		this->cantitate = i.cantitate;
		this->pret_per_kg = i.pret_per_kg;
	}
	
	return *this;
}

bool Decor::operator==(const Decor& g) const
{
	if (cantitate == g.cantitate && pret_per_kg == g.pret_per_kg)
		return true;
	return false;
}

bool Decor::operator!=(const Decor& p) const
{
	if (*this == p)
		return false;
	return true;
}

void operator*(Decor& g, double k) {
	g.pret_per_kg *= k;
}

std::ostream& operator<<(std::ostream& os, const Decor& p)
{
	os << "Decor in cantitatea " << p.cantitate << " kg cu pretul per kg " << p.pret_per_kg << ".\n";
	return os;
}

std::istream& operator>>(std::istream& is, Decor& p)
{
	std::cout << "Introduceti cantitatea (in kg) si pretul per kg al decorului:\n";
	is >> p.cantitate >> p.pret_per_kg;
	return is;
}

void Decor::actualizare_cantitate(int procent) {
	//altfel nu modifica int ul cu o fractie, aproxima fractia la 1 si nu modifica nimic
	cantitate = static_cast<long int>(cantitate * (1 + procent / 100.0));
}

//---------------------------------------------------------------clear

bool validare_data_calendaristica(int z, int l, int a) {		//verific daca data e valida

	if (z < 1 or z > 31 or l < 1 or l > 12 or a < 1900 or a > 3000)	return 0;

	if (l == 2 and z > 29) return 0;

	if ((l == 4 || l == 6 || l == 9 || l == 11) && z > 30) return 0;

	if ((l == 2) && (a % 4) && (z > 28)) return 0;

	return 1;
}

bool validare_string(std::string s) {							//verific daca data e in format valid
	if (s.length() != 10) return 0;
	if (s[2] != '.' and s[5] != '.') return 0;

	for (int i = 0; i < 10; i++)
		if (i != 2 and i != 5
			and	s[i] != '0' and s[i] != '1' and s[i] != '2'
			and s[i] != '3' and s[i] != '4' and s[i] != '5'
			and s[i] != '6' and s[i] != '7' and s[i] != '8' 
			and s[i] != '9') return 0;
	return 1;
}

bool comparare_date(int z1, int z2, int l1, int l2, int a1, int a2) {

	//true e data1<data2

	if (a2 < a1) return 0;

	if (a1 == a2) {
		if (l1 == l2)
			return (z1 < z2);
		return (l1 < l2);
	}

	return (a1 < a2);
}

//---------------------------------------------------------------clear

class Pudra : public Decor{
private:
	int granulatie;

public:
	Pudra(long int c = 0, double p = 0, int g=0);
	~Pudra();
	Pudra(const Pudra& g);
	Pudra& operator=(const Pudra& i);

	void set_granulatie(int c) { this->granulatie = c; }

	bool operator==(const Pudra& g) const;
	bool operator!=(const Pudra& p) const;

	friend void operator*(Pudra& g, double k);

	friend std::ostream& operator<<(std::ostream& os, const Pudra& p);
	friend std::istream& operator>>(std::istream& is, Pudra& p);

};

Pudra::Pudra(long int c, double p, int g) : Decor(c,p) {
	this->granulatie = g;
}

Pudra::~Pudra() {}

Pudra::Pudra(const Pudra& g) : Decor(g.cantitate, g.pret_per_kg) { //sper ca sa era
	this->granulatie = g.granulatie;
}

Pudra& Pudra::operator=(const Pudra& i)
{
	if (this != &i) {
		this->cantitate = i.cantitate;
		this->pret_per_kg = i.pret_per_kg;
		this->granulatie = i.granulatie;
	}

	return *this;
}

bool Pudra::operator==(const Pudra& g) const
{
	if (cantitate == g.cantitate && pret_per_kg == g.pret_per_kg && granulatie==g.granulatie)
		return true;
	return false;
}

bool Pudra::operator!=(const Pudra& p) const
{
	if (*this == p)
		return false;
	return true;
}

void operator*(Pudra& g, double k) {
	g.pret_per_kg *= k;
}

std::ostream& operator<<(std::ostream& os, const Pudra& p)
{
	os << "Pudra de granulatie " << p.granulatie << " si cantitate " << p.cantitate << ".\n";
	return os;
}

std::istream& operator>>(std::istream& is, Pudra& p)
{
	//std::cout << "Introduceti cantitatea (in kg), pretul per kg al pudrei si granulatia (int):\n";
	//is >> p.cantitate >> p.pret_per_kg;

	is >> static_cast<Decor&>(p);

	std::cout << "Citire granulatie:\n";
	is >> p.granulatie;

	return is;
}

//------------------------------------------------------------de verificat sa mearga actualizare ce era

class Fondant : public Decor {
private:
	std::string culoare;
	
public:
	Fondant(long int c = 0, double p = 0, std::string cul = "");
	~Fondant();
	Fondant(const Fondant& f);
	Fondant& operator=(const Fondant& f);

	void set_culoare(std::string c) { this->culoare = c; }

	bool operator==(const Fondant& g) const;
	bool operator!=(const Fondant& p) const;

	friend void operator*(Fondant& g, double k);

	friend std::ostream& operator<<(std::ostream& os, const Fondant& p);
	friend std::istream& operator>>(std::istream& is, Fondant& p);
};

Fondant::Fondant(long int c, double p, std::string cul) : Decor(c,p) {
	this->culoare = cul;
}

Fondant::~Fondant() {}

Fondant::Fondant(const Fondant& f) : Decor(f.cantitate, f.pret_per_kg) {
	this->culoare = f.culoare;
}

Fondant& Fondant::operator=(const Fondant& f) {
	if (this != &f) {
		this->cantitate = f.cantitate;
		this->pret_per_kg = f.pret_per_kg;
		this->culoare = f.culoare;
	}
	return *this;
}

bool Fondant::operator==(const Fondant& g) const
{
	if (cantitate == g.cantitate && pret_per_kg == g.pret_per_kg && culoare == g.culoare)
		return true;
	return false;
}

bool Fondant::operator!=(const Fondant& p) const
{
	if (*this == p)
		return false;
	return true;
}

void operator*(Fondant& g, double k) {
	g.pret_per_kg *= k;
}

std::ostream& operator<<(std::ostream& os, const Fondant& p)
{
	os << "Fondant de culoare " << p.culoare << " si cantitate " << p.cantitate << ".\n";
	return os;
}

std::istream& operator>>(std::istream& is, Fondant& p)
{
	is >> static_cast<Decor&>(p);

	std::cout << "Citire culoare:\n";
	is >> p.culoare;

	return is;
}

//--------------------------------------------------------------------mai sus

class Foita : public Decor {
private:
	int nr_carate;

public:
	Foita(long int c = 0, double p = 0, int car = 0);
	~Foita();
	Foita(const Foita& f);
	Foita& operator=(const Foita& f);

	void set_nr_carate(int c) { this->nr_carate = c; }

	bool operator==(const Foita& g) const;
	bool operator!=(const Foita& p) const;

	friend void operator*(Foita& g, double k);

	friend std::ostream& operator<<(std::ostream& os, const Foita& p);
	friend std::istream& operator>>(std::istream& is, Foita& p);
};

Foita::Foita(long int c, double p, int car) : Decor(c, p) {
	this->nr_carate = car;
}

Foita::~Foita() {}

Foita::Foita(const Foita& f) : Decor(f.cantitate, f.pret_per_kg) {
	this->nr_carate = f.nr_carate;
}

Foita& Foita::operator=(const Foita& f) {
	if (this != &f) {
		this->cantitate = f.cantitate;
		this->pret_per_kg = f.pret_per_kg;
		this->nr_carate = f.nr_carate;
	}
	return *this;
}

bool Foita::operator==(const Foita& g) const
{
	if (cantitate == g.cantitate && pret_per_kg == g.pret_per_kg && nr_carate == g.nr_carate)
		return true;
	return false;
}

bool Foita::operator!=(const Foita& p) const
{
	if (*this == p)
		return false;
	return true;
}

void operator*(Foita& g, double k) {
	g.pret_per_kg *= k;
}

std::ostream& operator<<(std::ostream& os, const Foita& p)
{
	os << "Foita de " << p.nr_carate << " carate si cantitate " << p.cantitate << ".\n";
	return os;
}

std::istream& operator>>(std::istream& is, Foita& p)
{
	is >> static_cast<Decor&>(p);

	std::cout << "Citire carate:\n";
	is >> p.nr_carate;

	return is;
}

//---------------------------------------------------------------mai sus

class Fructe_mici : public Decor {
private:
	std::string nume_fruct;

public:
	Fructe_mici(long int c = 0, double p = 0, std::string nu="");
	~Fructe_mici();
	Fructe_mici(const Fructe_mici& f);
	Fructe_mici& operator=(const Fructe_mici& f);

	void set_nume_fruct(std::string c) { this->nume_fruct = c; }

	bool operator==(const Fructe_mici& g) const;
	bool operator!=(const Fructe_mici& p) const;

	friend void operator*(Fructe_mici& g, double k);

	friend std::ostream& operator<<(std::ostream& os, const Fructe_mici& p);
	friend std::istream& operator>>(std::istream& is, Fructe_mici& p);
};

Fructe_mici::Fructe_mici(long int c, double p, std::string nu) : Decor(c, p) {
	this->nume_fruct = nu;
}

Fructe_mici::~Fructe_mici() {}

Fructe_mici::Fructe_mici(const Fructe_mici& f) : Decor(f.cantitate, f.pret_per_kg) {
	this->nume_fruct = f.nume_fruct;
}

Fructe_mici& Fructe_mici::operator=(const Fructe_mici& f) {
	if (this != &f) {
		this->cantitate = f.cantitate;
		this->pret_per_kg = f.pret_per_kg;
		this->nume_fruct = f.nume_fruct;
	}
	return *this;
}

bool Fructe_mici::operator==(const Fructe_mici& g) const
{
	if (cantitate == g.cantitate && pret_per_kg == g.pret_per_kg && nume_fruct == g.nume_fruct)
		return true;
	return false;
}

bool Fructe_mici::operator!=(const Fructe_mici& p) const
{
	if (*this == p)
		return false;
	return true;
}

void operator*(Fructe_mici& g, double k) {
	g.pret_per_kg *= k;
}

std::ostream& operator<<(std::ostream& os, const Fructe_mici& p)
{
	os << "Fruct decorativ " << p.nume_fruct << " si cantitate " << p.cantitate << ".\n";
	return os;
}

std::istream& operator>>(std::istream& is, Fructe_mici& p)
{
	is >> static_cast<Decor&>(p);

	std::cout << "Citire nume fruct:\n";
	is >> p.nume_fruct;

	return is;
}

//---------------------------------------------------------------mai sus

class Desert
{
protected:
	std::string denumire;
	long int bucati;
	std::string data_fabricatiei;
	std::string data_expirarii;
	double pret;
	const Decor* decoratiunea;

public:
	Desert(std::string d="", long int b=0, std::string date1="02.01.2004", std::string date2="03.01.2004", double p=0, const Decor* dec=nullptr);
	virtual ~Desert();
	Desert(const Desert& de);
	Desert& operator=(const Desert& i);

	virtual std::string get_denumire() const { return this->denumire; }
	virtual std::string get_data_expirare() const { return this->data_expirarii; }
	virtual std::string get_data_fabricatie() const { return this->data_fabricatiei; }
	virtual long int get_bucati() const { return this->bucati; }
	virtual double get_pret() const { return this->pret; }
	virtual const Decor* get_decoratiunea() const { return this->decoratiunea; }

	void set_denumire(std::string z) { this->denumire = z; }
	void set_data_expirarii(std::string t) { this->data_expirarii = t; }
	void set_data_fabricatiei(std::string d) { this->data_fabricatiei = d; }
	void set_bucati(long int c) { this->bucati = c; }
	void set_pret(double p) { this->pret = p; }
	void set_decoratiunea(const Decor* g) { this->decoratiunea = g; }

	virtual bool operator==(const Desert & g) const;
	virtual bool operator!=(const Desert& p) const;

	friend std::ostream& operator<<(std::ostream& os, const Desert& p);
	friend std::istream& operator>>(std::istream& is, Desert& p);

	virtual bool validare()	const; //NEFOLOSITOARE

};

Desert::Desert(std::string d, long int b, std::string date1, std::string date2, double p, const Decor* dec) {
	this->denumire = d;
	this->bucati = b;
	this->data_expirarii = date2;
	this->data_fabricatiei = date1;
	this->pret = p;
	this->decoratiunea = dec;

	if (!this->validare()) {
		std::cout << "O data a fost introdusa gresit!\n";
	}
	
}

Desert::~Desert() {};							//delete decoratiunile?

Desert::Desert(const Desert& de) {

	denumire = de.denumire;
	bucati = de.bucati;
	data_expirarii = de.data_expirarii;
	data_fabricatiei = de.data_fabricatiei;
	pret = de.pret;
	decoratiunea = de.decoratiunea;

}

Desert& Desert::operator=(const Desert& i) {
	if (this != &i) {
		this->denumire = i.denumire;
		this->bucati = i.bucati;
		this->data_expirarii = i.data_expirarii;
		this->data_fabricatiei = i.data_fabricatiei;
		this->pret = i.pret;
		this->decoratiunea = i.decoratiunea;
	}
	
	return *this;
}

bool Desert::operator==(const Desert& g) const
{
	if (denumire == g.denumire && data_expirarii == g.data_expirarii && data_fabricatiei == g.data_fabricatiei && pret == g.pret && decoratiunea == g.decoratiunea && bucati == g.bucati)
		return true;
	return false;
}

bool Desert::operator!=(const Desert& p) const
{
	if (*this == p)
		return false;
	return true;
}

std::ostream& operator<<(std::ostream& os, const Desert& p)
{
	if (!p.validare()) {
		std::cout << "O data a fost introdusa gresit!\n";
	}

	//os << "Desertul " << p.denumire << " cu decor de " <<p.decoratiunea->get_pret_per_kg()/100<< " lei, fabricat la data " << p.data_fabricatiei << " expira la data " << p.data_expirarii << " este in cantitatea " << p.bucati << " bucati cu pretul " << p.pret << ".\n";
	if(p.decoratiunea)
		os << "Desertul " << p.denumire << " are decor de " << p.decoratiunea->get_pret_per_kg() / 100 << " lei.\n";
	else
		os << "Desertul " << p.denumire << " nu are decor si este in cantitatea de " << p.bucati << ".\n";

	return os;
}

std::istream& operator>>(std::istream& is, Desert& p)
{
	std::cout << "Introduceti denumirea (un singur cuvant), cantitatea, data fabricatiei si a expirarii (zz.ll.aaaa) si pretul desertului:\n";
	is >> p.denumire >> p.bucati >> p.data_fabricatiei >> p.data_expirarii >> p.pret;
	std::cout << "\n";

	return is;
}

bool Desert::validare()	const {						//validare data
	if (validare_string(data_expirarii) and validare_string(data_fabricatiei)) {
		int zi, luna, an, z, l, a;

		zi = stoi(data_expirarii.substr(0, 2));
		luna = stoi(data_expirarii.substr(3, 2));
		an = stoi(data_expirarii.substr(6, 4));

		z = stoi(data_fabricatiei.substr(0, 2));
		l = stoi(data_fabricatiei.substr(3, 2));
		a = stoi(data_fabricatiei.substr(6, 4));

		return (validare_data_calendaristica(z, l, a) && validare_data_calendaristica(zi, luna, an) && comparare_date(z, zi, l, luna, a, an));
	}

	return 0;
}

//------------------------------------------------------------------sa mearga

std::vector<Desert> citire_n_deserturi(int nr, const std::vector<Decor>& tipuri_decor)
{
	std::vector<Desert> v; //vector gol
	std::string den, d1, d2; //denumire si datele
	long int b; //nr bucati
	double p; //pret

	std::cout << "\nVom creea deserturile folosind variantele de decor standard:\n"; //decorul va fi luat din vect tipuri_decor

	int tipul;

	for (int i = 0; i < nr; i++) {

		std::cout << "\nIntroduceti denumirea (un singur cuvant), cantitatea (nr de bucati), data fabricatiei si a expirarii (sub forma zz.ll.aaaa) si pretul pe bucata:\n";
		std::cin >> den >> b >> d1 >> d2 >> p;
		std::cout << "\n";
		
		std::cout << "Ce tip de decor folositi la acest " << den << "? Alegeti un nr de la 1 la 8 sau 0 daca nu doriti\n";

		std::cin >> tipul;

		Desert pa;

		if (tipul) {
			pa.set_denumire(den);
			pa.set_bucati(b);
			pa.set_data_fabricatiei(d1);
			pa.set_data_expirarii(d2);
			pa.set_pret(p);
			pa.set_decoratiunea(&tipuri_decor[tipul - 1]);
		}
		else {
			pa.set_denumire(den);
			pa.set_bucati(b);
			pa.set_data_fabricatiei(d1);
			pa.set_data_expirarii(d2);
			pa.set_pret(p);
		}

		v.push_back(pa); //sau emplace back
	}

	return v;
}

void afisare_n_deserturi(std::vector<Desert> p)
{
	if (p.empty()) {
		std::cout << "Vectorul este gol!\n";
		return;
	}

	for (const Desert& pa : p)
		if(pa.get_decoratiunea())
		//std::cout << "Desertul " << pa.get_denumire() << " cu decor de " << pa.get_decoratiunea().get_pret_per_kg()/100 << " lei, fabricat la " << pa.get_data_fabricatie() << " expira la " << pa.get_data_expirare() << " este in cantitatea " << pa.get_bucati() << " bucati cu pretul " << pa.get_pret() << ".\n";
			std::cout << "Desertul " << pa.get_denumire() << " are decor de aproximativ " << pa.get_decoratiunea()->get_pret_per_kg() / 100 << " lei.\n";
		else
			std::cout << "Desertul " << pa.get_denumire() << " nu are decor si este in cantitatea " << pa.get_bucati() << " bucati.\n";


}

//-------------------------------------------------------------------schimbari in citire

class Rulade : public Desert {
private:
	int nr_felii;
public:
	Rulade(std::string d="", long int b=0, std::string date1="02.01.2004", std::string date2="03.01.2004", double p=0, Decor* dec=nullptr, int nr_fel=0);
	~Rulade();
	Rulade(const Rulade& r);
	Rulade& operator=(const Rulade& i);

	void set_nr_felii(int c) { this->nr_felii = c; }

	bool operator==(const Rulade& g) const;
	bool operator!=(const Rulade& p) const;

	friend std::ostream& operator<<(std::ostream& os, const Rulade& p);
	friend std::istream& operator>>(std::istream& is, Rulade& p);
};

Rulade::Rulade(std::string d, long int b, std::string date1, std::string date2, double p, Decor* dec, int nr_fel) : Desert(d,b,date1,date2,p,dec) {

	this->nr_felii = nr_fel;
}

Rulade::~Rulade() {}							//delete decorurile?

Rulade::Rulade(const Rulade& r) : Desert(r.denumire, r.bucati, r.data_fabricatiei, r.data_expirarii, r.pret, r.decoratiunea) {
	this->nr_felii = r.nr_felii;
}

Rulade& Rulade::operator=(const Rulade& i) {
	if (this != &i) {

		Desert::operator=(i);
		this->nr_felii = i.nr_felii;
	}

	return *this;
}

bool Rulade::operator==(const Rulade& g) const
{
	if (Desert::operator==(g) && nr_felii == g.nr_felii) //asta fara static cast
		return true;
	return false;
}

bool Rulade::operator!=(const Rulade& p) const
{
	if (*this == p)
		return false;
	return true;
}

std::ostream& operator<<(std::ostream& os, const Rulade& p)
{
	os << static_cast<const Desert&>(p);  // afișare partea din desert
	os << "Nr felii: " << p.nr_felii << "\n";
	return os;
}

std::istream& operator>>(std::istream& is, Rulade& p)
{
	is >> static_cast<Desert&>(p);  // citire partea din desert
	std::cout << "Nr felii: ";
	is >> p.nr_felii;
	return is;
}


//--------------------------------------------------------------sa mearga


class Prajituri : public Desert {
private:
	std::string forma;
public:
	Prajituri(std::string d="", long int b=0, std::string date1="02.01.2004", std::string date2="03.01.2004", double p=0, Decor* dec=nullptr, std::string fo="");
	~Prajituri();
	Prajituri(const Prajituri& p);
	Prajituri& operator=(const Prajituri& i);

	void set_forma(std::string c) { this->forma = c; }

	bool operator==(const Prajituri& g) const;
	bool operator!=(const Prajituri& p) const;

	friend std::ostream& operator<<(std::ostream& os, const Prajituri& p);
	friend std::istream& operator>>(std::istream& is, Prajituri& p);
};

Prajituri::Prajituri(std::string d, long int b, std::string date1, std::string date2, double p, Decor* dec, std::string fo) :Desert(d, b, date1, date2, p, dec) {
	this->forma = fo;
}

Prajituri::~Prajituri() {}

Prajituri::Prajituri(const Prajituri& r) : Desert(r.denumire, r.bucati, r.data_fabricatiei, r.data_expirarii, r.pret, r.decoratiunea) {
	this->forma = r.forma;
}

Prajituri& Prajituri::operator=(const Prajituri& i) {
	if (this != &i) {

		Desert::operator=(i);
		this->forma = i.forma;
	}

	return *this;
}

bool Prajituri::operator==(const Prajituri& g) const
{
	if (Desert::operator==(static_cast<const Desert&>(g)) && forma == g.forma) //asta cu static cast pt ca de ce nu
		return true;
	return false;
}

bool Prajituri::operator!=(const Prajituri& p) const
{
	if (*this == p)
		return false;
	return true;
}

std::ostream& operator<<(std::ostream& os, const Prajituri& p)
{
	os << static_cast<const Desert&>(p);  // afișare partea din Decor
	os << "Forma: " << p.forma << "\n";
	return os;
}

std::istream& operator>>(std::istream& is, Prajituri& p)
{
	is >> static_cast<Desert&>(p);  // citire partea din Decor
	std::cout << "Forma: ";
	is >> p.forma;
	return is;
}

//-------------------------------------------------------------sa mearga

std::vector<Desert*> citire_n_deserturi_diferite(int nr) {
	std::vector<Desert*> v;

	for (int i = 0; i < nr; ++i) {
		int tip;
		std::cout << "Ce desert doriti sa adaugati? (1 - Rulada, 2 - Prajitura): ";
		std::cin >> tip;

		if (tip == 1) {
			Rulade* r = new Rulade();   // Alocare dinamică
			v.push_back(r);
		}
		else if (tip == 2) {
			Prajituri* p = new Prajituri();
			v.push_back(p);
		}
		else {
			std::cout << "Tip invalid. Se sare peste.\n";
		}
	}

	return v;
}

void sterge_n_deserturi_diferite(std::vector<Desert*>& v) {
	for (auto d : v)
		delete d;
	v.clear();
}

void afisare_n_deserturi_diferite(const std::vector<Desert*>& v) { //downcasting & dynamic_cast
	int i = 0;
	for (auto& d : v) {
		i++;

		auto* rulada = dynamic_cast<Rulade*>(d);

		if (rulada) {
			rulada->set_bucati(i);
			rulada->set_denumire("Rulada" + std::to_string(i));
			rulada->set_nr_felii(i + 2);
			rulada->set_pret((double)i);

			std::cout << *(rulada);
		}
		else {

			auto* prajitura = dynamic_cast<Prajituri*>(d);

			if (prajitura) {
				prajitura->set_bucati(i);
				prajitura->set_denumire("Prajitura" + std::to_string(i));
				prajitura->set_forma("cub");
				prajitura->set_pret((double)i);

				std::cout << *(prajitura);
			}
		}
	}

}

//-------------------------------------------------------------sa mearga

class Magazin {
protected:
	std::string nume;
	long int stoc;

public:
	Magazin(std::string n="", long int s=0);
	virtual ~Magazin();
	Magazin(const Magazin& m);
	Magazin& operator=(const Magazin& m);

	virtual std::string get_nume() const { return this->nume; }
	virtual long int get_stoc() const { return this->stoc; }
	virtual const std::string get_produs() = 0; //e abstracta acum, magazinul e generic si nu are un tip de produs standard
	//era mai misto ca validare stoc sa fi fost asta

	void set_nume(std::string z) { this->nume = z; }
	void set_stoc(long int c) { this->stoc = c; }

	virtual bool operator==(const Magazin& g) const;
	virtual bool operator!=(const Magazin& p) const;
};

Magazin::Magazin(std::string n, long int s) {
	this->nume = n;
	this->stoc = s;
}

Magazin::~Magazin() {}

Magazin::Magazin(const Magazin& g) {
	nume = g.nume;
	stoc = g.stoc;
}

Magazin& Magazin::operator=(const Magazin& i) {
	if (this != &i) {
		this->nume = i.nume;
		this->stoc = i.stoc;
	}
	return *this;
}

bool Magazin::operator==(const Magazin& g) const
{
	if (nume == g.nume && stoc == g.stoc)
		return true;
	return false;
}

bool Magazin::operator!=(const Magazin& p) const
{
	if (*this == p)
		return false;
	return true;
}

//-----------------------------------------------------------------sa mearga

class Cofetarie: public Magazin
{
private:
	std::vector <Desert> deserturile;									//DECLARAREA
	static int nr_comenzi; //e a tuturor cofetariilor create
	std::list<std::tuple<std::string, std::string, double>> comenzi_acceptate; //avem nume cofetarie, nume persoana si pret

	static int nr_comenzi_ultima_interogare;

public:
	Cofetarie();
	Cofetarie(std::string n, long int s, std::vector <Desert> p, std::list<std::tuple<std::string, std::string, double>> co);
	~Cofetarie();
	Cofetarie(const Cofetarie& g);
	Cofetarie& operator=(const Cofetarie& i);

	virtual const std::string get_produs() override { return "deserturi"; }
	std::vector <Desert> get_deserturile() const { return this->deserturile; }

	void set_deserturile(std::vector <Desert> g) { this->deserturile = g; }

	//set_comenzi nu prea arata ok daca comenzile tin de static int nr_comenzi

	bool operator==(const Cofetarie& g);
	bool operator!=(const Cofetarie& p);  //se compara mai greu si e mai mult nefolositor

	friend std::ostream& operator<<(std::ostream& os, const Cofetarie& p);
	friend std::istream& operator>>(std::istream& is, Cofetarie& p);

	double aflare_profit();
	void actualizare_stoc();

	bool validare_stoc();

	void genereaza_comanda(const std::string& nume, double pret, bool accept);
	static int get_nr_comenzi();
	void afiseaza_comenzi_acceptate() const;

	static int get_noi_comenzi_de_la_ultima_interogare() {
		int diferenta = nr_comenzi - nr_comenzi_ultima_interogare;
		nr_comenzi_ultima_interogare = nr_comenzi;
		return diferenta;
	}
};

Cofetarie::Cofetarie() : Magazin(), comenzi_acceptate{} { //interesant
	this->deserturile = std::vector <Desert>();
}

Cofetarie::Cofetarie(std::string d, long int b, std::vector<Desert> g, std::list<std::tuple<std::string, std::string, double>> co) : Magazin(d, b), deserturile(std::move(g)), comenzi_acceptate(std::move(co)) {} //move???????

Cofetarie::~Cofetarie() {};							//delete deserturi?

Cofetarie::Cofetarie(const Cofetarie& g) : Magazin(g.nume, g.stoc) {
	deserturile = g.deserturile;
	comenzi_acceptate = g.comenzi_acceptate;
}

Cofetarie& Cofetarie::operator=(const Cofetarie& i) {
	if (this != &i) {

		Magazin::operator=(i);
		this->deserturile = i.deserturile;
		this->comenzi_acceptate = i.comenzi_acceptate;
	}
	
	return *this;
}

bool Cofetarie::operator==(const Cofetarie& g)
{
	if (nume == g.nume && stoc == g.stoc && deserturile == g.deserturile && comenzi_acceptate == g.comenzi_acceptate)
		return true;
	return false;
}

bool Cofetarie::operator!=(const Cofetarie& p)
{
	if (*this == p)
		return false;
	return true;
}


std::ostream& operator<<(std::ostream& os, const Cofetarie& p)
{
	os << "Cofetaria " << p.nume << " are un stoc total de " << p.stoc << " deserturi.\n";

	std::cout << "Doriti afisarea tuturor deserturilor? Tastati Y sau N\n";
	char raspuns;
	std::cin >> raspuns;
	if(raspuns=='Y')
		for (const Desert& pa : p.deserturile)
			os << pa;

	//afisare_n_paini(p.paini);

	return os;
}

std::istream& operator>>(std::istream& is, Cofetarie& p)
{
	try {
		int nr; //cate deserturi unice sunt

		std::cout << "Introduceti numele (un singur cuvant) si stocul total de deserturi:\n";
		is >> p.nume >> p.stoc;

		std::cout << "\nIntroduceti nr de tipuri de deserturi: ";
		is >> nr;
		std::cout << "\n";

		const std::vector<Decor>& tipuri_decor = { Decor(2, 40.5), Decor(34, 2.00), Decor(14, 8.99), Decor(32, 8.44), Decor(3, 5.55), Decor(17, 21.2), Decor(10, 3.33), Decor(7, 8.88) };
		p.deserturile = citire_n_deserturi(nr, tipuri_decor); //nu cred ca am mai pus exceptii si in asta

		if (!p.validare_stoc())
			throw MyException2("Date invalide pentru stoc!");

		return is;
	}
	catch (const MyException2& e) {
		std::cerr << "Eroare: " << e.what() << "\n";
		return is;
	}
}

double Cofetarie::aflare_profit()
{
	try {
		double s = 0;

		if (!this->validare_stoc())
			throw MyException2("Date invalide pentru stoc!");

		for (const Desert& pa : this->deserturile)
			s += pa.get_bucati() * pa.get_pret();

		for (const std::tuple<std::string, std::string, double>& comanda : comenzi_acceptate) {
			s += std::get<2>(comanda); //sper ca indexa de la 0
		}
		return s;
	}
	catch (const MyException2& e) {
		std::cerr << "Eroare: " << e.what() << "\n";
		return 0;
	}
}

void Cofetarie::actualizare_stoc() {

	std::cout << "Vom verifica daca deserturile au expirat si le vom sterge.\n";

	time_t timestamp;
	time(&timestamp);
	std::string data_curenta = ctime(&timestamp), l;
	//std::cout << data_curenta;
	int zi, luna, an;

	zi = stoi(data_curenta.substr(8, 2));
	l = data_curenta.substr(4, 3);
	an = stoi(data_curenta.substr(20, 4));


	if (l == "Jan") luna = 1;
	else if (l == "Feb") luna = 2;
	else if (l == "Mar") luna = 3;
	else if (l == "Apr") luna = 4;
	else if (l == "May") luna = 5;
	else if (l == "Jun") luna = 6;
	else if (l == "Jul") luna = 7;
	else if (l == "Aug") luna = 8;
	else if (l == "Sep") luna = 9;
	else if (l == "Oct") luna = 10;
	else if (l == "Nov") luna = 11;
	else if (l == "Dec") luna = 12;
	else luna = 0;

	if (!luna) {
		std::cout << "Luna incorecta\nAbandonare\n";
		return;
	}

	//std::cout << "Data curenta este: " << std::setfill('0') << std::setw(2) << zi << ":" << std::setfill('0') << std::setw(2) << luna << ":" << an << "\n";

	//deci zi luna an au data curenta

	int day, month, year;

	if (validare_data_calendaristica(zi, luna, an)) {

		deserturile.erase(std::remove_if(deserturile.begin(), deserturile.end(), [&](const Desert& des) {
			day = stoi(des.get_data_expirare().substr(0, 2));
			month = stoi(des.get_data_expirare().substr(3, 2));
			year = stoi(des.get_data_expirare().substr(6, 4));

			if (!comparare_date(zi, day, luna, month, an, year)) {
				stoc -= des.get_bucati();
				return true; // Se elimină
			}
			return false; // Se păstrează
			}), deserturile.end());

		/*
		for (int i = 0; i < paini.size(); i++) {
			day = stoi(paini[i].get_data_expirare().substr(0, 2));
			month = stoi(paini[i].get_data_expirare().substr(3, 2));
			year = stoi(paini[i].get_data_expirare().substr(6, 4));

			//std::cout << "Expira la: " << std::setfill('0') << std::setw(2) << day<<":" << std::setfill('0') << std::setw(2) << month << ":" << year << "\n";

			if (!comparare_date(zi, day, luna, month, an, year)) {
				//std::cout << "Se va sterge o Desert\n";
				stoc -= paini[i].get_bucati();
				//std::cout << stoc;
				paini.erase(paini.begin() + i);
				i--;
			}
		}
		*/
	}
}

bool Cofetarie::validare_stoc() {
	long int s = 0;

	for (const Desert& pa : deserturile) {
		s += pa.get_bucati();
	}

	if(s==this->get_stoc())
		return true;

	return false;
}

void Cofetarie::genereaza_comanda(const std::string& nume, double pret, bool accept) {
	nr_comenzi++;
	if (accept) {
		comenzi_acceptate.emplace_back(this->get_nume(), nume, pret);
	}
}

int Cofetarie::get_nr_comenzi() {
	return nr_comenzi;
}

void Cofetarie::afiseaza_comenzi_acceptate() const {
	std::cout << "Comenzi acceptate:\n";
	for (const auto& comanda : comenzi_acceptate) {
		if(std::get<0>(comanda) == this->get_nume()) //daca e corecta comanda si nu e a altei cofetarii (mergea o functie de validare)
			std::cout << "Comanda data de " << std::get<1>(comanda) << ", cu pretul: " << std::get<2>(comanda) << " lei\n";
	}
}

int Cofetarie::nr_comenzi = 0;
