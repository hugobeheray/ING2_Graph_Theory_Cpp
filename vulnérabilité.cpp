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

///Permet de mettre a jour les successeurs apres la suppression d'une arete
void Graphe::Majsuccesseurs()
{
    for(size_t i=0; i<m_tabsommet.size(); ++i)
    {
        m_tabsommet[i]->RetirerSuccesseur();
    }
    for( size_t i=0; i<m_tabarete.size(); i++)
    {
        m_tabsommet[m_tabarete[i]->getExtrem1()]->AjouterSuccesseur(std::make_pair(m_tabsommet[m_tabarete[i]->getExtrem2()],m_tabpoids[i]->GetPoids()));///avec pair

        /// Si le graphe n'est pas oriente
        if(!m_orient)
        {
            m_tabsommet[m_tabarete[i]->getExtrem2()]->AjouterSuccesseur(std::make_pair(m_tabsommet[m_tabarete[i]->getExtrem1()],m_tabpoids[i]->GetPoids()));
        }
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
    while(choix<0);
    couleurbleue();

    for(int i=0; i<(int)m_tabarete.size(); i++)
    {
        if(choix==m_tabarete[i]->GetIndiceArete())
        {
            ///suppression de l'arete dans le tableau
            m_tabarete.erase(m_tabarete.begin() + i);
            m_tabpoids.erase(m_tabpoids.begin() + i);
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

void Graphe::comparaison_indices()
{
    std::vector<float> tabresultat_comparaison_cdn;
    std::vector<float> tabresultat_comparaison_cvn;
    std::vector<float> tabresultat_comparaison_cpn;
    std::vector<float> tabresultat_comparaison_cin;

    for(unsigned int i=0; i<m_tabsommet.size(); i++)
    {
        if(m_res_cdn_initial[i]==0)
        {
            tabresultat_comparaison_cdn.push_back(0);
        }
        else
        {
            tabresultat_comparaison_cdn.push_back((m_res_cdn_initial[i]-m_res_cdn[i])/m_res_cdn_initial[i] *100);
        }
        if(m_res_cvn_initial[i]==0)
        {
            tabresultat_comparaison_cdn.push_back(0);
        }
        else
        {
            tabresultat_comparaison_cvn.push_back((m_res_cvn_initial[i]-m_res_cvn[i])/m_res_cvn_initial[i] *100);
        }
        if(m_res_cpn_initial[i]==0)
        {
            tabresultat_comparaison_cdn.push_back(0);
        }
        else
        {
            tabresultat_comparaison_cpn.push_back((m_res_cpn_initial[i]-m_res_cpn[i])/m_res_cpn_initial[i] *100);
        }
        if(m_res_cin_initial[i]==0)
        {
            tabresultat_comparaison_cdn.push_back(0);
        }
        else
        {
            tabresultat_comparaison_cin.push_back((m_res_cin_initial[i]-m_res_cin[i])/m_res_cin_initial[i] *100);
        }
    }

    for(unsigned int i=0; i<m_tabsommet.size(); i++)
    {
        if(tabresultat_comparaison_cdn[i]>0)
        {
            if(tabresultat_comparaison_cdn[i]>1000)
            {
                std::cout << "Evolution Indice Degre : Sommet : " << i << " : 0%" << std::endl;
            }
            else
            {
                std::cout << "Evolution Indice Degre : Sommet : " << i << " : -" << tabresultat_comparaison_cdn[i] << "%" << std::endl;
            }
        }
        if(tabresultat_comparaison_cdn[i]<0)
        {
            if(tabresultat_comparaison_cdn[i]<1000)
            {
                std::cout << "Evolution Indice Degre : Sommet : " << i << " : 0%" << std::endl;
            }
            else
            {
                std::cout << "Evolution Indice Degre : Sommet : " << i << " : +" << -tabresultat_comparaison_cdn[i] << "%" << std::endl;
            }
        }
        if(tabresultat_comparaison_cdn[i]==0)
        {
            std::cout << "Evolution Indice Degre : Sommet : " << i << " : Pas de changement" << std::endl;
        }
    }

    std::cout<<std::endl;

    for(unsigned int i=0; i<m_tabsommet.size(); i++)
    {
        if(tabresultat_comparaison_cvn[i]>0)
        {
            if(tabresultat_comparaison_cvn[i]>1000)
            {
                std::cout << "Evolution Indice Vecteur propre : Sommet : " << i << " : 0%" << std::endl;
            }
            else
            {
                std::cout << "Evolution Indice Vecteur propre : Sommet : " << i << " : -" << tabresultat_comparaison_cvn[i] << "%" << std::endl;
            }
        }
        if(tabresultat_comparaison_cvn[i]<0)
        {
            if(tabresultat_comparaison_cvn[i]<1000)
            {
                std::cout << "Evolution Indice Vecteur propre : Sommet : " << i << " : 0%" << std::endl;
            }
            else
            {
                std::cout << "Evolution Indice Vecteur propre : Sommet : " << i << " : +" << -tabresultat_comparaison_cvn[i] << "%" << std::endl;
            }
        }
        if(tabresultat_comparaison_cvn[i]==0)
        {
            std::cout << "Evolution Indice Vecteur propre : Sommet : " << i << " : Pas de changement" << std::endl;
        }
    }

    std::cout<<std::endl;

    for(unsigned int i=0; i<m_tabsommet.size(); i++)
    {
        if(tabresultat_comparaison_cpn[i]>0)
        {
            if(tabresultat_comparaison_cpn[i]>1000)
            {
                std::cout << "Evolution Indice Proximite : Sommet : " << i << " : 0%" << std::endl;
            }
            else
            {
                std::cout << "Evolution Indice Proximite : Sommet : " << i << " : -" << tabresultat_comparaison_cpn[i] << "%" << std::endl;
            }
        }
        if(tabresultat_comparaison_cpn[i]<0)
        {
            if(tabresultat_comparaison_cpn[i]<1000)
            {
                std::cout << "Evolution Indice Proximite : Sommet : " << i << " : 0%" << std::endl;
            }
            else
            {
                std::cout << "Evolution Indice Proximite : Sommet : " << i << " : +" << -tabresultat_comparaison_cpn[i] << "%" << std::endl;
            }
        }
        if(tabresultat_comparaison_cpn[i]==0)
        {
            std::cout << "Evolution Indice Proximite : Sommet : " << i << " : Pas de changement" << std::endl;
        }
    }

    std::cout<<std::endl;

    for(unsigned int i=0; i<m_tabsommet.size(); i++)
    {
        if(tabresultat_comparaison_cin[i]>0)
        {
            if(tabresultat_comparaison_cin[i]>1000)
            {
                std::cout << "Evolution Indice Intermediarite : Sommet : " << i << " : 0%" << std::endl;
            }
            else
            {
                std::cout << "Evolution Indice Intermediarite : Sommet : " << i << " : -" << tabresultat_comparaison_cin[i] << "%" << std::endl;
            }
        }
        if(tabresultat_comparaison_cin[i]<0)
        {
            if(tabresultat_comparaison_cin[i]<1000)
            {
                std::cout << "Evolution Indice Intermediarite : Sommet : " << i << " : 0%" << std::endl;
            }
            else
            {
                std::cout << "Evolution Indice Intermediarite : Sommet : " << i << " : +" << -tabresultat_comparaison_cin[i] << "%" << std::endl;
            }
        }
        if(tabresultat_comparaison_cin[i]==0)
        {
            std::cout << "Evolution Indice Intermediarite : Sommet : " << i << " : Pas de changement" << std::endl;
        }
    }

    std::cout<<std::endl;

    ///Et on clear les tableaux pour une bonne gestion de la memoire
    tabresultat_comparaison_cdn.clear();
    tabresultat_comparaison_cin.clear();
    tabresultat_comparaison_cpn.clear();
    tabresultat_comparaison_cvn.clear();
}
