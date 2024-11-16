#include <algorithm>

#include "M3L/Tool/Splitter.hpp"

namespace split
{
    std::pair<std::string, std::string> noSpace(const std::string &_str, char _c)
    {
        std::pair<std::string, std::string> res = standard(_str, _c);

        res.first.erase(res.first.begin(), std::find_if_not(res.first.begin(), res.first.end(), [] (char _c) {
            return _c == ' ' || _c == '\t';
        }));
        std::reverse(res.first.begin(), res.first.end());
        res.first.erase(res.first.begin(), std::find_if_not(res.first.begin(), res.first.end(), [] (char _c) {
            return _c == ' ' || _c == '\t';
        }));
        std::reverse(res.first.begin(), res.first.end());

        res.second.erase(res.second.begin(), std::find_if_not(res.second.begin(), res.second.end(), [] (char _c) {
            return _c == ' ' || _c == '\t';
        }));
        std::reverse(res.second.begin(), res.second.end());
        res.second.erase(res.second.begin(), std::find_if_not(res.second.begin(), res.second.end(), [] (char _c) {
            return _c == ' ' || _c == '\t';
        }));
        std::reverse(res.second.begin(), res.second.end());
        return res;
    }

    std::pair<std::string, std::string> standard(const std::string &_str, char _c)
    {
        std::pair<std::string, std::string> res;

        res.first = _str.substr(0, _str.find(_c));
        if (_str.find(_c) != std::string::npos)
            res.second = _str.substr(_str.find(_c) + 1);
        return res;
    }

    std::vector<std::string> multiple(const std::string &_str, char _c, bool _nsp)
    {
        std::pair<std::string, std::string> pair;
        std::vector<std::string> res;

        pair.second = _str;
        do {
            if (_nsp)
                pair = noSpace(pair.second, _c);
            else
                pair = standard(pair.second, _c);
            res.push_back(pair.first);
        } while (!pair.second.empty());
        return res;
    }
}