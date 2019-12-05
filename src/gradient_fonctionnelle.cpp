//Calcul de la jacobienne de la fonctionnelle
#include "../include/matrice.hpp"
#include "../include/vecteur.hpp"
#include "../include/globals.hpp"
#include <cmath>
using namespace std;

//Définition du gradient de la fonctionnelle à minimiser
Vecteur<double> gradientFonctionnelle(const Vecteur<double> &x, const Matrice &image)
{
    Matrice p = x(0, image.n * image.m - 1).toMatrice(image.n, image.m);
    Matrice q = x(image.n * image.m, 2 * image.n * image.m - 1).toMatrice(image.n, image.m);
    Matrice G1(2 * image.n, image.m);
    Matrice G2(2 * image.n, image.m);
    Matrice G3(2 * image.n, image.m);

    for (int i = 1; i < image.n + 1; i++)
    {
        for (int j = 1; j < image.m + 1; j++)
        {
            G1(i, j) = -255*p(i, j) * (255 - image(i, j) * sqrt(pow(q(i, j), 2) + pow(p(i, j), 2) + 1)) / pow(pow(q(i, j), 2) + pow(p(i, j), 2) + 1, 2);
            if (i != 1 && j != 1 && i != image.n && j != image.m)
            {
                G2(i, j) = 2 * p(i, j) - p(i, j - 1) - p(i, j + 1) - q(i, j) + q(i + 1, j) - q(i + 1, j - 1) + q(i, j - 1);
                G3(i, j) = 4 * p(i, j) - p(i - 1, j) - p(i + 1, j) - p(i, j - 1) - p(i, j + 1);
            }
        }
    }
    for (int i = image.n + 1; i < 2 * image.n + 1; i++)
    {
        for (int j = 1; j < image.m + 1; j++)
        {
            G1(i, j) = -255*q(i - image.n, j) * (255 - image(i - image.n, j) * sqrt(pow(q(i - image.n, j), 2) + pow(p(i - image.n, j), 2) + 1)) / pow(pow(q(i - image.n, j), 2) + pow(p(i - image.n, j), 2) + 1, 2);
            if (i != image.n + 1 && j != 1 && i != 2 * image.n && j != image.m)
            {
                G2(i, j) = 2 * q(i - image.n, j) - q(i - 1 - image.n, j) - q(i + 1 - image.n, j) - p(i - image.n, j) + p(i - image.n, j + 1) - p(i - 1 - image.n, j + 1) + p(i - 1 - image.n, j);
                G3(i, j) = 4 * q(i - image.n, j) - q(i - 1 - image.n, j) - q(i + 1 - image.n, j) - q(i - image.n, j - 1) - q(i - image.n, j + 1);
            }
        }
    }
    G1 *= pas * pas;
    G2 *= lambda_int;
    G3 *= lambda_csmo;
    return toVecteur((G1 + G2 + G3) * 2);
};