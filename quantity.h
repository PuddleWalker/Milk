#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class quantity{
protected:

    int* quan;
    int Size;
    int random;

public:

    quantity(int size)//Конструктор по размеру
    {
        quan = new int[size];
        Size = size;

        for (int i = 0; i < size; i++)
        {
            do
            {
                random = rand() % (size * 4) - size * 2;
            } while (count(quan, quan + size, random) == 1);
            quan[i] = random;
        }
    }

    quantity(const quantity& other)//Конструктор копирования
    {
        random = 0;
        Size = other.Size;
        quan = new int[other.Size];

        for (int i = 0; i < other.Size; i++)
        {
            quan[i] = other.quan[i];
        }
    }

    bool find(int element) const//Поиск элемента
    {
        for (int i = 0; i < Size; i++)
        {
            if (quan[i] == element)
            {
                return true;
            }
        }
        return false;
    }

    quantity& operator+=(int num) {//Перегрузка оператора
        if (count(quan, quan + Size, num) == 0) {
            int* temp = new int[Size + 1];
            for (int i = 0; i < Size; i++) {
                temp[i] = quan[i];
            }
            temp[Size] = num;
            delete[] quan;
            quan = temp;
            Size++;
            return *this;
        }
    }

    quantity operator+(int num) const {//Перегрузка оператора
        quantity result(*this);
        if (count(quan, quan + Size, num) == 0) {
            int* temp = new int[Size + 1];
            for (int i = 0; i < Size; i++) {
                temp[i] = quan[i];
            }
            temp[Size] = num;
            delete[] result.quan;
            result.quan = temp;
            result.Size++;
        }
        return result;
    }

    quantity& operator +=(const quantity& other) {//Перегрузка оператора
        quantity result(*this);
        for (int i = 0; i < other.Size; i++) {
            if (!result.find(other.quan[i])) {
                result += other.quan[i];
            }
        }
        *this = result;
        return *this;
    }

    quantity operator+(const quantity& other) const {//Перегрузка оператора
        quantity result(*this);
        for (int i = 0; i < other.Size; i++) {
            if (!result.find(other.quan[i])) {
                result += other.quan[i];
            }
        }
        return result;
    }

    quantity& operator-=(int num) {//Перегрузка оператора
        int index = -1;
        for (int i = 0; i < Size; i++) {
            if (quan[i] == num) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            for (int i = index; i < Size - 1; i++) {
                quan[i] = quan[i + 1];
            }
            Size--;
        }
        return *this;
    }

    quantity& operator-(int num) const {//Перегрузка оператора
        quantity result(*this);
        int index = -1;
        for (int i = 0; i < result.Size; i++) {
            if (result.quan[i] == num) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            for (int i = index; i < result.Size - 1; i++) {
                result.quan[i] = result.quan[i + 1];
            }
            result.Size--;
        }
        return result;
    }

    quantity operator-=(const quantity& other) {//Перегрузка оператора
        quantity result(*this);
        for (int i = 0; i < other.Size; i++) {
            if (result.find(other.quan[i])) {
                result -= other.quan[i];
            }
        }
        *this = result;
        return *this;
    }

    quantity operator-(const quantity& other) const {//Перегрузка оператора
        quantity result(*this);
        for (int i = 0; i < other.Size; i++) {
            if (result.find(other.quan[i])) {
                result -= other.quan[i];
            }
        }
        return result;
    }

    quantity& operator=(const quantity& other) {//Перегрузка оператора
        if (this != &other) {
            delete[] quan;
            Size = other.Size;
            quan = new int[Size];
            for (int i = 0; i < Size; i++) {
                quan[i] = other.quan[i];
            }
        }
        return *this;
    }

    quantity& operator =(int size) {//Перегрузка оператора
        delete[] quan;
        quan = new int[size];
        Size = size;

        for (int i = 0; i < size; i++)
        {
            do
            {
                random = rand() % (size * 4) - size * 2;;
            } while (count(quan, quan + size, random) == 1);
            quan[i] = random;
        }
        return *this;
    }

    bool operator==(const quantity& other) {//Перегрузка оператора
        quantity result(*this);
        if (this->Size == other.Size) {
            for (int i = 0; i < Size; i++) {
                if (!result.find(other.quan[i])) return false;
            }
        }
        return true;
    }

    quantity operator*=(const quantity& other) {//Перегрузка оператора
        int len = 0;
        quantity result(*this);
        delete[] result.quan;
        result.quan = new int(Size);
        for (int i = 0; i < result.Size; i++) {
            if ((*this).find(other.quan[i])) {
                result.quan[len] = other.quan[i];
                len++;
            }
        }
        result.Size = len;
        *this = result;
        return *this;
    }

    quantity operator*(const quantity& other) const {//Перегрузка оператора
        int len = 0;
        quantity result(*this);
        delete[] result.quan;
        result.quan = new int(Size);
        for (int i = 0; i < result.Size; i++) {
            if ((*this).find(other.quan[i])) {
                result.quan[len] = other.quan[i];
                len++;
            }
        }
        result.Size = len;
        return result;
    }
    void print() const {
        cout << "{";
        for (int i = 0; i < Size - 1; i++)
        {
            cout << quan[i] << ", ";
        }
        if (Size != 0) cout << quan[Size - 1];
        cout << "}";
    }
};

ostream& operator <<(ostream& out, const quantity& other) {
    other.print();
    return out;
}

istream& operator >>(istream& in, quantity& other) {
    int num;
    cin >> num;
    other = num;
    return in;
}