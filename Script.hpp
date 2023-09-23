#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include "Image.hpp"

namespace prog
{
  class Script
  {
  public: 
    Script(const std::string &filename);
    ~Script();
    void run();
  private:
    Image *image = nullptr;
    std::ifstream input;
  private:
    void clear_image_if_any();            //Definição de todas as funções descritas e implementadas em "Script.cpp";
    void open();
    void blank();
    void save();
    void invert();
    void replace();         
    void to_gray_scale();
    void fill();
    void h_mirror();
    void v_mirror();
    void add();
    void rotate_left();
    void rotate_right();
    void crop();
    void median_filter(int ws);
  };
}
#endif
