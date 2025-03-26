
// Auto Genrated C++ file by aura CLI
// None
// Test Code
#include "setting.hpp"
#include<time.h>
#include<chrono>
#include<thread>
#include<filesystem>
#include<vector>
#include<string>
using namespace std::chrono_literals;
#ifdef _WIN32
std::string extention{".exe"};
#else
std::string extention{".x64"};
#endif
namespace fs=std::filesystem;
int main(int argc, char *argv[])
{
    System::Settings settings{};
    
    if (System::readConfigFile(settings)){
        for(const auto&setting:settings)
        {
            auto cmd=setting.compiler;
            cmd+=" -std=c++20 ";
            std::cout<<"Building "<<setting.name<<" ...\n";
            for(const auto&file:fs::recursive_directory_iterator(fs::path(setting.name))){
                if((!file.is_directory()) && file.path().string().find(".cpp")!=std::string::npos){
                    cmd+=" "+file.path().string();
                };
            };
            cmd+=" -o "+setting.name+extention;
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
