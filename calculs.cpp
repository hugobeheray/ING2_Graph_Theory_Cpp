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

///Pour la centralite de degre (on regarde les degres de chaque sommet et donc ses voisins)
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
    m_res_cd=m_tabdegre;
    std::cout<<std::endl;

    ///On clear les tableux en fin de ssprgm pour pouvoir avoir un affichage correct
    ///et avoir des tableaux par la suite de taille normal avec les bon nombres dans chaques cases pour les calculs
    m_tabdegre.clear();
}

///Pour la centralite de degre normalise
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

        ///Permet d'arrondir a deux chiffres apres la virgule
        entier = (int)((0.005 + compteur_normalise)*100.0);
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
    m_res_cdn=m_tabdegre;
    std::cout<<std::endl;
}

///Pour la centralite de vecteur, qui est de base normalise par la division par lambda...
void Graphe::centralite_vecteur_normalise()
{
    float i=0;
    float somme=0;
    std::vector<float> sommevoisins;
    float lambda=0;
    float lambda2=0;
    int entier;
    std::vector <float> tabresultat;

    for(i=0; i<getOrdre(); i++)
    {
        m_tabdegre[i]=1;
        tabresultat.push_back(0);
        sommevoisins.push_back(0);
    }


    do
    {
        lambda2=lambda;
        somme=0;

        ///Pour chaque sommet, faire la somme des indices de ses voisins
        for( int i=0; i<getOrdre() ; i++)
        {
            for(int j=0; j<getTaille(); j++)
            {
                if(m_tabarete[j]->getExtrem1()==i )///sommet 0 : detecter 1 voisin
                {
                    sommevoisins[i]=sommevoisins[i]+ m_tabdegre[m_tabarete[j]->getExtrem2()];
                    tabresultat[m_tabarete[j]->getExtrem1()]= sommevoisins[i];
                }
                if(m_tabarete[j]->getExtrem2()==i)
                {
                    sommevoisins[i]=sommevoisins[i]+ m_tabdegre[m_tabarete[j]->getExtrem1()];
                    tabresultat[m_tabarete[j]->getExtrem2()]= sommevoisins[i];
                }

            }
            sommevoisins[i]=0;
        }

        /* for(unsigned int i=0; i<tabresultat.size(); i++)
        {
            std::cout << "tabresultat " << i << " = " << tabresultat[i] << std::endl; //1/1/1/4/2/4/1/1/1 au premier tour de la grande boucle for
        }*/

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
            entier = (int)((0.005 + m_tabdegre[i])*100.0);
            m_tabdegre[i] = (double)entier / 100.0;
        }

        //std::cout<< "LAMBDA = " << lambda <<std::endl; //pour voir les differentes valeurs de lambda
    }

    ///tant que delta lambda est superieur a 0,01, ici notre condition
    while(abs(lambda-lambda2)>0.01);


    ///affichage des indices de chaque sommet
    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE VECTEUR PROPRE NORMALISE" << std::endl << std::endl;
    for(i=0; i<m_tabdegre.size(); i++)
    {
        std::cout << "              Sommet "<<i<<" : "<< m_tabdegre[i] << std::endl;
    }
    m_res_cvn=m_tabdegre;
    //m_tabdegre.clear();
}

///Pour la centralite de vecteur 'NON normalise', les resultats obtenus ne seront pas pertinents
///dans le sens ou ils n'apportent aucune valeures ajoutes pour les futures comparaisons d'indices
///et que la pseudo version 'NON Normalise' n'est pas demande dans le sujet
void Graphe::centralite_vecteur()
{
    float i=0;
    float somme=0;
    std::vector<float> sommevoisins;
    float lambda=0;
    float lambda2=0;
    int entier;
    std::vector <float> tabresultat;

    for(i=0; i<getOrdre(); i++)
    {
        m_tabdegre[i]=1;
        tabresultat.push_back(0);
        sommevoisins.push_back(0);
    }

    do
    {
        lambda2=lambda;
        somme=0;

        for( int i=0; i<getOrdre() ; i++)
        {
            for(int j=0; j<getTaille(); j++)
            {
                if(m_tabarete[j]->getExtrem1()==i )
                {
                    sommevoisins[i]=sommevoisins[i]+ m_tabdegre[m_tabarete[j]->getExtrem2()];
                    tabresultat[m_tabarete[j]->getExtrem1()]= sommevoisins[i];
                }
                if(m_tabarete[j]->getExtrem2()==i)
                {
                    sommevoisins[i]=sommevoisins[i]+ m_tabdegre[m_tabarete[j]->getExtrem1()];
                    tabresultat[m_tabarete[j]->getExtrem2()]= sommevoisins[i];
                }

            }
            sommevoisins[i]=0;
        }

        /* for(unsigned int i=0; i<tabresultat.size(); i++)
        {
            std::cout << "tabresultat " << i << " = " << tabresultat[i] << std::endl; //1/1/1/4/2/4/1/1/1 au premier tour de la grande boucle for
        }*/

        for(i=0; i<getOrdre(); i++)
        {
            somme=(pow(tabresultat[i],2))+somme;
        }
        lambda=sqrt(somme);

        for(i=0; i<getOrdre(); i++)
        {
            m_tabdegre[i]=(tabresultat[i]);
            entier = (int)((0.005 + m_tabdegre[i])*100.0);
            m_tabdegre[i] = (double)entier / 100.0;
        }

        //std::cout<< "LAMBDA = " << lambda <<std::endl;//pour voir les differentes valeurs de lambda
    }

    ///tant que delta lambda est inferieur a 25 (condition arbitraire et qui depend du graphe)
    while(abs(lambda-lambda2)<25);

    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE VECTEUR PROPRE ('NON NORMALISE')" << std::endl << std::endl;
    for(i=0; i<m_tabdegre.size(); i++)
    {
        std::cout << "              Sommet "<<i<<" : "<< m_tabdegre[i] << std::endl;
    }
    m_res_cv=m_tabdegre;
    m_tabdegre.clear();
}

