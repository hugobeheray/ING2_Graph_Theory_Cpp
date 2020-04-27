#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <vector>

class Sommet {
private:
    int m_indiceSommet;
    char m_nom;
    int m_x,m_y;
    std::vector< Sommet*> m_successeurs;

public:
    Sommet(int indice, char nom, int x, int y);
    int GetNum() ;
    void afficherSommet() ;
    void AjouterSuccesseur(Sommet*s);
     std::vector< Sommet*>& getSuccesseurs();

};

#endif // SOMMET_H_INCLUDED
