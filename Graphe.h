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
    int m_indiceSommet;
    int m_ordre;
    std::vector<Sommet*> m_tabsommet;
    std::vector<Arete*> m_tabarete;
    std::vector<Coords*> m_tabcoords;
    std::vector <float> m_tabdegre;
    std::vector<Arete*> m_tabpoids;
    std::vector <float> res_cd;
    std::vector <float> res_cdn;
    std::vector <float> res_cv;
    std::vector <float> res_cvn;


public:
    Graphe(std::string fichier,std::string fichierpoids);
    int getOrdre();
    int getTaille();
    void afficher();
    void centralite_degre();
    void centralite_degre_normalise();
    ~Graphe();
    //void marquage(int num,bool marque[]);
    void dessiner(Svgfile *svgout);
    void centralite_vecteur();
    void centralite_vecteur_normalise();
    void Dijkstra();
    void centralite_proximite();
    void centralite_proximite_normalise();
    void sauvegarde();


};
#endif // GRAPHE_H_INCLUDED
