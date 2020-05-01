#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

class Arete
{
private:
    int m_indiceArete;
    int m_extrem1,m_extrem2;
    int m_poids;

public:
    Arete(int indiceArete, int poids);
    Arete(int indiceArete,int extrem1, int extrem2);
    ~Arete();
    void AfficherArete();
    void AfficherAretePoids();
    int getExtrem1();
    int getExtrem2();
    int GetPoids();
    int GetIndiceArete();
};

#endif // ARETE_H_INCLUDED
