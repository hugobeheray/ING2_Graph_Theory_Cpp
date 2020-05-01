#include <vector>
#include <queue>
#include "Sommet.h"
#include <fstream>
#include <sstream>
#include <string>
#include "Arete.h"
#include "svgfile.h"
#include "Coords.h"
#include "Graphe.h"
#include <iostream>

void Graphe::suppression_arete(std::string &nomfichierpoids, std::string &nomfichiertopo,Graphe graphe)
{
    int indiceArete, poids;
    std::string nom,sauvPoids = "sauvegardesupAretePoids.txt",sauvtopo = "sauvegardesupArete.txt";
    int x,y, indiceSommet,extrem1,extrem2;
    std::ifstream lecture(nomfichierpoids);
    std::ofstream ecriture(sauvPoids);
    std::ifstream lecture2(nomfichiertopo);
    std::ofstream ecriture2(sauvtopo);
    int choix;
    do
    {
        std::cout << "Quelle arete voulez vous supprimer pour tester la connexite?" << std::endl;
        std::cin >> choix;
    }
    while(choix<0 || choix>getTaille());
    for(int i=0; i<(int)m_tabarete.size(); i++)
    {
        if(choix==m_tabarete[i]->GetIndiceArete())
        {
            m_tabarete.erase(m_tabarete.begin() + i);
            m_taille=m_taille -1;
        }
    }
    for( int i=0; i<(int)m_tabarete.size(); i++)
    {
        std::cout << "Arete "<<m_tabarete[i]->GetIndiceArete() << std::endl;
    }
    if(lecture)
    {
        if(ecriture)
        {
            lecture >>  m_taille;
            m_taille = m_taille-1;
            ecriture << m_taille << "\n";
            for(int i=0; i<(int)m_tabarete.size()+1; i++)
            {
                lecture >> indiceArete >> poids;
                if(i!=choix)
                {
                    if(i<choix)
                    {
                        ecriture << indiceArete << " " << poids << "\n";
                    }
                    else if(i>choix) // si on supprime le dernier indice
                    {
                        ecriture << indiceArete-1 << " " << poids << "\n";
                    }
                }

            }

        }
        else
            std::cout << "erreur lors de l'ouverture du fichier d'ecriture"<<std::endl;


    }
    else
        std::cout << "erreur lors de l'ouverture du fichier de lecture "<<std::endl;

    lecture.close();
    ecriture.close();

    /*m_tabarete.clear();
    m_tabdegre.clear();
    m_tabpoids.clear();
    m_tabcoords.clear();*/
    // m_tabsommet.clear();

    if(lecture2)
    {
        if(ecriture2)
        {

            lecture2 >> m_orient;
            ecriture2 << m_orient << "\n";
            lecture2 >> m_ordre;
            ecriture2 << m_ordre << "\n";
            for( int i=0; i<m_ordre; i++)
            {
                lecture2 >> indiceSommet >> nom >> x >> y;
                ecriture2 << indiceSommet << " " << nom << " " << x << " "<< y << "\n";
            }
            lecture2>>  m_taille;
            m_taille = m_taille-1;
            ecriture2 << m_taille << "\n";
            for(int i=0; i<(int)m_tabarete.size()+1; i++)
            {
                lecture2 >> indiceArete >> extrem1 >> extrem2 ;
                if(i!=choix)
                {
                    if(i<choix)
                    {
                        ecriture2 << indiceArete << " " << extrem1 << " " << extrem2 << "\n";
                    }
                    else if(i>choix) // si on supprime le dernier indice
                    {
                        ecriture2 << indiceArete-1 << " " << extrem1 << " " << extrem2<< "\n";
                    }
                }

            }

        }
        else
            std::cout << "erreur lors de l'ouverture du fichier d'ecriture"<<std::endl;


    }
    else
        std::cout << "erreur lors de l'ouverture du fichier de lecture "<<std::endl;
    lecture2.close();
    ecriture2.close();

    // std::copy(nomfichierpoids.begin(),nomfichierpoids.end(),sauvPoids.begin());
    //std::copy(nomfichiertopo.begin(),nomfichiertopo.end(),sauvtopo.begin());

    std::cout << sauvPoids << std::endl << sauvtopo << std::endl;
    graphe.chargementPoids(sauvPoids);
    graphe.chargementTopo(sauvtopo);
    graphe.afficher();
}


void Graphe::TestConnexite()
{
    for(int i=0; i<getOrdre(); i++)
    {
        if(m_tabdegre[i] == 0)
        {
            std::cout << "Sommet "  << i << "non connecte" << std::endl;
        }
        else
            std::cout << "Sommet " << i << "Graphe Connexe" << std::endl;
    }
}
