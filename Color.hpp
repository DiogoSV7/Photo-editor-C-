#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

namespace prog
{
  typedef unsigned char rgb_value;
  class Color
  {
    private:
      rgb_value red_;           //Definição de 3 variáveis alusivas ás 3 cores que compõe a estrutura de rgb (vermelho, verde e azul);
      rgb_value green_;         //Os nomes das variáveis são iguais apenas com um "_" acrescentado posteriormente, no âmbito de facilitar a perceção dos valores a serem utilizados;
      rgb_value blue_;
    public:
      Color();
      Color(const Color& c);
      Color(rgb_value r, rgb_value g, rgb_value b);
      rgb_value red() const;
      rgb_value& red();
      rgb_value green() const;
      rgb_value& green();
      rgb_value blue() const;
      rgb_value& blue();
  };
}
#endif
