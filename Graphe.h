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
    int m_id1,m_id2;
    int m_ordre;
    std::vector<Sommet*> m_tabsommet;


public:
    Graphe(std::string fichier);
    void afficher() ;
    ~Graphe();
    void marquage(int num,bool marque[]);

};
#endif // GRAPHE_H_INCLUDED
