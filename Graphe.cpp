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
        for(unsigned int i=0; i<m_tabarete.size(); ++i)
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
    int taille;
    Sommet sommet;
    int indiceSommet,indiceArete,extrem1,extrem2;

    ///Float pour les x et y pour gerer les nombres a virgule
    float x,y;
    std::string nom;

    std::ifstream iss(fichiertopo);
    if(iss)
    {
        iss >> m_orient; /// on recupere l'orientation du graphe
        iss >> m_ordre; /// on recupere l'ordre du graphe
        m_tabcoords.clear();
        m_tabsommet.clear();
        for( int i=0; i<getOrdre(); i++)
        {
            iss >> indiceSommet >> nom >> x >> y;
            m_tabsommet.push_back(new Sommet(indiceSommet,nom,x,y));
            m_tabcoords.push_back(new Coords(x,y));
        }
        iss >> taille;
        m_tabarete.clear();

        for( int i=0; i<taille; i++)
        {
            iss >> indiceArete >> extrem1 >> extrem2 ;
            // m_tabsommet[extrem1]->AjouterSuccesseur(std::make_pair(m_tabsommet[extrem2],m_tabpoids[i]->GetPoids()));///avec pair
            // m_tabsommet[extrem2]->AjouterSuccesseur(std::make_pair(m_tabsommet[extrem1],m_tabpoids[i]->GetPoids()));
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
    for( size_t i=0; i<m_tabarete.size(); i++)
    {
        m_tabarete[i]->AfficherArete();
    }
    std::cout << std::endl;

    for(size_t i=0; i<m_tabarete.size(); ++i)
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
        svgout->addText((m_tabsommet[i]->getX())*100-17, (m_tabsommet[i]->getY())*100-15,m_tabsommet[i]->getNom(), "black");
    }

    ///affichage texte aretes
    for(i=0; i<m_tabarete.size(); ++i)
    {
        svgout->addText((m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()+ m_tabsommet[m_tabarete[i]->getExtrem2()]->getX())*49,(m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()+ m_tabsommet[m_tabarete[i]->getExtrem1()]->getY())*49,m_tabarete[i]->GetIndiceArete(),"purple");
        svgout->addText((m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()+ m_tabsommet[m_tabarete[i]->getExtrem2()]->getX())*49+17,(m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()+ m_tabsommet[m_tabarete[i]->getExtrem1()]->getY())*49,"/","black");
        svgout->addText((m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()+ m_tabsommet[m_tabarete[i]->getExtrem2()]->getX())*49+22,(m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()+ m_tabsommet[m_tabarete[i]->getExtrem1()]->getY())*49,m_tabpoids[i]->GetPoids(),"red");
    }

    for(i=0; i<m_tabarete.size(); i++)
    {
        std::cout<<"poids:"<<m_tabpoids[i]->GetPoids()<<std::endl;

        if(m_tabpoids[i]->GetPoids()==1)
            svgout->addLine(m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem1()]->getY()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()*100,"black");
        if(m_tabpoids[i]->GetPoids()==2)
            svgout->addLine(m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem1()]->getY()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()*100,"grey");
        if(m_tabpoids[i]->GetPoids()==3)
            svgout->addLine(m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem1()]->getY()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()*100,"brown");
        if(m_tabpoids[i]->GetPoids()==4)
            svgout->addLine(m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem1()]->getY()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()*100,"blue");
        if(m_tabpoids[i]->GetPoids()==5)
            svgout->addLine(m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem1()]->getY()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()*100,"green");
        if(m_tabpoids[i]->GetPoids()==6)
            svgout->addLine(m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem1()]->getY()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()*100,"yellow");
        if(m_tabpoids[i]->GetPoids()==7)
            svgout->addLine(m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem1()]->getY()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()*100,"orange");
        if(m_tabpoids[i]->GetPoids()==8)
            svgout->addLine(m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem1()]->getY()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()*100,"red");
        if(m_tabpoids[i]->GetPoids()==9)
            svgout->addLine(m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem1()]->getY()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()*100,"purple");
        if(m_tabpoids[i]->GetPoids()==10)
            svgout->addLine(m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem1()]->getY()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()*100,"pink");
        if(m_tabpoids[i]->GetPoids()==11)
            svgout->addLine(m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem1()]->getY()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()*100,"magenta");
        if(m_tabpoids[i]->GetPoids()>=12)
            svgout->addLine(m_tabsommet[m_tabarete[i]->getExtrem1()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem1()]->getY()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getX()*100,m_tabsommet[m_tabarete[i]->getExtrem2()]->getY()*100,"cyan");
    }



    ///affichage coloration en fonction du degre et sommets
    for(i=0; i<getOrdre(); ++i)
    {
        if(m_tabsommet[i]->getImportance()==0)
            svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "cyan");
        if(m_tabsommet[i]->getImportance()==1)
            svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "black");
        if(m_tabsommet[i]->getImportance()==2)
            svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "grey");
        if(m_tabsommet[i]->getImportance()==3)
            svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "brown");
        if(m_tabsommet[i]->getImportance()==4)
            svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "blue");
        if(m_tabsommet[i]->getImportance()==5)
            svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "green");
        if(m_tabsommet[i]->getImportance()==6)
            svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "yellow");
        if(m_tabsommet[i]->getImportance()==7)
            svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "orange");
        if(m_tabsommet[i]->getImportance()==8)
            svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "red");
        if(m_tabsommet[i]->getImportance()==9)
            svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "purple");
        if(m_tabsommet[i]->getImportance()==10)
            svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "pink");
        if(m_tabsommet[i]->getImportance()==11)
            svgout->addCircle((m_tabsommet[i]->getX())*100, (m_tabsommet[i]->getY())*100, 5, 10, "magenta");

    }


    ///affichage des indices
    svgout->addRect(700,60,300,55 + (getOrdre()-1)*22,"white");
    svgout->addLine(700,60,1000,60,"black");
    svgout->addLine(700,100,1000,100,"black");
    svgout->addLine(800,100,700,60,"black");
    svgout->addText(710,95,"Som.", "black");
    svgout->addText(750,75,"Indices", "black");
    svgout->addText(810,85,"Deg", "black");
    svgout->addText(860,85,"V-P", "black");
    svgout->addText(910,85,"Prox", "black");
    svgout->addText(960,85,"Inter", "black");
    for(i=0; i<getOrdre(); ++i)
    {
        svgout->addText(705,113 + i*22,m_tabsommet[i]->getNom(), "grey");
        svgout->addText(810,113 + i*22, m_res_cdn[i], "purple");
        svgout->addText(860,113 + i*22, m_res_cvn[i], "pink");
        svgout->addText(910,113 + i*22, m_res_cpn[i], "blue");
        svgout->addText(960,113 + i*22, m_res_cin[i], "green");
        svgout->addLine(700,115 + i*22,1000,115 + i*22,"black");
    }
    svgout->addLine(700,60,700,115 + (getOrdre()-1)*22,"black");
    svgout->addLine(800,60,800,115 + (getOrdre()-1)*22,"black");
    svgout->addLine(850,60,850,115+ (getOrdre()-1)*22,"black");
    svgout->addLine(900,60,900,115 + (getOrdre()-1)*22,"black");
    svgout->addLine(950,60,950,115 + (getOrdre()-1)*22,"black");
    svgout->addLine(1000,60,1000,115 + (getOrdre()-1)*22,"black");
}

int Graphe::getOrdre()
{
    return m_ordre;
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
