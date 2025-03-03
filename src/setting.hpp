#ifndef SETTING_HPP
#define SETTING_HPP
#include <json.hpp>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
namespace fs = std::filesystem;
namespace System
{
    class ProjectSetting
    {
    public:
        std::string compiler{};
        std::string name{};
        std::vector<std::string> include_dirs{};
        std::vector<std::string> libs_dirs{};
        std::vector<std::string> libs{};

    private:
        static constexpr const char *CONFIG_FILE_NAME{"see-config.json"};
        static constexpr const char *NAME{"yourprojectname"};
        static constexpr const char *INCLUDE{"include"};
        static constexpr const char *LIBS_DIR{"libsDir"};
        static constexpr const char *LIBS{"libs"};
        static constexpr const char *COMPILER{"compiler"};
        friend bool readConfigFile(std::vector<ProjectSetting> &);
        friend bool generateConfigTemplate();
    };
    bool readConfigFile(std::vector<ProjectSetting> &settings)
    {
        nlohmann::json data{};
        std::ifstream in{ProjectSetting::CONFIG_FILE_NAME};
        if (!in.is_open())
            return false;
        in >> data;
        //...
        for (const auto &[name, project_data] : data.items())
        {
            ProjectSetting temp_setting{};
            temp_setting.name = name;
            if (!project_data.contains(ProjectSetting::LIBS))
                continue;
            ;
            ;
            temp_setting.libs = project_data[ProjectSetting::LIBS];
            if (!project_data.contains(ProjectSetting::LIBS_DIR))
                continue;
            ;
            temp_setting.libs_dirs = project_data[ProjectSetting::LIBS_DIR];
            if (!project_data.contains(ProjectSetting::INCLUDE))
                continue;
            temp_setting.include_dirs = project_data[ProjectSetting::INCLUDE];
            if (!project_data.contains(ProjectSetting::COMPILER))
                continue;
            temp_setting.compiler = project_data[ProjectSetting::COMPILER];

            settings.push_back(temp_setting);
        };
        in.close();
        return true;
    };
    bool generateConfigTemplate()
    {
        nlohmann::json data{};
        if (fs::exists(ProjectSetting::CONFIG_FILE_NAME))
        {
            std::cout << "config.json already exist!" << '\n';
            return false;
        }
        std::ofstream out{ProjectSetting::CONFIG_FILE_NAME};
        if (!out.is_open())
            return false;
        //...
        data[ProjectSetting::NAME][ProjectSetting::INCLUDE] = std::vector<std::string>();
        data[ProjectSetting::NAME][ProjectSetting::LIBS_DIR] = std::vector<std::string>();
        data[ProjectSetting::NAME][ProjectSetting::LIBS] = std::vector<std::string>();
        data[ProjectSetting::NAME][ProjectSetting::COMPILER] = "clang++";
        out << data.dump();
        out.close();
        return true;
    }

    void printProjectSetting(const std::vector<System::ProjectSetting> &settings)
    {
        for (const auto &setting : settings)
        {

            std::cout << "Project name : " << setting.name << std::endl;
            std::cout << "Compiler : " << setting.compiler;
            std::cout << "\ninclude dirs : ";
            for (const auto &path : setting.include_dirs)
                std::cout << path << " ";
            std::cout << "\nlibs : ";
            for (const auto &path : setting.libs)
                std::cout << path << " ";
            std::cout << "\nlibs dir : ";
            for (const auto &path : setting.libs_dirs)
                std::cout << path << " ";
            std::cout << std::endl
                      << std::endl;
            ;
        }
    }
    typedef std::vector<System::ProjectSetting> Settings;
}
#endif