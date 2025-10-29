#include <stdexcept>
#include <vector>

struct EquationRoot4
{
    double numRoots;
    double roots[4];
};

void ToNormalKoef(double& a, double& b, double& c, double& d, double& e)
{
    b = b / a;
    c = c / a;
    d = d / a;
    e = e / a;
    a = 1;
}

std::vector<double> SolveCubic(double a, double b, double c) 
{
    double Q = (a * a - 3 * b) / 9;
    double R = (2 * a * a * a - 9 * a * b + 27 * c) / 54;
    double Q3 = Q * Q * Q;
    double R2 = R * R;
    double discriminant = Q3 - R2;

    std::vector<double> roots;

    if (discriminant >= 0) 
    {
        double theta = acos(R / sqrt(Q3));
        double sqrtQ = sqrt(Q);
        roots.push_back(-2 * sqrtQ * cos(theta / 3) - a / 3);
        roots.push_back(-2 * sqrtQ * cos((theta + 2 * M_PI) / 3) - a / 3);
        roots.push_back(-2 * sqrtQ * cos((theta - 2 * M_PI) / 3) - a / 3);
    }
    else 
    {
        double alpha = cbrt(sqrt(R2 - Q3) + fabs(R));
        if (R > 0)
            alpha = -alpha;
        double beta = (alpha == 0) ? 0 : Q / alpha;
        double x = (alpha + beta) - a / 3;
        roots.push_back(x);
        // Остальные корни комплексные, их не учитываем
    }

    return roots;
}

// Вычисляем корни кубического уравнения ax^4 + bx^3 + cx^2 + dx + e = 0
EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
    if (a == 0)
        throw std::invalid_argument("a");

    ToNormalKoef(a, b, c, d, e);

    EquationRoot4 result;
    result.numRoots = 0;

    double f = -c;
    double g = b * d - 4 * e;
    double h = 4 * c * e - b * b * e - d * d;

    std::vector<double> cubicRoots = SolveCubic(f, g, h);
}

int main()
{

}