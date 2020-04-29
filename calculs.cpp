#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include <vector>
#include "svgfile.h"
#include "menu.h"
#include "Coords.h"
#include "calculs.h"
#include <math.h>
#include<queue>

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
    for(unsigned int i=0; i<m_tabdegre.size(); i++)
    {
        std::cout << "              Sommet "<<i<<" : "<< m_tabdegre[i] << std::endl;
    }
    res_cd=m_tabdegre;
    std::cout<<std::endl;
    m_tabdegre.clear();
}

void Graphe::centralite_degre_normalise()
{
    int j;
    int entier=0;
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
        entier = (int)((0.005 + compteur_normalise)*100.0); //arrondi
        compteur_normalise = (double)entier / 100.0;
        m_tabdegre.push_back(compteur_normalise);
        compteur=0;
        compteur_normalise=0;
    }
    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE DEGRE NORMALISE" << std::endl << std::endl;
    for(unsigned int i=0; i<m_tabdegre.size(); i++)
    {
        std::cout << "              Sommet "<<i<<" : "<< m_tabdegre[i] << std::endl;
    }
    res_cdn=m_tabdegre;
    std::cout<<std::endl;
}

void Graphe::centralite_vecteur()
{
    float i=0;
    float somme=0;
    float lambda=0;
    int compteur=0;
    int entier;
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
            entier = (int)((0.005 + m_tabdegre[i])*100.0); //arrondi
            m_tabdegre[i] = (double)entier / 100.0;
        }
        //std::cout<<lambda<<std::endl;//pour voir les differentes valeurs de delata
    }
    while((lambda>0) && (lambda<95.7));///tant que delta lambda est sup�rieur � 0,1
    ///affichage des indices de chaque sommet

    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE VECTEUR PROPRE" << std::endl << std::endl;
    for(i=0; i<m_tabdegre.size(); i++)
    {
        std::cout << "              Sommet "<<i<<" : "<< m_tabdegre[i] << std::endl;
    }
    res_cv=m_tabdegre;
    m_tabdegre.clear();
}

void Graphe::centralite_vecteur_normalise()
{
    float i=0;
    float somme=0;
    float lambda=0;
    int compteur=0;
    int entier=0;
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
            entier = (int)((0.005 + tabdegrenormalise[i])*100.0); //arrondi
            tabdegrenormalise[i] = (double)entier / 100.0;
        }
    }
    while((lambda>0) && (lambda<4));
    ///affichage des indices de chaque sommet

    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE VECTEUR PROPRE NORMALISE" << std::endl << std::endl;
    for(i=0; i<tabdegrenormalise.size(); i++)
    {
        std::cout << "              Sommet "<<i<<" : "<< tabdegrenormalise[i] << std::endl;
    }
    res_cvn=tabdegrenormalise;
//m_tabdegre.clear();/// peut etre a supr
}



void Graphe :: centralite_proximite (std::vector<float> &tabresultats)
{
    int entier;
    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE PROXIMITE" << std::endl << std::endl;
    for(unsigned int i=0;i<tabresultats.size();i++)
        {
            tabresultats[i]=1/tabresultats[i];
            entier = (int)((0.005 + tabresultats[i])*100.0); //arrondi
            tabresultats[i] = (double)entier / 100.0;
            std::cout << "               Sommet " << i << " : " << tabresultats[i] << std::endl;
        }
    res_cp=tabresultats;
}

void Graphe :: centralite_proximite_normalise (std::vector<float> &tabresultats)
{
    int entier;
    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE PROXIMITE NORMALISE" << std::endl << std::endl;
    for(unsigned int i=0;i<tabresultats.size();i++)
        {
            tabresultats[i]=(getOrdre()-1)/tabresultats[i];
            entier = (int)((0.005 + tabresultats[i])*100.0); //arrondi
            tabresultats[i] = (double)entier / 100.0;
            std::cout << "               Sommet " << i << " : " << tabresultats[i] << std::endl;
        }
    res_cpn=tabresultats;
}


void Graphe::centralite_intermediarite()
{

}

