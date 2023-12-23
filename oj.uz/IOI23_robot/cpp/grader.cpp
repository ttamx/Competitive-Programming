#include "robot.cpp"
#include <cassert>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

static const int MAX_COLOR = 19;
static const int MAX_STATE = 5153632; // = (MAX_COLOR + 3) ^ 5
static const int MAX_STEPS = 500000;

static std::ofstream output;

[[noreturn]] static void die(const std::string &message)
{
    std::cout << message << "\n";
    output.close();
    exit(0);
}

[[noreturn]] static void pv(const std::string &message)
{
    die("Protocol Violation: " + message);
}

static int encode_state(const std::vector<int> &S)
{
    int state = 0;
    for (int s : S)
    {
        state = (MAX_COLOR + 3) * state + s + 2;
    }
    return state;
}

struct instruction
{
    char color;
    char action;
};

static int encode_instr(instruction instr)
{
    if (!instr.action)
    {
        return 0;
    }
    int index = std::string("HWSENT").find_first_of(instr.action) + 1;
    return (index << 5) | instr.color;
}

static instruction program[MAX_STATE];

void set_instruction(std::vector<int> S, int Z, char A)
{
    if (S.size() != 5)
    {
        pv("Invalid array");
    }
    for (int s : S)
    {
        if (s < -2 || s > MAX_COLOR)
        {
            pv("Invalid array");
        }
    }
    if (Z < 0 || Z > MAX_COLOR)
    {
        pv("Invalid color");
    }
    if (std::string("HWSENT").find_first_of(A) == std::string::npos)
    {
        pv("Invalid action");
    }
    int code = encode_state(S);
    if (program[code].action)
    {
        pv("Same state array");
    }
    program[code].color = Z;
    program[code].action = A;
}

static std::vector<std::vector<int>> cells;
static int H, W;
static int rx = 1, ry = 1;

static bool step(instruction instr)
{
    cells[rx][ry] = instr.color;
    switch (instr.action)
    {
    case 'H':
        break;
    case 'W':
        ry--;
        break;
    case 'S':
        rx++;
        break;
    case 'E':
        ry++;
        break;
    case 'N':
        rx--;
        break;
    case 'T':
        return true;
    }
    if (cells[rx][ry] < 0)
    {
        die("Invalid move");
    }
    return false;
}

int main()
{
    std::string line;
    std::getline(std::cin, line);
    std::istringstream line_ss(line);
    assert((line_ss >> H >> W) && (line_ss >> std::ws).eof());
    cells.resize(H + 2, std::vector<int>(W + 2));
    for (int j = 0; j <= W + 1; j++)
    {
        cells[0][j] = cells[H + 1][j] = -2;
    }
    for (int i = 1; i <= H; i++)
    {
        cells[i][0] = cells[i][W + 1] = -2;
        std::getline(std::cin, line);
        line_ss.str(line);
        line_ss.clear();
        for (int j = 1; j <= W; j++)
        {
            bool cell;
            line_ss >> cell;
            cells[i][j] = cell ? -1 : 0;
        }
        assert(line_ss && (line_ss >> std::ws).eof());
    }
    program_pulibot();
    output.open("robot.bin", std::ios::binary);
    output.put(H).put(W);
    for (int i = 1; i <= H; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            output.put(cells[i][j]);
        }
    }
    bool done = false;
    int steps = 0;
    while (!done && ++steps <= MAX_STEPS)
    {
        std::vector<int> state = {
            cells[rx][ry],
            cells[rx][ry - 1],
            cells[rx + 1][ry],
            cells[rx][ry + 1],
            cells[rx - 1][ry]};
        instruction instr = program[encode_state(state)];
        output.put(encode_instr(instr));
        if (!instr.action)
        {
            die("Unexpected state");
        }
        done = step(instr);
    }
    if (!done)
    {
        output.put(0xE0);
        die("Too many steps");
    }
    for (int i = 1; i <= H; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            std::cout << std::setw(2) << cells[i][j] << (j == W ? "\n" : " ");
        }
    }
}
