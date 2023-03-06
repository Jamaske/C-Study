#include <iostream>
#include <string>
#include <fstream>

int main(){
    std::ofstream fout;
    fout.open("../tmp.txt");
    if (fout.is_open()){
        std::cout << "file opened successful" << std::endl;
    }

    fout << "template<typename function>\n"
         << "void better_for(int n, function func){\n"
         << "    switch (n) {\n";
    for (long long i = INT16_MIN +2; i <= 0  ; ++i) {
        fout << "        case " <<  i <<  ':' << std::endl;
    }
    std::cout << "mid way" << std::endl;
    fout << "            return;\n"
         <<"        default:\n"
         <<"            func();\n";
    for(long long i = INT16_MAX; i; i--){
        fout << "        case " << i << ':' << std::endl;
        fout << "            func();" <<std::endl;
    }
    fout << "}";
    std::cout << "wright complete" << std::endl;
    fout.close();
    std::cout << "save successful" << std::endl;

}