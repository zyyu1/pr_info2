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
              << std::setw(24) << "Current Speed (km/h)"
              //4.4.2增加两列，分别显示累计耗油量和当前油量。
              << std::setw(22) << "Total Fuel Used (L)"
              << std::setw(18) << "Fuel Level (L)"
              << '\n';
}

//输出列表
/*void Fahrzeug::vAusgeben() const
{
    std::cout << std::right << std::fixed << std::setprecision(2)
              << std::setw(6)  << p_iID
              << std::setw(14) << p_sName
              << std::setw(20) << p_dMaxGeschwindigkeit
              << std::setw(22) << p_dGesamtStrecke
              //4.4.3增加一列，显示当前速度。
              << std::setw(24) << dGeschwindigkeit();
}
*/
//4.5.1 将 vAusgeben() 改为接受 std::ostream& 参数，方便输出到不同的流。
void Fahrzeug::vAusgeben(std::ostream& oAusgabe) const
{
    oAusgabe << std::right << std::fixed << std::setprecision(2)
      << std::setw(6)  << p_iID
      << std::setw(14) << p_sName
      << std::setw(20) << p_dMaxGeschwindigkeit
      << std::setw(22) << p_dGesamtStrecke
      << std::setw(24) << dGeschwindigkeit();
}

//4.3.7
void Fahrzeug::vSimulieren()
{
    //4.4.4：double 运算可能产生微小误差；时间差不超过 1e-6 小时视为同一时刻。
    //只有时间确实前进才模拟，避免舍入误差引起重复行驶。
    const double dEpsilon = 1e-6;
    //if (dGlobaleZeit > p_dZeit)
    if (dGlobaleZeit - p_dZeit > dEpsilon)
    {
        //p_dGesamtStrecke += p_dMaxGeschwindigkeit * (dGlobaleZeit - p_dZeit);
        p_dGesamtStrecke += dGeschwindigkeit() * (dGlobaleZeit - p_dZeit);  //调用 vSimulieren() 时会通过虚函数获取对应车辆的速度
        p_dGesamtZeit += dGlobaleZeit - p_dZeit;
        p_dZeit = dGlobaleZeit;
    }
}

//4.4.2普通车辆的实现
//旧签名：double Fahrzeug::dTanken(double dMenge)
//无油箱车辆不使用加油参数，省略参数名以避免未使用参数警告。
double Fahrzeug::dTanken(double /* dMenge */)
{
    return 0.0;
}

//4.4.3
double Fahrzeug::dGeschwindigkeit() const
{
    return p_dMaxGeschwindigkeit;
}

//4.5.2
std::ostream& operator<<(std::ostream& oAusgabe, const Fahrzeug& tFahrzeug)
{
    tFahrzeug.vAusgeben(oAusgabe);
    return oAusgabe;
}

//4.5.4
bool Fahrzeug::operator<(const Fahrzeug& tVergleichsfahrzeug) const
{
    return p_dGesamtStrecke < tVergleichsfahrzeug.p_dGesamtStrecke;
}

//4.5.5禁止复制构造，实现赋值运算符
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& tVergleichsfahrzeug)
{
    p_sName = tVergleichsfahrzeug.p_sName;
    p_dMaxGeschwindigkeit = tVergleichsfahrzeug.p_dMaxGeschwindigkeit;

    return *this;
}