#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void binarySearch(int arr[], int size, int target) {
    int low = 0, high = size - 1, mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            printf("Elemento %d encontrado no índice %d\n", target, mid);
            return;
        }
        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    printf("Elemento %d não encontrado\n", target);
}

void interpolationSearch(int arr[], int size, int target) {
    int low = 0, high = size - 1, mid;
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        mid = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low]);
        if (arr[mid] == target) {
            printf("Elemento %d encontrado no índice %d\n", target, mid);
            return;
        }
        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    printf("Elemento %d não encontrado\n", target);
}

void jumpSearch(int arr[], int size, int target) {
    int step = sqrt(size);
    int prev = 0;
    while (arr[step < size ? step : size - 1] < target) {
        prev = step;
        step += sqrt(size);
        if (prev >= size)
            break;
    }
    for (int i = prev; i < (step < size ? step : size); i++) {
        if (arr[i] == target) {
            printf("Elemento %d encontrado no índice %d\n", target, i);
            return;
        }
    }
    printf("Elemento %d não encontrado\n", target);
}

void exponentialSearch(int arr[], int size, int target) {
    if (arr[0] == target) {
        printf("Elemento %d encontrado no índice 0\n", target);
        return;
    }
    int i = 1;
    while (i < size && arr[i] <= target)
        i = i * 2;

    int low = i / 2, high = (i < size) ? i : size - 1;
    binarySearch(arr, size, target);  // Usando Binary Search para a busca final
}

void ternarySearch(int arr[], int size, int target) {
    int low = 0, high = size - 1, mid1, mid2;
    while (high >= low) {
        mid1 = low + (high - low) / 3;
        mid2 = high - (high - low) / 3;

        if (arr[mid1] == target) {
            printf("Elemento %d encontrado no índice %d\n", target, mid1);
            return;
        }
        if (arr[mid2] == target) {
            printf("Elemento %d encontrado no índice %d\n", target, mid2);
            return;
        }

        if (target < arr[mid1])
            high = mid1 - 1;
        else if (target > arr[mid2])
            low = mid2 + 1;
        else {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }
    printf("Elemento %d não encontrado\n", target);
}

void shellSort(int arr[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void bucketSort(float arr[], int size) {
    float bucket[5][size];
    int bucketCount[5] = {0};
    for (int i = 0; i < size; i++) {
        int index = (int)(arr[i] * 5);
        bucket[index][bucketCount[index]++] = arr[i];
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 1; j < bucketCount[i]; j++) {
            float key = bucket[i][j];
            int k = j - 1;
            while (k >= 0 && bucket[i][k] > key) {
                bucket[i][k + 1] = bucket[i][k];
                k--;
            }
            bucket[i][k + 1] = key;
        }
    }

    int index = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < bucketCount[i]; j++) {
            arr[index++] = bucket[i][j];
        }
    }
}

void countingSort(int arr[], int size, int exp) {
    int output[size];
    int count[10] = {0};

    for (int i = 0; i < size; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < size; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int size) {
    for (int exp = 1; exp <= 1000; exp *= 10)
        countingSort(arr, size, exp);
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printFloatArray(float arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

int main() {
    int size, choice, sortChoice, num;
    printf("Digite o tamanho do array: ");
    scanf("%d", &size);

    int arr[size];
    float arrFloat[size];
    printf("Digite os elementos do array (inteiros):\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    do {
        printf("\nSelecione um algoritmo de busca:\n");
        printf("1. Binary Search\n2. Interpolation Search\n3. Jump Search\n4. Exponential Search\n5. Ternary Search\n");
        printf("Digite a opção: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 5) {
            printf("Selecione um algoritmo de ordenação:\n");
            printf("1. Shell Sort\n2. Merge Sort\n3. Selection Sort\n4. Quick Sort\n5. Radix Sort\n");
            printf("Digite a opção de ordenação: ");
            scanf("%d", &sortChoice);

            switch (sortChoice) {
                case 1: shellSort(arr, size); break;
                case 2: mergeSort(arr, 0, size - 1); break;
                case 3: selectionSort(arr, size); break;
                case 4: quickSort(arr, 0, size - 1); break;
                case 5: radixSort(arr, size); break;
                default: printf("Opção de ordenação inválida.\n");
            }

            printf("Array ordenado: ");
            printArray(arr, size);

            printf("Digite o número a ser buscado: ");
            scanf("%d", &num);

            switch (choice) {
                case 1: binarySearch(arr, size, num); break;
                case 2: interpolationSearch(arr, size, num); break;
                case 3: jumpSearch(arr, size, num); break;
                case 4: exponentialSearch(arr, size, num); break;
                case 5: ternarySearch(arr, size, num); break;
                default: printf("Opção de busca inválida.\n");
            }
        }
    } while (choice != 0);

    return 0;
}
