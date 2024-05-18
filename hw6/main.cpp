#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include "SearchEngine.h"
#include "Trie.h"

int main(int argc, char **argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    if (argc != 4)
    {
        cout << "Not enough file." << '\n';
        return 0;
    }

    SearchEngine search_engine;
    search_engine.input(argv[1]);
    search_engine.ouput(argv[2], stoi(argv[3]));
    return 0;
}