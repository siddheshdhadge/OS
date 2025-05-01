#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE 100

void bubbleSort(int arr[], int n);
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void printArray(int arr[], int size);

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}


void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[MAX_SIZE];
    int arrSize;

    
    printf("Enter the number of elements: ");
    scanf("%d", &arrSize);

    if (arrSize > MAX_SIZE || arrSize <= 0) {
        printf("Invalid size. Exiting.\n");
        return 1;
    }

    
    printf("Enter the elements:\n");
    for (int i = 0; i < arrSize; i++) {
        scanf("%d", &arr[i]);
    }

    int arrCopy[MAX_SIZE];
    
    for (int i = 0; i < arrSize; i++) {
        arrCopy[i] = arr[i];
    }

    pid_t pid = fork();

    if (pid < 0) {
               perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        
        printf("Child Process (Bubble Sort):\n");
        bubbleSort(arrCopy, arrSize);
        printArray(arrCopy, arrSize);
        exit(0);
    } else {
        
        wait(NULL);         
        printf("Parent Process (Quick Sort):\n");
        quickSort(arr, 0, arrSize - 1);
        printArray(arr, arrSize);
    }

    return 0;
}
