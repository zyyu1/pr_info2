//申明类

#pragma once

#include <string>
#include <limits>
#include <ostream>
#include "Simulationsobjekt.h"

//class Fahrzeug
class Fahrzeug : public Simulationsobjekt   //修改继承关系
{

/* 成员现在都由 Simulationsobjekt 提供
private:
    std::string p_sName = ""; // 每辆车各自的名称
    const int p_iID;          // 每辆车各自的编号，初始化后不能改变
    static int p_iMaxID;      // 所有车辆共享的编号计数器
*/

//4.4.2
protected:

    //初始化, 普通 Fahrzeug 对象会自动初始化为 "Vehicle"，子类也可以访问这个成员
    std::string p_sTyp = "Vehicle"; // Vehicle category.
    //4.3.4
    double p_dMaxGeschwindigkeit = 0.0; // Maximum speed in km/h.
    double p_dGesamtStrecke = 0.0;      // Total distance traveled in km.
    double p_dGesamtZeit = 0.0;         // Total driving time in hours.
    //由 Simulationsobjekt 提供
    //double p_dZeit = 0.0;               // Time of the last simulation step in hours.


public:

    Fahrzeug();                    // 默认构造函数
    Fahrzeug(std::string sName);    // 带名称的构造函数
   // ~Fahrzeug();                   // 析构函数

   /*
    //4.4.1 virtual 让程序通过 Fahrzeug 指针也能调用对应子类的实现
    virtual ~Fahrzeug();                 
    //virtual void vAusgeben() const;

    //4.5.1
    virtual void vAusgeben(std::ostream& oAusgabe) const;
    virtual void vSimulieren();
    */

    //统一使用 Simulationsobjekt 提供的版本
    ~Fahrzeug() override = default;
    void vAusgeben(std::ostream& oAusgabe) const override;
    void vSimulieren() override;






    Fahrzeug(std::string sName, double dMaxGeschwindigkeit);

    //4.3.5
    static void vKopf();            //vKopf() 是 static，可以直接用 Fahrzeug::vKopf() 打印一次表头
    //void vAusgeben() const;         //通过具体的车辆对象调用，末尾的 const 表示它只读取车辆数据

    //4.3.7
    //void vSimulieren();

    //4.4.2
    virtual double dTanken(
    double dMenge = std::numeric_limits<double>::infinity());

    //4.4.3
    virtual double dGeschwindigkeit() const;   //返回当前速度，若油量为 0，则返回 0。

    //4.5.4
    bool operator<(const Fahrzeug& tVergleichsfahrzeug) const;

    //4.5.5禁止复制构造，实现赋值运算符
    Fahrzeug(const Fahrzeug& tVergleichsfahrzeug) = delete;
    Fahrzeug& operator=(const Fahrzeug& tVergleichsfahrzeug);

};

/*统一使用 Simulationsobjekt 提供的版本
//4.5.2重载输出运算符 <<。完成后，就能使用 std::cout << auto1 输出车辆。
std::ostream& operator<<(std::ostream& oAusgabe, const Fahrzeug& tFahrzeug);
*/