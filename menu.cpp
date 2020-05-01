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
    std::string nomfichierpoids,nomfichiertopo;
    int choixnomfichierpoids;


    Graphe graphe;




    while(choix!=6)
    {
        do
        {
            std::cout << "Bienvenue" << std::endl << "Que voulez vous faire?" << std::endl << "1.Charger un graphe" << std::endl << "2.Supprimer une arete" << std::endl <<
                      "3. Calculer, afficher et sauvegarder les differents indices de centralite" << std::endl << "4.Dessiner" << std::endl << "5.Tester la connexite" <<  std::endl << "6.Quitter" << std::endl;
            couleurverte();
            std::cin >> choix;
            couleurcyan();
        }
        while(choix < 1 || choix > 6);
        switch(choix)
        {
        case 1:
   couleurcyan();
            std::cout << "Veuillez indiquer le nom du fichier a charger\n\n\n" << std::endl;
            std::cout <<"\t 1- Graphe Etoile 1\n\t 2- Graphe Etoile 3\n\t 3- Graphe Cycle 4" << std::endl;
            std::cout <<"\t 4- Graphe Cycle 5\n\t 5- Graphe Amerique du Sud\n\t 6- Graphe Metro Parisien" << std::endl;
            couleurverte();
            std::cin >> choixnomfichierpoids;
            while(choixnomfichierpoids<1 || choixnomfichierpoids>6)
            {
                couleurcyan();
                std::cout << "Erreur de saisie. Veuillez saisir un choix valide." << std::endl;
                couleurverte();
                std::cin >> choixnomfichierpoids;
            }
            if(choixnomfichierpoids==1) {nomfichierpoids="graphe_etoile1_topo_poids.txt";nomfichiertopo="graphe_etoile1_topo.txt";}
            if(choixnomfichierpoids==2) {nomfichierpoids="graphe_etoile3_topo_poids.txt";nomfichiertopo="graphe_etoile3_topo.txt";}
            if(choixnomfichierpoids==3) {nomfichierpoids="graphe_cycle4_topo_poids.txt";nomfichiertopo="graphe_cycle4_topo.txt";}
            if(choixnomfichierpoids==4) {nomfichierpoids="graphe_cycle5_topo_poids.txt";nomfichiertopo="graphe_cycle5_topo.txt";}
            if(choixnomfichierpoids==5) {nomfichierpoids="graphe_ameriquedusud_topo_poids.txt";nomfichiertopo="graphe_ameriquedusud_topo.txt";}
            if(choixnomfichierpoids==6) {nomfichierpoids="graphe_metro_paris_topo_poids.txt";nomfichiertopo="graphe_metro_paris_topo.txt";}
            couleurcyan();
            graphe.chargementPoids(nomfichierpoids);
            graphe.chargementTopo(nomfichiertopo);
            graphe.afficher();
            break;
            break;
        case 2:
            graphe.suppression_arete(nomfichierpoids,nomfichiertopo,graphe);
            std::cout<<std::endl;
            break;
        case 3:
            graphe.centralite_degre();
            graphe.centralite_degre_normalise();
            graphe.centralite_vecteur_normalise();
            graphe.centralite_vecteur();


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
            //graphe.sauvegarde();
            break;
        case 4:
        {
            Svgfile svgfile;
            graphe.coloration();
            graphe.dessiner(&svgfile);
        }
        break;
        case 5:
            graphe.TestConnexite();
            break;
        case 6:
            exit(0);
            break;
        }

    }

}
