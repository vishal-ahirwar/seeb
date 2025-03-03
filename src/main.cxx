
// Auto Genrated C++ file by aura CLI
// None

#include <seebconfig.h>
#include <setting.hpp>
int main(int argc, char *argv[])
{
    System::Settings settings{};
    
    if (System::readConfigFile(settings)){
        System::printProjectSetting(settings);
    }
    else{
        std::cerr << "FAILED\n";
        System::generateConfigTemplate();
    }
    return 0;
};
