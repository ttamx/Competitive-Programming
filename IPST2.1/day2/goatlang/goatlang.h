#include <tuple>
#include <vector>

std::tuple<std::vector<std::vector<int>>, int, int> example1();
std::tuple<std::vector<std::vector<int>>, int, int> example2();

std::tuple<std::vector<std::vector<int>>, int, int>
task1(std::vector<std::vector<int>> A, int r, int c);
std::tuple<std::vector<std::vector<int>>, int, int>
task2(std::vector<std::vector<int>> H, int a, int b);
std::tuple<std::vector<std::vector<int>>, int, int> task3(std::vector<int> a);
std::tuple<std::vector<std::vector<int>>, int, int> task4();
std::tuple<std::vector<std::vector<int>>, int, int> task5(std::vector<int> D);
std::tuple<std::vector<std::vector<int>>, int, int> task6(int m);