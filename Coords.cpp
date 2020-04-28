#include <iostream>
#include "Coords.h"

Coords::Coords(double x, double y)
    : m_x{x}, m_y{y}
{ }

Coords::Coords()
    : m_x{0}, m_y{0}
{ }

void Coords::afficher() const
{
    std::cout << "(" << m_x << ";" << m_y << ")";
}

void Coords::saisir()
{
    std::cout << "Abscisse : ";
    std::cin >> m_x;

    std::cout << "Ordonnee : ";
    std::cin >> m_y;

    std::cout << std::endl;
}

double Coords::getX() const
{
    return m_x;
}

double Coords::getY() const
{
    return m_y;
}

void Coords::setX(double x)
{
    m_x = x;
}

void Coords::setY(double y)
{
    m_y = y;
}


/// Somme vectorielle (version courte)
Coords operator+(const Coords& c1, const Coords& c2)
{
    return {c1.m_x + c2.m_x, c1.m_y + c2.m_y  };
}
