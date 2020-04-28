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
   std::vector<std::pair<Sommet*,int>> m_successeurs;
    Sommet *m_sommet;
    float m_importance;


public:
    Sommet(int indice, char nom, int x, int y);
    int getX();
    int getY();
    int getIndiceSommet();
    float getImportance();
    void setImportance(float importance);
    std::string getNom();
    void afficherSommet() ;
    void afficherSuccesseurs() ;
    void AjouterSuccesseur(std::pair<Sommet*,int> s);
    std::vector<std::pair<Sommet*,int>>& getSuccesseurs();

};

#endif // SOMMET_H_INCLUDED
