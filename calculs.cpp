#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include <vector>
#include "svgfile.h"
#include "menu.h"
#include "Coords.h"
#include "calculs.h"
#include <math.h>

void Graphe::centralite_degre()
{
    int i;
    int j;

    float compteur=0;
    for(i=0; i<getOrdre() ; i++)
    {
        for(j=0; j<getTaille(); j++)
        {
            if( (m_tabarete[j]->getExtrem1()==i || m_tabarete[j]->getExtrem2()==i) )
            {
                compteur++;
            }
        }
        m_tabdegre.push_back(compteur);
        compteur=0;
    }
    for(i=0; i<m_tabdegre.size(); i++)
    {
        std::cout << "Sommet "<<i<<" : "<< m_tabdegre[i] <<" degres"<< std::endl;
    }

    std::cout<<std::endl;
}
void Graphe::centralite_degre_normalise()
{
    int i;
    int j;

    float compteur=0;
    float compteur_normalise=0;
    for(i=0; i<getOrdre() ; i++)
    {
        for(j=0; j<getTaille(); j++)
        {
            if( (m_tabarete[j]->getExtrem1()==i || m_tabarete[j]->getExtrem2()==i) )
            {
                compteur++;
            }
        }
        compteur_normalise=compteur/(getOrdre() - 1);
        m_tabdegre.push_back(compteur_normalise);
        compteur=0;
        compteur_normalise=0;
    }
    for(i=0; i<m_tabdegre.size(); i++)
    {
        std::cout << "Sommet "<<i<<" : "<< m_tabdegre[i] <<" degres normalises"<< std::endl;
    }

    std::cout<<std::endl;
}



void Graphe::centralite_vecteur()
{
    std::vector <float>copie_tabdegre;
    float i=0;
    float j=0;
    float res=0;
    float somme=0;
    float lambda=0;

    copie_tabdegre=m_tabdegre;

    for(i=0; i<getOrdre(); i++)
    {
        m_tabdegre[i]=1;
    }

    do
    {
        for(i=0; i<getOrdre(); i++)
        {
            somme=copie_tabdegre[m_tabsommet[i]->getIndiceSommet()]+somme;
        }
        for(i=0; i<getOrdre(); i++)
        {
            lambda=(pow(copie_tabdegre[m_tabsommet[i]->getIndiceSommet()],2))+lambda;
        }
        lambda=sqrt(lambda);

        for(j=0; j<getOrdre(); j++)
        {
            m_tabdegre[j]=(somme/lambda);
        }
        std::cout<<"lambda :" << lambda<<std::endl;

    }
    while((lambda>1) && (lambda<5));

    for(i=0; i<m_tabdegre.size(); i++)
    {
        std::cout << "Sommet "<<i<<" : "<< m_tabdegre[i] <<" degres lambda"<< std::endl;
    }

}
