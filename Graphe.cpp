#include "graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include <stack>
#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include "svgfile.h"
#include "Coords.h"
#include "calculs.h"

Graphe::Graphe()
{

}

///ssprgm qui charge le fichier contenant le poids des aretes et stock tout ça dans des tableaux
void Graphe::chargementPoids(std::string &fichierpoids)
{

    int indiceArete,poids;
    std::ifstream iss2(fichierpoids);

    if(iss2)
    {
        iss2 >> m_taille;
        m_tabpoids.clear();
        for( int i=0; i<m_taille; ++i)
        {
            iss2 >> indiceArete >> poids;
            m_tabpoids.push_back(new Arete(indiceArete,poids));
        }
    }
    else
        std::cout << "erreur lors de l'ouverture du fichier "<<std::endl;
        iss2.close();

}

///ssprgm qui charge le fichier et stock tout ça dans des tableaux
void Graphe::chargementTopo(std::string &fichiertopo)
{
    Sommet sommet;
    int x,y, indiceSommet,indiceArete,extrem1,extrem2;
    std::string nom;

    std::ifstream iss(fichiertopo);
    if(iss)
    {
        iss >> m_orient; /// on recupere l'orientation du graphe
        iss >> m_ordre; /// on recupere l'ordre du graphe
        m_tabcoords.clear();
        m_tabsommet.clear();
        for( int i=0; i<m_ordre; i++)
        {
            //std::cout <<m_tabpoids[i]->GetPoids() << std::endl;
            iss >> indiceSommet >> nom >> x >> y;
            m_tabsommet.push_back(new Sommet(indiceSommet,nom,x,y));
            m_tabcoords.push_back(new Coords(x,y));
            //m_tabsommet[i]->setPoidsD(m_tabpoids[i]->GetPoids());
        }
        iss >> m_taille;
        m_tabarete.clear();

        sommet.clearSuccesseur();
        sommet.afficherSuccesseurs();
        for( int i=0; i<m_taille; i++)
        {
            iss >> indiceArete >> extrem1 >> extrem2 ;
            m_tabsommet[extrem1]->AjouterSuccesseur(std::make_pair(m_tabsommet[extrem2],m_tabpoids[i]->GetPoids()));///avec pair
            m_tabsommet[extrem2]->AjouterSuccesseur(std::make_pair(m_tabsommet[extrem1],m_tabpoids[i]->GetPoids()));
            m_tabsommet[extrem1]->AjouterSuccesseurNoPair(m_tabsommet[extrem2]);/// sans pair
            m_tabsommet[extrem2]->AjouterSuccesseurNoPair(m_tabsommet[extrem1]);

            m_tabarete.push_back(new Arete(indiceArete,extrem1,extrem2));
        }
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
    }
    iss.close();
}

///Pour gerer l'affichage de ce que l'on a charge
void Graphe::afficher()
{
    int i;

    for(auto i : m_tabsommet)
    {
        i->afficherSuccesseurs();
        std::cout<<std::endl;
    }
    std::cout<< "Graphe ";
    if(m_orient)
        std::cout<<"oriente"<<std::endl;
    else
        std::cout<<"non oriente"<<std::endl;

    std::cout<<"ordre = "<<m_tabsommet.size()<<std::endl;

    for( i=0; i<m_ordre; i++)
    {
        m_tabsommet[i]->afficherSommet();
    }
    std::cout << std::endl;
    std::cout << "Taille :" << m_taille << std::endl;
    for( i=0; i<m_taille; i++)
    {
        m_tabarete[i]->AfficherArete();
    }
    std::cout << std::endl;

    for(i=0; i<m_taille; ++i)
    {
        m_tabpoids[i]->AfficherAretePoids();
    }
    std::cout << std::endl;
}

