
#pragma once

#include "Simulationsobjekt.h"
#include "Tempolimit.h"

#include <list>
#include <memory>
#include <string>
#include <ostream>

// Forward declaration
class Fahrzeug;

class Weg : public Simulationsobjekt
{
private:
    // Road length in kilometers
    double p_dLaenge = 0.0;

    // Vehicles currently on this road
    //表示道路拥有一个车辆列表：
    //- std::list：STL 双向链表。
    //- std::unique_ptr<Fahrzeug>：每个车辆对象由一个独占智能指针管理。
    //- p_pFahrzeuge：保存当前道路上的车辆。
    //这里使用 class Fahrzeug; 前向声明（Forward Declaration），避免头文件之间产生循环包含。
    std::list<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;

    // Speed limit category
    Tempolimit p_eTempolimit = Tempolimit::Autobahn;

public:
    // Constructors
    Weg();

    Weg(const std::string& sName,
        double dLaenge,
        Tempolimit eTempolimit = Tempolimit::Autobahn);

    // Destructor
    ~Weg() override;

    // Return the numeric speed limit
    double getTempolimit() const;

    // Simulate all vehicles on this road
    void vSimulieren() override;

    // Output road information
    void vAusgeben(std::ostream& oAusgabe) const override;

    // Print table header
    static void vKopf();
};
