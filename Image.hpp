#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"
#include <vector>

namespace prog
{
  class Image
  {
  private:                              //Definição das variáveis de Largura("width"), Altura("height") e de referência a cada Pixel, que serão utilizadas;
    int width_;                         //Os nomes das variáveis são iguais apenas com um "_" acrescentado posteriormente, no âmbito de facilitar a perceção dos valores a serem utilizados;
    int height_;
    std::vector<Color> pixel_;          //Criação de uma variável "pixel_" necessária para conseguirmos alterar, obter informação acerca de cada pixel. Inicializada como "nullptr" para não existirem erros se a variável for acessada antes de ser propriamente alocada;
  public:                               //Public functions necessárias para uma correta representação das dimensões da imagem, assim como do "pixel matrix" e também as funções necessárias para que "script" possa ser corretamente implementado (no caso int& height e também int& width)
    Image(int w, int h, const Color &fill = {255, 255, 255});
    ~Image();
    int width() const;
    int height() const;
    int& width();
    int& height();
    Color &at(int x, int y);
    const Color &at(int x, int y) const;
  };
}
#endif