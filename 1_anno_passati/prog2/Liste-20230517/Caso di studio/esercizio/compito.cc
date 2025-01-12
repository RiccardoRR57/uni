#include <parola.h>
#include <fstream>
#include <liste.h>
#include <tipo.h>

using namespace std;

parola* load(int& dim) {
    ifstream in("inverted");

    int temp = 0;

    in >> dim;

    parola *arr = new parola[dim];

    for (int i = 0; i < dim; i++)
    {
        in >> arr[i].p;

        in >> arr[i].n_doc;

        for (int j = 0; j < arr[i].n_doc; j++)
        {
            in >> temp;
            arr[i].l = insert_elem(arr[i].l, new_elem(temp));
        }
    }
    return arr;
}
