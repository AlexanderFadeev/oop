#pragma once

#include <iostream>
#include <map>
#include <string>

using Mapping = std::map<std::string, std::string>;

std::string ExpandTemplate(const std::string& tpl, const Mapping& params);
