#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#define MAX 100 // valor maximo de caracteres en el buffer

#ifdef DOLOG
#define LOG(...) fprintf(log, __VA_ARGS__);
#else
#define LOG(...)
#endif

struct array
{
    int *pdata;
    int size;
};

void initArray(struct array *);
void getArray(struct array *);
void arrayCommon(struct array *, struct array *, struct array *);
void printArray(struct array *);
void freeMemory(struct array *, struct array *, struct array *);

void initArray(struct array *arr)
{
    arr->pdata = NULL;
    arr->size = -1;
}

void printArray(struct array *parr)
{
    for (int i = 0; i < parr->size; i++)
    {
        printf("%d ", parr->pdata[i]);
    }
    printf("\n");
}

void getArray(struct array *parr)
{
    // codigo para entrar un caracter
    int value;
    char bufferArray[MAX];
    char *endptr;

    printf("Enter the size of the array: ");
    if (fgets(bufferArray, MAX, stdin) != NULL) // ingreso del tamaño del array por fgets
    {
        bufferArray[strlen(bufferArray) - 1] = 0;

        // convertir el dato ingresado a un numero con strtol() y pasarle el dato del valor al dato de size en la estruc array{}
        errno = 0;
        value = strtol(bufferArray, &endptr, 10);
        if (errno == 0 && *bufferArray != 0 && bufferArray != endptr) // prueba de errores
        {
            parr->size = value;
            // asignarle el "size" a la posicion en memoria donde ira el arreglo
            parr->pdata = malloc(sizeof(int) * parr->size);
        }
        else
            exit(EXIT_FAILURE);
    }

    // Agregar datos al array
    for (uint i = 0; i < parr->size; i++)
    {
        if (fgets(bufferArray, MAX, stdin) != NULL)
        {
            value = strtol(bufferArray, &endptr, 10);                     // convertir los datos del arreglo a numeros
            if (errno == 0 && *bufferArray != 0 && bufferArray != endptr) // prueba de errores
                parr->pdata[i] = value;
            else
                exit(EXIT_FAILURE);
        }
    }
}

void arrayCommon(struct array *arrIn1, struct array *arrIn2, struct array *arrOut)
{
    // necesito una variable para pasar el size al array arrOut
    // necesito un array donde guardar los datos que son repetidos para luego pasarlo al array arrOut
    // necesito algo para saber, dado el caso en que la variable del array se haya repetido
    int size_vdataOut = 0;
    char vdataOut[MAX];
    int valueOut = 0;
    bool stateRepeated = false;

    // recorrer los arreglos y preguntar si los datos en la posicion i de arr1[i] y arr2[i] son iguales
    for (uint i = 0; i < arrIn1->size; i++)
    {
        for (uint j = 0; j < arrIn2->size; j++)
        {
            if (arrIn1->pdata[i] == arrIn2->pdata[j])
            {
                valueOut = arrIn1->pdata[i];
                stateRepeated = true;
                for (uint k = 0; k < size_vdataOut; k++) // recorro y verifico en el vdataOut si el numero a evaluar ya esta en el array
                {
                    if (vdataOut[k] == valueOut)
                    {
                        stateRepeated = true;
                        k = size_vdataOut;
                    }
                }

                if (stateRepeated)
                {
                    vdataOut[size_vdataOut] = valueOut;
                    size_vdataOut++;
                }
            }
        }
        stateRepeated = false;
    }

    // asignar las variables al array arrayOut y el espacio en la memoria para almacenar los datos
    arrOut->size = size_vdataOut;
    arrOut->pdata = malloc(sizeof(int) * arrOut->size);
    for (uint i = 0; i < arrOut->size; i++)
    {
        arrOut->pdata[i] = vdataOut[i];
    }
}

void freeMemory(struct array *arr1, struct array *arr2, struct array *arr3)
{
    free(arr1->pdata);
    free(arr1);

    free(arr2->pdata);
    free(arr2);

    free(arr3->pdata);
    free(arr3);
}

int main(void)
{

#ifdef DOLOG
    FILE *log = fopen("log", "w");
    if (log == NULL)
    {
        perror("log file creation fails: ");
        return EXIT_FAILURE;
    }
#endif

    char commandBuf[64];

    LOG("creating an object for each array\n");

    struct array *arr1 = malloc(sizeof(struct array) * 1);
    initArray(arr1);
    struct array *arr2 = malloc(sizeof(struct array) * 1);
    initArray(arr2);
    struct array *arr3 = malloc(sizeof(struct array) * 1);
    initArray(arr3);

    LOG("Init command loop\n");

    while (fgets(commandBuf, sizeof(commandBuf), stdin) != NULL)
    {
        commandBuf[strlen(commandBuf) - 1] = 0;

        if (strncmp(commandBuf, "arr1", strlen("arr1")) == 0)
        {
            LOG("getting array1\n");
            getArray(arr1);
        }
        else if (strncmp(commandBuf, "arr2", strlen("arr2")) == 0)
        {
            LOG("getting array2\n");
            getArray(arr2);
        }
        else if (strncmp(commandBuf, "printArr1", strlen("printArr1")) == 0)
        {
            LOG("printing arr1\n");
            printArray(arr1);
        }
        else if (strncmp(commandBuf, "printArr2", strlen("printArr2")) == 0)
        {
            LOG("printing arr2\n");
            printArray(arr2);
        }
        else if (strncmp(commandBuf, "compare", strlen("compare")) == 0)
        {
            LOG("Compare arrays\n");
            arrayCommon(arr1, arr2, arr3);
        }
        else if (strncmp(commandBuf, "printResult", strlen("printResult")) == 0)
        {
            LOG("printing compare result\n");
            printf("%d\n", arr3->size);
            if (arr3->size != 0)
            {
                printArray(arr3);
            }
        }
        else if (strncmp(commandBuf, "exit", strlen("exit")) == 0)
        {
            LOG("running exit command\n");
            freeMemory(arr1, arr2, arr3);
            break;
        }
    }

    return EXIT_SUCCESS;
}
