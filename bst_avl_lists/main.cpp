#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <Windows.h>

#include "avl.h"
#include "bst.h"
#include "lists.h"
using namespace std;

int main()
{
    LARGE_INTEGER freq, T1, T2;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&T1);

    avl<int, int>* a = new avl<int, int>();
    bst<int, int>* b = new bst<int, int>();
    lists<int, int>* c = new lists<int, int>();

    //srand(time(NULL));
    ifstream plik;
    string przed[] = { "ros", "mal", "rand", "A", "V"};
    string po[] = { "1000", "10000", "50000", "100000" };

    string txt_in = "";
    float time_ms;
    for (int elements_type = 0; elements_type < 5; elements_type++)
    {
        for (int elements_count = 0; elements_count < 4; elements_count++)
        {
            int Number = stoi(po[elements_count]);
            int *elements_to_bst_avl_lists = new int[Number];
            txt_in = "dane\\" + przed[elements_type] + "_elem" + po[elements_count] + ".txt";
        //    printf("%s\n", txt_in.c_str());
            plik.open(txt_in.c_str());

            int in_number;
            if (!plik.fail())
            {
                for (int k = 0; k < Number; k++)
                {
                    plik >> in_number;
                    elements_to_bst_avl_lists[k] = in_number;
                }
            }
            else
            {
                return -1;
            }
//-------------------------------------------------------------------------------------------
            
            QueryPerformanceCounter(&T1);
            for (int k = 0; k < Number; k++)
            {
                a->add(elements_to_bst_avl_lists[k], 1);
            }
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "avl add " << przed[elements_type] << " " <<po[elements_count] << " " << (time_ms) << endl;
            /*
            QueryPerformanceCounter(&T1);
            for (int k = 0; k < Number; k++)
            {
                b->add(elements_to_bst_avl_lists[k], 1);
            }
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "bst add " << przed[elements_type] << " " << po[elements_count] << " " << (time_ms) << endl;
            */
            QueryPerformanceCounter(&T1);
            for (int k = 0; k < Number; k++)
            {
                c->add(elements_to_bst_avl_lists[k], 1);
            }
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "lists add " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;
            
//-------------------------------------------------------------------------------------------
            
            QueryPerformanceCounter(&T1);
            a->if_exists(1) ? "exists" : "not exists";
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "avl minexists " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;

            QueryPerformanceCounter(&T1);
            a->if_exists(Number) ? "exists" : "not exists";
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "avl maxexists " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;

            QueryPerformanceCounter(&T1);
            a->if_exists(int(Number / 2)) ? "exists" : "not exists";
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "avl medexists " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;
            
            //-------------------------------------------------------------------------------------------
            /*
            QueryPerformanceCounter(&T1);
            b->if_exists(1) ? "exists" : "not exists";
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "bst exists " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;

            QueryPerformanceCounter(&T1);
            b->if_exists(Number) ? "exists" : "not exists";
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "bst exists " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;

            QueryPerformanceCounter(&T1);
            b->if_exists(int(Number / 2)) ? "exists" : "not exists";
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "bst exists " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;

            //-------------------------------------------------------------------------------------------
            */
            QueryPerformanceCounter(&T1);
            c->if_exists(1) ? "exists" : "not exists";
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "lists minexists " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;

            QueryPerformanceCounter(&T1);
            c->if_exists(Number) ? "exists" : "not exists";
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "lists maxexists " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;

            QueryPerformanceCounter(&T1);
            c->if_exists(int(Number / 2)) ? "exists" : "not exists";
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "lists medexists " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;
            
//-------------------------------------------------------------------------------------------
            
            QueryPerformanceCounter(&T1);
            a->remove(1);
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "avl minremove " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;

            QueryPerformanceCounter(&T1);
            a->remove(Number);
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "avl maxremove " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;

            QueryPerformanceCounter(&T1);
            a->remove(int(Number / 2));
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "avl medremove " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;
            /*
            QueryPerformanceCounter(&T1);
            b->remove(1);
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "bst remove " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;

            QueryPerformanceCounter(&T1);
            b->remove(Number);
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "bst remove " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;

            QueryPerformanceCounter(&T1);
            b->remove(int(Number / 2));
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "bst remove " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;
            */
            QueryPerformanceCounter(&T1);
            c->remove(1);
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "lists minremove " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;

            QueryPerformanceCounter(&T1);
            c->remove(Number);
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "lists maxremove " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;

            QueryPerformanceCounter(&T1);
            c->remove(int(Number / 2));
            QueryPerformanceCounter(&T2);
            time_ms = (float)(T2.QuadPart - T1.QuadPart) * 1000 / freq.QuadPart;
            cout << "lists medremove " << przed[elements_type] << " " << po[elements_count] << " " << time_ms << endl;
            
            plik.close();
            delete[] elements_to_bst_avl_lists;
        }
    }

    /*
    for (int i = 0; i < 20; i++)
    {
        unsigned int key = rand()% 100 + 1, value = rand() % 100 + 1;
        a->add(key, value);
        b->add(key, value);
        c->add(key, value);
    }
    printf("Dodano nowe klucze i wartosci do struktur: AVL, BST, lista.\n");

    printf("\nAVL: ");
    a->foreach(avl<int, int>::show);
    printf("\nBST: ");
    b->inorder(b->root);
    printf("\nListy: ");
    c->_order(c->root);

    printf("\nUsuwa:\n");
    for (int i = 0; i < 5; i++)
    {
        unsigned int key = rand() % 100 + 1;
        printf("%d ", key);
        a->remove(key);
        b->remove(key);
        c->remove(key);
    }
    printf("\n");

    for (int i = 0; i < 20; i++)
    {
        unsigned int key = rand() % 100 + 1;
        printf("\nCzy istnieje %d?\n", key);
        printf("w AVL: %s \n", a->if_exists(key) ? "istnieje" : "nie istnieje");
        printf("w BST: %s \n", b->if_exists(key) ? "istnieje" : "nie istnieje");
        printf("w liscie: %s \n", c->if_exists(key) ? "istnieje" : "nie istnieje");
    }
    for (int i = 0; i < 3; i++)
    {
        unsigned int key = rand() % 100 + 1;
        printf("\nCzy istnieje %d?\n", key);
        printf("w AVL: %s \n", a->if_exists(key) ? "istnieje" : "nie istnieje");
        printf("w BST: %s \n", b->if_exists(key) ? "istnieje" : "nie istnieje");
        printf("w liscie: %s \n", c->if_exists(key) ? "istnieje" : "nie istnieje");
    }
    */
    plik.close();
    return 0;
}
