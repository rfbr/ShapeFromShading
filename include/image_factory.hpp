#ifndef __IMAGEFACTORY__
#define __IMAGEFACTORY__

#include "./matrice.hpp"
#include "./vecteur.hpp"

class ImageFactory
{
public:
    int n_vert, n_quad; //nombre de points/quadrangles du maillage
    int pix_m, pix_n; //dimensions de l'image
    Matrice vertices; //points du maillage
    Matrice quadrangles; //quadrangles du maillages (sommets indexés par vertices)
    Matrice image;  //image en niveaux de gris 0->255
    Matrice derivH; //dérivées directionnelles de la hauteur en chaque point de l'image

    ImageFactory(const char*);  //constructeur qui lit le fichier de maillage
    void aplatir(Vecteur<double> &source); //maillage 3D -> matrice 2D
    void save2D(const char*);  //enregistrement de la matrice 2D
};

Matrice csvtoMatrix(const char* csvfile); //convertit fichier csv en matrice

#endif
