#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>

const int dp_size = 100;

char op[dp_size + 1][dp_size + 1];
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
            char oper = 'M';
            if (src[i - 1] != dst[j - 1])
            {
                dist += 2;
                oper = 'S';
            }
            if (last_dp[j] + 1 < dist)
            {
                dist = last_dp[j] + 1;
                oper = 'D';
            }
            if (current_dp[j - 1] + 1 < dist)
            {
                dist = current_dp[j - 1] + 1;
                oper = 'I';
            }
            current_dp[j] = dist;
            op[i][j] = oper;
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
    std::memset(op, 0, sizeof(op));
    for (int i = 0; i < dp_size + 1; ++i)
    {
        op[i][0] = 'D';
        op[0][i] = 'I';
    }
    op[0][0] = '\0';
}

struct PathOp
{
    int i;
    int j;
    char oper;
    PathOp(int ii, int jj, char o)
    {
        i = ii;
        j = jj;
        oper = o;
    }
};

void reconstruct_path(const char* src, const char* dst)
{
    int srclen = std::strlen(src);
    int dstlen = std::strlen(dst);

    std::stack<PathOp> opstack;
    int i = srclen;
    int j = dstlen;
    while ((i != 0 || j != 0))
    {
        PathOp opinfo(i, j, op[i][j]);
        opstack.push(opinfo);
        switch (opinfo.oper)
        {
            case 'M':
            case 'S':
            {
                --i; --j;
            }
            break;
            case 'I':
            {
                -- j;
            }
            break;
            case 'D':
            {
                -- i;
            }
            default:
            {
            }
        }
        if (i < 0 || j < 0)
        {
            std::printf("Err2\n");
            std::exit(-1);
        }
    }

    while (!opstack.empty())
    {
        const PathOp& opinfo = opstack.top();
        switch (opinfo.oper)
        {
            case 'S':
            {
                std::printf("%c --> %c @ (%d, %d) \n", src[opinfo.i - 1], dst[opinfo.j - 1], opinfo.i, opinfo.j);
            }
            break;
            case 'I':
            {
                std::printf("+ %c @ (%d, %d)\n", dst[opinfo.j - 1], opinfo.i, opinfo.j);
            }
            break;
            case 'D':
            {
                std::printf("- %c @ (%d, %d)\n", src[opinfo.i - 1], opinfo.i, opinfo.j);
            }
            break;
            default:
            {
            }
        }
        opstack.pop();
    }
}

int main(int argc, char* argv[])
{
    char src[dp_size];
    char dst[dp_size];

    int re = std::scanf("%s %s", src, dst);

    init_dp();
    std::printf("%d\n", edit_dist(src, dst));
    reconstruct_path(src, dst);
    return 0;
}

