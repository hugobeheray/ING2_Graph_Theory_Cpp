#include <iostream>
#include "Coords.h"

/// Les coordonnees servent essentiellement a l'affichage

Coords::Coords(double x, double y)
    : m_x{x}, m_y{y}
{ }

Coords::Coords()
    : m_x{0}, m_y{0}
{ }
double Coords::getX() const
{
    return m_x;
}

double Coords::getY() const
{
    return m_y;
}
