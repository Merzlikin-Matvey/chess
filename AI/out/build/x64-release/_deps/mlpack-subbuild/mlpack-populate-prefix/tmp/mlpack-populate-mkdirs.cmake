# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/User/source/repos/Merzlikin-Matvey/chess/AI/out/build/x64-release/_deps/mlpack-src"
  "C:/Users/User/source/repos/Merzlikin-Matvey/chess/AI/out/build/x64-release/_deps/mlpack-build"
  "C:/Users/User/source/repos/Merzlikin-Matvey/chess/AI/out/build/x64-release/_deps/mlpack-subbuild/mlpack-populate-prefix"
  "C:/Users/User/source/repos/Merzlikin-Matvey/chess/AI/out/build/x64-release/_deps/mlpack-subbuild/mlpack-populate-prefix/tmp"
  "C:/Users/User/source/repos/Merzlikin-Matvey/chess/AI/out/build/x64-release/_deps/mlpack-subbuild/mlpack-populate-prefix/src/mlpack-populate-stamp"
  "C:/Users/User/source/repos/Merzlikin-Matvey/chess/AI/out/build/x64-release/_deps/mlpack-subbuild/mlpack-populate-prefix/src"
  "C:/Users/User/source/repos/Merzlikin-Matvey/chess/AI/out/build/x64-release/_deps/mlpack-subbuild/mlpack-populate-prefix/src/mlpack-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/User/source/repos/Merzlikin-Matvey/chess/AI/out/build/x64-release/_deps/mlpack-subbuild/mlpack-populate-prefix/src/mlpack-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/User/source/repos/Merzlikin-Matvey/chess/AI/out/build/x64-release/_deps/mlpack-subbuild/mlpack-populate-prefix/src/mlpack-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
