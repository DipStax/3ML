#pragma once

#include <string>
#include <vector>

#include "M3L/Tool/Export.hpp"

namespace split
{
    M3L_API std::pair<std::string, std::string> noSpace(const std::string &_str, char _c);
    M3L_API std::pair<std::string, std::string> standard(const std::string &_str, char _c);
    M3L_API std::vector<std::string> multiple(const std::string &_str, char _c, bool _nsp = false);
}