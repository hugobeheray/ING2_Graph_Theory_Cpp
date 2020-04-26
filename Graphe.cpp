#include "graphe.h"
#include "Sommet.h"
#include <stack>
#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream> /// Pour les fichiers
#include <sstream>/// Pour les ostringstream


Graphe::Graphe(std::string fichier)
{
    std::ifstream iss(fichier);
    int i;
    if(iss)
    {
        std::cout<<"test1";
        iss >> m_orient; /// on récupère l'orientation du graphe
        iss >> m_ordre; /// on récupère l'ordre du graphe
        for ( i=0; i<m_ordre; i++)
        {
            m_tabsommet.push_back(new Sommet(i));
        }
        for( i=0; i<m_taille; i++)
        {
            iss >> m_id1 >> m_id2;
            m_tabsommet[m_id1]->AjouterSuccesseur(m_tabsommet[m_id2]);
            if(!m_orient) // si le graphe n'est pas orienté.
            {
                m_tabsommet[m_id2]->AjouterSuccesseur(m_tabsommet[m_id1]);
            }
        }
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
    }

}

void Graphe::afficher()
{
    std::cout<< "graphe ";
    if(m_orient)
        std::cout<<"oriente"<<std::endl;
    else
        std::cout<<"non oriente"<<std::endl;
    std::cout<<"ordre = "<<m_tabsommet.size()<<std::endl;
    std::cout<<"liste d'adjacence : "<<std::endl;
    for(auto i : m_tabsommet)
    {
        i->afficherSuccesseurs();
        std::cout<<std::endl;
    }
}

Graphe::~Graphe()
{
    for(auto i : m_tabsommet)
    {
        delete i;
    }
}

