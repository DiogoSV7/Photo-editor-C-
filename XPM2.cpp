#include <unordered_map>
#include <iostream>
#include "XPM2.hpp"
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

namespace prog {
    int hexadecimal_para_decimal(std::string hexadecimal) {
        int resultado1 = 0;                                                 //Definição de uma função "hexadecimal_para_decimal" que apresenta como argumento uma string, que como o nome indíca, transforma um número de hexadecimal para um número inteiro;
        int length = hexadecimal.length();

        for (int i = 0; i < length; i++) {                                  //Através deste ciclo "for" iremos iterarsobre todos os caracteres de uma string que contém o número em hexadecimal;
            char c = hexadecimal[i];
            int resultado;
            if (c >= '0' && c <= '9') {
                resultado = c - '0';
            } else if (c >= 'A' && c <= 'F') {
                resultado = c - 'A' + 10;
            } else if (c >= 'a' && c <= 'f') {
                resultado = c - 'a' + 10;
            }
            resultado1 = (resultado1 * 16) + resultado;                     //Avaliando o caracter por todas estas condições, no fim iremos receber da função um numero inteiro;
        }
        return resultado1;
    }

    Image* loadFromXPM2(const std::string& file) {
        std::ifstream input(file);                                          //Definição que dá load a uma imagem no formato XPM2;Nesta linha usando o ifstream conseguimos dar input do ficheiro que vamos analisar;
        if (!input.is_open()) {                                             //Caso este não esteja aberto, retornaremos um nullpointer, para evitarmos erros e "leaks" de memória;
            return nullptr;
        }
        std::string line;                                                   //Definição de uma variável do tipo "string";
        getline(input, line);                                               //Através desta chamada a "getLine" conseguimos evitar o cabeçalho;
        getline(input, line);                                               //Agora sim, com a segunda chamada consecutiva iremos começar a analisar as linhas do ficheiro;
        int w, h, n;                                                        //Definição de 3 variáveis do tipo "int", às quais correspondem a largura, altura e o número de cores diferentes;
        std::istringstream iss(line);                                       //Através do método do "istringstream" iremos transformar cada uma das linhas do ficheiro em strings;
        iss >> w >> h >> n;                                                 //Desse modo, iremos conseguir atribuir os valores determinados às variáveis definidas previamente;
        Image* imagemnova = new Image(w, h);                                //Criação de um apontado "imagemnova" no qual iremos criar uma nova imagem com as dimensões (w,h);
        
        std::map<char, Color> mapeamento_de_cores;                          //Criação de um "map" para conseguirmos fazer uma associação entre um caracter e a cor que o mesmo representa em formato XPM2;
        for (int i = 0; i < n; i++) {                                       //Através deste ciclo "for" vamos iterar sobre todos os símbolos diferentes da imagem;
            getline(input, line);                                           //Da mesma forma que fizemos anteriormente, iremos analisar linha a linha;
            char simbolo;                                                   //Definição de uma variável que irá conter o símbolo que corresponde a cada cor;
            std::istringstream iss(line);
            std::string c, hexcode;                                         
            iss >> simbolo;
            iss >> c;
            iss >> hexcode;
            Color cornova;
            cornova.red() = hexadecimal_para_decimal(hexcode.substr(1, 2)); //Para cada simbolo novo descoberto, iremos armazenar a porção de cada cor, com a sua parte da cor RGB, usando a função "hexadeciaml_para_decimal";
            cornova.green() = hexadecimal_para_decimal(hexcode.substr(3, 2));
            cornova.blue() = hexadecimal_para_decimal(hexcode.substr(5, 2));
            mapeamento_de_cores[simbolo] = cornova;                         //Atribuição da cor de cada símbolo dentro do "map";
        }
        for (int y = 0; y < h; y++) {                                       //Através destes dois ciclos "for" iremos iterar sobre todos os píxeis da imagem, dentro dos limites w e h, definidos anteriormente;
            getline(input, line);
            std::istringstream iss(line);
            std::string var;
            iss >> var;
            for (int x = 0; x < w; x++) {
                Color cor = mapeamento_de_cores[var[x]];                    //A cada píxel iremos ver qual é o valor da sua cor, e substituiremos na imagemnova;
                imagemnova->at(x, y).red() = cor.red();
                imagemnova->at(x, y).green() = cor.green();
                imagemnova->at(x, y).blue() = cor.blue();
            }
        }
        input.close();                                                      //Finalmente, depois de percorridos todos os píxeis, podemos fechar o ficheiro e retornar a "imagemnova";
        return imagemnova;
    }
    bool operator<(const Color& primeira, const Color& segunda) {               //Overload do operador "<";
        int primeiraRGB = primeira.red() + primeira.green() + primeira.blue();  //Soma de todas as componentes rgbs das duas cores;
        int segundaRGB = segunda.red() + segunda.green() + segunda.blue();      

        return primeiraRGB < segundaRGB;
    }       
    bool operator==(const Color& primeira, const Color& segunda) {              //Overload do operador "=="  
        return ((primeira.red() == segunda.red()) && (primeira.green() == segunda.green()) && (primeira.blue() == segunda.blue())); //Verificação se cada uma das componentes RGB´s de facto é igual à da outra cor;
    }
    
