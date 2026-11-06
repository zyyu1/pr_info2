#include "Fahrzeug.h"
#include <iostream>
#include <iomanip>

extern double dGlobaleZeit;

// 定义所有 Fahrzeug 对象共享的计数器，初始值为 0。
int Fahrzeug::p_iMaxID = 0;

Fahrzeug::Fahrzeug()
    : Fahrzeug("")  // 将空名称交给带参数的构造函数。
{
}

/*
Fahrzeug::Fahrzeug(std::string sName)
    : p_sName(sName),
      p_iID(++p_iMaxID)  // 先把计数器加 1，再用新值初始化 ID。
{
    std::cout << "Vehicle created: Name=\"" << p_sName
            << "\", ID=" << p_iID << '\n';
}

Fahrzeug::~Fahrzeug()
{
    std::cout << "Vehicle destroyed: Name=\"" << p_sName
            << "\", ID=" << p_iID << '\n';
}
*/

//4.3.4
Fahrzeug::Fahrzeug(std::string sName)
    : Fahrzeug(sName, 0.0)
{
}

Fahrzeug::Fahrzeug(std::string sName, double dMaxGeschwindigkeit)
    : p_sName(sName),
      p_iID(++p_iMaxID),
      //完整的条件运算符 条件 ? 值1 : 值2。
      p_dMaxGeschwindigkeit(dMaxGeschwindigkeit > 0.0
                                ? dMaxGeschwindigkeit
                                : 0.0)
{
    std::cout << "Vehicle created: Name=\"" << p_sName
              << "\", ID=" << p_iID << '\n';
}

Fahrzeug::~Fahrzeug()
{
    std::cout << "Vehicle destroyed: Name=\"" << p_sName
            << "\", ID=" << p_iID << '\n';
}


//4.3.5 设置列表
//std::setw() 只设置紧随其后的一个字段的宽度，所以每列都要写一次。
void Fahrzeug::vKopf()
{
    std::cout << std::right
              << std::setw(6)  << "ID"
              << std::setw(14) << "Name"
              << std::setw(20) << "Max Speed (km/h)"
              << std::setw(22) << "Total Distance (km)"
              << '\n';
}

void Fahrzeug::vAusgeben() const
{
    std::cout << std::right << std::fixed << std::setprecision(2)
              << std::setw(6)  << p_iID
              << std::setw(14) << p_sName
              << std::setw(20) << p_dMaxGeschwindigkeit
              << std::setw(22) << p_dGesamtStrecke;
}

//4.3.7
void Fahrzeug::vSimulieren()
{
    if (dGlobaleZeit > p_dZeit)
    {
        p_dGesamtStrecke += p_dMaxGeschwindigkeit * (dGlobaleZeit - p_dZeit);
        p_dGesamtZeit += dGlobaleZeit - p_dZeit;
        p_dZeit = dGlobaleZeit;
    }
}