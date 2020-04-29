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
    std::vector<float> tabresultats;
    std::string nomfichier;
    std::string nomfichierpoids;
/*
    std::cout << "Veuillez indiquer le nom du fichier de poids a charger" << std::endl;
    couleurverte();
    std::cin >> nomfichierpoids;
    couleurcyan();
    std::cout << "Veuillez indiquer le nom du fichier a charger" << std::endl;
    couleurverte();
    std::cin >> nomfichier;
    couleurcyan();*/
    Graphe graphe("graphe_ameriquedusud_topo.txt","graphe_ameriquedusud_topo_poids.txt");



    while(choix!=5)
    {
        do
        {
            std::cout << "Bienvenue" << std::endl << "Que voulez vous faire?" << std::endl << "1.Charger un graphe" << std::endl << "2.Rien" << std::endl <<
                      "3. Calculer, afficher et sauvegarder les differents indices de centralite" << std::endl << "4.Dessiner" << std::endl << "5.Quitter" << std::endl;
            couleurverte();
            std::cin >> choix;
            couleurcyan();
        }
        while(choix < 1 || choix > 5);
        switch(choix)
        {
        case 1:
            graphe.afficher();
            break;
        case 2:
            std::cout<<std::endl;
            break;
        case 3:
            graphe.centralite_degre();
            graphe.centralite_degre_normalise();
            graphe.centralite_vecteur();
            graphe.centralite_vecteur_normalise();

            graphe.Dijsktra(tabresultats);
            graphe.centralite_proximite(tabresultats);
            tabresultats.clear();
            graphe.Dijsktra(tabresultats);
            graphe.centralite_proximite_normalise(tabresultats);

            graphe.Dijsktra(tabresultats);
            graphe.sauvegarde();
            break;
        case 4:
        {
            Svgfile svgfile;
            graphe.coloration();
            graphe.dessiner(&svgfile);
        }
        break;
        case 5:
            exit(0);
            break;
        }

    }

}
