
// Auto Genrated C++ file by aura CLI
// None
// Test Code
#include <seebconfig.h>
#include <setting.hpp>
#include<time.h>
#include<chrono>
#include<thread>
using namespace std::chrono_literals;
#ifdef WIN32
std::string extention{".exe"};
#else
std::string extention{".x64"};
#endif
int main(int argc, char *argv[])
{
    System::Settings settings{};
    
    if (System::readConfigFile(settings)){
        for(const auto&setting:settings)
        {
            std::cout<<"Building "<<setting.name<<" ...\n";
            auto cmd=setting.compiler+" "+setting.name+"/src/main.cxx"+" -o "+setting.name+extention;
            std::cerr<<"Executing "<<cmd<<std::endl;
            std::system(cmd.c_str());
            std::cout<<"Done\n";
        }
    }
    else{
        std::cerr << "FAILED\n";
        System::generateConfigTemplate();
    }
    return 0;
};
