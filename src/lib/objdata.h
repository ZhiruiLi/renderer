#pragma once

#include <string>

#include "model.h"

namespace sren {
bool LoadObjFile(std::string const &path, Model *model);
}  // namespace sren
