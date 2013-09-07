#include <cstdio>

int main(int argc, char* argv[])
{
    int N = -1;
    std::scanf("%d", &N);
    int Cas = 1;
    std::vector<int> p;
    while (Cas <= N)
    {
        int C = -1;
        std::scanf("%d", &C);
        int I = -1;
        std::scanf("%d", &I);
        p.clear();
        p.reserve(I);
        for (int i = 0; i < I; ++i)
        {
            int pi;
            std::scanf("%d", &pi);
            p.push_back(pi);
            solve_pack(C, I, P);
        }
        ++ Cas;
    }
    return 0;
}

