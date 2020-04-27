#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include <vector>

int main(int argc, char *argv[])
{
    Graphe graphe("graphe_etoile1_topo.txt");
    graphe.afficher();

    return 0;
}
