
#include <cstdio>
#include <cstring>

char linebuf[2048];

int tbl[256];
int repeat[256];

void init_tbl()
{
    tbl[' '] = 0;
    repeat[' '] = 1;

    tbl['a'] = 2;
    tbl['b'] = 2;
    tbl['c'] = 2;

    tbl['d'] = 3;
    tbl['e'] = 3;
    tbl['f'] = 3;

    tbl['g'] = 4;
    tbl['h'] = 4;
    tbl['i'] = 4;

    tbl['j'] = 5;
    tbl['k'] = 5;
    tbl['l'] = 5;

    tbl['m'] = 6;
    tbl['n'] = 6;
    tbl['o'] = 6;

    tbl['p'] = 7;
    tbl['q'] = 7;
    tbl['r'] = 7;
    tbl['s'] = 7;

    tbl['t'] = 8;
    tbl['u'] = 8;
    tbl['v'] = 8;

    tbl['w'] = 9;
    tbl['x'] = 9;
    tbl['y'] = 9;
    tbl['z'] = 9;

    repeat['a'] = 1;
    repeat['b'] = 2;
    repeat['c'] = 3;

    repeat['d'] = 1;
    repeat['e'] = 2;
    repeat['f'] = 3;

    repeat['g'] = 1;
    repeat['h'] = 2;
    repeat['i'] = 3;

    repeat['j'] = 1;
    repeat['k'] = 2;
    repeat['l'] = 3;

    repeat['m'] = 1;
    repeat['n'] = 2;
    repeat['o'] = 3;

    repeat['p'] = 1;
    repeat['q'] = 2;
    repeat['r'] = 3;
    repeat['s'] = 4;

    repeat['t'] = 1;
    repeat['u'] = 2;
    repeat['v'] = 3;

    repeat['w'] = 1;
    repeat['x'] = 2;
    repeat['y'] = 3;
    repeat['z'] = 4;
}

int main(int argc, char* argv[])
{
    std::memset(tbl, -1, sizeof(tbl));
    std::memset(repeat, -1, sizeof(repeat));
    init_tbl();
    int N = -1;
    std::scanf("%d", &N);
    std::fgets(linebuf, 2048, stdin);
    int cases = 0;
    while(cases < N)
    {
        std::printf("Case #%d: ", ++cases);
        int last_key = -1;
        std::fgets(linebuf, 2048, stdin);
        //std::printf("\n%s", linebuf);
        char* p = linebuf; 
        while(tbl[*p] != -1)
        {
            //if (*p == ' ')
            //{
            //    fputc('0', stdout);
            //    //std::printf("0");
            //    last_key = -1;
            //}
            //else 
            {
                int key = tbl[*p];
                int rep = repeat[*p];
                if (key == last_key)
                {
                    fputc(' ', stdout);
                    //std::printf(" ");
                }
                for (int i = 0; i < rep; ++i)
                {
                    fputc(key + '0', stdout);
                    //std::printf("%d", key);
                }

                last_key = key;
            }
            ++p;
        }
        fputc('\n', stdout);
        //std::printf("\n");
    }
    return 0;
}
