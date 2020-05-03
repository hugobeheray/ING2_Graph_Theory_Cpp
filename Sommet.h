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
    //std::vector<Sommet*> m_successeursNopair;
    //int m_poidsD;
    int m_importance;

public:
    Sommet(int indice, std::string nom, float x, float y);
    float getX();
    float getY();
    Sommet();
    int getIndiceSommet();
    int getImportance();
    void RetirerSuccesseur();
    void setImportance(int importance);
    void setPoidsD(int poidsD);
    std::string getNom();
    void afficherSommet() ;
    void afficherSuccesseurs() ;
    void RetirerSuccesseur();
    void AjouterSuccesseur(std::pair<Sommet*,int> s);
    std::vector<std::pair<Sommet*,int>>& getSuccesseurs();
    std::vector< Sommet*>& getSuccesseursNoPair();
};

#endif // SOMMET_H_INCLUDED
