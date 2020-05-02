#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include <vector>
#include "svgfile.h"
#include "windows.h"

///affichage du parcours
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

///ssprgm permettant de changer la couleur dans la console
void couleurverte()
{
    HANDLE couleurcin=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(couleurcin, 10);
}
void couleurbleue()
{
    HANDLE couleurcin=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(couleurcin, 11);
}
void couleurjaune()
{
    HANDLE couleurcin=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(couleurcin, 14);
}

void menu()
{
    couleurbleue();
    int choix;

    ///Pour une bonne gestion du blindage menu
    bool blindagemenu=false;
    bool blindagemenu2=false;
    int choixnomfichier;
    std::vector<float> tabresultats;
    std::string nomfichierpoids,nomfichiertopo;

    Graphe graphe;

    ///Tant qu'on ne quitte pas l'application...
    while(choix!=6)
    {
        do
        {
            couleurjaune();
            std::cout << "\n\n\t\t\t\tBienvenue dans notre projet Theorie des graphes !\n\n" << std::endl;
            std::cout << "\t\t\t\t\t    Que voulez vous faire ?\n\n" << std::endl;
            couleurbleue();
            std::cout << "\t\t1 - Charger un graphe" << std::endl << "\t\t2 - Supprimer une arete" << std::endl <<
                      "\t\t3 - Calculer, afficher et sauvegarder les differents indices de centralite" << std::endl << "\t\t4 - Dessiner(impossible avant calculs)" << std::endl << "\t\t5 - Tester la connexite" <<  std::endl << "\t\t6 - Quitter\n\n\n\n" << std::endl;
            couleurverte();
            std::cin >> choix;
            if(choix==4 && blindagemenu==false)
            {
                do
                {
                    couleurbleue();
                    std::cout << "Impossible de dessiner avant de faire les calculs d'indices. Veuillez resaisir un choix" << std::endl;
                    couleurverte();
                    std::cin >> choix;
                }while(choix==4 || choix <1 || choix >6);
            }
            if(choix==2 && blindagemenu2==false || choix==3 && blindagemenu2==false || choix==4 && blindagemenu2==false || choix==5 && blindagemenu2==false)
            {
                do
                {
                    couleurbleue();
                    std::cout << "Impossible d'effectuer des actions avant de charger un graphe. Veuillez resaisir un choix" << std::endl;
                    couleurverte();
                    std::cin >> choix;
                }while(choix!=1 || choix <1 || choix >6);
            }
            couleurbleue();
        }
        while(choix < 1 || choix > 6);

        ///En fonction du choix de l'utilisateur...
        switch(choix)
        {
        case 1:
            blindagemenu=false;
            blindagemenu2=true;
            couleurbleue();
            std::cout << "Veuillez indiquer le nom du fichier a charger\n\n\n" << std::endl;
            std::cout <<"\t 1- Graphe Etoile 1\n\t 2- Graphe Etoile 3\n\t 3- Graphe Cycle 4" << std::endl;
            std::cout <<"\t 4- Graphe Cycle 5\n\t 5- Graphe Amerique du Sud\n\t 6- Graphe Metro Parisien" << std::endl;
            couleurverte();
            std::cin >> choixnomfichier;
            while(choixnomfichier<1 || choixnomfichier>6)
            {
                couleurbleue();
                std::cout << "Erreur de saisie. Veuillez saisir un choix valide." << std::endl;
                couleurverte();
                std::cin >> choixnomfichier;
            }
            if(choixnomfichier==1) {nomfichierpoids="graphe_etoile1_topo_poids.txt";nomfichiertopo="graphe_etoile1_topo.txt";}
            if(choixnomfichier==2) {nomfichierpoids="graphe_etoile3_topo_poids.txt";nomfichiertopo="graphe_etoile3_topo.txt";}
            if(choixnomfichier==3) {nomfichierpoids="graphe_cycle4_topo_poids.txt";nomfichiertopo="graphe_cycle4_topo.txt";}
            if(choixnomfichier==4) {nomfichierpoids="graphe_cycle5_topo_poids.txt";nomfichiertopo="graphe_cycle5_topo.txt";}
            if(choixnomfichier==5) {nomfichierpoids="graphe_ameriquedusud_topo_poids.txt";nomfichiertopo="graphe_ameriquedusud_topo.txt";}
            if(choixnomfichier==6) {nomfichierpoids="graphe_metro_paris_topo_poids.txt";nomfichiertopo="graphe_metro_paris_topo.txt";}
            couleurbleue();
            graphe.chargementPoids(nomfichierpoids);
            graphe.chargementTopo(nomfichiertopo);
            graphe.afficher();
            break;
        case 2:
            graphe.suppression_arete(nomfichierpoids,nomfichiertopo,graphe);
            std::cout<<std::endl;
            break;
        case 3:
            blindagemenu=true;
            graphe.centralite_degre();
            graphe.centralite_degre_normalise();
            graphe.centralite_vecteur_normalise();
            graphe.centralite_vecteur();
            //tabresultats.clear();

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
            tabresultats.clear();

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
