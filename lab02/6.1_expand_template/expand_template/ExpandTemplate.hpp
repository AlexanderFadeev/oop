#pragma once

#include <iostream>
#include <map>
#include <string>

using Mapping = std::map<std::string, std::string>;

std::string ExpandTemplate(const std::string& tpl, const Mapping& params);
void ExpandTemplate(std::istream&, std::ostream&, const Mapping& params);
void ExpandTemplate(const std::string& inputFilename, const std::string& outputFilename, const Mapping& params);
