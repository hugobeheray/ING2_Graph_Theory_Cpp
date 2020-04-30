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

void Graphe::suppression_arete()
{
    int choix;
    do
    {
        std::cout << "Quelle arete voulez vous supprimer?" << std::endl;
        std::cin >> choix;
    }
    while(choix<0); // a changer
    for(unsigned int i=0;i<m_tabarete.size();i++)
    {
        if(choix==m_tabarete[i]->GetIndiceArete())
        {
            m_tabarete.erase(m_tabarete.begin() + i);
            m_taille=m_taille -1;
        }
    }
    for(unsigned int i=0;i<m_tabarete.size();i++)
    {
        std::cout << "Arete "<<m_tabarete[i]->GetIndiceArete() << std::endl;
    }

    for(int i=0;i<getOrdre();i++)
    {
        if(m_tabdegre[i] == 0)
    {
        std::cout << "Non connexes" << std::endl;
    }
    else
        std::cout << "Graphe Connexe" << std::endl;
    }

}
