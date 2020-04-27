#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <stdio.h>
#include <vector>
#include <queue>
#include "Sommet.h"
#include <fstream>
#include <sstream>
#include <string>
#include "Arete.h"
#include "svgfile.h"
#include "Coords.h"

class Graphe {
private:

    int m_orient;
    int m_taille;
    int m_indiceSommet2;
    int m_indiceSommet;
    int m_ordre;
    std::vector<Sommet*> m_tabsommet;
    std::vector<Arete*> m_tabarete;
    std::vector<Coords*> m_tabcoords;


public:
    Graphe(std::string fichier);
    int getOrdre();
    int getTaille();
    void afficher();
    ~Graphe();
    void marquage(int num,bool marque[]);
    void dessiner(Svgfile *svgout);

};
#endif // GRAPHE_H_INCLUDED
