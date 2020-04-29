#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <vector>
#include <string>

class Sommet
{
private:
    float m_x,m_y;
    int m_indiceSommet;
    std::string m_nom;
    std::vector<std::pair<Sommet*,int>> m_successeurs;
   int m_poidsD;
    Sommet *m_sommet;
    float m_importance;


public:
    Sommet(int indice, std::string nom, float x, float y);
    float getX();
    float getY();
    int getIndiceSommet();
    float getImportance();
    void setImportance(float importance);
    void setPoidsD(int poidsD);
    std::string getNom();
    void afficherSommet() ;
    void afficherSuccesseurs() ;
    void AjouterSuccesseur(std::pair<Sommet*,int> s);
    std::vector<std::pair<Sommet*,int>>& getSuccesseurs();
   // ~Sommet();

};

#endif // SOMMET_H_INCLUDED
