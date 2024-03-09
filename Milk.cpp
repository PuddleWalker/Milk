#include "quantity.h"
#include <Windows.h>

int main()
{
    srand(time(NULL));
    quantity maks(4);
    quantity dima(4);
    cout << maks << endl;
    cout << dima << endl;
    cout << maks * dima << endl;
    cout << maks;
}
