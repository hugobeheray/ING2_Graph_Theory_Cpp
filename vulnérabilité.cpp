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
void Graphe::suppression_arete(std::string &nomfichierpoids, std::string &nomfichiertopo,Graphe graphe)
{
    int indiceArete, poids;
    std::string nom,sauvPoids = "sauvegardesupAretePoids.txt", sauvtopo = "sauvegardesupArete.txt";
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
    while(choix<0 || choix>getTaille()-1);
    for(int i=0; i<(int)m_tabarete.size(); i++)
    {
        if(choix==m_tabarete[i]->GetIndiceArete())
        {
            ///suppression de l'arete dans le tableau
            m_tabarete.erase(m_tabarete.begin() + i);
            m_taille=m_taille -1;
        }
    }
    for( int i=0; i<(int)m_tabarete.size(); i++)
    {
        std::cout << "Arete "<<m_tabarete[i]->GetIndiceArete() << std::endl;
    }

    ///Changement de fichiers
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
                    else if(i>choix)
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

    ///A GARDER?????
    /*m_tabarete.clear();
    m_tabdegre.clear();
    m_tabpoids.clear();
    m_tabcoords.clear();*/
    // m_tabsommet.clear();

    ///Changement de fichiers
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

    std::cout << sauvPoids << std::endl << sauvtopo << std::endl;

    ///Et on charge les nouveaux fichiers pour la suite...
    graphe.chargementPoids(sauvPoids);
    graphe.chargementTopo(sauvtopo);
    graphe.afficher();
}

///C'est ici que l'on teste la connexite des reseaux pour savoir si notre graphe et d'un seul tenant ou non
void Graphe::TestConnexite()
{
    int cpt=0;

    ///Pour cela, on fait un BFS a partir d'un sommet de depart quelconque, et on regarde en resultat si tous
    /// les sommets on ete colores ou non...
    cpt=BFSconnexite(0);
    std::cout<<"cpt = "<<cpt<<std::endl;
    std::cout<<"ordre = "<<getOrdre()<<std::endl;

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

        std::cout<<"s = "<<s->getIndiceSommet()<<std::endl;

        for(size_t i=0; i<succ.size(); ++i)
        {
            std::cout<<succ[i].first->getIndiceSommet()<<std::endl;
        }

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
