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
    }
    while((lambda>0) && (lambda<4));
    ///affichage des indices de chaque sommet

    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE VECTEUR PROPRE NORMALISE" << std::endl << std::endl;
    for(i=0; i<tabdegrenormalise.size(); i++)
    {
        std::cout << "              Sommet "<<i<<" : "<< tabdegrenormalise[i] <<" degres"<< std::endl;
    }

}

std::vector<int> Graphe:: Dijkstra(std::vector<int> bfs, std::vector<int> finalBfs, Graphe &graphe, std::vector<int> poidF)
{
    int temp;
    int find2=0;


    /// on cherche le premier sommet de la liste non noir ///
    do
    {
        temp = bfs[find2];
        find2++;

    }
    while((graphe.GetSommet()[temp].getColor() == 2) && (find2 < bfs.size()));


    /// le sommet S est égale a la plus petite valeur de parcours poyr arriver a ce sommet
    if(poidF[temp] != 9999999)
    {
        graphe.SetSomSome(temp, poidF[temp],0);
    }


    ///on le met gris///
    graphe.SetCol(temp, 1);


    /// on parcours tout ses adjacent et les rajoutes a la listes et deviennent gris///
    for(int i=0; i<graphe.GetSommet()[temp].GetAdjacent().size(); i++)
    {

        if( graphe.GetSommet()[temp].GetAdjacent()[i].getId() != bfs[0])
        {
            bfs.push_back(graphe.GetSommet()[temp].GetAdjacent()[i].getId());
            finalBfs.push_back(graphe.GetSommet()[temp].GetAdjacent()[i].getId());


            /// l'adjacent S' est égale a la somme du sommet S plus la somme du poid de l'arete
            graphe.SetSomSome(graphe.GetSommet()[temp].GetAdjacent()[i].getId(), graphe.rechercheArete(temp,graphe.GetSommet()[temp].GetAdjacent()[i].getId()) + graphe.GetSommet()[temp].getSomme(), 0);

            /// si la nouvelle distance est inférieur a l'ancienne, le chemin est plus court donc on prend cette nouvelle distance et nouveau prev
            if(graphe.GetSommet()[graphe.GetSommet()[temp].GetAdjacent()[i].getId()].getSomme() < poidF[graphe.GetSommet()[temp].GetAdjacent()[i].getId()])
            {
                poidF[graphe.GetSommet()[temp].GetAdjacent()[i].getId()] = graphe.GetSommet()[graphe.GetSommet()[temp].GetAdjacent()[i].getId()].getSomme();
                graphe.SetPrev(graphe.GetSommet()[temp].GetAdjacent()[i].getId(), temp);

                /// un sommet avec une nouvelle som peut décourdre de nouveau chemin plus court donc il sera réutilisable pour le parcours du graphe
                if(graphe.GetSommet()[graphe.GetSommet()[temp].GetAdjacent()[i].getId()].getId() != bfs[0])
                {
                    graphe.SetCol(graphe.GetSommet()[graphe.GetSommet()[temp].GetAdjacent()[i].getId()].getId(), 0);
                }

            }
        }

    }

    /// le sommet deviens noir ///
    graphe.SetCol(temp, 2);

    /// on test pour savoir si il reste des sommet non noir ( on test voir si l'ont a tout parcourue) ///
    for(int i=0; i<bfs.size(); i++)
    {
        temp = bfs[i];
        if(graphe.GetSommet()[temp].getColor() != 2)
        {
            poidF = Dijkstra(bfs, finalBfs, graphe, poidF);
        }
    }


    return poidF;
}
