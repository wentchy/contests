#include <cstdio>
#include <algorithm>
#include <vector>

int main(int argc, char* argv[])
{
    int test;
    std::scanf("%d", &test);
    std::vector<long long> veca;
    std::vector<long long> vecb;
    int tst_cnt = 0;
    while(tst_cnt < test)
    {
        int len;
        std::scanf("%d", &len);
        veca.clear();
        vecb.clear();
        veca.reserve(len);
        vecb.reserve(len);
        for (int i = 0; i < len; ++i)
        {
            long long val;
            std::scanf("%lld", &val);
            veca.push_back(val);
        }
        for (int i = 0; i < len; ++i)
        {
            long long val;
            std::scanf("%lld", &val);
            vecb.push_back(val);
        }

        std::sort(veca.begin(), veca.end());
        std::sort(vecb.begin(), vecb.end());
        std::reverse(vecb.begin(), vecb.end());
        long long res = 0;
        for (int i = 0; i < len; ++i)
        {
            res += veca[i] * vecb[i];
        }
        std::printf("Case #%d: %lld\n", tst_cnt + 1, res);
        ++ tst_cnt;
    }
    return 0;
}
