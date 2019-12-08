/* CONFIG_PARSER.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  A file that parses a config file and puts them in a map. Then, another class
*  can easily read this map to obtain the required results.
**/

#include "ConfigParser.h"

#include <iostream>
#include <sstream>
#include <limits>

using namespace std;
using namespace Parser;

ConfigParser::ConfigParser(std::string path)
    :err_int(numeric_limits<int>::min()),
    err_float(numeric_limits<float>::min())
{
    // Try to open an fstream
    this->file.open(path);
    if (!this->file.is_open()) {
        throw runtime_error("Could not open file at \"" + path + "\"");
    }

    // We opened it, yay
    this->handle_open = true;
    this->is_multiline_comment = false;
}
ConfigParser::~ConfigParser() {
    this->close();
}

void ConfigParser::parse_all() {
    // Simply run parse_next until it returns an empty string
    while (!this->parse_next().empty()) {
        // Nothing, as the parsing is handled above
    }
}
string ConfigParser::parse_next() {
    // Get the next line
    string line;
    string key;
    string val;
    stringstream buffer;

    while (true) {
        // Quit if nothing to be done anymore
        if (!getline(this->file, line)) {
            return "";
        }
        // Loop and try to parse
        bool set_key = false;
        bool is_comment = false;
        for (int i = 0; i < line.length(); i++) {
            char c = line[i];
            if (this->is_multiline_comment) {
                // Check for end of comment, ignore the rest
                if (i > 0 && line[i - 1] == '*' && c == '/') {
                    // Disable the multiline_comment
                    this->is_multiline_comment = false;
                }
            } else if (i > 0 && line[i - 1] == '/' && c == '*') {
                // A new comment begins
                this->is_multiline_comment = true;
            } else if (i > 0 && line[i - 1] == '/' && c == '/') {
                // A single-line comment begins
                break;    
            } else if (c == '=' && !set_key) {
                // Split the data
                key = buffer.str();
                buffer.str("");
                buffer.clear();
                set_key = true;
            } else if (c != '\n' && (i == line.length() - 1 || c != '/'  || (line[i + 1] != '/' && line[i + 1] != '*'))) {
                // Add it to the buffer
                buffer << c;
            }
        }
        // Set the value to the buffer
        if (!set_key) {
            key = buffer.str();
        } else {
            val = buffer.str();
        }
        buffer.str("");
        buffer.clear();
        // Stop if the buffers are non-empty
        if (!key.empty() && !val.empty()) {
            break;
        }
    }
    // Set the value in the map
    this->config[key] = val;
    // Return the key
    return key;
}

bool ConfigParser::contains(std::string key) {
    return this->config.count(key) == 1;
}
template<> string ConfigParser::get<string>(std::string key) {
    // Check if the key exists
    if (!this->contains(key)) {
        throw runtime_error("Key \"" + key + "\" does not exist in the config so far");
    }

    // Easy. Now return the value
    return this->config[key];
}
template<> int ConfigParser::get<int>(std::string key) {
    // Check if the key exists
    if (!this->contains(key)) {
        throw runtime_error("Key \"" + key + "\" does not exist in the config so far");
    }

    // Try to convert the string to an int
    try {
        return stoi(this->config[key]);
    } catch (std::invalid_argument e) {
        return this->err_int;
    }
}
template<> float ConfigParser::get<float>(std::string key) {
    // Check if the key exists
    if (!this->contains(key)) {
        throw runtime_error("Key \"" + key + "\" does not exist in the config so far");
    }

    // Try to convert the string to a float
    try {
        return stof(this->config[key]);
    } catch (std::invalid_argument e) {
        return this->err_float;
    }
}

void ConfigParser::close() {
    if (this->handle_open) {
        this->file.close();
        this->handle_open = false;
    }
}

string ConfigParser::to_string() {
    stringstream sstr;
    sstr << "{";
    bool skipped_comma = false;
    for (auto const& [key, val] : this->config) {
        if (!skipped_comma) {
            skipped_comma = true;
        } else {
            sstr << ", ";
        }
        sstr << "'" << key << "': '" << val << "'";
    }
    sstr << "}";
    return sstr.str();
}