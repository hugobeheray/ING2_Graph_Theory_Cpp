#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <stdio.h>
#include <vector>
#include <queue>
#include "Sommet.h"
#include <fstream>
#include <sstream>
#include <string>

class Graphe {
private:

    int m_orient;
    int m_taille;
    int m_indiceSommet;
    int m_indiceSommet2;
    char m_nom;
    int m_x,m_y;
    int m_ordre;
    int m_indiceArrete;
    int m_extrem1,m_extrem2;
    std::vector<Sommet*> m_tabsommet;


public:
    Graphe(std::string fichier);
    int getOrdre();
    void afficher() ;
    ~Graphe();
    void marquage(int num,bool marque[]);

};
#endif // GRAPHE_H_INCLUDED
