
#include <stdio.h>

void printNums(int *arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d\n", arr[i]);
    }
}

int main() {
    int nums[] = {10, 20, 30};
    printNums(nums, 3);
}
