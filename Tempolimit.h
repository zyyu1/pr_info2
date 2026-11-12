
#pragma once

#include <limits>

// enum class（Aufzählungsklasse）定义三种Speed limit categories
enum class Tempolimit
{
    Innerorts = 50,
    Landstrasse = 100,
    Autobahn = std::numeric_limits<int>::max()
};
