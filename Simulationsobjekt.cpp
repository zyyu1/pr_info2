
#include "Simulationsobjekt.h"
#include <iomanip>

// Static class variable
int Simulationsobjekt::p_iMaxID = 0;

// Constructor
Simulationsobjekt::Simulationsobjekt(
    const std::string& sName)
    : p_sName(sName),
      p_iID(++p_iMaxID)
{
}

// Destructor
Simulationsobjekt::~Simulationsobjekt()
{
    std::cout << "Simulationsobjekt geloescht: "
              << p_sName << " (ID: "
              << p_iID << ")" << std::endl;
}

// Output
void Simulationsobjekt::vAusgeben(
    std::ostream& out) const
{
    out << std::setw(6) << p_iID
        << std::setw(14) << p_sName;
}

// Comparison operator
bool Simulationsobjekt::operator==(
    const Simulationsobjekt& other) const
{
    return p_iID == other.p_iID;
}

// Assignment operator
Simulationsobjekt& Simulationsobjekt::operator=(
    const Simulationsobjekt& other)
{
    if (this != &other)
    {
        p_sName = other.p_sName;
    }

    return *this;
}

// Output operator
std::ostream& operator<<(
    std::ostream& out,
    const Simulationsobjekt& objekt)
{
    objekt.vAusgeben(out);
    return out;
}

// Return the object name
//Weg 就可以访问道路上每辆车的名称，而不需要直接访问 Fahrzeug 的成员变量
const std::string& Simulationsobjekt::getName() const
{
    return p_sName;
}