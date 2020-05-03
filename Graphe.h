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

class Graphe
{
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

    ///permet de stocker les differents resultats d'indices pour les sauvegarder par la suite
    std::vector <float> m_res_cd;
    std::vector <float> m_res_cdn;
    std::vector <float> m_res_cv;
    std::vector <float> m_res_cvn;
    std::vector <float> m_res_cp;
    std::vector <float> m_res_cpn;
    std::vector <float> m_res_ci;
    std::vector <float> m_res_cin;

    ///permet de stocker les differents resultats d'indices INITIAUX
    std::vector <float> m_res_cdn_initial;
    std::vector <float> m_res_cvn_initial;
    std::vector <float> m_res_cpn_initial;
    std::vector <float> m_res_cin_initial;


public:
    Graphe();
    ~Graphe();
    void couleurverte();
    void couleurjaune();
    void couleurbleue();
    void couleurbleufonce();
    void couleurturquoise();
    void couleurbleufluo();
    void couleurvertfonce();
    void couleurgrisclair();
    void couleurgrisfonce();
    void couleurvertfluo();
    void couleurblanc1();
    void couleurblanc();
    void couleurtest();
    int getOrdre();
   // int getTaille();
    void afficher();
    void centralite_degre();
    void centralite_degre_normalise(int &compteur_comparaison);
    void dessiner(Svgfile *svgout);
    void centralite_vecteur();
    void centralite_vecteur_normalise(int &compteur_comparaison);
    void centralite_proximite(std::vector<float> &tabresultats);
    void centralite_proximite_normalise(std::vector<float> &tabresultats,int &compteur_comparaison);
    void calcul_intermediarite(std::vector<float> &tabresultats);
    void sauvegarde();
    void coloration();
    void Majsuccesseurs();
    void suppression_arete();
    void comparaison_indices();
    void Dijsktra(std::vector<float> &tabresultats);
    void centralite_intermediarite(std::vector<float> &tabresultats);
    void centralite_intermediarite_normalise(std::vector<float> &tabresultats,int &compteur_comparaison);
    void chargementTopo(std::string &fichiertopo);
    void chargementPoids(std::string &fichierpoids);
    void TestConnexite();
    void k_connexite();
    int BFSconnexite(int num_s0);
};
#endif // GRAPHE_H_INCLUDED
