#include <cstdint>
#include <iostream>
#include <cstring>
#include <array>

#define N_HASHES 13
#define N_KEYWORDS 13

const char *keywords[] = { "forward",  "rotate",  "penup",  "pendown",  "pencolour",  "goto", "pensize",
                          "scale",  "pushstate",  "popstate", "evaluate", "execute", "redefine" };

uint32_t c1 = 0, c2 = 0, c3 = 0;
uint32_t bestC1 = 0, bestC2 = 0, bestC3 = 0;
std::array<int, N_HASHES> hashTable;
std::array<int, N_KEYWORDS> hashes;
int minHashCollisions = N_KEYWORDS;

void resetHashTable()
{
    hashTable.fill(-1);
}

int gethash(const char *str)
{
    uint32_t h = 0;
    for(; *str; ++str)
    {
        uint32_t c = (uint32_t)(*str);
        h = (h*c1 + c3) ^ (c*c2);
    }
    return static_cast<int>(h % N_HASHES);
}

int main()
{
    for(c1 = 0; c1 < 30; ++c1)
    {
        for(c2 = 0; c2 < 30; ++c2)
        {
            for(c3 = 0; c3 < 1000; ++c3)
            {
                resetHashTable();
                int collisions = 0;
                for(uint32_t i = 0; i < N_KEYWORDS; ++i)
                {
                    int h = gethash(keywords[i]);
                    hashes[i] = h;
                    if(hashTable.at(h) != -1)
                        ++collisions;
                    hashTable.at(h) = i;
                }
                if(collisions < minHashCollisions)
                {
                    minHashCollisions = collisions;
                    bestC1 = c1; bestC2 = c2; bestC3 = c3;
                }
            }
        }
    }
    std::cout << "min hash collisions: " << minHashCollisions << "\n"
                 "best coefficients: (" << bestC1 << ", " << bestC2 << ", " << bestC3 << ")\n";
    c1 = bestC1; c2 = bestC2; c3 = bestC3;
    resetHashTable();
    std::cout << "hashes:\n";
    for(int i = 0; i < N_KEYWORDS; ++i)
    {
        int h = gethash(keywords[i]);
        hashTable[h] = i;
        std::cout << keywords[i] << " -> " << h << "\n";
    }
    if(minHashCollisions == 0)
    {
        std::cout << "Found optimal 1-1 hashing (without collisions):\n";
        for(int i = 0; i < N_HASHES; ++i)
            std::cout << "{ " << keywords[hashTable[i]] << "_keyword, Literal(\"" << keywords[hashTable[i]] << "\") },\n";
    }
}
