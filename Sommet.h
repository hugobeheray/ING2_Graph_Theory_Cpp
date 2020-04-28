#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <vector>
#include <string>

class Sommet
{
private:
    int m_x,m_y;
    int m_indiceSommet;
    std::string m_nom;
    std::vector<Sommet*> m_successeurs;///pour Dijsktra
    Sommet *m_sommet;

public:
    Sommet(int indice, char nom, int x, int y);
    int GetNum() ;
    int getX();
    int getY();
    int getIndiceSommet();
    std::string getNom();
    void afficherSommet() ;
    void afficherSuccesseurs() ;
    void AjouterSuccesseur(Sommet*s);
    std::vector< Sommet*>& getSuccesseurs();

};

#endif // SOMMET_H_INCLUDED
