#include "Sommet.h"
#include <stdio.h>
#include <iostream>

///Constructeur de Sommet
Sommet::Sommet(int indice, std::string nom, float x, float y)
{
    m_indiceSommet = indice;
    m_nom = nom;
    m_x = x;
    m_y = y;
}

Sommet::Sommet()
{

}

///ssprgm d'affichages et de get pour pouvoir utiliser les donnees de la classe Sommet dans les ssprgm de Graphe
float Sommet::getX()
{
    return m_x;
}
float Sommet::getY()
{
    return m_y;
}

int Sommet::getIndiceSommet()
{
    return m_indiceSommet;
}
void Sommet::afficherSommet()
{
    std::cout << "Indice: " << m_indiceSommet << " Nom :" << m_nom << " x :"<< m_x << " y: " << m_y << std::endl;
}

void Sommet::AjouterSuccesseur(std::pair<Sommet*,int> s)
{
    m_successeurs.push_back(s);
}

void Sommet::RetirerSuccesseur()
{
    m_successeurs.clear();
}

void Sommet::afficherSuccesseurs()
{
    std::cout <<"AFFICHAGE SUCCESSEURS" << std::endl;
    std::cout << " sommet " << m_indiceSommet << " : ";
    for(size_t i =0; i<m_successeurs.size(); ++i)
    {
        std::cout<< m_successeurs[i].first->getIndiceSommet() << " /(Poids :" << m_successeurs[i].second<< ") ";
    }
    std::cout << "FIN AFFICHAGE SUCCESSEURS" << std::endl;
}

std::vector<std::pair<Sommet*,int>>& Sommet::getSuccesseurs()
{
    return m_successeurs;
}

void Sommet::clearSuccesseur()
{
    m_successeurs.clear();
}

int Sommet::getImportance()
{
    return m_importance;
}

void Sommet::setImportance(int importance)
{
     m_importance=importance;
}

std::string Sommet::getNom()
{
    return m_nom;
}

/*void Sommet::setPoidsD(int poidsD)
{
    m_poidsD=poidsD;
}*/






