#ifndef COORDS_H_INCLUDED
#define COORDS_H_INCLUDED

class Coords
{
public :
    Coords(double x, double y);
    Coords();
    double getX() const;
    double getY() const;

private :
    double m_x;
    double m_y;
};

#endif // COORDS_H_INCLUDED
