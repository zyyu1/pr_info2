//申明类

#pragma once

#include <string>

class Fahrzeug
{
private:
    std::string p_sName = ""; // 每辆车各自的名称
    const int p_iID;          // 每辆车各自的编号，初始化后不能改变
    static int p_iMaxID;      // 所有车辆共享的编号计数器

    //4.3.4
    double p_dMaxGeschwindigkeit = 0.0; // Maximum speed in km/h.
    double p_dGesamtStrecke = 0.0;      // Total distance traveled in km.
    double p_dGesamtZeit = 0.0;         // Total driving time in hours.
    double p_dZeit = 0.0;               // Time of the last simulation step in hours.


public:
    Fahrzeug();                    // 默认构造函数
    Fahrzeug(std::string sName);    // 带名称的构造函数
    ~Fahrzeug();                   // 析构函数

    Fahrzeug(std::string sName, double dMaxGeschwindigkeit);

    //4.3.5
    static void vKopf();            //vKopf() 是 static，可以直接用 Fahrzeug::vKopf() 打印一次表头
    void vAusgeben() const;         //通过具体的车辆对象调用，末尾的 const 表示它只读取车辆数据

    //4.3.7
    void vSimulieren();

};