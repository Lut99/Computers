/* CHAOS MAKE.cpp
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 11:37:07 AM
 * Last edited:
 *   3/1/2020, 12:53:45 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The chaos_make is the entry function for the Assembly compiler of the
 *   Chaos Instruction set. It makes use of flex and bison to parse the
 *   file. Which version or edition of Chaos to make can be specified on
 *   the command line.
**/

#include <iostream>
#include <fstream>
#include <string>

#include "lib/include/Version.hpp"
#include "parser/output/AssemblyParser.tab.h"
#include "lib/include/cxxopts.hpp"

using namespace cxxopts;
using namespace std;
using namespace Tools;


extern "C" FILE* yyin;

int main(int argc, char** argv) {
    // Init the option variables
    string edition, input, output;
    bool verbose;
    Version version(0, 0, 0);

    // Parse the options
    Options arguments("chaos_make", "Compiles Chaos Assembly to the binary equivalent for a Chaos Instruction Set.");
    arguments.add_options()
        ("E,edition", "The string identifier of the Chaos edition that needs to be compiled. Default is the general purpose desktop branch.", value<string>())
        ("V,version", "The string identifier of the Chaos version of the selected edition that needs to be compiled. Default is the most recent.", value<Version>())
        ("i,input", "The name of the input file.", value<string>())
        ("o,output", "The name of the output file.", value<string>())
        ("v,verbose", "If given, prints debug texts.")
        ;
    arguments.parse_positional("input");

    auto result = arguments.parse(argc, argv);
    
    // Parse the edition and version
    try {
        edition = result["edition"].as<string>();
    } catch (domain_error& opt) {
        edition = "main";
    } catch (OptionParseException& opt) {
        cerr << "Could not parse edition: " << opt.what() << endl;
        exit(-1);
    }
    try {
        version = result["version"].as<Version>();
    } catch (domain_error& opt) {
        version = Version(1, 0, 0);
    } catch (OptionParseException& opt) {
        cerr << "Could not parse version: " << opt.what() << endl;
        exit(-1);
    }

    // Parse the input and the output
    try {
        input = result["input"].as<string>();
    } catch (OptionParseException& opt) {
        cerr << "Could not parse input: " << opt.what() << endl;
        exit(-1);
    }
    try {
        output = result["output"].as<string>();
    } catch (domain_error& opt) {
        output = "output.cex";
    } catch (OptionParseException& opt) {
        cerr << "Could not parse output: " << opt.what() << endl;
        exit(-1);
    }

    // Check verbosity
    verbose = result.count("verbose") > 0;

    // Open the input file
    yyin = fopen(input.c_str(), "r");
    // Run the parser
    yyparse();
    // Close the input again
    fclose(yyin);

    return 0;
}