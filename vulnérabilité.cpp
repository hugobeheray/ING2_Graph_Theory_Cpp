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

void Graphe::suppression_arete(std::string *nomfichier)
{
    int indiceArete, poids;
    bool test=false;
    std::ifstream lecture("graphe_cycle5_topo_poids.txt");
    std::ofstream ecriture("sauvegardesupArete.txt");
    int choix;
    do
    {
        std::cout << "Quelle arete voulez vous supprimer?" << std::endl;
        std::cin >> choix;
    }
    while(choix<0); // a changer
    for(unsigned int i=0; i<m_tabarete.size(); i++)
    {
        if(choix==m_tabarete[i]->GetIndiceArete())
        {
            m_tabarete.erase(m_tabarete.begin() + i);
            m_taille=m_taille -1;
        }
    }
    for(unsigned int i=0; i<m_tabarete.size(); i++)
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
            for(unsigned int i=0; i<m_tabarete.size()+1; i++)
            {
                lecture >> indiceArete >> poids;
                std::cout << "Indice arete:"<< indiceArete << std::endl;
                if(i!=choix)
                {
                    if(i<choix)
                    {
                       ecriture << indiceArete << " " << poids << "\n";
                    }
                    else if(i>choix) // si on supprime le dernier indice
                    {
                        std::cout << "premier if" << std::endl;
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









    /*for(int i=0;i<getOrdre();i++)
    {
        if(m_tabdegre[i] == 0)
    {
        std::cout << "Non connexes" << std::endl;
    }
    else
        std::cout << "Graphe Connexe" << std::endl;
    }*/

}
