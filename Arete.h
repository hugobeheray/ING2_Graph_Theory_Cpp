#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

class Arete
{
private:
    int m_indiceArete;
    int m_extrem1,m_extrem2;


public:
    Arete(int indiceArete,int extrem1, int extrem2);
    ~Arete();
    void AfficherArete();


};


#endif // ARETE_H_INCLUDED
