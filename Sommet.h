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
    float m_importance;


public:
    Sommet(int indice, char nom, int x, int y);
    int GetNum() ;
    int getX();
    int getY();
    int getIndiceSommet();
    float getImportance();
    void setImportance(float importance);
    std::string getNom();
    void afficherSommet() ;
    void afficherSuccesseurs() ;
    void AjouterSuccesseur(Sommet*s);
    std::vector< Sommet*>& getSuccesseurs();

};

#endif // SOMMET_H_INCLUDED
