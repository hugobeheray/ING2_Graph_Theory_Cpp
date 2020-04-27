#include "Sommet.h"
#include <stdio.h>
#include <iostream>
#include "arete.h"

Arete::Arete(int indiceArete, int extrem1, int extrem2)
{
    m_indiceArete = indiceArete;
    m_extrem1 = extrem1;
    m_extrem2 = extrem2;
}

void Arete::AfficherArete()
{
  std::cout << "Indice: " << m_indiceArete << " Extremite 1: " << m_extrem1 << " Extremite 2 :"<< m_extrem2 << std::endl;
}

int Arete::getExtrem1()
{
    return m_extrem1;
}

int Arete::getExtrem2()
{
    return m_extrem2;
}

