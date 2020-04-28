#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include <vector>
#include "svgfile.h"
#include "menu.h"
#include "Coords.h"
#include "calculs.h"

int main(int argc, char *argv[])
{
   // menu();
    std::string nomfichier;
    std::string nomfichierpoids;
    //std::cout << "Veuillez indiquer le nom du fichier a charger" << std::endl;
    //std::cin >> nomfichier;
    Graphe graphe("graphe_cycle5_topo.txt","graphe_cycle5_topo_poids.txt");
    graphe.afficher();
    Svgfile svgfile;
    graphe.dessiner(&svgfile);

    graphe.centralite_degre();
    graphe.centralite_degre_normalise();
    graphe.centralite_vecteur();
    graphe.centralite_vecteur_normalise();
    return 0;
}

