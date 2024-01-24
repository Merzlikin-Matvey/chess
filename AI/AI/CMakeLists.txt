# CMakeList.txt : CMake project for AI, include source and define
# project specific logic here.
#

# Add source to this project's executable.

add_executable (AI "AI.cpp" "AI.h" "mnist.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AI PROPERTY CXX_STANDARD 20)
endif()

include(FetchContent)
FetchContent_Declare(mlpack                           
  GIT_REPOSITORY https://github.com/mlpack/mlpack.git 
  GIT_TAG        master                            
 )

FetchContent_MakeAvailable(mlpack)

FetchContent_Declare(armadillo                           
  GIT_REPOSITORY https://gitlab.com/conradsnicta/armadillo-code.git
  GIT_TAG        9.800.x  # Укажите версию Armadillo
)
FetchContent_MakeAvailable(armadillo)

# Интеграция Armadillo с проектом
add_dependencies(AI armadillo)

# Добавьте следующие строки для поиска Armadillo
find_package(Armadillo 9.800 REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

target_link_libraries(AI PRIVATE ${ARMADILLO_LIBRARIES})


