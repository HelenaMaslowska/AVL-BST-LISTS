#include <fstream>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <random>

using namespace std;
int N = 50000;

int main()
{
    int *tab = new int[N];
    for(int i = 0; i<N; i++)
    {
        tab[i] = i;
    }
    random_shuffle(tab,tab+N);
    std::ofstream plik;
    plik.open("rand_elem50000.txt");
    printf("%d\n",N);
    for(int i = 0; i<N; i++)
    {
        plik<<tab[i]<<"\n";
    }
    plik.close();
    return 0;
}
