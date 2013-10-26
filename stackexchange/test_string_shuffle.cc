
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

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
                    path[i][j] = 2;
                }
                else if (j == 0)
                {
                    dp[i][j] = dp[i - 1][j] && (Z[i - 1] == X[i - 1]);
                    path[i][j] = 1;
                }
                else
                {
                    dp[i][j] = (dp[i][j - 1] && Z[i + j - 1] == Y[j - 1]) ||
                                (dp[i - 1][j] && Z[i + j - 1 == X[i - 1]]);
                    if (dp[i][j])
                    {
                        if (Z[i + j - 1] == Y[j - 1])
                        {
                            path[i][j] = 2;
                        }
                        else
                        {
                            path[i][j] = 1;
                        }
                    }
                }
            }
            //std::printf("%d ", dp[i][j]);
            //std::printf("%d ", path[i][j]);
        }
        //std::printf("\n");
    }
    return dp[Xlen][Ylen];
}

void init_dp()
{
    std::memset(dp, 0, sizeof(dp));
    std::memset(path, 0, sizeof(path));
}

void rec_path(const char* X, const char* Y, const char* Z)
{
    int i = std::strlen(X);
    int j = std::strlen(Y);
    int Zlen = std::strlen(Z);
    int pz = Zlen;

    int path_stack[2*(dp_size + 2)];

    while(pz > 0)
    {
        int p = path[i][j];
        if (p == 1)
        {
            -- i;
        }
        else if (p == 2)
        {
            -- j;
        }
        else
        {
            std::printf("Err1\n");
            std::exit(-1);
        }
        -- pz;
        path_stack[pz] = (p);
    }

    const char* px = X;
    for (int i = 0; i < Zlen; ++i)
    {
        std::printf("%c", path_stack[i] == 1 ? *px++ : ' ' );
    }
    std::printf("\n");
    const char* py = Y;
    for (int i = 0; i < Zlen; ++i)
    {
        std::printf("%c", path_stack[i] == 2 ? *py++ : ' ' );
    }
    std::printf("\n");
}

int main(int argc, char* argv[])
{
    char X[dp_size + 2];
    char Y[dp_size + 2];
    char Z[2 * (dp_size + 2)];

    int re = std::scanf("%s %s %s", X, Y, Z);

    std::printf("%s\n%s\n%s\n", X, Y, Z);
    init_dp();
    bool is_shuffle = judge_shuffle(X, Y, Z);
    std::printf("%d\n", is_shuffle);
    if (is_shuffle)
    {
        rec_path(X, Y, Z);
    }
    return 0;
}

