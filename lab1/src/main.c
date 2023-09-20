#include "stdlib.h"
#include <unistd.h>
#include <stdio.h>

int getNumberOfNumbers(char* stringOfNumbers, int stringLen) {
    if (stringLen == 0 || (stringLen == 1 && stringOfNumbers[0] == '\n')) {
        return 0;
    }
    int spaceCount = 0;
    for (int i = 0; i < stringLen; ++i) {
        if (stringOfNumbers[i] == ' ') {
            ++spaceCount;
        }
    }
    return spaceCount + 1;
}

void fillArrayWithNumbers(char *stringOfNumbers, int stringLen, int* array) {
    int currentNumber = 0;
    int arrayIndex = 0;
    for (int i = 0; i < stringLen; ++i) {
        if (!(stringOfNumbers[i] == ' ' || stringOfNumbers[i] == '\n')) {
            currentNumber *= 10;
            currentNumber += stringOfNumbers[i] - '0';
        } else {
            array[arrayIndex] = currentNumber;
            ++arrayIndex;
            currentNumber = 0;
        }
    }
    // Если конец строки через EOF, нужно обработать последний элемент
    if (currentNumber) {
        array[arrayIndex] = currentNumber;
    }
}

double devide(int* array, int numberOfNumbers) {
    double result = array[0];
    
    for (int i = 1; i < numberOfNumbers; ++i) {
        result /= array[i];
    }
    
    return result;
}


int main(int argc, char **argv)
{
    // pid_t pid = fork();
    pid_t pid = 0;

    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) { // parent procces
        printf("Введите числа:\n");

        char *input;
        size_t n = 1024;
        ssize_t readed;
        input = (char *) malloc(n * sizeof(char)); // Сделать free

        if (input == NULL) {
            perror("Unable allocate buffer");
            exit(1);
        }

        if ((readed = getline(&input, &n, stdin)) != -1) { // Считывается перенос тоже
            printf("Readed %ld symbols\n", readed);
            printf("Input string: %s\n", input);
            printf("n equal: %ld\n", n);
            int numberOfNumbers = getNumberOfNumbers(input, readed);
            printf("Количество чисел: %d\n", numberOfNumbers);
            if (numberOfNumbers > 0) {
                int *arrayOfNumbers = malloc(sizeof(int) * numberOfNumbers);
                fillArrayWithNumbers(input, readed, arrayOfNumbers);
                for (int i = 0; i < numberOfNumbers; ++i) {
                    printf("HERE %d\n", arrayOfNumbers[i]);
                }
                printf("%lf", devide(arrayOfNumbers, numberOfNumbers));
                free(arrayOfNumbers);
            } else {
                printf("Вы не ввели числа!\n");
            }

        }

        
        free(input);
    }
    if (pid > 0) { // child procces
        execl("child", "child", NULL);
    }
}