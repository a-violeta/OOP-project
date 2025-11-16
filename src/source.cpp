#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include "classes.h"
#include <stdlib.h>

void uiMeniu() {
	std::cout << "+++++++++++++++++++++++++++++++\n";
    std::cout << " Introdu 1 pentru a creea decor comestibil\n";
    std::cout << " Introdu 2 pentru a actualiza cantitatea de fondant\n"; //functionalitate
    std::cout << " Introdu 3 pentru a creste pretul decorului comestibil\n"; //op* friend
    std::cout << " Introdu 4 pentru a verifica daca 2 feluri de decor comestibil sunt identice sau nu\n"; //op== membru

	std::cout << " Introdu 5 pentru a citi si afisa n deserturi\n";

    std::cout << " Introdu 6 pentru a afla profitul unei cofetarii\n"; //functionalitate
    std::cout << " Introdu 7 pentru a actualiza stocul unei cofetarii\n"; //functionalitate mai complexa

    std::cout << " Introdu 8 pentru a citi si afisa n deserturi diferite\n";

    //si Desert validare() e o functionalitate mai complexa

    //noile chestii sunt 2 (modificat) si 8

    std::cout << " Pentru a iesi din program apasa 0\n";
    std::cout << "-------------------------------\n\n";
}

void meniu() {
    bool stop = false;
    int opt;
    while (stop == false) {
        uiMeniu();
        std::cout << "Introdu optiunea: ";
        std::cin >> opt;

        switch (opt) {
        case 1: {
            try {
                Decor g;
                std::cin >> g;

                if (g.get_cantitate() <= 0 || g.get_pret_per_kg() <= 0)
                    throw MyException2("Date invalide pentru decor: cantitate sau pret nule!");

                std::cout << "Decorul comestibil creat:\n" << g << "\n";
            }
            catch (const MyException2& e) {
                std::cerr << "Eroare: " << e.what() << "\n";
            }

            break;
        }
        case 2: {
            Fondant g(10, 20.50, "verde");
            int nr;

            std::cout << g;

            std::cout << "Introduceti procentul pentru actualizare. Daca valoarea rezultata nu este una intreaga aceasta se va aproxima in jos. ";
            std::cin >> nr;

            g.actualizare_cantitate(nr);
            std::cout << "\n" << g;

            break;
        }
        case 3: {
            Decor g(14, 54.70);
            double nr;

            std::cout << g;

            std::cout << "Introduceti de cate ori va creste pretul decorului comestibil: ";
            std::cin >> nr;

            g*nr;
            std::cout << "\n" << g;
            break;
        }
        case 4: {
            try {
                Decor g1(40, 74.20), g2;

                std::cout << g1;

                std::cin >> g2;

                if (g2.get_cantitate() <= 0 || g2.get_pret_per_kg() <= 0)
                    throw MyException2("Date invalide pentru decor: cantitate sau pret nule!");

                if (g1 == g2)
                    std::cout << "Este acelasi.\n";
                else
                    std::cout << "Nu este acelasi.\n";
            }
            catch (const MyException2& e) {
                std::cerr << "Eroare: " << e.what() << "\n";
            }

            break;
        }
        case 5: {
            int nr2;
            std::cout << "Cate deserturi?\n";
            std::cin >> nr2;

            if (nr2 > 0) {
                const std::vector<Decor>& tipuri_decor = { Decor(2, 40.5), Decor(34, 2.00), Decor(14, 8.99), Decor(32, 8.44), Decor(3, 5.55), Decor(17, 21.2), Decor(10, 3.33), Decor(7, 8.88) };
                std::vector<Desert> k = citire_n_deserturi(nr2, tipuri_decor); //daca fac vectorul de Decor in functia citeste_n_paini isi pierde scopul si se sterge pana sa apelez afisarea

                std::cout << "S au creat:\n";
                afisare_n_deserturi(k);
            }
            else
                std::cout << "Nr prea mic.\n";
            break;
        }
        case 6: {
            //std::vector<Decor> tipuri_decor = { Decor(2, 40.5), Decor(34, 2.00), Decor(14, 8.99), Decor(32, 8.44), Decor(3, 5.55), Decor(17, 21.2), Decor(10, 3.33), Decor(7, 8.88) };
            //std::vector<Desert> tipuri_desert = { Desert(), Desert(34, 2.00), Desert(14, 8.99), Desert(32, 8.44), Desert(3, 5.55), Desert(17, 21.2), Desert(10, 3.33), Desert(7, 8.88) };
            try {
                int nr2;
                std::cout << "Cate deserturi?\n";
                std::cin >> nr2;

                const std::vector<Decor>& tipuri_decor = { Decor(2, 40.5), Decor(34, 2.00), Decor(14, 8.99), Decor(32, 8.44), Decor(3, 5.55), Decor(17, 21.2), Decor(10, 3.33), Decor(7, 8.88) };

                std::vector<Desert> k = citire_n_deserturi(nr2, tipuri_decor);

                std::string nume;
                long int stoc;
                std::cout << "Introduceti numele (un singur cuvant) si cate deserturi are cofetaria:\n";
                std::cin >> nume >> stoc;

                if (nume.empty() || nume.find(' ') != std::string::npos || stoc <= 0)
                    throw MyException2("Date invalide pentru numele sau stocul cofetariei!");

                Cofetarie b;

                b.set_nume(nume);
                b.set_stoc(stoc);
                b.set_deserturile(k);
                //b.genereaza_comanda("Enache Pop", 50.00, 1);

                std::cout << "Profitul cofetariei este: " << b.aflare_profit() << ".\n";
            }
            catch (const MyException2& e) {
                std::cerr << "Eroare: " << e.what() << "\n";
            }

            break;
        }
        case 7: {
            try {
                int nr2;
                std::cout << "Cate deserturi?\n";
                std::cin >> nr2;

                const std::vector<Decor>& tipuri_decor = { Decor(2, 40.5), Decor(34, 2.00), Decor(14, 8.99), Decor(32, 8.44), Decor(3, 5.55), Decor(17, 21.2), Decor(10, 3.33), Decor(7, 8.88) };
                std::vector<Desert> k = citire_n_deserturi(nr2, tipuri_decor);

                std::string nume;
                long int stoc;
                std::cout << "Introduceti numele (un singur cuvant) si cate deserturi are cofetaria:\n";
                std::cin >> nume >> stoc;

                if (nume.empty() || nume.find(' ') != std::string::npos || stoc <= 0)
                    throw MyException2("Date invalide pentru numele sau stocul cofetariei!");


                Cofetarie b;

                b.set_nume(nume);
                b.set_stoc(stoc);
                b.set_deserturile(k);
                b.genereaza_comanda("Enache Pop", 25.00, 1);

                std::cout << b << "\n";
                b.actualizare_stoc();
                std::cout << b << "\n";

            }
            catch (const MyException2& e) {
                std::cerr << "Eroare: " << e.what() << "\n";
            }

            break;
        }
        case 8: {
            int nr2;
            std::cout << "Cate deserturi?\n";
            std::cin >> nr2;

            if (nr2 > 0) {
                std::vector<Desert*> k = citire_n_deserturi_diferite(nr2); //alocare cu new, altfel isi iese din scop
                
                std::cout << "S au creat:\n";
                afisare_n_deserturi_diferite(k);

                sterge_n_deserturi_diferite(k); //delete
            }
            else
                std::cout << "Nr prea mic.\n";
            break;
        }
        case 0:

            stop = true;
            break;
        default:
            std::cout << "Optiune nevalida! Incearca din nou.\n";
        }

        system("pause");
        system("cls");

    }
}

int main()
{
    meniu();

    return 0;
}