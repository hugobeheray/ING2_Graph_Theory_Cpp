#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include <vector>
#include "svgfile.h"
#include "menu.h"
#include "Coords.h"

int main(int argc, char *argv[])
{
   // menu();
    std::string nomfichier;
    //std::cout << "Veuillez indiquer le nom du fichier a charger" << std::endl;
    //std::cin >> nomfichier;
    Graphe graphe("graphe_cycle4_topo.txt");
    graphe.afficher();
    Svgfile svgfile;
    graphe.dessiner(&svgfile);
    return 0;
}

