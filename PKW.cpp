#include "PKW.h"
#include <algorithm>
extern double dGlobaleZeit; //全局时间声明
#include <iomanip>
#include <iostream>

//4.4.2给汽车增加油耗、油箱容量和当前油量。
//构造时可以指定油箱容量，省略时用 55 L。新车的油量始终初始化为油箱容量的一半。
PKW::PKW(std::string sName, double dMaxGeschwindigkeit,
         double dVerbrauch, double dTankvolumen)
    : Fahrzeug(sName, dMaxGeschwindigkeit),
      p_dVerbrauch(dVerbrauch),
      p_dTankvolumen(dTankvolumen),
      p_dTankinhalt(p_dTankvolumen / 2.0)
{
     p_sTyp = "Car";        //4.4.2设置类型为 Car
}

//返回实际加油量, 限制在当前油量和油箱容量之间。负数表示放油。
double PKW::dTanken(double dMenge)
{
    const double dTankmenge = std::clamp(
        dMenge,
        -p_dTankinhalt,
        p_dTankvolumen - p_dTankinhalt);

    p_dTankinhalt += dTankmenge;

    return dTankmenge;
}

//4.4.2
//重写 vSimulieren()，在调用父类的 vSimulieren() 后计算油量变化。若油量为 0，则不再前进。
void PKW::vSimulieren()
{
    //4.4.4：与父类采用相同的时间容差，保证两层模拟对同一时刻的判断一致。
    const double dEpsilon = 1e-6;
    //if (dGlobaleZeit <= p_dZeit)
    if (dGlobaleZeit - p_dZeit <= dEpsilon)
    {
        return;
    }

    //油量不超过 1e-6 升视为空箱，避免微小正残余让汽车额外行驶一个完整时间步。
    //if (p_dTankinhalt > 0.0)
    if (p_dTankinhalt > dEpsilon)
    {
        const double dVorherigeStrecke = p_dGesamtStrecke;

        Fahrzeug::vSimulieren();

        p_dTankinhalt -=
            (p_dGesamtStrecke - dVorherigeStrecke) * p_dVerbrauch / 100.0;

        p_dTankinhalt = std::max(0.0, p_dTankinhalt);
        //将接近零的剩余油量归零，统一后续空箱判断和输出。
        if (p_dTankinhalt <= dEpsilon)
        {
            p_dTankinhalt = 0.0;
        }
    }
    else
    {
        p_dTankinhalt = 0.0;
        //停车时仍同步模拟时间，避免加油后补算停车期间的路程。
        p_dZeit = dGlobaleZeit;
    }
}

//汽车的输出函数
/*
void PKW::vAusgeben() const
{
    //先输出 ID、车名、最高速度和累计路程，并设置两位小数的格式。
    //随后追加汽车的累计耗油量和当前油量。换行仍由调用方负责。
    Fahrzeug::vAusgeben();

    std::cout << std::setw(22)
              << p_dGesamtStrecke * p_dVerbrauch / 100.0
              << std::setw(18)
              << p_dTankinhalt;
}
*/

//4.5.1：输出到传入的流。
void PKW::vAusgeben(std::ostream& oAusgabe) const
{
    //先输出 ID、车名、最高速度和累计路程，并设置两位小数的格式。
    //随后追加汽车的累计耗油量和当前油量。换行仍由调用方负责。
    Fahrzeug::vAusgeben(oAusgabe);

    oAusgabe << std::setw(22)
              << p_dGesamtStrecke * p_dVerbrauch / 100.0
              << std::setw(18)
              << p_dTankinhalt;
}