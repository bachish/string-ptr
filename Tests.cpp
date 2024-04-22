#include "StringPtr.hpp"
#include <cstring>
#include <ios>
#include <iostream>
#include <type_traits>

void check(bool exp, const char* msg = "StingPtr test error!")
{
    if (!exp) {
        std::cout << std::endl
                  << msg;
        exit(1);
    }
}

void check_initialization()
{
    StringPtr defaultPtr;
    StringPtr defaultPtr2;
    check(defaultPtr.get() == nullptr, "Default ptr must point to null_object");
    check(defaultPtr.shared(), "Default ptr must be shared");

    const char* str = "Initialized from string";
    StringPtr strPtr = str;
    check(!strPtr.shared(), "Must be not shared");
    check(strcmp(strPtr.get(), str) == 0, "Points wrong str");

    StringPtr fromPtr = strPtr;
    check(fromPtr.shared(), "Must be shared");
    check(strPtr.shared(), "Must be shared");
    check(strcmp(fromPtr.get(), str) == 0, "Points wrong str");

    std::cout << "\nInitialization test passed!";
}

void check_assignment()
{
    const char* str1 = "check_assignment_1";
    const char* str2 = "check_assignment_2";

    StringPtr p1 = str1;
    p1 = p1;
    check(!p1.shared(), "Self-assignment must not make shared!");
    check(strcmp(p1.get(), str1) == 0, "Self-assignment must not change value!");

    StringPtr p2 = p1;

    check(p2.get() == p1.get());
    check(p1.shared());
    check(p2.shared());

    p1 = str2;
    p1 = "check_assignment_3_literal";
    check(!p1.shared());
    check(p2.shared());

    std::cout << "\nAssignment test passed!";
}

void check_release()
{
    StringPtr p1 = "string_for_release";
    // check output in DEBUG mode
    p1 = "baab";
}

/*
Always pick the first element as a pivot
*/
int partition(StringPtr ptrs[], int start, int end)
{
    int pivotIndex = start;
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (strcmp(ptrs[i].get(), ptrs[pivotIndex].get()) <= 0)
            count++;
    }
    pivotIndex = start + count;
    std::swap(ptrs[pivotIndex], ptrs[start]);

    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {
        while (strcmp(ptrs[i].get(), ptrs[pivotIndex].get()) <= 0) {
            i++;
        }
        while (strcmp(ptrs[j].get(), ptrs[pivotIndex].get()) > 0) {
            j--;
        }
        if (i < pivotIndex && j > pivotIndex) {
            std::swap(ptrs[i++], ptrs[j--]);
        }
    }
    return pivotIndex;
}
void quickSort(StringPtr* ptrs, int start, int end)
{
    if (start >= end)
        return;

    int p = partition(ptrs, start, end);
    quickSort(ptrs, start, p - 1);
    quickSort(ptrs, p + 1, end);
}

void check_sorting()
{
    const char* strs[] = { "d", "b", "a", "c" };
    const char* sorted[] = { "a", "b", "c", "d" };
    int n = 4;
    StringPtr ptrs[] = { StringPtr(strs[0]), StringPtr(strs[1]), StringPtr(strs[2]), StringPtr(strs[3]) };

    quickSort(ptrs, 0, n - 1);
    for (int i = 0; i < n; i++) {
        check(!ptrs[i].shared(), "Sorting algorithm change pointer counter!");
        check(strcmp(ptrs[i].get(), sorted[i]) == 0, "Incorrect sorting algorithm");
    }

    std::cout << "\nSorting test passed!";
}
int main(int argc, char* argv[])
{
    check_initialization();
    check_assignment();
    check_release();
    check_sorting();
    std::cout << "\nAll test passed!" << std::endl;
    return 0;
}
