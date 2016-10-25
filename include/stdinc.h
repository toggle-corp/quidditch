#pragma once

// STL

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <typeinfo>
#include <algorithm>
#include <utility>
#include <memory>

#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>

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

// Bullet
  #include <BulletDynamics/btBulletDynamicsCommon.h>

// Misc
#include <utils/file_io.h>
#include <utils/Exception.h>
#include <utils/Manager.h>