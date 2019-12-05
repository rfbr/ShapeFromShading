#include "../include/matrice.hpp"
#include "../include/vecteur.hpp"
#include "../include/globals.hpp"
#include <cmath>

//Definition de la fonctionnelle à minimiser
double fonctionnelle(const Vecteur<double> &x, const Matrice &image)
{
    Matrice p = x(0, image.n * image.m - 1).toMatrice(image.n, image.m);
    Matrice q = x(image.n * image.m, 2 * image.n * image.m - 1).toMatrice(image.n, image.m);
    double e1 = 0;
    double e2 = 0;
    double e3 = 0;

    for (int i = 1; i < image.n + 1; i++)
    {
        for (int j = 1; j < image.m + 1; j++)
        {
            e1 += pow(image(i, j) - (255 / sqrt(1 + pow(p(i, j),2) + pow(q(i, j),2))), 2);
            if (i != image.n && j != image.m)
            {
                e2 += pow(p(i, j + 1) - p(i, j) - q(i + 1, j) + q(i, j), 2);
                e3 += pow(p(i + 1, j) - p(i, j), 2) + pow(p(i, j + 1) - p(i, j), 2) + pow(q(i, j + 1) - q(i, j), 2) + pow(q(i + 1, j) - q(i, j), 2);
            }
        }
    }
    e1 *= pas * pas;
    e2 *= lambda_int;
    e3 *= lambda_csmo;
    return (e1 + e2 + e3);
}