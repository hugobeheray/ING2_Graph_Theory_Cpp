#include "Sommet.h"
#include <stdio.h>
#include <iostream>

Sommet::Sommet(int num)
{
  m_num = num;
}

int Sommet::GetNum()  {return m_num;}
int Sommet::getX()  {return m_x;}
int Sommet::getY()  {return m_y;}
void Sommet::afficherSuccesseurs()
{
  std::cout << " sommet " << m_num << " : ";
  for(auto s : m_successeurs)
  {
    std::cout << s->GetNum() << " ";
  }
}
void Sommet::AjouterSuccesseur(Sommet*s)
{
  m_successeurs.push_back(s);
}

 std::vector< Sommet*>& Sommet::getSuccesseurs()
{
  return m_successeurs;
}
