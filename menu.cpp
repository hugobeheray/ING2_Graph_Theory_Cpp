#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include <vector>
#include "svgfile.h"
#include "windows.h"

void couleurverte()
{
    HANDLE couleurcin=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(couleurcin, 10);
}
void couleurcyan()
{
    HANDLE couleurcin=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(couleurcin, 3);
}

void menu()
{
    couleurcyan();
    int choix;
    while(choix!=5)
    {
        do
        {
            std::cout << "Bienvenue" << std::endl << "Que voulez vous faire?" << std::endl << "1.Charger un graphe" << std::endl << "2.Changer le systeme de ponderation d'un graphe" << std::endl <<
                      "3. Calculer, afficher et sauvegarder les differents indices de centralite" << std::endl << "4.Tester la vulnerabilite du graphe" << std::endl << "5.Quitter" << std::endl;
            couleurverte();
            std::cin >> choix;
            couleurcyan();
        }
        while(choix < 1 || choix > 5);
        switch(choix)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            exit(0);
            break;
        }

    }

}
