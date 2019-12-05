#include "../include/lbfgs.hpp"
#include "../include/matrice.hpp"
#include "../include/vecteur.hpp"
#include <cmath>
using namespace std;

//Implémentation de la descente de gradient L-BFGS
Vecteur<double> LBFGS(Vecteur<double> &x, double (*fonction)(const Vecteur<double> &, const Matrice &), Vecteur<double> (*fonctionGradient)(const Vecteur<double> &, const Matrice &), const Matrice &M, double eps)
{
    Matrice_diag Id(x.dim, 1);
    double gamma = 1;  //Facteur de mise à l'échelle
    int m = 5;        //Nombre d'itérations stockées pour calculer Hk
    int k = 0;         //Itération
    int wolfemax = 20; //nombre d'itérations max pour la RL de Wolfe
    Vecteur<Vecteur<double>> s(m);
    Vecteur<Vecteur<double>> y(m);
    Vecteur<double> a(m, 0);
    double b;
    double c1 = pow(10, -4);
    double c2 = 0.9999999;
    while (true)
    {
        cout << "Itération: " << k << "\n";
        Vecteur<double> gradient = fonctionGradient(x, M);
        Vecteur<double> q = gradient;
        cout << "Norme du gradient " << gradient.norm() << "\n";
        if (gradient.norm() < eps || k == 10000)
        {
            return x;
        }
        if (k > 0)
        {
            gamma = (s.val[(k - 1) % m] * y.val[(k - 1) % m]) / (y.val[(k - 1) % m] * y.val[(k - 1) % m]);
        }
        //Approximation de l'inverse de la Hessienne de la forme quadratique de la fonction
        Matrice_diag Hk_0 = Id * gamma;
        //Calcul de la direction de descente Hk*Delta(e) approche two loop recursion
        for (int i = max(k - 1, 0); i > max(k - m - 1, 0); i--)
        {
            a.val[i % m] = (1 / (y.val[i % m] * s.val[i % m])) * (s.val[i % m] * q);
            q = q - y.val[i % m] * a.val[i % m];
        }
        Vecteur<double> r = Hk_0 * q;

        for (int i = max(k - m, 0); i < max(k, 0); i++)
        {
            b = (1 / (y.val[i % m] * s.val[i % m])) * (y.val[i % m] * r);
            r = r + s.val[i % m] * (a.val[i % m] - b);
        }

        Vecteur<double> directionDescente = r * -1;

        //Calcul du pas optimal alpha à l'aide des conditions fortes de Wolfe
        double alpha = 1;
        double f = fonction(x, M);
        cout << "fonction: " << f << "\n";
        double ps = gradient * directionDescente;
        //Rechreche lineaire de Wolfe
        int wolfe = 0;
        while (true)
        {
            Vecteur<double> xd = x + directionDescente * alpha;
            double fd = fonction(xd, M);
            Vecteur<double> g = fonctionGradient(xd, M);

            //Conditions fortes de Wolf
            if ((fd <= f + c1 * alpha * ps && abs(g * directionDescente) <= c2 * abs(ps)) || (wolfe > wolfemax))
            {
                break;
            }
            alpha = alpha / 2;
            wolfe++;
        }

        Vecteur<double> xkPlusUn = x + directionDescente * alpha;

        y.val[k % m] = fonctionGradient(xkPlusUn, M) - fonctionGradient(x, M);
        s.val[k % m] = xkPlusUn - x;
        x = xkPlusUn;
        k++;
    }
};
