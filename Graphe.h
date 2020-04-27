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

class Graphe {
private:

    int m_orient;
    int m_taille;
    int m_indiceSommet2;
    int m_indiceSommet;
    int m_ordre;
    std::vector<Sommet*> m_tabsommet;
    std::vector<Arete*> m_tabarete;


public:
    Graphe(std::string fichier);
    int getOrdre();
    void afficher() ;
    ~Graphe();
    void marquage(int num,bool marque[]);

};
#endif // GRAPHE_H_INCLUDED
