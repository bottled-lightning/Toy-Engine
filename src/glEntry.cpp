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

namespace po = boost::program_options;

// engine defaults
const short int VERSION_MAJOR = 0;
const short int VERSION_MINOR = 1;
const int DEFAULT_NUMTHREAD = 1;

bool handleCommandLineArguments(int argc, char **argv,
                                const po::options_description &command_desc,
                                const po::options_description &config_desc,
                                po::variables_map &values);
bool handleConfigurationOptions(const po::options_description &config_desc,
                                po::variables_map &values);

int main(int argc, char **argv) {

    // the values we get from config file and command line
    po::variables_map values;

    po::options_description command_desc("Command line options");
    command_desc.add_options()
        ("help,h", "  usage")
        ("version,v", "  current version of Toy Engine")
        ("verbose", "  output log to console")
        ("no_log", "  do not log to file")
        (",f", po::value<std::string>(), "  set path to module config file,"
            " will override environment variable TOYENGINE_CFG if flag is set")
        (",l", po::value<std::string>(), "  set path to module shared lib,"
            " will override entry in config file if flag is set")
    ;

    po::options_description config_desc("Engine configuration file options");
    config_desc.add_options()
        ("engine.num_threads", po::value<int>(), "  number of threads to run" )
        ("engine.modules_path", po::value<std::string>(),
            "  path to modules shared library. Can be overriden by the -f flag")
        ("engine.log.log_lvl", po::value<std::string>(), 
            "  output file filters messages below this")
        ("engine.log.log_output", po::value<std::string>(), "  output file path")
    ;

    // parse command line options, want to eventually end up with a config_path
    if(handleCommandLineArguments(argc, argv, command_desc, config_desc, values) == false)
        return 1;

    // parse config file, guaranteed to have a modules_path by now
    if(handleConfigurationOptions(config_desc, values) == false)
        return 1;

    std::cout << "Found configuration file: " << values["-f"].as<std::string>() << std::endl
              << "Found modules shared lib: " << values["-l"].as<std::string>() << std::endl;

    // import plugins, now we have enough information

    return 0;
}

bool handleCommandLineArguments(int argc, char **argv,
                                const po::options_description &command_desc,
                                const po::options_description &config_desc,
                                po::variables_map &values)
{

    try {

        // parse the arguments and put them into the variable map
        po::store(po::parse_command_line(argc, argv, command_desc), values);
        po::notify(values);

        if(values.count("help")) {
            std::cout << command_desc
                      << config_desc << std::endl;
            return false;
        } else if(values.count("version")) {
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

        // command line takes precedence
        if(!values.count("-f")) {
            if(c_style_environment != nullptr)
                values.insert(
                    std::make_pair(
                        "-f",
                        po::variable_value(std::string(c_style_environment), false)
                    )
                );
            else
                throw engineException("Did not find path to config file either with -f "
                                      "or in environment variable TOYENGINE_CFG");
        }

        // invariant: values["-f"] has to have a value by now
        assert(values.count("-f"));

    } catch(std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    return true;

}

bool handleConfigurationOptions(const po::options_description &config_desc,
                                po::variables_map &values)
{
    try {

        std::ifstream config_file(values["-f"].as<std::string>().c_str());
        if(!config_file)
            throw engineException("Did not specify good configuration file path");

        po::store(po::parse_config_file(config_file, config_desc, true), values);
        po::notify(values);

        // command line takes precedence
        if(values.count("-l") == 0) {
            if(values.count("engine.modules_path") != 0) {
                // transfer the value to values["-f"] so we can easily access the value later
                values.insert(
                    std::make_pair(
                        "-l",
                        po::variable_value(
                            values["engine.modules_path"].as<std::string>(), 
                            false // defaulted value
                        )
                    )
                );
                values.erase("engine.modules_path");
            } else
                throw engineException("Did not specify path to modules shared library "
                                      "either with -l or in the config file as modules_path");
        }

        // invariant: values["-l"] has to have a value by now
        assert(values.count("-l"));

    } catch(std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    return true;
}