///Pour la centralite proximite, on y calcule l'eloignement moyen
void Graphe :: centralite_proximite (std::vector<float> &tabresultats)
{
    int entier;
    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE PROXIMITE" << std::endl << std::endl;
    for(unsigned int i=0; i<tabresultats.size(); i++)
    {
        tabresultats[i]=1/tabresultats[i];
        entier = (int)((0.005 + tabresultats[i])*100.0);
        tabresultats[i] = (double)entier / 100.0;
        std::cout << "               Sommet " << i << " : " << tabresultats[i] << std::endl;
    }
    m_res_cp=tabresultats;
}

///Pour la centralite proximite normalisee
void Graphe :: centralite_proximite_normalise (std::vector<float> &tabresultats)
{
    int entier;
    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE PROXIMITE NORMALISE" << std::endl << std::endl;
    for(unsigned int i=0; i<tabresultats.size(); i++)
    {
        tabresultats[i]=(getOrdre()-1)/tabresultats[i];
        entier = (int)((0.005 + tabresultats[i])*100.0);
        tabresultats[i] = (double)entier / 100.0;
        std::cout << "               Sommet " << i << " : " << tabresultats[i] << std::endl;
    }
    m_res_cpn=tabresultats;
}

///Pour la centralite intermediarite
void Graphe::centralite_intermediarite(std::vector<float> &tabresultats)
{
    int entier;
    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE INTERMEDIARITE" << std::endl << std::endl;
    for(unsigned int i=0; i<tabresultats.size(); i++)
    {
        tabresultats[i]=tabresultats[i]/1;
        entier = (int)((0.005 + tabresultats[i])*100.0);
        tabresultats[i] = (double)entier / 100.0;
        std::cout << "               Sommet " << i << " : " << tabresultats[i] << std::endl;
    }
    m_res_ci=tabresultats;
}

///Pour la centralite intermediarite normalisee
void Graphe::centralite_intermediarite_normalise(std::vector<float> &tabresultats)
{
    int entier;
    std::cout << std::endl << std::endl << "           RESULTATS CENTRALITE INTERMEDIARITE NORMALISE" << std::endl << std::endl;
    for(unsigned int i=0; i<tabresultats.size(); i++)
    {
        tabresultats[i]=(tabresultats[i]/1)/(pow(getOrdre(),2)-3*getOrdre()+2);
        entier = (int)((0.005 + tabresultats[i])*100.0);
        tabresultats[i] = (double)entier / 100.0;
        std::cout << "               Sommet " << i << " : " << tabresultats[i] << std::endl;
    }
    m_res_cin=tabresultats;
}