///Pour le dessin dans le .svg
void Graphe::dessiner(Svgfile *svgout)
{
    int i;
    svgout->addGrid();

    ///affichage lettres sommets
    for(i=0; i<getOrdre(); ++i)
    {
        svgout->addText((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100-35,m_tabsommet[i]->getNom(), "black");
        svgout->addText((m_tabsommet[i]->getX())*100+7, (m_tabsommet[i]->getY())*100-15,m_tabsommet[i]->getImportance(), "purple");
    }

    ///affichage aretes
    for(i=0; i<getTaille(); ++i)
    {
        svgout->addLine(m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem1()]->getY()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()*100);
        svgout->addText((m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()+ m_tabsommet[m_tabarete[i]->getExtrem2()]->getX())*50 + 5,(m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()+ m_tabsommet[m_tabarete[i]->getExtrem1()]->getY())*49,m_tabpoids[i]->GetPoids(),"red");
    }

    ///affichage coloration en fonction du degre et sommets
    for(i=0; i<getOrdre(); ++i)
    {
        if(m_tabsommet[i]->getImportance()==0)
        svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "black");
        if(m_tabsommet[i]->getImportance()==1)
        svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "grey");
        if(m_tabsommet[i]->getImportance()==2)
        svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "blue");
        if(m_tabsommet[i]->getImportance()==3)
        svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "red");
        if(m_tabsommet[i]->getImportance()==4)
        svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "green");
        if(m_tabsommet[i]->getImportance()==5)
        svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "purple");
        if(m_tabsommet[i]->getImportance()==6)
        svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "pink");
        if(m_tabsommet[i]->getImportance()==7)
        svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "brown");
        if(m_tabsommet[i]->getImportance()==8)
        svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "yellow");
        if(m_tabsommet[i]->getImportance()==9)
        svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "cyan");
        if(m_tabsommet[i]->getImportance()==10)
        svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "orange");

    }
    /*  ///affichage de la legende
    svgout->addRect(600,400,300,100,"white");
    svgout->addLine(600,400,900,400,"red");
    svgout->addLine(600,400,600,500,"red");
    svgout->addLine(900,400,900,500,"red");
    svgout->addLine(600,500,900,500,"red");
    svgout->addText(605,415,"- Rouge : Indice de poids des arêtes", "red");
    svgout->addText(605,435,"- Violet : Indice de centralité de degré", "purple");
    svgout->addText(605,455,"- Rose : Indice de centralité de vecteur propre", "pink");
    svgout->addText(605,475,"- Bleu : Indice de centralité de proximité", "blue");
    svgout->addText(605,495,"- Vert : Indice de centralité d'intermédiarité", "green");*/

    ///affichage des indices
    for(i=0; i<getOrdre(); ++i)
    {
        svgout->addText((m_tabsommet[i]->getX())*100-65+12, (m_tabsommet[i]->getY())*100-20," (", "black");
        svgout->addText((m_tabsommet[i]->getX())*100-65+16, (m_tabsommet[i]->getY())*100-20,m_res_cdn[i], "purple");
        svgout->addText((m_tabsommet[i]->getX())*100-65+46, (m_tabsommet[i]->getY())*100-20,m_res_cvn[i], "pink");
        svgout->addText((m_tabsommet[i]->getX())*100-65+76, (m_tabsommet[i]->getY())*100-20,m_res_cpn[i], "blue");
        svgout->addText((m_tabsommet[i]->getX())*100-65+106, (m_tabsommet[i]->getY())*100-20,m_res_cin[i], "green");
        svgout->addText((m_tabsommet[i]->getX())*100-65+120, (m_tabsommet[i]->getY())*100-20," )", "black");
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

///ssprgm qui gere la sauvegarde
void Graphe::sauvegarde()
{
    std::string fichiersauv;
    std::ofstream flux("sauv.txt");

    if (flux)
    {
        for(int i=0; i<getOrdre(); ++i)
        {
            flux << m_tabsommet[i]->getIndiceSommet() << "\t" << m_res_cd[i] << "\t" << m_res_cdn[i] << "\t" << m_res_cv[i] << "\t" << m_res_cvn[i] <<"\t" << m_res_cp[i] << "\t" << m_res_cpn[i] << "\t " << m_res_ci[i] << "\t" << m_res_cin[i] << std::endl;
        }
    }
}

///introduction de l'attribut m_importance
///(peut etre assujetti aux plusieurs methodes de centralisation, ici adapte seulement qu'a la 1ere methode)
void Graphe::coloration()
{
    for(int i=0; i<getOrdre(); ++i)
    {
        m_tabsommet[i]->setImportance(m_res_cd[i]);
    }
}

Graphe::~Graphe()
{
    for(auto i : m_tabsommet)
    {
        delete i;
    }

     for(auto i : m_tabarete)
    {
        delete i;
    }

    for(auto i : m_tabpoids)
    {
        delete i;
    }

    for(auto i : m_tabcoords)
    {
        delete i;
    }
}
