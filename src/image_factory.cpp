#include "../include/image_factory.hpp"
#include "../include/matrice.hpp"
#include "../include/vecteur.hpp"
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

ImageFactory::ImageFactory(const char *filename)
{ //constructeur qui lit le fichier de maillage
  ifstream fichier(filename, ios::in);

  if (fichier)
  {
    for (int i = 0; i < 8; i++)
    {
      fichier.ignore(50, '\n');
    }

    fichier >> n_vert;
    Matrice V(n_vert, 3);

    for (int i = 1; i < n_vert + 1; i++)
    {
      fichier >> V(i, 1);
      fichier >> V(i, 2);
      fichier >> V(i, 3);
      fichier.ignore(50, '\n');
    }

    fichier.ignore(50, '\n');
    fichier.ignore(50, '\n');

    fichier >> n_quad;
    Matrice Q(n_quad, 4);

    for (int i = 1; i < n_quad + 1; i++)
    {
      fichier >> Q(i, 1);
      fichier >> Q(i, 2);
      fichier >> Q(i, 3);
      fichier >> Q(i, 4);
      fichier.ignore(50, '\n');
    }

    fichier.close();
    vertices = V;
    quadrangles = Q;
    pix_n = vertices(n_vert, 1);
    pix_m = vertices(n_vert, 2);
  }
  else
  {
    cerr << "Impossible d'ouvrir le fichier !" << endl;
  }
}

void ImageFactory::aplatir(Vecteur<double> &source)
{ //maillage -> matrice 2D
  Matrice I(pix_n, pix_m);
  int S1, S2, S3;
  Vecteur<double> V1(3);
  Vecteur<double> V2(3);
  Vecteur<double> V3(3);
  Matrice h(2 * pix_n, pix_m);
  for (int i = 0; i < n_quad; i++)
  {//parcours des rectangles du maillage
    S1 = int(quadrangles(i + 1, 1));
    S2 = int(quadrangles(i + 1, 2));
    S3 = int(quadrangles(i + 1, 3));

    // On prend deux côtés du rectangle
    V1(1) = vertices(S1, 1) - vertices(S2, 1);
    V1(2) = vertices(S1, 2) - vertices(S2, 2);
    V1(3) = vertices(S1, 3) - vertices(S2, 3);

    V2(1) = vertices(S3, 1) - vertices(S2, 1);
    V2(2) = vertices(S3, 2) - vertices(S2, 2);
    V2(3) = vertices(S3, 3) - vertices(S2, 3);

    // normale au maillage : produit vectoriel de côtés du rectangle
    V3 = V1 ^ V2;
    V3 /= V3.norm(); //normalisation

    // Calcul du niveau de gris (supposé le même dans tout le rectangle)
    I.val[i / pix_n][i % pix_m] = abs(255 * (source * V3));

    // calcul des dérivées directionnelles de la hauteur
    h.val[i / pix_m][i % pix_m] = -V3(1)/V3(3);
    h.val[(i / pix_m) + pix_n][i % pix_m] = -V3(2)/V3(3);
  }
  derivH = h;
  image = I;
}

void ImageFactory::save2D(const char *savefile)
{ //enregistre matrice -> fichier image (ppm)
  string grey;
  ofstream img(savefile);
  img << "P3" << endl;
  img << pix_m << " " << pix_n << endl;
  img << "255" << endl;
  for (int i = 0; i < pix_n; i++)
  {
    for (int j = 0; j < pix_m; j++)
    {
      grey = to_string(int(image.val[i][j]));
      img << grey << " " << grey << " " << grey << endl;
    }
  }
  img.close();
}

Matrice csvtoMatrix(const char* csvfile)
{ //lit fichier csv
  ifstream csv(csvfile, ios::in);
  int n, m;
  csv >> n;
  csv >> m;
  Matrice M(n, m);
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      csv >> M.val[i][j];
    }
  }
  return M;
}
