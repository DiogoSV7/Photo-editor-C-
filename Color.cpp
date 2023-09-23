#include "Color.hpp"

namespace prog {
    Color::Color(){                             //Default Constructor - Define todas as componentes da cor com o valor 0, ou seja, representa a cor Preto;
        red_ = 0;                         //Variável "red_" inicializada com o valor 0;
        green_ = 0;                       //Variável "green_" inicializada com o valor 0;
        blue_ = 0;                        //Variável "blue_" inicializada com o valor 0;
    }
    Color::Color(const Color& other){           //Copy Constructor - Cria uma nova cor através da cópia de uma outra cor "other"
        red_ = other.red();               //Através da função definida posteriormente "red()", "copiamos" o valor de "red_" referente à cor "other";
        green_ = other.green();           //Através da função definida posteriormente "green()", "copiamos" o valor de "green_" referente à cor "other";
        blue_ = other.blue();             //Através da função definida posteriormente "blue()", "copiamos" o valor de "blue_" referente à cor "other";
    }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue){   //Construtor using supplied values;
        red_ = red;                       //Atribui à variável "red_", previamente definida em "Color.hpp", o valor de "red" fornecido;
        green_ = green;                   //Atribui à variável "green_", previamente definida em "Color.hpp", o valor de "green" fornecido;
        blue_ = blue;                     //Atribui à variável "green_", previamente definida em "Color.hpp", o valor de "blue" fornecido;
    }
    rgb_value Color::red() const {
        return red_;                       //Definição, através de uma função "red()", que retorna um valor inalterável (const), dos valores de cada variável para obter a cor "Vermelho";
    }
    
    rgb_value Color::green() const {
        return green_;                       //Definição, através de uma função "green()", que retorna um valor inalterável (const), dos valores de cada variável para obter a cor "Verde";
    }
    
    rgb_value Color::blue() const {
        return blue_;                       //Definição, através de uma função "blue()", que retorna um valor inalterável (const), dos valores de cada variável para obter a cor "Azul";
    }


    rgb_value& Color::red()  {
        return red_;                      //Função que retorna o valor da quantidade de "Red" de uma determinada cor;
    }
    rgb_value& Color::green()  {
      return green_;                      //Função que retorna o valor da quantidade de "Green" de uma determinada cor;
    }
    rgb_value& Color::blue()  {
      return blue_;                        //Função que retorna o valor da quantidade de "Blue" de uma determinada cor;
    }
}