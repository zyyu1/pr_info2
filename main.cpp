
#include <iostream>
#include "Fahrzeug.h"
#include <memory>
#include <utility>  // std::move
#include <vector>   // std::vector
#include "PKW.h"
#include "Fahrrad.h"
#include <cmath>
#include <algorithm>  // std::min：限制最后一步的目标时间。

//4.3.6定义全局变量,表示模拟的总时间，单位为小时。
double dGlobaleZeit = 0.0;

//////////////////////// test 4.3.1 /////////////////////////
/*
int main()
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}
*/

//命名：i=int，d=double，b=bool，s=string，p=指针，t=对象或容器。
//4.3.3
void vAufgabe_1()
{
    Fahrzeug tAuto1;
    Fahrzeug tAuto2("su7");

    //4.3.5
    Fahrzeug::vKopf();

    //4.3.5
    //auto1.vAusgeben();
    //4.5.1
    //auto1.vAusgeben(std::cout);
    //std::cout << '\n';
    //4.5.3
    std::cout << tAuto1 << '\n';

    //4.3.5
    //auto2.vAusgeben();
    //4.5.1
    //auto2.vAusgeben(std::cout);
    //std::cout << '\n';
    //4.5.3
    std::cout << tAuto2 << '\n';

    Fahrzeug* pAuto1 = new Fahrzeug;
    Fahrzeug* pAuto2 = new Fahrzeug("yu7");

    //调试：delete 立即销毁指针所指车辆，可在析构函数设置断点查看调用栈。
    delete pAuto1;
    delete pAuto2;

    //各自独占一辆车
    auto pUniqueAuto1 = std::make_unique<Fahrzeug>("model3");
    auto pUniqueAuto2 = std::make_unique<Fahrzeug>("modely");

    //各自创建并持有一辆车
    auto pSharedAuto1 = std::make_shared<Fahrzeug>("model3");
    auto pSharedAuto2 = std::make_shared<Fahrzeug>("modely");

    // use_count()测试
    //两个指针现在共同持有同一辆 model3（ID 7）
    std::cout << "Owners before copy: " << pSharedAuto1.use_count() << '\n';

    auto pSharedAuto1Kopie = pSharedAuto1;

    std::cout << "Owners after copy: " << pSharedAuto1.use_count() << '\n';

    // unique_ptr 复制测试
    //unique_ptr 对车辆拥有独占所有权。如果允许这行复制，两个 unique_ptr 就会同时拥有同一辆车。
    //因此 C++ 禁用了 unique_ptr 的复制赋值，复制构造也同样被禁用。
    //uniqueAuto2 = uniqueAuto1;

    //把两个 unique_ptr 移入 vector，再用 clear() 观察车辆何时销毁

    std::vector<std::unique_ptr<Fahrzeug>> tUniqueAutos;

    //push_back 将车辆的所有权转交给 uniqueAutos
    //转移完成后，uniqueAuto1 和 uniqueAuto2 都为空，容器持有 ID 5 和 6 的车辆。
    tUniqueAutos.push_back(std::move(pUniqueAuto1));
    tUniqueAutos.push_back(std::move(pUniqueAuto2));

    //调试：clear 在本行释放独占所有权，两个车辆在调用期间销毁。
    tUniqueAutos.clear();

    //在同一个 vector 中，复制 sharedAuto1，再移动 sharedAuto2，比较两辆车的引用计数
    std::vector<std::shared_ptr<Fahrzeug>> tSharedAutos;

    //复制 sharedAuto1 后，model3（ID 7）有三个所有者：sharedAuto1、sharedAuto1Copy 和容器里的第一个元素。
    tSharedAutos.push_back(pSharedAuto1);
    std::cout << "Model 3 owners after copy: "
            << pSharedAuto1.use_count() << '\n';

    //移动 sharedAuto2 后，modely（ID 8）的所有权转给容器。sharedAutos.back() 取出容器中最后一个指针来查询计数，结果为 1。
    //原来的 sharedAuto2 变为空，计数为 0
    tSharedAutos.push_back(std::move(pSharedAuto2));
    std::cout << "Model Y owners after move: "
            << tSharedAutos.back().use_count() << '\n';
    std::cout << "Original Model Y pointer count: "
            << pSharedAuto2.use_count() << '\n';
    //调试：离开作用域时，容器先销毁；共享车辆仅在最后一个所有者释放时销毁。
    //局部对象 tAuto2、tAuto1 按构造逆序销毁；详见 Block1_Debug_Notes.md。
    }

