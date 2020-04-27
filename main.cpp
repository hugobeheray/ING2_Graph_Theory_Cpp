#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include <vector>
#include "svgfile.h"

int main(int argc, char *argv[])
{
    Graphe graphe("graphe_etoile1_topo.txt");
    graphe.afficher();
    Svgfile svgfile;

    return 0;
}

