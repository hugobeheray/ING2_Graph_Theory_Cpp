#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <vector>

class Sommet {
private:
    int m_num;
    int m_x;
    int m_y;
    std::vector< Sommet*> m_successeurs;

public:
    Sommet(int num);
    int GetNum() ;
    int getX();
    int getY();
    void afficherSuccesseurs() ;
    void AjouterSuccesseur(Sommet*s);
     std::vector< Sommet*>& getSuccesseurs();

};

#endif // SOMMET_H_INCLUDED
