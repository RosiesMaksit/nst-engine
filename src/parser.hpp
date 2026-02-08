#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <fstream>
#include "world.hpp"

class Parser {
public:
    // Основной метод загрузки
    int loadNST(const std::string& path, World& world);
    
    // Заглушки для остальных (как в твоем исходнике)
    int loadKBD(const std::string& path);
    int loadCNF(const std::string& path);
    int loadLOC(const std::string& path);
};

#endif