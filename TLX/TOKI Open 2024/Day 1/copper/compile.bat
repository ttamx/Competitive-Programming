@echo off
SETLOCAL
set problem=copper
set grader_name=grader

g++ -std=c++17 -o "%problem%" "%grader_name%.cpp" "%problem%.cpp" -O2 -lm
ENDLOCAL
