
#include "Weg.h"
#include "Fahrzeug.h"

#include <iostream>
#include <iomanip>
#include <utility>

// Default constructor
Weg::Weg()
    : Weg("", 0.0)
{
}

// Constructor with name, length and speed limit
Weg::Weg(const std::string& sName,
         double dLaenge,
         Tempolimit eTempolimit)
    : Simulationsobjekt(sName),
      p_dLaenge(dLaenge),
      p_eTempolimit(eTempolimit)
{
}

// Destructor
Weg::~Weg() = default;

// Return the numeric speed limit
double Weg::getTempolimit() const
{
    return static_cast<double>(p_eTempolimit);
}

// Simulate all vehicles on this road
void Weg::vSimulieren()
{
    for (const auto& pFahrzeug : p_pFahrzeuge)
    {
        if (pFahrzeug)
        {
            pFahrzeug->vSimulieren();
        }
    }
}

// Output road data and vehicle names
void Weg::vAusgeben(std::ostream& oAusgabe) const
{
    Simulationsobjekt::vAusgeben(oAusgabe);

    oAusgabe << " : "
             << std::setw(7) << p_dLaenge
             << " (";

    for (const auto& pFahrzeug : p_pFahrzeuge)
    {
        if (pFahrzeug)
        {
            oAusgabe << " " << pFahrzeug->getName();
        }
    }

    oAusgabe << " )";
}

// Print table header
void Weg::vKopf()
{
    std::cout << std::setw(6) << "ID"
              << std::setw(14) << "Name"
              << std::setw(10) << "Laenge"
              << " | Fahrzeuge" << '\n';
}