///ssprgm executant l'algorithme de Dijsktra
void Graphe::Dijsktra(std::vector<float> &tabresultats)
{
    int POIDS;
    int depart, arrivee, somme=0;

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

                ///on utilise "pair" pour stocker deux choses n'ayant pas le meme type : un type Sommet* et un type integer
                ///utilisation de la priority queue, trie du poids par ordre decroissant
                std::priority_queue<std::pair<Sommet*,int>,std::vector<std::pair<Sommet*,int>>,decltype(cmp)>file(cmp);
                std::vector<int> marquage((int)m_tabsommet.size(),0);
                std::vector<int> predecesseur((int)m_tabsommet.size(),-1);
                std::vector<int> poidsTotale((int)m_tabsommet.size(),-1);
                poidsTotale[depart] = 0;
                file.push({m_tabsommet[depart],0});
                std::pair<Sommet*,int> p;
                std::pair<Sommet*,int> ptemporaire;

                ///tant que la file n'est pas vide on fait tourner l'algorithme
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
                            if((poidsTotale[(Psucc.first)->getIndiceSommet()]==-1)||(p.second + Psucc.second < poidsTotale[(Psucc.first)->getIndiceSommet()]))
                            {
                                poidsTotale[(Psucc.first)->getIndiceSommet()] = p.second+Psucc.second;
                                predecesseur[(Psucc.first)->getIndiceSommet()] = p.first->getIndiceSommet();

                                ///on met a jour la file d'attente
                                file.push(std::make_pair(Psucc.first,poidsTotale[(Psucc.first)->getIndiceSommet()]));
                            }
                        }
                    }
                }

                ///AFFICHAGE
                /*
                                    std::cout <<"Sommet d'arrivee: "<<arrivee;
                                    for(auto z = predecesseur[arrivee]; z!= -1; z = predecesseur[z])
                                    {
                                        std::cout << " <- " << z;
                                    }

                                    std::cout <<std::endl << "Longueur totale: " << poidsTotale[arrivee]-poidsTotale[predecesseur[arrivee]];
                                    for(auto z = predecesseur[arrivee]; z!= -1; z = predecesseur[z])
                                    {
                                        if(poidsTotale[z]!=0)
                                        {
                                            std::cout << "+" << poidsTotale[z]-poidsTotale[predecesseur[z]];
                                        }

                                    }

                                    std::cout << "=" << poidsTotale[arrivee];//ici le plus court chemin d'un sommet A � un sommet b
                                    std::cout << std::endl;
                                    */

                POIDS=poidsTotale[arrivee];
                somme=POIDS+somme;
            }
        }
        tabresultats.push_back(somme);
        somme=0;
    }
}

///ssprgm permettant de calculer l'intermediarite
void Graphe::calcul_intermediarite(std::vector<float> &tabresultats)
{
    int POIDS;
    int i;
    int depart, arrivee, somme=0;
    int tabcompteur[getOrdre()] =  {0};

    ///ou l'on stocke les resultats pour l'intermediarite
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

                std::priority_queue<std::pair<Sommet*,int>,std::vector<std::pair<Sommet*,int>>,decltype(cmp)>file(cmp);
                std::vector<int> marquage((int)m_tabsommet.size(),0);
                std::vector<int> predecesseur((int)m_tabsommet.size(),-1);
                std::vector<int> poidsTotale((int)m_tabsommet.size(),-1);
                poidsTotale[depart] = 0;
                file.push({m_tabsommet[depart],0});
                std::pair<Sommet*,int> p;

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
                            if((poidsTotale[(Psucc.first)->getIndiceSommet()]==-1)||(p.second + Psucc.second < poidsTotale[(Psucc.first)->getIndiceSommet()]))
                            {
                                poidsTotale[(Psucc.first)->getIndiceSommet()] = p.second+Psucc.second;
                                predecesseur[(Psucc.first)->getIndiceSommet()] = p.first->getIndiceSommet();
                                file.push(std::make_pair(Psucc.first,poidsTotale[(Psucc.first)->getIndiceSommet()]));
                            }
                        }
                    }
                }

                ///AFFICHAGE en commentaire pour ne pas surcharger la console

                //  std::cout <<"Sommet d'arrivee: "<<arrivee;
                for(auto z = predecesseur[arrivee]; z!= -1; z = predecesseur[z])
                {
                    //    std::cout << " <- " << z;
                    tabcompteur[z]++;
                }

                // std::cout <<std::endl << "Longueur totale: " << poidsTotale[arrivee]-poidsTotale[predecesseur[arrivee]] << std::endl;
                for(auto z = predecesseur[arrivee]; z!= -1; z = predecesseur[z])
                {
                    if(poidsTotale[z]!=0)
                    {
                        //         std::cout << "+" << poidsTotale[z]-poidsTotale[predecesseur[z]] << std::endl;
                    }

                }

                //   std::cout << "=" << poidsTotale[arrivee];//ici le plus court chemin d'un sommet A � un sommet b
                //    std::cout << std::endl;

                POIDS=poidsTotale[arrivee];
                somme= POIDS+somme;

            }
        }
        //tabresultats.push_back(somme);
        somme=0;
    }

    for(i=0; i<getOrdre(); i++)
    {
        tabcompteur[i] = tabcompteur[i] - (getOrdre() -1);
    }

    for(i=0; i<getOrdre(); i++)
    {
        if (tabcompteur[i]%2==0)
            tabcompteur[i] = tabcompteur[i]/2;
        else
            tabcompteur[i] = (tabcompteur[i]/2)+1;
    }

    for ( i=0; i<getOrdre(); i++)
    {
        tabresultats.push_back(tabcompteur[i]);
    }

      /* for(i=0; i<getOrdre(); ++i)
      {
          std::cout << "INDICE INTER SOMMET " << i << " : " << tabcompteur[i] << std::endl;
      }*/

}
