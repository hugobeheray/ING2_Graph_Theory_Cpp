#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include <vector>
#include "svgfile.h"
#include "menu.h"
#include "Coords.h"
#include "calculs.h"

void Graphe::centralite_degre()
{
    int i;
    int j;
    std::vector <int> tabdegre;
    int compteur=0;
    for(i=0;i<getOrdre() ; i++)
    {
        for(j=0;j<getTaille();j++)
        {
            if( (m_tabarete[j]->getExtrem1()==i || m_tabarete[j]->getExtrem2()==i) )
            {
                compteur++;
            }
        }
        tabdegre.push_back(compteur);
        compteur=0;
    }
    for(i=0;i<tabdegre.size();i++)
    {
        std::cout << "Sommet "<<i<<" : "<< tabdegre[i] <<" degres"<< std::endl;
    }
    std::cout<<std::endl;
}
void Graphe::centralite_degre_normalise()
{
    int i;
    int j;
    std::vector <float> tabdegre;
    float compteur=0;
    float compteur_normalise=0;
    for(i=0;i<getOrdre() ; i++)
    {
        for(j=0;j<getTaille();j++)
        {
            if( (m_tabarete[j]->getExtrem1()==i || m_tabarete[j]->getExtrem2()==i) )
            {
                compteur++;
            }
        }
        compteur_normalise=compteur/(getOrdre() - 1);
        tabdegre.push_back(compteur_normalise);
        compteur=0;
        compteur_normalise=0;
    }
    for(i=0;i<tabdegre.size();i++)
    {
        std::cout << "Sommet "<<i<<" : "<< tabdegre[i] <<" degres normalises"<< std::endl;
    }
 std::cout<<std::endl;
}
