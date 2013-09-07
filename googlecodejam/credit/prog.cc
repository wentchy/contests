#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>

//int A[1010][2010];
//
//void solve_pack_dp(int C, int I, const int* p)
//{
//
//    for (int cc = 0; cc <= C; ++cc)
//    {
//        A[cc][0] = 0;
//        for (int j = 1; j <= I; ++j)
//        {
//            int pj = p[j - 1];
//            if (pj > cc)
//            {
//                A[cc][j] = A[cc][j - 1];
//            }
//            else
//            {
//                A[cc][j] = std::max(A[cc][j - 1], A[cc - pj][j - 1] + pj);
//            }
//            std::printf("A[%d][%d] = %d, A[cc][j - 1] = %d, A[cc - pj][j - 1] = %d, pj = %d\n", 
//                    cc, j, A[cc][j], A[cc][j - 1], pj <= cc ? A[cc - pj][j - 1] : -1, pj);
//        }
//    }
//    std::printf("%d\n", A[C][I]);
//}

void solve_pack_sort(int C, int I, int* p)
{
    std::vector<std::pair<int, int> > p_idx(I);
    //std::printf("C = %d\n", C);
    //std::printf("I = %d\n", I);
    for (int j = 0; j < I; ++j)
    {
        p_idx[j].first = p[j];
        p_idx[j].second = j;
    }
    std::sort(p_idx.begin(), p_idx.end());
    for (int j = 0; j < I; ++j)
    {
        p[j] = p_idx[j].first;
    }
    //int high_bound = std::lower_bound(p, p + I, C) - 1 - p;
    int high_idx = std::lower_bound(p, p + I, C) - 1 - p;

    int center = std::upper_bound(p, p + high_idx, (p[high_idx] >> 1)) - 1 - p;
    int opt_h_idx = -1;
    int opt_l_idx = -1;
    int opt_credit = -1;
    for (;high_idx > center; -- high_idx)
    {
        int high_price = p[high_idx];
        int low_price = C - p[high_idx];
        int low_idx = std::upper_bound(p, p + high_idx, low_price) - 1 - p;
        if (low_idx < 0)
        {
            continue;
        }

        int current_credit = p[high_idx] + p[low_idx];
        if (current_credit == C)
        {
            opt_h_idx = high_idx;
            opt_l_idx = low_idx;
            break;
        }
        if (current_credit > opt_credit)
        {
            opt_h_idx = high_idx;
            opt_l_idx = low_idx;
            opt_credit = current_credit;
        }
    }
    if (opt_h_idx < 0 || opt_l_idx < 0 || opt_h_idx < opt_l_idx)
    {
        std::fprintf(stderr, "ERROR...\n");
    }

    opt_l_idx = p_idx[opt_l_idx].second;
    opt_h_idx = p_idx[opt_h_idx].second;
    if (opt_l_idx > opt_h_idx)
    {
        std::swap(opt_l_idx, opt_h_idx);
    }
    std::printf("%d %d\n", opt_l_idx + 1, opt_h_idx + 1);
}

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
        }
        std::printf("Case #%d: ", Cas);
        solve_pack_sort(C, I, &p[0]);
        ++ Cas;
    }
    return 0;
}

