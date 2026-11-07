#pragma once

#include "Fahrzeug.h"

class PKW : public Fahrzeug
{
private:
    double p_dVerbrauch;    // Fuel consumption in L/100 km.
    double p_dTankvolumen;  // Tank capacity in L.
    double p_dTankinhalt;   // Current fuel level in L.

public:
    PKW(std::string sName, double dMaxGeschwindigkeit,
        double dVerbrauch, double dTankvolumen = 55.0);

    //4.4.2覆盖声明
    double dTanken(
    double dMenge = std::numeric_limits<double>::infinity()) override;
    void vSimulieren() override;
    //void vAusgeben() const override;
    //4.5.1
    void vAusgeben(std::ostream& oAusgabe) const override;  
};