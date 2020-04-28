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
#include "Coords.h"
#include "calculs.h"

Graphe::Graphe(std::string fichier,std::string fichierpoids)
{
    std::ifstream iss(fichier);
    std::ifstream iss2(fichierpoids);
    int i, indiceSommet, x, y;
    int indiceArete,extrem1, extrem2, poids;
    char nom;
    if(iss2)
    {
        iss2 >> m_taille;
        for(i=0;i<m_taille;++i)
        {
            iss2 >> indiceArete >> poids;
            m_tabpoids.push_back(new Arete(indiceArete,poids));
        }


    }
    if(iss)
    {
        iss >> m_orient; /// on récupère l'orientation du graphe
        iss >> m_ordre; /// on récupère l'ordre du graphe
        for( i=0; i<m_ordre; i++)
        {

            iss >> indiceSommet >> nom >> x >> y;
            m_tabsommet.push_back(new Sommet(indiceSommet,nom,x,y));
            m_tabcoords.push_back(new Coords(x,y));
        }
        iss >> m_taille;
        for( i=0; i<m_taille; i++)
        {
            iss >> indiceArete >> extrem1 >> extrem2 ;
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
    }

    for(i=0;i<m_taille;++i)
    {
        m_tabpoids[i]->AfficherAretePoids();
    }


}

void Graphe::dessiner(Svgfile *svgout)
{

    int i;
    svgout->addGrid();
    ///affichage lettres sommets et points sommets
    for(i=0; i<getOrdre(); ++i)
    {
        svgout->addText((m_tabsommet[i]->getX())*100-5, (m_tabsommet[i]->getY())*100-15,m_tabsommet[i]->getNom(), "black");
        svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 1, "black");
    }
    ///affichage aretes
    for(i=0; i<getTaille(); ++i)
    {
        svgout->addLine(m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem1()]->getY()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()*100);
    }
}

int Graphe::getOrdre()
{
    return m_ordre;
}

int Graphe::getTaille()
{
    return m_taille;
}


Graphe::~Graphe()
{
    for(auto i : m_tabsommet)
    {
        delete i;
    }
}

