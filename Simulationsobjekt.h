
#ifndef SIMULATIONSOBJEKT_H
#define SIMULATIONSOBJEKT_H

#include <string>
#include <iostream>

class Simulationsobjekt
{
public:
    Simulationsobjekt(const std::string& sName = "");
    virtual ~Simulationsobjekt();

    // Disable copy construction
    Simulationsobjekt(const Simulationsobjekt&) = delete;

    Simulationsobjekt& operator=(
        const Simulationsobjekt& other);

    // Pure virtual simulation method =0纯虚函数
    virtual void vSimulieren() = 0;

    // Virtual output method
    virtual void vAusgeben(std::ostream& out) const;

    // Compare object IDs
    bool operator==(
        const Simulationsobjekt& other) const;

    //5.4 修复：补充 cpp 中已有的 getName 声明，供 Weg 只读访问车辆名称。
    const std::string& getName() const;

protected:
    std::string p_sName;
    double p_dZeit = 0.0;

private:
    const int p_iID;
    static int p_iMaxID;
};

// Output operator
std::ostream& operator<<(
    std::ostream& out,
    const Simulationsobjekt& objekt);

#endif
