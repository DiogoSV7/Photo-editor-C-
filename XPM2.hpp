#ifndef __prog_XPM2_hpp__
#define __prog_XPM2_hpp__

#include <string>
#include "Image.hpp"

namespace prog {
    std::string decimal_para_hexadecimal(int decimal);              //Definição da função que transformará números decimais em hexadecimais;
    int hexadecimal_para_decimal(std::string hexadecimal);          //Definição da função que transformará números hexadecimais em decimais;
    Image* loadFromXPM2(const std::string &file);                   //Definição da função que criará imagens a partir do formato XPM2;
    void saveToXPM2(const std::string& file, const Image* img);     //Definição da função que guardará imagens no formato XPM2;
}
#endif
