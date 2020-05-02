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

///Lors de la suppression d'une arete, on reecris dans deux nouveaux fichiers de sauvegarde
///ne contenant pas les informations de l'arete supprimee pour
///pouvoir par la suite les utiliser pour les calculs et l'affichage dans le .svg


void Graphe::Majsuccesseurs()
{
    for(size_t i=0; i<m_tabsommet.size(); ++i)
    {
        m_tabsommet[i]->RetirerSuccesseur();///avec pair
    }
    for( size_t i=0; i<m_tabarete.size(); i++)
    {
        m_tabsommet[m_tabarete[i]->getExtrem1()]->AjouterSuccesseur(std::make_pair(m_tabsommet[m_tabarete[i]->getExtrem2()],m_tabpoids[i]->GetPoids()));///avec pair
        m_tabsommet[m_tabarete[i]->getExtrem2()]->AjouterSuccesseur(std::make_pair(m_tabsommet[m_tabarete[i]->getExtrem1()],m_tabpoids[i]->GetPoids()));
    }
}
void Graphe::suppression_arete()
{
    int choix;
    ///afficher les indices des aretes a faire
    for(size_t i=0; i<m_tabarete.size(); i++)
    {
        std::cout <<"Arete: " << m_tabarete[i]->GetIndiceArete() << std::endl;
    }

    do
    {

        std::cout << "Quelle arete voulez vous supprimer pour tester la connexite?" << std::endl;
        couleurverte();
        std::cin >> choix;
        couleurbleue();

    }
    while(choix<0 /*|| choix> (int)m_tabarete.size()-1*/);
    couleurbleue();

    for(int i=0; i<(int)m_tabarete.size(); i++)
    {
        if(choix==m_tabarete[i]->GetIndiceArete())
        {
            ///suppression de l'arete dans le tableau
            m_tabarete.erase(m_tabarete.begin() + i);
            break;
        }
    }
    for( int i=0; i<(int)m_tabarete.size(); i++)
    {
        std::cout << "Arete "<<m_tabarete[i]->GetIndiceArete() << std::endl;
    }
    this->Majsuccesseurs();
}

///C'est ici que l'on teste la connexite des reseaux pour savoir si notre graphe et d'un seul tenant ou non
void Graphe::TestConnexite()
{
    int cpt=0;

    ///Pour cela, on fait un BFS a partir d'un sommet de depart quelconque, et on regarde en resultat si tous
    /// les sommets on ete colores ou non...
    cpt=BFSconnexite(0);
  //  std::cout<<"cpt = "<<cpt<<std::endl;
   // std::cout<<"ordre = "<<getOrdre()<<std::endl;

    ///Si le nombre de sommets colores equivaut au nombre sommet total, alors le graphe est en effet connexe, sinon non!
    if(cpt==getOrdre())
    {
        std::cout<<"Le graphe est connexe"<<std::endl;
    }
    else
    {
        std::cout<<"Le graphe n'est pas connexe"<<std::endl;
    }
}

///sssprgm qui retourne un compteur = nombre de sommets colores au cours de l'execution du BFS
int Graphe::BFSconnexite(int num_s0)
{
    /// déclaration de la file
    std::queue<Sommet*> file;

    /// pour le marquage
    std::vector<int> couleurs((int)m_tabsommet.size(),0);

    ///pour noter les predecesseurs
    std::vector<int> preds((int)m_tabsommet.size(),-1);
    int cpt=0;

    ///On enfile et on marque le sommet initial
    file.push(m_tabsommet[num_s0]);
    couleurs[num_s0] = 1;
    cpt++;
    Sommet*s;

    ///tant que la file n'est pas vide
    while(!file.empty())
    {
        s=file.front();
        std::vector<std::pair<Sommet*,int>> succ;
        succ=m_tabsommet[s->getIndiceSommet()]->getSuccesseurs();

        //std::cout<<"s = "<<s->getIndiceSommet()<<std::endl;

      /*  for(size_t i=0; i<succ.size(); ++i)
        {
            std::cout<<succ[i].first->getIndiceSommet()<<std::endl;
        }*/

        file.pop();
        for(size_t i=0; i<succ.size(); ++i)
        {

            if(couleurs[succ[i].first->getIndiceSommet()] == 0)
            {
                file.push(succ[i].first);
                couleurs[succ[i].first->getIndiceSommet()] = 1;
                cpt++;
                preds[succ[i].first->getIndiceSommet()]= s->getIndiceSommet();

            }
        }

    }
    return cpt;
}
