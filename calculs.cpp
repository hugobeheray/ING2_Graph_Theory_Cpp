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
    float compteur=0;
    for( int i=0; i<getOrdre() ; i++)
    {
        for(int j=0; j<getTaille(); j++)
        {
            if( (m_tabarete[j]->getExtrem1()==i || m_tabarete[j]->getExtrem2()==i) )
            {
                compteur++;
            }
        }
        m_tabdegre.push_back(compteur);
        compteur=0;
    }
    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE DEGRE" << std::endl << std::endl;
    for(int i=0; i<m_tabdegre.size(); i++)
    {
        std::cout << "              Sommet "<<i<<" : "<< m_tabdegre[i] <<" degres"<< std::endl;
    }

    std::cout<<std::endl;
    m_tabdegre.clear();
}
void Graphe::centralite_degre_normalise()
{
    int j;
    float compteur=0;
    float compteur_normalise=0;
    for( int i=0; i<getOrdre() ; i++)
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
    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE DEGRE NORMALISE" << std::endl << std::endl;
    for(unsigned int i=0; i<m_tabdegre.size(); i++)
    {
        std::cout << "              Sommet "<<i<<" : "<< m_tabdegre[i] <<" degres"<< std::endl;
    }

    std::cout<<std::endl;
}


void Graphe::centralite_vecteur()
{
    float i=0;
    float j=0;
    float somme=0;
    float lambda=0;
    int compteur=0;
    std::vector <float> tabresultat;
    ///INITIALISATION
    for(i=0; i<getOrdre(); i++)
    {
        m_tabdegre[i]=1;
    }

    ///FAIRE
    do
    {
        ///Pour chaque sommet, faire la somme des indices de ses voisins
        for( int i=0; i<getOrdre() ; i++)
        {
            for(int j=0; j<getTaille(); j++)
            {
                if( (m_tabarete[j]->getExtrem1()==i || m_tabarete[j]->getExtrem2()==i) )
                {
                    compteur++;
                }
            }
            tabresultat.push_back(compteur);
            compteur=0;
        }

        ///Calcul de lambda
        for(i=0; i<getOrdre(); i++)
        {
            somme=(pow(tabresultat[i],2))+somme;
        }
        lambda=sqrt(somme);
        ///Recalcul de l'indice
        for(i=0; i<getOrdre(); i++)
        {
            m_tabdegre[i]=(tabresultat[i]/lambda);
        }
        //std::cout<<"lambda :" << lambda<<std::endl;
    }
    while((lambda>0) && (lambda<4));
    ///affichage des indices de chaque sommet

    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE VECTEUR PROPRE" << std::endl << std::endl;
    for(i=0; i<m_tabdegre.size(); i++)
    {
        std::cout << "              Sommet "<<i<<" : "<< m_tabdegre[i] <<" degres"<< std::endl;
    }
    m_tabdegre.clear();
}

void Graphe::centralite_vecteur_normalise()
{
    float i=0;
    float j=0;
    float somme=0;
    float lambda=0;
    int compteur=0;
    std::vector <float> tabresultat;
    std::vector <float> tabdegrenormalise;
    ///INITIALISATION
    for(i=0; i<getOrdre(); i++)
    {
        m_tabdegre[i]=1;
    }

    ///FAIRE
    do
    {
        ///Pour chaque sommet, faire la somme des indices de ses voisins
        for( int i=0; i<getOrdre() ; i++)
        {
            for(int j=0; j<getTaille(); j++)
            {
                if( (m_tabarete[j]->getExtrem1()==i || m_tabarete[j]->getExtrem2()==i) )
                {
                    compteur++;
                }
            }
            tabresultat.push_back(compteur);
            compteur=0;
        }

        ///Calcul de lambda
        for(i=0; i<getOrdre(); i++)
        {
            somme=(pow(tabresultat[i],2))+somme;
        }
        lambda=sqrt(somme);
        ///Recalcul de l'indice
        for(i=0; i<getOrdre(); i++)
        {
            m_tabdegre[i]=(tabresultat[i]/lambda);
            tabdegrenormalise.push_back(m_tabdegre[i]/(getOrdre()-1));
        }
        //std::cout<<"lambda :" << lambda<<std::endl;
    }
    while((lambda>0) && (lambda<4));
    ///affichage des indices de chaque sommet

    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE VECTEUR PROPRE NORMALISE" << std::endl << std::endl;
    for(i=0; i<tabdegrenormalise.size(); i++)
    {
        std::cout << "              Sommet "<<i<<" : "<< tabdegrenormalise[i] <<" degres"<< std::endl;
    }

}
