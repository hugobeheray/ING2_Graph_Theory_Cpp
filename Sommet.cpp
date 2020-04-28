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

void Sommet::AjouterSuccesseur(Sommet*s)
{
    m_successeurs.push_back(s);
}

std::vector< Sommet*>& Sommet::getSuccesseurs()
{
    return m_successeurs;
}

float Sommet::getImportance()
{
    return m_importance;
}

std::string Sommet::getNom()
{
    return m_nom;
}
