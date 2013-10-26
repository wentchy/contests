#include <cstdio>
#include <cstring>
#include <algorithm>

const int dp_size = 100;

int dp[dp_size + 1][dp_size + 1];

int edit_dist(const char* src, const char* dst)
{
    int srclen = std::strlen(src);
    int dstlen = std::strlen(dst);
    for (int i = 1; i < srclen + 1; ++i)
    {
        for (int j = 1; j < dstlen + 1; ++j)
        {
            int dist = dp[i - 1][j - 1];
            if (src[i - 1] != dst[j - 1])
            {
                dist += 2;
            }
            dist = std::min(dist, dp[i - 1][j] + 1);
            dist = std::min(dist, dp[i][j - 1] + 1);
            dp[i][j] = dist;
        }
    }
    return dp[srclen][dstlen];
}

void init_dp()
{
    std::memset(dp, 0, sizeof(dp));
    for (int i = 0; i < dp_size + 1; ++i)
    {
        dp[i][0] = i;
        dp[0][i] = i;
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

