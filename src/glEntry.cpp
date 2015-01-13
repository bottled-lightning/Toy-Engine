#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>

#include "engine/engineException.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <cstdlib> // get environment variable
#endif

const short int VERSION_MAJOR = 0;
const short int VERSION_MINOR = 1;
const int DEFAULT_NUMTHREAD = 1;

bool handleCommandLineArguments(int argc, char **argv,
                                std::string &config_path,
                                std::string &modules_path);
bool handleConfigurationOptions(const std::string &config_path,
                                std::string &modules_path,
                                boost::program_options::variables_map &vm);

int main(int argc, char **argv) {
    std::string config_path, modules_path;

    // parse command line options, want to eventually end up with a config_path
    if(!handleCommandLineArguments(argc, argv, config_path, modules_path))
        return 1;

    // parse config file, make sure we have a modules_path by now
    boost::program_options::variables_map vm;
    if(!handleConfigurationOptions(config_path, modules_path, vm))
        return 1;

    // import plugins

    return 0;
}

bool handleCommandLineArguments(int argc, char **argv,
                                std::string &config_path,
                                std::string &modules_path)
{

    try {
        namespace po = boost::program_options;

        boost::program_options::variables_map vm;
        po::options_description opts_desc("Command line options");
        opts_desc.add_options()
            ("help,h", "  usage")
            ("version,v", "  current version of Toy Engine")
            (",f", po::value<std::string>(), "  set path to module config file,"
                " will override environment variable TOYENGINE_CFG  if flag is set")
            (",l", po::value<std::string>(), "  set path to module shared lib,"
                " will override entry in config file if flag is set")
        ;

        // parse the arguments and put them into the variable map
        po::store(po::parse_command_line(argc, argv, opts_desc), vm);

        po::notify(vm);
        if(vm.count("help")) {
            std::cout << opts_desc << std::endl;
            return false;
        } else if(vm.count("version")) {
            std::cout << "Toy Engine version "
                      << VERSION_MAJOR << "."
                      << VERSION_MINOR << std::endl;
            return false;
        }

#ifdef _WIN32
        // TODO: Support Unicode (LPSTR supports unicode, c++ char does not)
        char c_style_environment[100];
        GetEnvironmentVariable("TOYENGINE_CFG", c_style_environment, 100);
#else
        char *c_style_environment = std::getenv("TOYENGINE_CFG");
#endif

        // if we got a valid config_path, we are done, otherwise look at environment variables
        if(vm.count("-f"))
            config_path = vm["-f"].as<std::string>();
        else if(c_style_environment != nullptr)
            config_path = c_style_environment;
        else
            throw engineException("Did not find path to config file either with -f "
                                  "or in environment variable TOYENGINE_CFG");

        // modules_path may or may not be defined here
        if(vm.count("-l"))
            modules_path = vm["-l"].as<std::string>();

    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    } catch(...) {
        std::cerr << "Unknown Error" << std::endl;
        return false;
    }

    return true;
}

bool handleConfigurationOptions(const std::string &config_path,
                                std::string &modules_path,
                                boost::program_options::variables_map &vm)
{

    try {

        namespace po = boost::program_options;

        std::ifstream config_file(config_path.c_str());
        if(!config_file)
            throw engineException("Did not specify good configuration file path");

        po::options_description desc("Configuration file options");
        desc.add_options()
            ("engine.num_threads", po::value<int>(), "number of threads to run" )
            ("engine.modules_path", po::value<std::string>(), "path to modules shared library")
            ("log.log_lvl", po::value<std::string>(), "output file filters messages below this")
            ("log_output", po::value<std::string>(), "output file path")
        ;

        po::store(
            po::parse_config_file(
                config_file,
                desc,
                true // allow_unregistered
            ),
            vm
        );

        po::notify(vm);

        if(modules_path == "" && vm.count("engine.modules_path") == 0)
            throw engineException("Did not specify path to modules shared library "
                                  "either with -l or in the config file as modules_path");
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}