//4.3.8
//从终端读取三辆车的名称和最高速度，用 std::make_unique<Fahrzeug>() 创建车辆并存入 vector，然后循环推进全局时钟。
//每个时间步都调用每辆车的 vSimulieren()，再用 vAusgeben() 打印结果。
//4.5.3：输出改为使用 operator<<。
void vAufgabe_1a()
{
    std::vector<std::unique_ptr<Fahrzeug>> tUniqueAutos;

    for (int iIndex = 0; iIndex < 3; ++iIndex)
    {
        std::string sName;
        double dMaxGeschwindigkeit = 0.0;

        std::cout << "Enter vehicle " << iIndex + 1
                  << " name and maximum speed (km/h): ";

        if (!(std::cin >> sName >> dMaxGeschwindigkeit))
        {
            std::cout << "Invalid input.\n";
            return;
        }

        tUniqueAutos.push_back(std::make_unique<Fahrzeug>(sName, dMaxGeschwindigkeit));
    }

    dGlobaleZeit = 0.0;

    //模拟循环,每次循环推进全局时钟 0.25 小时，打印当前时间和所有车辆的状态。
    for (int iIndex = 0; iIndex < 4; ++iIndex)
    {
        dGlobaleZeit += 0.25;

        std::cout << "\nSimulation time: " << dGlobaleZeit << " h\n";
        Fahrzeug::vKopf();

        for (const auto& pFahrzeug : tUniqueAutos)
        {
            pFahrzeug->vSimulieren();
            //vehicle->vAusgeben();
            //4.5.1
            //vehicle->vAusgeben(std::cout);
            //std::cout << '\n';
            //4.5.3
            std::cout << *pFahrzeug << '\n';
        }
    }
}

//4.4.4从终端读取汽车和自行车的数量及参数，将它们一起存入 std::vector<std::unique_ptr<Fahrzeug>>，
//循环模拟并输出状态，在模拟到 3 小时时给汽车加满油。
void vAufgabe_2()
{
    std::vector<std::unique_ptr<Fahrzeug>> tFahrzeuge;

    int iAnzahlPKW = 0;
    int iAnzahlFahrraeder = 0;

    std::string sName;
    std::string sTankauswahl;

    double dMaxGeschwindigkeit = 0.0;
    double dVerbrauch = 0.0;
    double dTankvolumen = 55.0;

    std::cout << "Enter the number of cars: ";
    if (!(std::cin >> iAnzahlPKW) || iAnzahlPKW < 0)
    {
        std::cout << "Invalid number of cars.\n";
        return;
    }

    for (int iIndex = 0; iIndex < iAnzahlPKW; ++iIndex)
    {
        std::cout << "Enter car " << iIndex + 1
                  << " name, maximum speed (km/h), "
                  << "and fuel consumption (L/100 km): ";

        if (!(std::cin >> sName >> dMaxGeschwindigkeit >> dVerbrauch)
            || dVerbrauch < 0.0)
        {
            std::cout << "Invalid car data.\n";
            return;
        }

        std::cout << "Specify tank capacity? (y/n): ";
        std::cin >> sTankauswahl;

        if (sTankauswahl == "y")
        {
            std::cout << "Enter tank capacity (L): ";

            if (!(std::cin >> dTankvolumen) || dTankvolumen <= 0.0)
            {
                std::cout << "Invalid tank capacity.\n";
                return;
            }

            tFahrzeuge.push_back(std::make_unique<PKW>(
                sName, dMaxGeschwindigkeit, dVerbrauch, dTankvolumen));
        }
        else if (sTankauswahl == "n")
        {
            tFahrzeuge.push_back(std::make_unique<PKW>(
                sName, dMaxGeschwindigkeit, dVerbrauch));
        }
        else
        {
            std::cout << "Invalid choice. Please enter y or n.\n";
            return;
        }
    }

    std::cout << "Enter the number of bicycles: ";
    if (!(std::cin >> iAnzahlFahrraeder) || iAnzahlFahrraeder < 0)
    {
        std::cout << "Invalid number of bicycles.\n";
        return;
    }

    for (int iIndex = 0; iIndex < iAnzahlFahrraeder; ++iIndex)
    {
        std::cout << "Enter bicycle " << iIndex + 1
                  << " name and maximum speed (km/h): ";

        if (!(std::cin >> sName >> dMaxGeschwindigkeit))
        {
            std::cout << "Invalid bicycle data.\n";
            return;
        }

        tFahrzeuge.push_back(
            std::make_unique<Fahrrad>(sName, dMaxGeschwindigkeit));
    }

    //加入6小时模拟和第3小时加油
    //旧版固定 0.25 h 的模拟段，保留作为完成痕迹。
/*
    dGlobaleZeit = 0.0;

    bool refueled = false;
    const double epsilon = 1e-6;

    for (int i = 0; i < 24; ++i)
    {
        dGlobaleZeit += 0.25;

        for (const auto& vehicle : vehicles)
        {
            vehicle->vSimulieren();
        }

        if (!refueled && dGlobaleZeit >= 3.0 - epsilon)
        {
            std::cout << "\nRefueling at 3 hours.\n";

            for (const auto& vehicle : vehicles)
            {
                std::cout << "Fuel added (L): "
                        << vehicle->dTanken() << '\n';
            }

            refueled = true;
        }

        std::cout << "\nSimulation time: " << dGlobaleZeit << " h\n";
        Fahrzeug::vKopf();

        for (const auto& vehicle : vehicles)
        {
            //vehicle->vAusgeben();
            //4.5.1
            //vehicle->vAusgeben(std::cout);
            //std::cout << '\n';
            //4.5.3
            std::cout << *vehicle << '\n';
        }
    }
*/
    //4.4.4：可修改时间步长；跨越加油时刻时拆步，保证恰好在 3 h 加油。
    dGlobaleZeit = 0.0;
    bool bGetankt = false;
    const double dEpsilon = 1e-6;
    const double dZeitschritt = 0.4;
    const double dDauer = 6.0;

    for (int iIndex = 0; iIndex * dZeitschritt < dDauer - dEpsilon; ++iIndex)
    {
        //从整数步号计算目标，避免重复累加时间；最后一步不得超过模拟总时长。
        const double dZielzeit = std::min((iIndex + 1) * dZeitschritt, dDauer);
        while (dGlobaleZeit < dZielzeit - dEpsilon)
        {
            if (!bGetankt && dZielzeit >= 3.0 - dEpsilon)
            {
                dGlobaleZeit = 3.0;
            }
            else
            {
                dGlobaleZeit = dZielzeit;
            }

            for (const auto& pFahrzeug : tFahrzeuge)
            {
                pFahrzeug->vSimulieren();
            }

            //先模拟到 3 h，再加油；bGetankt 保证只执行一次。
            if (!bGetankt && std::fabs(dGlobaleZeit - 3.0) < dEpsilon)
            {
                std::cout << "\nRefueling at 3 hours.\n";
                for (const auto& pFahrzeug : tFahrzeuge)
                {
                    std::cout << "Fuel added (L): " << pFahrzeug->dTanken() << '\n';
                }
                bGetankt = true;
            }

            std::cout << "\nSimulation time: " << dGlobaleZeit << " h\n";
            Fahrzeug::vKopf();
            for (const auto& pFahrzeug : tFahrzeuge)
            {
                std::cout << *pFahrzeug << '\n';
            }
        }
    }
} 

