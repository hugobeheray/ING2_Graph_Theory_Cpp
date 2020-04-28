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
        for(i=0; i<m_taille; ++i)
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
            m_tabsommet[i]->setPoidsD(m_tabpoids[i]->GetPoids());
        }
        iss >> m_taille;
        for( i=0; i<m_taille; i++)
        {
            iss >> indiceArete >> extrem1 >> extrem2 ;
            m_tabsommet[extrem1]->AjouterSuccesseur(std::make_pair(m_tabsommet[extrem2],m_tabpoids[i]->GetPoids()));
            m_tabsommet[extrem2]->AjouterSuccesseur(std::make_pair(m_tabsommet[extrem1],m_tabpoids[i]->GetPoids()));

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

void Graphe::dessiner(Svgfile *svgout)
{
    int i;
    svgout->addGrid();
    ///affichage lettres sommets
    for(i=0; i<getOrdre(); ++i)
    {
        svgout->addText((m_tabsommet[i]->getX())*100-5, (m_tabsommet[i]->getY())*100-15,m_tabsommet[i]->getNom(), "black");
        svgout->addText((m_tabsommet[i]->getX())*100+7, (m_tabsommet[i]->getY())*100-15,m_tabsommet[i]->getImportance(), "purple");
    }
    ///affichage aretes
    for(i=0; i<getTaille(); ++i)
    {
        svgout->addLine(m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem1()]->getY()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()*100);
        svgout->addText((m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()+ m_tabsommet[m_tabarete[i]->getExtrem2()]->getX())*50,(m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()+ m_tabsommet[m_tabarete[i]->getExtrem1()]->getY())*49,m_tabpoids[i]->GetPoids(),"red");
    }
    ///affichage coloration et sommets
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
    }
    ///affichage legende
    svgout->addRect(600,200,300,100,"white");
    svgout->addLine(600,200,900,200,"red");
    svgout->addLine(600,200,600,300,"red");
    svgout->addLine(900,200,900,300,"red");
    svgout->addLine(600,300,900,300,"red");
    svgout->addText(605,215,"- Rouge : Indice de poids des arêtes", "red");
    svgout->addText(605,235,"- Violet : Indice de centralité de degré", "purple");
    svgout->addText(605,255,"- Rose : Indice de centralité de vecteur propre", "pink");
    svgout->addText(605,275,"- Bleu : Indice de centralité de proximité", "blue");
    svgout->addText(605,295,"- Vert : Indice de centralité d'intermédiarité", "green");

}

int Graphe::getOrdre()
{
    return m_ordre;
}

int Graphe::getTaille()
{
    return m_taille;
}

void Graphe::sauvegarde()
{
    std::string fichiersauv;
    std::ofstream flux("sauv.txt");
    ///std::cout<<"nom du fichier"<<std::endl;
    ///std::cin>>fichiersauv;
    if (flux)
    {
        for(int i=0; i<getOrdre(); ++i)
        {
            flux << m_tabsommet[i]->getIndiceSommet() << " " << res_cd[i] << " " << res_cdn[i] << " " << res_cv[i] << " " << res_cvn[i] <<" " << std::endl;
        }
    }
}

///introduction de l'attribut m_importance (peut etre assujetti aux plusieurs methodes de centralisation, ici adapté seulement qu'à la 1ere methode)
void Graphe::coloration()
{
    for(int i=0; i<getOrdre(); ++i)
    {
        m_tabsommet[i]->setImportance(res_cd[i]);
        //std::cout<<m_tabsommet[i]->getImportance()<<std::endl;
    }


}

Graphe::~Graphe()
{
    for(auto i : m_tabsommet)
    {
        delete i;
    }
}
