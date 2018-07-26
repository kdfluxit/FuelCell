#include <iostream>
#include "currentDensity.h"
/*
        double freeEnergy_Equilibrium_Intrinsic_DA;0.258
        double freeEnergy_Equilibrium_Intrinsic_RA;0.459
        double freeEnergy_Equilibrium_Intrinsic_RT;0.502
        double freeEnergy_Equilibrium_Intrinsic_RD;0.455
        double freeEnergy_Intrinsic_O;              -0.477
        double freeEnergy_Intrinsic_OH;             -0.12
 */
using namespace std;

int main() {
    double V;
    inputStruct::inputs inputs1 =
            {
                    0.258,
                    0.459,
                    0.502,
                    0.455,
                    -0.477,
                    -0.12
            };
    currentDensity cD = currentDensity(inputs1);

    cD.calculateCurrentDensity(0.77);
    cout << "This is 1: " << cD.getCurrentDensity() << endl;
    cD.calculateCurrentDensity2(0.77);
    cout << "This is 2: " << cD.getCurrentDensity();
    /*
    for (V = 0.1; V < 1; V = V + 0.01)
    {
        cD.calculateCurrentDensity(V);
        std::cout << "current Density:" << cD.getCurrentDensity() << " Voltage: " << V << std::endl;
    }
    */
    return 0;
}


