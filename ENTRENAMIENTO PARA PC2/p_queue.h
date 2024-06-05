#pragma once
#ifndef _P_QUEUE_H
#define _P_QUEUE_H

#include <iostream>
#include "Registro.h"
#include <limits>
using namespace std;

class p_queue
{
public:
    p_queue(Registro** A, int n) {
        for (int i = 0; i < n; i++) {
            a[i] = A[i];
        }
        currentSize = n;
        buildMaxHeap(a, currentSize);
    }

    void insert(Registro* x) {
        currentSize++;
        a[currentSize - 1] = x;
        int i = currentSize - 1;
        while (i > 0 && a[parent(i)]->getTotal_Deaths() < a[i]->getTotal_Deaths()) {
            std::swap(a[i], a[parent(i)]);
            i = parent(i);
        }
    }

    Registro* maximum() {
        if (currentSize <= 0) {
            std::cerr << "heap overflow" << std::endl;
            return nullptr;
        }
        return a[0];
    }

    Registro* extract_max() {
        if (currentSize <= 0) {
            std::cerr << "heap overflow" << std::endl;
            return nullptr;
        }
        Registro* max = a[0];
        a[0] = a[currentSize - 1];
        currentSize--;
        maxHeapify(a, currentSize, 0);
        return max;
    }

    void increase_key(int i, Registro* x) {
        a[i] = (a[i]->getTotal_Deaths() > x->getTotal_Deaths()) ? a[i] : x;

        while (i > 0 && a[parent(i)]->getTotal_Deaths() < a[i]->getTotal_Deaths()) {
            std::swap(a[parent(i)], a[i]);
            i = parent(i);
        }
    }

    int size() {
        return currentSize;
    }

private:
    Registro* a[10000];
    int currentSize;

    int parent(int i) {
        return (i - 1) / 2;
    }

    int left(int i) {
        return 2 * i + 1;
    }

    int right(int i) {
        return 2 * i + 2;
    }

    void maxHeapify(Registro* A[], int n, int i) {
        int l = left(i);
        int r = right(i);
        int largest = i;
        if (l <= (n - 1) && A[l]->getTotal_Deaths() > A[i]->getTotal_Deaths())
            largest = l;
        if (r <= (n - 1) && A[r]->getTotal_Deaths() > A[largest]->getTotal_Deaths())
            largest = r;
        if (largest != i) {
            std::swap(A[i], A[largest]);
            maxHeapify(A, n, largest);
        }
    }

    void buildMaxHeap(Registro* A[], int n) {
        for (int i = n / 2 - 1; i >= 0; i--)
            maxHeapify(A, n, i);
    }

    void heapsort(Registro* A[], int n) {
        buildMaxHeap(A, n);
        for (int i = n - 1; i > 0; i--) {
            std::swap(A[0], A[i]);
            maxHeapify(A, --n, 0);
        }
    }
};

#endif
