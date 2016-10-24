#pragma once

// STL

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <functional>
#include <typeinfo>
#include <algorithm>
#include <utility>

// GLEW

#define GLEW_STATIC
#include <GL/glew.h>

// GLM

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

// Misc
#include <utils.h>
#include <Exception.h>