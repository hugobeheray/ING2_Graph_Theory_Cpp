#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <vector>

class Sommet {
private:
    int m_num;
    std::vector< Sommet*> m_successeurs;

public:
    Sommet(int num);
    int GetNum() ;
    void afficherSuccesseurs() ;
    void AjouterSuccesseur(Sommet*s);
     std::vector< Sommet*>& getSuccesseurs();

};

#endif // SOMMET_H_INCLUDED
