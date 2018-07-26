//
// Created by 丁中航 on 2018/7/26.
//

#ifndef CURRENTDENSITY_CURRENTDENSITY_H
#define CURRENTDENSITY_CURRENTDENSITY_H

#include "inputNamespace.h"
#include <cmath>

using namespace inputStruct;

class currentDensity {
    double currentDensityValue;
    const double e = 2.71828;//natural constant
    const double beta = 0.5;
    const double k = 8.617e-5;//Boltzmann constant: eV * K^-1
    const double T = 296.0;//K
    const double E_0 = 1.23;//V
    const double j_star = 1000.0;
    double electrodePotential = 0.0;//electrode potential
    double m_freeEnergy_Equilibrium_Intrinsic_DA;
    double m_freeEnergy_Equilibrium_Intrinsic_RA;
    double m_freeEnergy_Equilibrium_Intrinsic_RT;
    double m_freeEnergy_Equilibrium_Intrinsic_RD;
    double m_freeEnergy_Intrinsic_O;
    double m_freeEnergy_Intrinsic_OH;
    //----------------------------
    struct freeEnergyStruct
    {
        double DA, intrinsicRate_DA;
        double RA, intrinsicRate_RA;
        double RT, intrinsicRate_RT;
        double RD, intrinsicRate_RD;
        double minusDA, intrinsicRate_minusDA;
        double minusRA, intrinsicRate_minusRA;
        double minusRT, intrinsicRate_minusRT;
        double minusRD, intrinsicRate_minusRD;
    };
    freeEnergyStruct freeEnergy;

    struct abcStruct
    {
        double a1;
        double b1;
        double c1;
        double a2;
        double b2;
        double c2;
    };
    abcStruct abc;
    double coverageO;//theta_O
    double coverageOH;//theta_OH
    //-------------------
    void freeEnergyCalculation();
    void abcCalculation();
    void coverageCalculation();

public:
    currentDensity(inputs inputStruct);
    ~currentDensity();
    void calculateCurrentDensity(double Voltage);
    void calculateCurrentDensity2(double Voltage);
    double getCurrentDensity();
    void show();

};


#endif //CURRENTDENSITY_CURRENTDENSITY_H
