
#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include <vector>
#include "svgfile.h"
#include "windows.h"

void afficher_parcours(size_t num, std::vector<int>& arbre)
{
    for(size_t i=0; i<arbre.size(); ++i)
    {
        if(i!=num)
        {
            if(arbre[i]!=-1)
            {
                std::cout<<i<<" <-- ";
                size_t j=arbre[i];
                while(j!=num)
                {
                    std::cout<<j<<" <-- ";
                    j=arbre[j];
                }
                std::cout<<j<<std::endl;
            }
        }
    }
}

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
    Graphe graphe;
    //Graphe graphe("metro_paris.txt","metro_paris_poids.txt");




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

            graphe.chargementPoids();
            graphe.chargementTopo();
            graphe.afficher();
            break;
        case 2:
            graphe.suppression_arete(&nomfichierpoids);
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
            tabresultats.clear();

            graphe.calcul_intermediarite(tabresultats);
            graphe.centralite_intermediarite(tabresultats);
            tabresultats.clear();

            graphe.calcul_intermediarite(tabresultats);
            graphe.centralite_intermediarite_normalise(tabresultats);

            //graphe.Dijsktra(tabresultats);
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
