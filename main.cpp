#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include <vector>

int main(int argc, char *argv[])
{
    Graphe graphe("graphe_etoile1_topo.txt");
    graphe.afficher();
    Svgfile svgfile;

    return 0;
}
void Graphe::dessiner(Svgfile *svgout)
{
    unsigned int i;
    ///affichage lettres sommets et points sommets
    for(i=0;i<getOrdre();++i)
    {
        svgout-->addText(m_indiceSommet.getX(), m_indiceSommet.getY(), GetNum(), "black");
        svgout-->addCircle(m_indiceSommet.getX(), m_indiceSommet.getY(), 5 , 5 , "black");
    }
    ///affichage aretes
    svgout->addLine(m_indiceSommet.getX(), m_indiceSommet.getY(), m_indiceSommet2.getX(),m_indiceSommet2.getY(), "black");
}
