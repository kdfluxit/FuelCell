//
// Created by 丁中航 on 2018/7/26.
//

#include "currentDensity.h"

#include <iostream>
using namespace std;


//----------------construct & deconstruct
currentDensity::currentDensity(inputStruct::inputs inputStruct) {
    m_freeEnergy_Equilibrium_Intrinsic_DA = inputStruct.freeEnergy_Equilibrium_Intrinsic_DA;
    m_freeEnergy_Equilibrium_Intrinsic_RA = inputStruct.freeEnergy_Equilibrium_Intrinsic_RA;
    m_freeEnergy_Equilibrium_Intrinsic_RD = inputStruct.freeEnergy_Equilibrium_Intrinsic_RD;
    m_freeEnergy_Equilibrium_Intrinsic_RT = inputStruct.freeEnergy_Equilibrium_Intrinsic_RT;
    m_freeEnergy_Intrinsic_O = inputStruct.freeEnergy_Intrinsic_O;
    m_freeEnergy_Intrinsic_OH = inputStruct.freeEnergy_Intrinsic_OH;
};

currentDensity::~currentDensity() {

};

//----------------- free energy & intrinsic rate calculation------------------
void currentDensity::freeEnergyCalculation() {
    //------------------------free energy
    this->freeEnergy.DA = m_freeEnergy_Equilibrium_Intrinsic_DA;
    this->freeEnergy.RA = m_freeEnergy_Equilibrium_Intrinsic_RA - beta * e * (E_0 - electrodePotential);
    this->freeEnergy.RT = m_freeEnergy_Equilibrium_Intrinsic_RT - beta * e * (E_0 - electrodePotential);
    this->freeEnergy.RD = m_freeEnergy_Equilibrium_Intrinsic_RD - beta * e * (E_0 - electrodePotential);
    this->freeEnergy.minusDA = m_freeEnergy_Equilibrium_Intrinsic_DA - m_freeEnergy_Intrinsic_O;
    this->freeEnergy.minusRA = m_freeEnergy_Equilibrium_Intrinsic_RA - \
            m_freeEnergy_Intrinsic_OH + \
             (1.0 - beta) * e * (E_0 - electrodePotential);
    this->freeEnergy.minusRT = m_freeEnergy_Equilibrium_Intrinsic_RT - \
            m_freeEnergy_Intrinsic_OH + \
            m_freeEnergy_Intrinsic_O + \
            (1.0 - beta) * (E_0 - electrodePotential);
    this->freeEnergy.minusRD = m_freeEnergy_Equilibrium_Intrinsic_RD + \
            m_freeEnergy_Intrinsic_OH + \
            (1.0 - beta) * e * (E_0 - electrodePotential);
    //----------------------------intrinsic rate
    this->freeEnergy.intrinsicRate_DA = exp(-this->freeEnergy.DA / (k * T));
    this->freeEnergy.intrinsicRate_RA = exp(-this->freeEnergy.RA / (k * T));
    this->freeEnergy.intrinsicRate_RT = exp(-this->freeEnergy.RT / (k * T));
    this->freeEnergy.intrinsicRate_RD = exp(-this->freeEnergy.RD / (k * T));
    this->freeEnergy.intrinsicRate_minusDA = exp(-this->freeEnergy.minusDA / (k * T));
    this->freeEnergy.intrinsicRate_minusRA = exp(-this->freeEnergy.minusRA / (k * T));
    this->freeEnergy.intrinsicRate_minusRT = exp(-this->freeEnergy.minusRT / (k * T));
    this->freeEnergy.intrinsicRate_minusRD = exp(-this->freeEnergy.minusRD / (k * T));

    //Test

}

//-----------------a,b,c

void currentDensity::abcCalculation() {
    abc.a1 = freeEnergy.intrinsicRate_DA + freeEnergy.intrinsicRate_minusDA + freeEnergy.intrinsicRate_RT;
    abc.b1 = freeEnergy.intrinsicRate_DA - freeEnergy.intrinsicRate_minusRT;
    abc.c1 = freeEnergy.intrinsicRate_DA;
    abc.a2 = freeEnergy.intrinsicRate_RA - freeEnergy.intrinsicRate_RT + freeEnergy.intrinsicRate_minusRD;
    abc.b2 = freeEnergy.intrinsicRate_RA + freeEnergy.intrinsicRate_minusRA + freeEnergy.intrinsicRate_minusRT +\
            freeEnergy.intrinsicRate_RD + freeEnergy.intrinsicRate_minusRD;
    abc.c2 = freeEnergy.intrinsicRate_RA + freeEnergy.intrinsicRate_minusRD;

}
//-----------------coverage Calculation
void currentDensity::coverageCalculation() {
    coverageO = (abc.c1 * abc.b2 - abc.c2 * abc.b1) / (abc.a1 * abc.b2 - abc.a2 * abc.b1);
    coverageOH = (abc.c1 * abc.a2 - abc.c2 * abc.a1) / (abc.b1 * abc.a2 - abc.b2 * abc.a1);
}
//-----------------calcualte current density
void currentDensity::calculateCurrentDensity(double Voltage) {
    electrodePotential = Voltage;
    freeEnergyCalculation();
    abcCalculation();
    coverageCalculation();
/*
    currentDensityValue =j_star * exp(-1.0 / (k * T)) * (1.0 - coverageO - coverageOH) * \
            ( exp(freeEnergy.DA) + exp(freeEnergy.RA - (E_0 - Voltage) / 2.0));
*/
    currentDensityValue = j_star * exp(-1.0 * m_freeEnergy_Equilibrium_Intrinsic_DA / (k * T)) * \
    ( 1.0 - coverageOH - coverageO) + \
    j_star * exp(-1.0 * m_freeEnergy_Equilibrium_Intrinsic_RA / (k * T)) * \
    exp((E_0 - Voltage) / (2.0 * k * T)) * (1.0 - coverageO - coverageOH);

    //show();
}


void currentDensity::calculateCurrentDensity2(double Voltage) {
    electrodePotential = Voltage;
    freeEnergyCalculation();
    abcCalculation();
    coverageCalculation();
    currentDensityValue = j_star * exp(-m_freeEnergy_Equilibrium_Intrinsic_RD/(k*T)) *\
     exp((E_0 - Voltage)/(2*k*T)) * coverageOH;
    //show();
}
//---------------------
double currentDensity::getCurrentDensity() {
    return currentDensityValue;
}
//-----------------show()

void currentDensity::show() {
    std::cout << "free energy:" << std::endl;
    std::cout << "RD:" << m_freeEnergy_Equilibrium_Intrinsic_RD << std::endl;
    std::cout << "RT:" << m_freeEnergy_Equilibrium_Intrinsic_RT << std::endl;
    //-------test

    std::cout << "DA: " << this->freeEnergy.DA << std::endl;
    std::cout << "RA: " << this->freeEnergy.RA << std::endl;
    std::cout << "minusRD: " << this->freeEnergy.minusRD << std::endl;
    std::cout << "Intrinsic RA: " << this->freeEnergy.intrinsicRate_RA << endl;
    std::cout << "k: " << k*100000 << endl;
    std::cout << "T: " << T << endl;
    cout << "abc: " <<abc.a1 << endl << abc.b1 << endl << abc.c1 << endl;
    cout << "Coverage: " << endl << "O: " << coverageO << endl << "OH:" << coverageOH << endl;
}