
#include <cstdio>
#include <cstring>
#include <algorithm>

const int dp_size = 100;

bool dp[dp_size + 1][dp_size + 1];

int path[dp_size + 1][dp_size + 1];

bool judge_shuffle(const char* X, const char* Y, const char* Z)
{
    int Xlen = std::strlen(X);
    int Ylen = std::strlen(Y);
    int Zlen = std::strlen(Z);
    if (Zlen != Xlen + Ylen)
    {
        return false;
    }
    for (int i = 0; i < Xlen + 1; ++i)
    {
        for (int j = 0; j < Ylen + 1; ++j)
        {
            bool up = (i == 0) || dp[i - 1][j];
            bool left = (j == 0) || dp[i][j - 1];
            if (i == 0 && j == 0)
            {
                dp[i][j] = true;
            }
            else 
            {
                if (i == 0)
                {
                    dp[i][j] = dp[i][j - 1] && (Z[j - 1] == Y[j - 1]);
                }
                else if (j == 0)
                {
                    dp[i][j] = dp[i - 1][j] && (Z[i - 1] == X[i - 1]);
                }
                else
                {
                    dp[i][j] = (dp[i][j - 1] && Z[i + j - 1] == Y[j - 1]) ||
                                (dp[i - 1][j] && Z[i + j - 1 == X[i - 1]]);
                }
            }
            std::printf("%d ", dp[i][j]);
        }
        std::printf("\n");
    }
    return dp[Xlen][Ylen];
}

void init_dp()
{
    std::memset(dp, 0, sizeof(dp));
    std::memset(path, 0, sizeof(path));
}


int main(int argc, char* argv[])
{
    char X[dp_size + 2];
    char Y[dp_size + 2];
    char Z[2 * (dp_size + 2)];

    int re = std::scanf("%s %s %s", X, Y, Z);

    std::printf("%s\n%s\n%s\n", X, Y, Z);
    init_dp();
    std::printf("%d\n", judge_shuffle(X, Y, Z));
    return 0;
}

