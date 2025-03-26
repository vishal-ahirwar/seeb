#ifndef SETTING_HPP
#define SETTING_HPP

// Include necessary headers
#include "json.hpp"            // JSON handling library (nlohmann/json)
#include <vector>              // For using std::vector
#include <filesystem>          // For filesystem operations (std::filesystem)
#include <algorithm>           // For using algorithms like std::find, etc.
#include <string>              // For std::string
#include <map>                 // For std::map if needed
#include <fstream>             // For file input/output operations
#include <iostream>            // For standard input/output

namespace fs = std::filesystem; // Define filesystem alias for convenience

namespace System
{
    // ProjectSetting class to hold the configuration for each project
    class ProjectSetting
    {
    public:
        // Data members to store project-specific information
        std::string compiler{};             // Compiler used for the project (e.g., clang++)
        std::string name{};                 // Name of the project
        std::vector<std::string> include_dirs{};  // Include directories for the project
        std::vector<std::string> libs_dirs{};     // Library directories for the project
        std::vector<std::string> libs{};         // Libraries used in the project

    private:
        // Static constants for configuration file names and keys
        static constexpr const char *CONFIG_FILE_NAME{"see-config.json"};  // Config file name
        static constexpr const char *NAME{"yourprojectname"};  // Key for project name in the JSON
        static constexpr const char *INCLUDE{"include"};  // Key for include directories in the JSON
        static constexpr const char *LIBS_DIR{"libsDir"};  // Key for library directories in the JSON
        static constexpr const char *LIBS{"libs"};  // Key for libraries in the JSON
        static constexpr const char *COMPILER{"compiler"};  // Key for compiler in the JSON

        // Friend functions that have access to private members of ProjectSetting class
        friend bool readConfigFile(std::vector<ProjectSetting> &); // For reading the config file
        friend bool generateConfigTemplate();  // For generating a config template if none exists
    };

    // Function to read the configuration file and populate the settings vector
    bool readConfigFile(std::vector<ProjectSetting> &settings)
    {
        nlohmann::json data{};  // JSON data container to hold the parsed config data
        std::ifstream in{ProjectSetting::CONFIG_FILE_NAME};  // Open config file
        if (!in.is_open())  // If file cannot be opened, return false
            return false;

        in >> data;  // Parse the JSON data from the file

        // Loop through each project entry in the JSON file
        for (const auto &[name, project_data] : data.items())
        {
            ProjectSetting temp_setting{};  // Temporary ProjectSetting to populate

            // Set project name
            temp_setting.name = name;

            // If the project doesn't contain the "libs" key, skip it
            if (!project_data.contains(ProjectSetting::LIBS))
                continue;

            // Assign libs from the JSON data
            temp_setting.libs = project_data[ProjectSetting::LIBS];

            // If the project doesn't contain the "libsDir" key, skip it
            if (!project_data.contains(ProjectSetting::LIBS_DIR))
                continue;

            // Assign libs_dir from the JSON data
            temp_setting.libs_dirs = project_data[ProjectSetting::LIBS_DIR];

            // If the project doesn't contain the "include" key, skip it
            if (!project_data.contains(ProjectSetting::INCLUDE))
                continue;

            // Assign include_dirs from the JSON data
            temp_setting.include_dirs = project_data[ProjectSetting::INCLUDE];

            // If the project doesn't contain the "compiler" key, skip it
            if (!project_data.contains(ProjectSetting::COMPILER))
                continue;

            // Assign compiler from the JSON data
            temp_setting.compiler = project_data[ProjectSetting::COMPILER];

            // Add the populated ProjectSetting to the settings vector
            settings.push_back(temp_setting);
        };

        in.close();  // Close the file after reading
        return true;  // Return true if the config file was read successfully
    };

    // Function to generate a configuration template if none exists
    bool generateConfigTemplate()
    {
        nlohmann::json data{};  // JSON data container for the template

        // Check if the config file already exists
        if (fs::exists(ProjectSetting::CONFIG_FILE_NAME))
        {
            std::cout << "config.json already exist!" << '\n';  // If it exists, notify the user
            return false;
        }

        std::ofstream out{ProjectSetting::CONFIG_FILE_NAME};  // Create or open the config file for writing
        if (!out.is_open())  // If file cannot be opened, return false
            return false;

        // Populate the template with empty lists and a default compiler
        data[ProjectSetting::NAME][ProjectSetting::INCLUDE] = std::vector<std::string>();
        data[ProjectSetting::NAME][ProjectSetting::LIBS_DIR] = std::vector<std::string>();
        data[ProjectSetting::NAME][ProjectSetting::LIBS] = std::vector<std::string>();
        data[ProjectSetting::NAME][ProjectSetting::COMPILER] = "clang++";  // Default compiler is clang++

        // Write the JSON data to the file
        out << data.dump();  // Dump the JSON data to the file
        out.close();  // Close the file after writing

        return true;  // Return true if the template was successfully generated
    }

    // Function to print out the project settings
    void printProjectSetting(const std::vector<System::ProjectSetting> &settings)
    {
        // Loop through each project setting in the vector
        for (const auto &setting : settings)
        {
            // Print out the details for each project
            std::cout << "Project name : " << setting.name << std::endl;
            std::cout << "Compiler : " << setting.compiler;
            std::cout << "\ninclude dirs : ";
            for (const auto &path : setting.include_dirs)  // Print include directories
                std::cout << path << " ";
            std::cout << "\nlibs : ";
            for (const auto &path : setting.libs)  // Print libraries
                std::cout << path << " ";
            std::cout << "\nlibs dir : ";
            for (const auto &path : setting.libs_dirs)  // Print library directories
                std::cout << path << " ";
            std::cout << std::endl << std::endl;  // Add extra space between projects
        }
    }

    // Typedef for a vector of ProjectSetting objects (Settings type alias)
    typedef std::vector<System::ProjectSetting> Settings;
}

#endif  // End of setting.hpp
