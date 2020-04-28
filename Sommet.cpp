#include "Sommet.h"
#include <stdio.h>
#include <iostream>

Sommet::Sommet(int indice, char nom, int x, int y)
{
    m_indiceSommet = indice;
    m_nom = nom;
    m_x = x;
    m_y = y;
}

int Sommet::getX()
{
    return m_x;
}
int Sommet::getY()
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

void Sommet::afficherSuccesseurs()
{
    std::cout << " sommet " << m_indiceSommet << " : ";
    for(size_t i =0; i<m_successeurs.size(); ++i)
    {
        std::cout<< m_successeurs[i].first->getIndiceSommet() << " /(Poids :" << m_successeurs[i].second<< ") ";
    }
}

std::vector<std::pair<Sommet*,int>>& Sommet::getSuccesseurs()
{
    return m_successeurs;
}

float Sommet::getImportance()
{
    return m_importance;
}

void Sommet::setImportance(float importance)
{
     m_importance=importance;
}

std::string Sommet::getNom()
{
    return m_nom;
}
