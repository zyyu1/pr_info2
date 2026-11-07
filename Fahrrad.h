#pragma once

#include "Fahrzeug.h"

//class PKW : public Fahrzeug 表示 PKW 是一种 Fahrzeug。
//之后可以通过 Fahrzeug 指针管理汽车和自行车。两种车也都能使用亲类的公开函数，例如 vAusgeben()。
class Fahrrad : public Fahrzeug
{
public:
    Fahrrad(std::string sName, double dMaxGeschwindigkeit);

    double dGeschwindigkeit() const override;
};