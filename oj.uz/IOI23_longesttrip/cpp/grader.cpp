#include "longesttrip.cpp"

#include <cassert>
#include <cstdio>
#include <string>
#include <vector>

static inline constexpr int maxNumberOfCalls = 32640;
static inline constexpr int maxTotalNumberOfCalls = 150000;
static inline constexpr int maxTotalNumberOfLandmarksInCalls = 1500000;
static int call_counter = 0;
static int total_call_counter = 0;
static int landmark_counter = 0;

static int C, N, D;
static std::vector<std::vector<int>> U;
static std::vector<bool> present;

static inline void protocol_violation(std::string message)
{
    printf("Protocol Violation: %s\n", message.c_str());
    exit(0);
}

bool are_connected(std::vector<int> A, std::vector<int> B)
{
    ++call_counter;
    ++total_call_counter;
    if (call_counter > maxNumberOfCalls || total_call_counter > maxTotalNumberOfCalls)
    {
        protocol_violation("too many calls");
    }

    int nA = A.size(), nB = B.size();
    landmark_counter += nA + nB;
    if (landmark_counter > maxTotalNumberOfLandmarksInCalls)
    {
        protocol_violation("too many elements");
    }

    if (nA == 0 || nB == 0)
    {
        protocol_violation("invalid array");
    }
    for (int i = 0; i < nA; ++i)
    {
        if (A[i] < 0 || N <= A[i])
        {
            protocol_violation("invalid array");
        }
        if (present[A[i]])
        {
            protocol_violation("invalid array");
        }
        present[A[i]] = true;
    }
    for (int i = 0; i < nA; ++i)
    {
        present[A[i]] = false;
    }
    for (int i = 0; i < nB; ++i)
    {
        if (B[i] < 0 || N <= B[i])
        {
            protocol_violation("invalid array");
        }
        if (present[B[i]])
        {
            protocol_violation("invalid array");
        }
        present[B[i]] = true;
    }
    for (int i = 0; i < nB; ++i)
    {
        present[B[i]] = false;
    }

    for (int i = 0; i < nA; ++i)
    {
        for (int j = 0; j < nB; ++j)
        {
            if (A[i] == B[j])
            {
                protocol_violation("non-disjoint arrays");
            }
        }
    }

    for (int i = 0; i < nA; ++i)
    {
        for (int j = 0; j < nB; ++j)
        {
            if (U[std::max(A[i], B[j])][std::min(A[i], B[j])] == 1)
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    assert(1 == scanf("%d", &C));
    int maximumCalls = 0;
    for (int c = 0; c < C; ++c)
    {
        call_counter = 0;
        assert(2 == scanf("%d %d", &N, &D));

        present.assign(N, false);
        U.resize(N);
        for (int i = 1; i < N; ++i)
        {
            U[i].resize(i);
            for (int j = 0; j < i; ++j)
            {
                assert(1 == scanf("%d", &U[i][j]));
            }
        }

        for (int i = 2; i < N; ++i)
        {
            for (int j = 1; j < i; ++j)
            {
                for (int k = 0; k < j; ++k)
                {
                    if (U[i][j] + U[i][k] + U[j][k] < D)
                    {
                        printf("Insufficient Density\n");
                        exit(0);
                    }
                }
            }
        }

        std::vector<int> t = longest_trip(N, D);
        int l = t.size();
        printf("%d\n", l);
        for (int i = 0; i < l; ++i)
        {
            printf(i == 0 ? "%d" : " %d", t[i]);
        }
        printf("\n");
        printf("%d\n", call_counter);

        maximumCalls = std::max(maximumCalls, call_counter);
        call_counter = 0;
    }
    printf("%d\n", maximumCalls);

    return 0;
}
