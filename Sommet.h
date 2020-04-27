#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <vector>

class Sommet {
private:
    int m_x,m_y;
    int m_indiceSommet;
    char m_nom;
    std::vector< Sommet*> m_successeurs;
    Sommet *m_sommet;

public:
    Sommet(int indice, char nom, int x, int y);
    int GetNum() ;
    int getX();
    int getY();
    void afficherSommet() ;
    void afficherSuccesseurs() ;
    void AjouterSuccesseur(Sommet*s);
     std::vector< Sommet*>& getSuccesseurs();

};

#endif // SOMMET_H_INCLUDED
