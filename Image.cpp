#include "Image.hpp"
#include "Color.hpp"
#include <vector>

namespace prog {
    Image::Image(int w, int h, const Color& fill){
      width_ = w;                                             //Atribui a width_, previamente definido em image.hpp, o valor de "w" fornecido
      height_ = h;                                            //Atribui a height_, previamente definido em iamge.hpp, o valor de "h" fornecido
      pixel_ = std::vector<Color>(w * h, fill);               //Atribui a pixel_, perviamente definido em image.hpp, o vector que atribui a acada pixel da imagem de dimensão "w*h" a cor fill
    }

    Image::~Image() {                                         // Destructor (vazio porque não é utilizada dynamically allocated memory de forma explícita)
    }

    int Image::width() const { 
      return width_;                                          // Definição da função width(), que retorna a largura da imagem em questão
    }

    int Image::height() const { 
      return height_;                                         // Definição da função height(), que retorna a altura da imagem em questão
    }

    int& Image::width(){ 
      return width_;                                          //Definição de uma nova função width_(), desta vez por referência, necessária para a implementação de "script"
    }

    int& Image::height(){ 
      return height_;                                         //Definição de uma nova função height_(), desta vez por referência, necessária para a implementação de "script"
    }

    Color& Image::at(int x, int y) {
      return pixel_[y * width_ + x];                          //Definição da função que permite obter uma "mutable reference" ao valor do pixel (x, y), acessando o vetor pixel_ na posição y * width + x 
    }
    
    const Color& Image::at(int x, int y) const { 
      return pixel_[y * width_ + x]; //Definição da função que permite obter uma referência, para "read-only purposes", do valor do pixel (x, y), obtido novamente através do acesso ao vetro pixel_ na posição y * width + x
    }
}
