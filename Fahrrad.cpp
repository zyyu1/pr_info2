#include "Fahrrad.h"

#include <algorithm>
#include <cmath>

Fahrrad::Fahrrad(std::string sName, double dMaxGeschwindigkeit)
    : Fahrzeug(sName, dMaxGeschwindigkeit)
{
    p_sTyp = "Bicycle"; //初始化
}

//4.4.3
double Fahrrad::dGeschwindigkeit() const
{
    return std::max(
        12.0,
        p_dMaxGeschwindigkeit
            * std::pow(0.9, std::floor(p_dGesamtStrecke / 20.0)));
            //std::floor(p_dGesamtStrecke / 20.0) 算出已经完成多少个整段 20 km
            //std::pow(0.9, …) 算出速度衰减比例。
            //std::max(12.0, …) 将速度下限设为 12 km/h。
}