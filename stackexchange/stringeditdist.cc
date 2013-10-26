#include <cstdio>
#include <cstring>
#include <algorithm>

const int dp_size = 100;

//int dp[dp_size + 1][dp_size + 1];
int dp1[dp_size + 1];
int dp2[dp_size + 1];

int edit_dist(const char* src, const char* dst)
{
    int srclen = std::strlen(src);
    int dstlen = std::strlen(dst);
    int* last_dp = dp1;
    int* current_dp = dp2;
    for (int i = 1; i < srclen + 1; ++i)
    {
        current_dp[0] = i;
        for (int j = 1; j < dstlen + 1; ++j)
        {
            int dist = last_dp[j - 1];
            if (src[i - 1] != dst[j - 1])
            {
                dist += 2;
            }
            dist = std::min(dist, last_dp[j] + 1);
            dist = std::min(dist, current_dp[j - 1] + 1);
            current_dp[j] = dist;
        }
        std::swap(last_dp, current_dp);
    }
    return last_dp[dstlen];
}

void init_dp()
{
    std::memset(dp1, 0, sizeof(dp1));
    std::memset(dp2, 0, sizeof(dp2));
    for (int i = 0; i < dp_size + 1; ++i)
    {
        dp1[i] = i;
    }

}

int main(int argc, char* argv[])
{
    char src[dp_size];
    char dst[dp_size];

    int re = std::scanf("%s %s", src, dst);

    init_dp();
    std::printf("%d\n", edit_dist(src, dst));
    return 0;
}

