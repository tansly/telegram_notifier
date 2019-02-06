/*
    Copyright (C) 2018 Yağmur Oymak

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "config/config.hpp"
#include <fstream>
#include <iostream>
#include <string>

namespace Config {

/*
 * TODO: Design a proper config file syntax.
 * Right now it is only the API token followed by chat id, seperated by whitespace.
 */
bool parse_config(std::string path)
{
    std::ifstream file {path};
    if (!file.is_open()) {
        std::cerr << "parse_config(): Failed to open file " << path << '\n';
        return false;
    }

    if (!(file >> Config::token)) {
        std::cerr << "parse_config(): Failed to read token\n";
        return false;
    }

    if (!(file >> Config::chat_id)) {
        std::cerr << "parse_config(): Failed to read chat id\n";
        return false;
    }

    return true;
}

}
