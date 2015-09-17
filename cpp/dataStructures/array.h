#ifndef __DS_ARRAY__
#define __DS_ARRAY__

#include <iostream>

void printArray(int* arr, size_t size)
{
    for (size_t index = 0; index < size; ++index)
    {
        std:: cout << arr[index] << " ";
    }
}

void rotateLeft(int *arr, size_t size, size_t n);
void mirror(int *arr, size_t size);


#endif __DS_ARRAY__
