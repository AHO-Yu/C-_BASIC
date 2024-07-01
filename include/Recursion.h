#ifndef RECURSION_H
#define RECURSION_H

/*
 *  1.header for this .cpp
 *  2.C system file
 *  3.C++ system file
 *  4.other lib .h
 *  5.personal .h
 */

double power(double, int); // return n**P
int show_parenthesis(int);
void hanoi(char from, char to, char buffer, int n_disks);

namespace castle
{
    void place(int, int);
    void show_board(int);
}

namespace queen
{
    void place(int);

}
namespace MakeChange
{
    void exchange(int, int, int);

}

namespace Merge_sort
{
    void merge_sort(int *, int);
}

namespace merge2
{
    void merge_sort(int *, int, int);
}
#endif