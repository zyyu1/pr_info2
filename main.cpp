
#include <iostream>
#include "Fahrzeug.h"
#include <memory>
#include <utility>  // std::move
#include <vector>   // std::vector

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

//4.3.3
void vAufgabe_1()
{
    Fahrzeug auto1;
    Fahrzeug auto2("su7");

    //4.3.5
    Fahrzeug::vKopf();

    auto1.vAusgeben();
    std::cout << '\n';

    auto2.vAusgeben();
    std::cout << '\n';

    Fahrzeug* p_Auto1 = new Fahrzeug;
    Fahrzeug* p_Auto2 = new Fahrzeug("yu7");

    delete p_Auto1;
    delete p_Auto2;

    //各自独占一辆车
    auto uniqueAuto1 = std::make_unique<Fahrzeug>("model3");
    auto uniqueAuto2 = std::make_unique<Fahrzeug>("modely");

    //各自创建并持有一辆车
    auto sharedAuto1 = std::make_shared<Fahrzeug>("model3");
    auto sharedAuto2 = std::make_shared<Fahrzeug>("modely");

    // use_count()测试
    //两个指针现在共同持有同一辆 model3（ID 7）
    std::cout << "Owners before copy: " << sharedAuto1.use_count() << '\n';

    auto sharedAuto1Copy = sharedAuto1;

    std::cout << "Owners after copy: " << sharedAuto1.use_count() << '\n';

    // unique_ptr 复制测试
    //unique_ptr 对车辆拥有独占所有权。如果允许这行复制，两个 unique_ptr 就会同时拥有同一辆车。
    //因此 C++ 禁用了 unique_ptr 的复制赋值，复制构造也同样被禁用。
    //uniqueAuto2 = uniqueAuto1;

    //把两个 unique_ptr 移入 vector，再用 clear() 观察车辆何时销毁

    std::vector<std::unique_ptr<Fahrzeug>> uniqueAutos;

    //push_back 将车辆的所有权转交给 uniqueAutos
    //转移完成后，uniqueAuto1 和 uniqueAuto2 都为空，容器持有 ID 5 和 6 的车辆。
    uniqueAutos.push_back(std::move(uniqueAuto1));
    uniqueAutos.push_back(std::move(uniqueAuto2));

    uniqueAutos.clear();

    //在同一个 vector 中，复制 sharedAuto1，再移动 sharedAuto2，比较两辆车的引用计数
    std::vector<std::shared_ptr<Fahrzeug>> sharedAutos;

    //复制 sharedAuto1 后，model3（ID 7）有三个所有者：sharedAuto1、sharedAuto1Copy 和容器里的第一个元素。
    sharedAutos.push_back(sharedAuto1);
    std::cout << "Model 3 owners after copy: "
            << sharedAuto1.use_count() << '\n';

    //移动 sharedAuto2 后，modely（ID 8）的所有权转给容器。sharedAutos.back() 取出容器中最后一个指针来查询计数，结果为 1。
    //原来的 sharedAuto2 变为空，计数为 0
    sharedAutos.push_back(std::move(sharedAuto2));
    std::cout << "Model Y owners after move: "
            << sharedAutos.back().use_count() << '\n';
    std::cout << "Original Model Y pointer count: "
            << sharedAuto2.use_count() << '\n';
    }

//4.3.8
//从终端读取三辆车的名称和最高速度，用 std::make_unique<Fahrzeug>() 创建车辆并存入 vector，然后循环推进全局时钟。
//每个时间步都调用每辆车的 vSimulieren()，再用 vAusgeben() 打印结果。
void vAufgabe_1a()
{
    std::vector<std::unique_ptr<Fahrzeug>> uniqueAutos;

    for (int i = 0; i < 3; ++i)
    {
        std::string name;
        double maxSpeed = 0.0;

        std::cout << "Enter vehicle " << i + 1
                  << " name and maximum speed (km/h): ";

        if (!(std::cin >> name >> maxSpeed))
        {
            std::cout << "Invalid input.\n";
            return;
        }

        uniqueAutos.push_back(std::make_unique<Fahrzeug>(name, maxSpeed));
    }

    dGlobaleZeit = 0.0;

    //模拟循环,每次循环推进全局时钟 0.25 小时，打印当前时间和所有车辆的状态。
    for (int i = 0; i < 4; ++i)
    {
        dGlobaleZeit += 0.25;

        std::cout << "\nSimulation time: " << dGlobaleZeit << " h\n";
        Fahrzeug::vKopf();

        for (const auto& vehicle : uniqueAutos)
        {
            vehicle->vSimulieren();
            vehicle->vAusgeben();
            std::cout << '\n';
        }
    }
}

int main()
{
    //4.3.2
    /*
    Fahrzeug auto1;          // 调用默认构造函数，名称为空。
    Fahrzeug auto2("su7");  // 调用带名称的构造函数。
    */

    //4.3.3
    vAufgabe_1();
    vAufgabe_1a();

    return 0;
}
