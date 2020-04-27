#include "graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include <stack>
#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream> /// Pour les fichiers
#include <sstream>/// Pour les ostringstream
#include "svgfile.h"


Graphe::Graphe(std::string fichier)
{
    std::ifstream iss(fichier);
    int i, indiceSommet, x, y;
    int indiceArete,extrem1, extrem2;
    char nom;
    if(iss)
    {
        iss >> m_orient; /// on récupère l'orientation du graphe
        iss >> m_ordre; /// on récupère l'ordre du graphe
        for( i=0; i<m_ordre; i++)
        {

            iss >> indiceSommet >> nom >> x >> y;
            m_tabsommet.push_back(new Sommet(indiceSommet,nom,x,y));
            //m_tabsommet[m_id1]->AjouterSuccesseur(m_tabsommet[m_id2]);
            /* if(!m_orient) // si le graphe n'est pas orienté.
             {
                 m_tabsommet[m_id2]->AjouterSuccesseur(m_tabsommet[m_id1]);
             }
             */
        }
        iss >> m_taille;
        for( i=0; i<m_taille; i++)
        {
            iss >> indiceArete >> extrem1 >> extrem2;
           m_tabarete.push_back(new Arete(indiceArete,extrem1,extrem2));
        }

    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
    }

}

void Graphe::afficher()
{
    int i;
    std::cout<< "graphe ";
    if(m_orient)
        std::cout<<"oriente"<<std::endl;
    else
        std::cout<<"non oriente"<<std::endl;

    std::cout<<"ordre = "<<m_tabsommet.size()<<std::endl;

    for( i=0; i<m_ordre; i++)
    {
        m_tabsommet[i]->afficherSommet();
    }
        std::cout << "Taille :" << m_taille << std::endl;
        for( i=0; i<m_taille; i++)
        {
            m_tabarete[i]->AfficherArete();
           // std::cout << "Indice arrete: " << m_indiceArrete << " Extremite 1: " << m_extrem1 << " Extremite 2: "<< m_extrem2 << std::endl;
        }

        /*for(auto i : m_tabsommet)
        {
            i->afficherSuccesseurs();
            std::cout<<std::endl;
        }
        */
}

void Graphe::dessiner(Svgfile *svgout)
{
    unsigned int i;
    ///affichage lettres sommets et points sommets
    for(i=0;i<getOrdre();++i)
    {
        svgout-->addText(m_indiceSommet.getX(), m_indiceSommet.getY(), GetNum(), "black");
        svgout-->addCircle(m_indiceSommet.getX(), m_indiceSommet.getY(), 5 , 5 , "black");
    }
    ///affichage aretes
    svgout->addLine(m_indiceSommet.getX(), m_indiceSommet.getY(), m_indiceSommet2.getX(),m_indiceSommet2.getY(), "black");
}

Graphe::~Graphe()
{
    for(auto i : m_tabsommet)
    {
        delete i;
    }
}