//ss prgm qui �xecute l'algo de Dijsktra
void Graphe::Dijsktra(std::vector<float> &tabresultats)
{
    int POIDS;
    int i;
    int depart, arrivee, somme=0;

    int tabcompteur[getOrdre()] =  {0};

    int sommeintermediarite=0;
    std::vector<float> tabresintermediarite;

    for(depart=0; depart<getOrdre(); ++depart)
    {
        for(arrivee=0; arrivee<getOrdre(); ++arrivee)
        {
            if(depart!=arrivee)
            {

                auto cmp = [](std::pair<const Sommet*,int> p1, std::pair<Sommet*,int> p2)
                {
                    return p2.second<p1.second;
                };
//on utilise "pair" pour stocker deux choses n'ayant pas le meme type : un type Sommet* et un type integer
///utilisation de la priority queue, trie du poids par ordre decroissant
                std::priority_queue<std::pair<Sommet*,int>,std::vector<std::pair<Sommet*,int>>,decltype(cmp)>file(cmp);
                std::vector<int> marquage((int)m_tabsommet.size(),0); // pour le marquage
                std::vector<int> predecesseur((int)m_tabsommet.size(),-1);
                std::vector<int> poidsTotale((int)m_tabsommet.size(),-1);
                poidsTotale[depart] = 0;
                file.push({m_tabsommet[depart],0});
                std::pair<Sommet*,int> p;



//tant que la file n'est pas vide, on applique l'algo
                while(!file.empty())
                {
                    p=file.top();
                    file.pop();
                    while((!file.empty()) && (marquage[p.first->getIndiceSommet()]))
                    {
                        p=file.top();
                        file.pop();
                    }


                    marquage[(p.first)->getIndiceSommet()]=1;
                    for(auto Psucc:(p.first)->getSuccesseurs())
                    {
                        if(marquage[(Psucc.first)->getIndiceSommet()]==0)
                        {
                            if((poidsTotale[(Psucc.first)->getIndiceSommet()]==-1)||(p.second + Psucc.second <= poidsTotale[(Psucc.first)->getIndiceSommet()]))
                            {

                                poidsTotale[(Psucc.first)->getIndiceSommet()] = p.second+Psucc.second;
                                predecesseur[(Psucc.first)->getIndiceSommet()] = p.first->getIndiceSommet();
                                file.push(std::make_pair(Psucc.first,poidsTotale[(Psucc.first)->getIndiceSommet()]));//on met � jour la file d'attente

                            }
                        }
                    }

                }

              /*  for(int i=0; i<tabcompteur.size();++i)
                {
                     sommeintermediarite=tabcompteur[i]+sommeintermediarite;
                }
                for(int i=0; i<tabcompteur.size();++i)
                {
                     tabresintermediarite[i]=tabcompteur[i]/sommeintermediarite;
                }*/

///AFFICHAGE
                std::cout <<"Sommet d'arrivee: "<<arrivee;
                for(auto z = predecesseur[arrivee]; z!= -1; z = predecesseur[z])
                {

                    std::cout << " <- " << z;
                    tabcompteur[z]++;

                }
                std::cout <<std::endl << "Longueur totale: " << poidsTotale[arrivee]-poidsTotale[predecesseur[arrivee]];
                for(auto z = predecesseur[arrivee]; z!= -1; z = predecesseur[z])
                {
                    if(poidsTotale[z]!=0)
                    {
                        std::cout << "+" << poidsTotale[z]-poidsTotale[predecesseur[z]];
                    }

                }
                for(i=0;i<getOrdre();++i)
                    {
                        std::cout << "INDICE INTER SOMMET" << i << " : " << tabcompteur[i] << std::endl;
                    }

                std::cout << "=" << poidsTotale[arrivee];//ici le plus court chemin d'un sommet A � un sommet b
                std::cout << std::endl;

                POIDS=poidsTotale[arrivee];
                somme= POIDS+somme;


            }

        }
        tabresultats.push_back(somme);
        somme=0;
    }
}