    std::string decimal_para_hexadecimal(int decimal) {                     //Definição de uma função "decimal_para_hecadecimal(int decimal)", que transforma valores decimais em valores hexadecimais;
        std::string hexadecimal;
        while (decimal > 0) {                                               //Enquanto o valor decimal for superior a 0, iremos repetir continuamente este conjunto de condições;
            int resto = decimal % 16;
            char digito;
            if (resto < 10) {
                digito = '0' + resto;
            } else {
                digito = 'A' + (resto - 10);
            }
            hexadecimal = digito + hexadecimal;
            decimal /= 16;
        }

        if (hexadecimal.empty()) {                                          //Caso o número decimal seja igual a 0;
            hexadecimal = "00";
        } else if (hexadecimal.length() == 1) {                             //Se o número decimal apenas tiver apenas 1 dígito;
            hexadecimal = "0" + hexadecimal;
        }
        return hexadecimal;
    }

    
    void saveToXPM2(const std::string &file, const Image *image)
    {
        std::ofstream output(file); //abre o ficheiro para escrita, d� o nome output
        Color alist['~' - '!']; //cria um array com o tamanho de todos os "simbolos" possiveis para armazenar as cores nos enderessos dos simbolos
        int width = image->width(); //recebe a largura da imagem e associa � variavel width
        int height = image->height(); //recebe a altura da imagem e associa � variavel height
        unsigned char simbolo1 = '!'; //associa � variael simbolo1 o simbolo inicial (simbolo que ser� associado � primeira cor do ficheiro)
        std::unordered_map<Color,char,ColorHash,ColorEqual> mapa; //cria um unordered map em que as keys s�o as cores e os objetos s�o os simbolos. Nos dois parametros seguintes s�o mencionados structs que cont�m operadores, uma delas(ColorHash) calcula os valores hash das cores e outra (ColorEqual) determina se duas cores s�o iguais. Basicamente servem para que o map consiga funcionar com as chaves do tipo Color.
        for (int i = 0; i < height; i++) //ciclo for para percorrer a altura da imagem
        {
            for (int j = 0; j < width; j++)//ciclo for para percorrer a largura da imagem
            {
                Color color = image->at(j, i); //a variavel color assume a cor do pixel atual da imagem 
                if (mapa.find(color) == mapa.end()) //se a cor atual n�o se encontrar no mapa
                {
                    mapa.insert({color, simbolo1}); // adiciona-se a cor ao mapa e assume-se um simbolo a essa cor (a cor � a key e o simbolo � o objeto)
                    alist[simbolo1 - '!'] = color; //no indice do simbolo atual (primeiro simbolo indice 0, segundo simbolo indice 1...) associar uma cor unica a esse simbolo
                    simbolo1++; //incrementar o simbolo (mudar o simbolo para que a proxima cor tenha um simbolo novo)
                }
            }
        }

        output << "! XPM2" << std::endl; // header
        output << width << " " << height << " " << mapa.size() << " " //segunda linha do ficheiro que contem as caracteristicas do ficheiro: largura, altura, numero de cores (que � o tamanho do mapa) e o n�mero de caracteres por cor, que � um por defini��o
               << "1"
               << "\n";

        for (char car = '!'; car < simbolo1; car++) //para cada cor (que � desde o simbolo inicial('!') at� ao simbolo atual) escreve-se uma linha com o simbolo e a respetiva cor
        {
            Color color = alist[car - '!']; //associa uma cor dependendo do simbolo selecionado
            output << car << " c #" //d� output do simbolo e de seguida a respetiva cor em hexadecimal
                << std::hex << std::uppercase 
                << std::setw(2) << std::setfill('0')
                << (int) color.red() 
                << std::setw(2) << std::setfill('0')
                << (int) color.green() 
                << std::setw(2) << std::setfill('0')
                << (int) color.blue() 
                << std::endl;   } //converte as diferentes cores para hexadecimal, preechendo os espa�os caso o valor tenha zeros � esquerda


        for (int i = 0; i < height; i++) //ciclo for para percorrer a altura da imagem
        {
            for (int j = 0; j < width; j++)//ciclo for para percorrer a largura da imagem
            {
                Color color = image->at(j, i); //a variavel color assume a cor do pixel atual da imagem 
                output << mapa.at(color); //escreve o simbolo que est� associado � chave (cada simbolo est� associado a apenas uma cor)
            }
            output << "\n";// faz um paragrafo novo a cada fim de cada linha
        }

        output.close(); //fecha a escrita do ficheiro
    }
}

