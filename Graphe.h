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
    std::vector<int> DFS(int num_s0) ;
    void marquage(int num,bool marque[]);
    std::vector<int> BFS(int num_s0) ;
    void rechercher_afficher_CC();
};
#endif // GRAPHE_H_INCLUDED
