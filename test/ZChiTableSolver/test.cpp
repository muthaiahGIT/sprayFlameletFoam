#include "tableSolver.H"
#include <ctime>
using namespace std;

int main()
{
    tableSolver ts;
    std::ofstream outfile("lookupResult.csv");

    size_t nsp = 231;
    std::vector<double> Z;
    std::vector<double> chi;
    for (size_t i=0; i<1200; i++)
    {
        for (size_t j=0; j<1001; j++)
        {
            Z.push_back(double(j/1000.0));
            chi.push_back(double(i));
        }
    }
    std::vector<double> T(Z.size());
    std::vector<bool> ext(Z.size());
    std::vector<std::vector<double> > Y(nsp);
    for(size_t i=0; i<nsp; i++)
    {
        Y[i].resize(Z.size());
    }
    clock_t startTime, endTime;
    startTime = clock();
    for(size_t i=0; i<Z.size(); i++)
    {
        ts.find(Z[i], chi[i]);
        T[i] = ts.lookupT();
        ext[i] = ts.extrapol();
        for(size_t j=0; j<nsp; j++)
        {
            Y[j][i] = ts.lookupY(j);
        }
    }
    endTime = clock();
    std::cout << "Run time:\t" << double(endTime - startTime) / CLOCKS_PER_SEC
             << " s" << std::endl;
    for(size_t i=0; i<Z.size(); i++)
    {
        // if (ext[i] == false)
        if (true)
        {
            outfile << Z[i] << "," << chi[i] << "," << T[i] << ",";
            for(size_t j=0; j<nsp; j++)
            {
                outfile << Y[j][i];
                if (j!=nsp-1) outfile << ",";
            }
            outfile << std::endl;
        }
    }

    return 0;
}