//4.5.6编写 vAufgabe_3()，测试运算符<，创建几辆车并比较它们的累计路程，输出结果。
void vAufgabe_3()
{
    dGlobaleZeit = 0.0;

    PKW tAuto1("su7", 100.0, 8.0);
    PKW tAuto2("yu7", 150.0, 10.0);
    Fahrrad tFahrrad1("RC100", 30.0);

    std::cout << "\nInitial vehicles:\n";
    Fahrzeug::vKopf();
    std::cout << tAuto1 << '\n'
              << tAuto2 << '\n'
              << tFahrrad1 << '\n';

    std::cout << "Initially, auto1 < auto2: "
              << (tAuto1 < tAuto2 ? "true" : "false") << '\n';

    dGlobaleZeit = 1.0;

    tAuto1.vSimulieren();
    tAuto2.vSimulieren();
    tFahrrad1.vSimulieren();

    std::cout << "\nAfter 1 hour:\n";
    Fahrzeug::vKopf();
    std::cout << tAuto1 << '\n'
              << tAuto2 << '\n'
              << tFahrrad1 << '\n';

    std::cout << "auto1 < auto2: "
              << (tAuto1 < tAuto2 ? "true" : "false") << '\n';

    std::cout << "auto2 < auto1: "
              << (tAuto2 < tAuto1 ? "true" : "false") << '\n';

    //验证同一时刻重复模拟不会重复行驶
    tAuto1.vSimulieren();
    tAuto2.vSimulieren();
    tFahrrad1.vSimulieren();

    std::cout << "\nRepeated simulation at the same time:\n";
    Fahrzeug::vKopf();
    std::cout << tAuto1 << '\n'
            << tAuto2 << '\n'
            << tFahrrad1 << '\n';

    tAuto2 = tAuto1;

    std::cout << "\nAfter auto2 = auto1:\n";
    Fahrzeug::vKopf();
    std::cout << tAuto1 << '\n'
              << tAuto2 << '\n';

    // Fahrzeug copy = auto1; // Copy construction is disabled.
}

int main()
{
    //4.3.2
    /*
    Fahrzeug auto1;          // 调用默认构造函数，名称为空。
    Fahrzeug auto2("su7");  // 调用带名称的构造函数。
    */

    //4.3.3
    
    //vAufgabe_1();
    //vAufgabe_1a();
    //vAufgabe_2();
    //验收入口：依次执行四个测试函数；输入提示分别属于 1a 和 2。
    vAufgabe_1();
    vAufgabe_1a();
    vAufgabe_2();
    vAufgabe_3();

    return 0;
}
