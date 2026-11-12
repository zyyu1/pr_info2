#pragma once

#include "Fahrzeug.h"
#include "Simulationsobjekt.h"
#include <string>
#include <limits>
#include <ostream>

/*
//class PKW : public Fahrzeug 表示 PKW 是一种 Fahrzeug。
//之后可以通过 Fahrzeug 指针管理汽车和自行车。两种车也都能使用亲类的公开函数，例如 vAusgeben()。
class Fahrrad : public Fahrzeug
{
public:
    Fahrrad(std::string sName, double dMaxGeschwindigkeit);

    double dGeschwindigkeit() const override;
};
*/

//5.4 修复：以下误放的 Fahrzeug 定义保留为注释；实际定义位于 Fahrzeug.h。
/*
//5.4.1 — 修改 Fahrzeug，使其继承 Simulationsobjekt
//继承新的抽象亲类
class Fahrzeug : public Simulationsobjekt
{
protected:
    // Vehicle-specific data
    std::string p_sTyp = "Vehicle";
    double p_dMaxGeschwindigkeit = 0.0;
    double p_dGesamtStrecke = 0.0;
    double p_dGesamtZeit = 0.0;

public:
    // Constructors
    Fahrzeug();
    Fahrzeug(std::string sName);
    Fahrzeug(std::string sName, double dMaxGeschwindigkeit);

    // Virtual destructor
    ~Fahrzeug() override = default;

    // Simulation and output
    void vSimulieren() override;
    void vAusgeben(std::ostream& oAusgabe) const override;

    static void vKopf();

    // Vehicle functions
    virtual double dTanken(
        double dMenge = std::numeric_limits<double>::infinity());

    virtual double dGeschwindigkeit() const;

    // Comparison operator
    bool operator<(const Fahrzeug& tVergleichsfahrzeug) const;

    // Copy constructor and assignment operator
    Fahrzeug(const Fahrzeug& tVergleichsfahrzeug) = delete;
    Fahrzeug& operator=(const Fahrzeug& tVergleichsfahrzeug);
};
*/

//5.4 修复：恢复 Fahrrad 子类，通过 Fahrzeug 间接继承 Simulationsobjekt。
class Fahrrad : public Fahrzeug
{
public:
    Fahrrad(std::string sName, double dMaxGeschwindigkeit);
    double dGeschwindigkeit() const override;
};
