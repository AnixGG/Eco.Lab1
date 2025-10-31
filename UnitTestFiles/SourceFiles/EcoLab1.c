/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */
//#undef ECO_LIB
//#define ECO_DLL
/* Eco OS */
#include "IEcoSystem1.h"

#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"
#include "IEcoCalculatorY.h"
#include "IEcoCalculatorX.h"

/* Components headers */
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorC.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"



static void print_separator(const char* title) {
    printf("\n-------------------\n%s\n-------------------\n", title);
}



void run_calculator_tests_ext(IEcoLab1* pIEcoLab1) {
    void* tmp = 0;
    IEcoCalculatorX* pIX = 0;
    IEcoCalculatorY* pIY = 0;
    IEcoLab1* pLabBack = 0;
    int16_t a = 51;
    int16_t b = 8;
    int16_t res = 0;

    printf("\n--- Calculator Interface Tests (extended) ---\n");

    /* Получаем IEcoCalculatorX от IEcoLab1 */
    printf("Query IEcoCalculatorX from IEcoLab1...");
    if (pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, &tmp) == 0 && tmp != 0) {
        pIX = (IEcoCalculatorX*)tmp;
        printf("OK\n");
    }
    else {
        printf("FAILED\n");
    }

    /* Addition/Subtraction tests via X */
    if (pIX) {
        print_separator("Addition Test");
        printf("Input: %d + %d\n", a, b);
        res = pIX->pVTbl->Addition(pIX, a, b);
        printf("Result: %d\n", res);
        print_separator("Subtraction Test");
        printf("Input: %d - %d\n", a, b);
        res = pIX->pVTbl->Subtraction(pIX, a, b);
        printf("Result: %d\n", res);
    }

    /* Проверка: QueryInterface с pIX -> IEcoLab1 (обратная проверка) */
    if (pIX) {
        tmp = 0;
        printf("\nChecking QI from IEcoCalculatorX to IEcoLab1...");
        if (pIX->pVTbl->QueryInterface(pIX, &IID_IEcoLab1, &tmp) == 0 && tmp != 0) {
            pLabBack = (IEcoLab1*)tmp;
            printf("OK (got IEcoLab1 via pIX)\n");
            /* освобождаем полученный интерфейс */
            pLabBack->pVTbl->Release(pLabBack);
            pLabBack = 0;
        }
        else {
            printf("FAILED\n");
        }
    }

    /* Получаем IEcoCalculatorY от IEcoLab1 */
    tmp = 0;
    printf("\nQuery IEcoCalculatorY from IEcoLab1...");
    if (pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, &tmp) == 0 && tmp != 0) {
        pIY = (IEcoCalculatorY*)tmp;
        printf("OK\n");
    }
    else {
        printf("FAILED\n");
    }

    /* Multiplication/Division tests via Y */
    if (pIY) {
        print_separator("Multiplication Test");
        printf("Input: %d * %d\n", a, b);
        res = pIY->pVTbl->Multiplication(pIY, a, b);
        printf("Result: %d\n", res);
        print_separator("Division Test");
        printf("Input: %d / %d\n", a, b);
        res = pIY->pVTbl->Division(pIY, a, b);
        printf("Result: %d\n", res);
    }

    /* Проверка: QueryInterface с pIY -> IEcoLab1 (обратная проверка) */
    if (pIY) {
        tmp = 0;
        printf("\nChecking QI from IEcoCalculatorY to IEcoLab1...");
        if (pIY->pVTbl->QueryInterface(pIY, &IID_IEcoLab1, &tmp) == 0 && tmp != 0) {
            pLabBack = (IEcoLab1*)tmp;
            printf("OK (got IEcoLab1 via pIY)\n");
            /* освобождаем полученный интерфейс */
            pLabBack->pVTbl->Release(pLabBack);
            pLabBack = 0;
        }
        else {
            printf("FAILED\n");
        }
    }

    /* Дополнительная демонстрация: QI между X и Y (через IEcoLab1 это должно сработать) */
    if (pIX) {
        tmp = 0;
        printf("\nChecking QI from IEcoCalculatorX to IEcoCalculatorY...");
        if (pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorY, &tmp) == 0 && tmp != 0) {
            IEcoCalculatorY* pYFromX = (IEcoCalculatorY*)tmp;
            printf("OK (got IEcoCalculatorY via pIX)\n");
            /* Пробуем вызвать на нём метод */
            printf("Test Multiplication via IEcoCalculatorY obtained from IEcoCalculatorX: %d * %d = %d\n", a, b, pYFromX->pVTbl->Multiplication(pYFromX, a, b));
            pYFromX->pVTbl->Release(pYFromX);
        }
        else {
            printf("FAILED\n");
        }
    }

    /* Освобождение интерфейсов */
    if (pIX) pIX->pVTbl->Release(pIX);
    if (pIY) pIY->pVTbl->Release(pIY);

    printf("\nAll calculator interface tests complete.\n");
}


/*
 *
 * <сводка>
 *   Компаратор для int (возрастание)
 * </сводка>
 *
 */
static int ECOCALLMETHOD cmp_int_asc_eco(const void* a, const void* b) {
    const int ia = *(const int*)a;
    const int ib = *(const int*)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

/* Вторая версия для qsort (требуется при условии запуска на WINDOWS)*/
static int __cdecl cmp_int_asc(const void* a, const void* b) {
    const int ia = *(const int*)a;
    const int ib = *(const int*)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

/*
 *
 * <сводка>
 *   Компаратор для char (возрастание)
 * </сводка>
 *
 */
static int ECOCALLMETHOD cmp_char_asc_eco(const void* a, const void* b) {
    char x = *(const char*)a;
    char y = *(const char*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

static int __cdecl cmp_char_asc(const void* a, const void* b) {
    char x = *(const char*)a;
    char y = *(const char*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

/*
 *
 * <сводка>
 *   Компаратор для float (возрастание)
 * </сводка>
 *
 */
static int ECOCALLMETHOD cmp_float_asc_eco(const void* a, const void* b) {
    float x = *(const float*)a;
    float y = *(const float*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

static int __cdecl cmp_float_asc(const void* a, const void* b) {
    float x = *(const float*)a;
    float y = *(const float*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

/*
 *
 * <сводка>
 *   Компаратор для double (возрастание)
 * </сводка>
 *
 */
static int ECOCALLMETHOD cmp_double_asc_eco(const void* a, const void* b) {
    double x = *(const double*)a;
    double y = *(const double*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

static int __cdecl cmp_double_asc(const void* a, const void* b) {
    float x = *(const float*)a;
    float y = *(const float*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

/*
 *
 * <сводка>
 *   Компаратор для long long (возрастание)
 * </сводка>
 *
 */
static int ECOCALLMETHOD cmp_long_asc_eco(const void* a, const void* b) {
    long x = *(const long*)a;
    long y = *(const long*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

static int __cdecl cmp_long_asc(const void* a, const void* b) {
    long x = *(const long*)a;
    long y = *(const long*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}


/*
 *
 * <сводка>
 *   Компаратор для long long (возрастание)
 * </сводка>
 *
 */
static int ECOCALLMETHOD cmp_long_long_asc_eco(const void* a, const void* b) {
    long long x = *(const long long*)a;
    long long y = *(const long long*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

static int __cdecl cmp_long_long_asc(const void* a, const void* b) {
    long long x = *(const long long*)a;
    long long y = *(const long long*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

/*
 *
 * <сводка>
 *   Компаратор для long double (возрастание)
 * </сводка>
 *
 */
static int ECOCALLMETHOD cmp_long_double_asc_eco(const void* a, const void* b) {
    long double x = *(const long double*)a;
    long double y = *(const long double*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

static int __cdecl cmp_long_double_asc(const void* a, const void* b) {
    long double x = *(const long double*)a;
    long double y = *(const long double*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

/*
 *
 * <сводка>
 *   Функция проверки отсортированных данных
 * </сводка>
 *
 */
static void check_is_sorted(void* base, size_t nmemb, size_t size,
                     int (*compar)(const void*, const void*)){
    size_t i;
    char* int_arr = (char*)base;
    void* p1;
    void* p2;
    
    for (i = 0; i + 1 < nmemb; ++i) {
            p1 = int_arr + i * size;
            p2 = int_arr + (i + 1) * size;
            if (compar(p1, p2) > 0) {
                /* не отсортирован */
                printf("FAIL\n");
                return;
            }
    }
    /* отсортирован */
    printf("PASS\n");

}

/*
 *
 * <сводка>
 *   Функция тестирования Gnome Sort
 * </сводка>
 *
 */
static int16_t test_gnom_sort(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem){
    size_t nmemb;
    size_t elsize;
    int16_t result;
    int* int_arr;
    char* char_arr;
    double* double_arr;
    float* float_arr;
    long* long_arr;
    long long* long_long_arr;
    long double* long_double_arr;
    
    printf("=== Testing GnomeSort ===\n");
    
    printf("%-30s", "Test 1: Normal int sort");
    {
        nmemb = 6;
        elsize = sizeof(int);

        int_arr = (int*)pIMem->pVTbl->Alloc(pIMem, nmemb * elsize);

        int_arr[0] = 6;
        int_arr[1] = 2;
        int_arr[2] = 1;
        int_arr[3] = 5;
        int_arr[4] = 0;
        int_arr[5] = 8;
        
        result = pIEcoLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)int_arr, nmemb, elsize, cmp_int_asc_eco);
        
        if (result != 0){
            pIMem->pVTbl->Free(pIMem, int_arr);
            return ERR_ECO_FAIL;
        }

        check_is_sorted(int_arr, nmemb, elsize, cmp_int_asc_eco);

        pIMem->pVTbl->Free(pIMem, int_arr);
    }
    
    printf("%-30s", "Test 2: Already sorted array");
    {
        nmemb = 6;
        elsize = sizeof(int);

        int_arr = (int*)pIMem->pVTbl->Alloc(pIMem, nmemb * elsize);

        int_arr[0] = 1;
        int_arr[1] = 2;
        int_arr[2] = 3;
        int_arr[3] = 4;
        int_arr[4] = 5;
        int_arr[5] = 6;
        
        result = pIEcoLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)int_arr, nmemb, elsize, cmp_int_asc_eco);
        
        if (result != 0){
            pIMem->pVTbl->Free(pIMem, int_arr);
            return ERR_ECO_FAIL;
        }

        check_is_sorted(int_arr, nmemb, elsize, cmp_int_asc_eco);

        pIMem->pVTbl->Free(pIMem, int_arr);
    }
    
    printf("%-30s", "Test 3: Reverse order");
    {
        nmemb = 6;
        elsize = sizeof(int);

        int_arr = (int*)pIMem->pVTbl->Alloc(pIMem, nmemb * elsize);

        int_arr[0] = 6;
        int_arr[1] = 5;
        int_arr[2] = 4;
        int_arr[3] = 3;
        int_arr[4] = 2;
        int_arr[5] = 1;
        
        result = pIEcoLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)int_arr, nmemb, elsize, cmp_int_asc_eco);
        
        if (result != 0){
            pIMem->pVTbl->Free(pIMem, int_arr);
            return ERR_ECO_FAIL;
        }

        check_is_sorted(int_arr, nmemb, elsize, cmp_int_asc_eco);
        
        pIMem->pVTbl->Free(pIMem, int_arr);
    }
    
    printf("%-30s", "Test 4: Doubled element");
    {
        nmemb = 6;
        elsize = sizeof(int);

        int_arr = (int*)pIMem->pVTbl->Alloc(pIMem, nmemb * elsize);

        int_arr[0] = 3;
        int_arr[1] = 5;
        int_arr[2] = 4;
        int_arr[3] = 3;
        int_arr[4] = 2;
        int_arr[5] = 1;
        
        result = pIEcoLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)int_arr, nmemb, elsize, cmp_int_asc_eco);
        
        if (result != 0){
            pIMem->pVTbl->Free(pIMem, int_arr);
            return ERR_ECO_FAIL;
        }

        check_is_sorted(int_arr, nmemb, elsize, cmp_int_asc_eco);

        pIMem->pVTbl->Free(pIMem, int_arr);
    }
    
    printf("%-30s", "Test 5: One element");
    {
        nmemb = 1;
        elsize = sizeof(int);

        int_arr = (int*)pIMem->pVTbl->Alloc(pIMem, nmemb * elsize);

        int_arr[0] = 19;
        
        result = pIEcoLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)int_arr, nmemb, elsize, cmp_int_asc_eco);
        
        if (result != 0){
            pIMem->pVTbl->Free(pIMem, int_arr);
            return ERR_ECO_FAIL;
        }

        check_is_sorted(int_arr, nmemb, elsize, cmp_int_asc_eco);

        pIMem->pVTbl->Free(pIMem, int_arr);
    }
    
    printf("%-30s", "Test 6: Zero element");
    {
        nmemb = 0;
        elsize = sizeof(int);
        
        int_arr = (int*)pIMem->pVTbl->Alloc(pIMem, 1 * elsize);

        result = pIEcoLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)int_arr, 0, elsize, cmp_int_asc_eco);
        
        if (result != 0){
            pIMem->pVTbl->Free(pIMem, int_arr);
            return ERR_ECO_FAIL;
        }

        check_is_sorted(int_arr, nmemb, elsize, cmp_int_asc_eco);

        pIMem->pVTbl->Free(pIMem, int_arr);
    }
    
    printf("%-30s", "Test 7: Char elements");
    {
        nmemb = 5;
        elsize = sizeof(char);
        
        char_arr = (char*)pIMem->pVTbl->Alloc(pIMem, nmemb * elsize);
        /* Инициализация массива: {'n','i','y','a','z'} */
        char_arr[0] = 'n';
        char_arr[1] = 'i';
        char_arr[2] = 'y';
        char_arr[3] = 'a';
        char_arr[4] = 'z';
        
        result = pIEcoLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)char_arr, nmemb, elsize, cmp_char_asc_eco);
        
        if (result != 0){
            pIMem->pVTbl->Free(pIMem, char_arr);
            return ERR_ECO_FAIL;
        }

        check_is_sorted(char_arr, nmemb, elsize, cmp_char_asc_eco);
        /* Освобождение */
        pIMem->pVTbl->Free(pIMem, char_arr);
    }
    
    printf("%-30s", "Test 8: Double elements");
    {
        nmemb = 7;
        elsize = sizeof(double);
        
        double_arr = (double*)pIMem->pVTbl->Alloc(pIMem, nmemb * elsize);
        /* Инициализация массива: {0.1,1.2,2.3,36.6,19.007,0.00009,1975.127} */
        double_arr[0] = 0.1;
        double_arr[1] = 1.2;
        double_arr[2] = 2.3;
        double_arr[3] = 36.6;
        double_arr[4] = 19.007;
        double_arr[5] = 0.00009;
        double_arr[6] = 1975.127;
        
        result = pIEcoLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)double_arr, nmemb, elsize, cmp_double_asc_eco);
        
        if (result != 0){
            pIMem->pVTbl->Free(pIMem, double_arr);
            return ERR_ECO_FAIL;
        }

        check_is_sorted(double_arr, nmemb, elsize, cmp_double_asc_eco);

        pIMem->pVTbl->Free(pIMem, double_arr);
    }
    
    printf("%-30s", "Test 9: Float elements");
    {
        nmemb = 7;
        elsize = sizeof(float);
        float_arr = (float*)pIMem->pVTbl->Alloc(pIMem, nmemb * elsize);

        /* Инициализация массива: {0.1,1.2,2.3,36.6,19.007,0.00009,1975.127} */
        float_arr[0] = 0.1f;
        float_arr[1] = 1.2f;
        float_arr[2] = 2.3f;
        float_arr[3] = 36.6f;
        float_arr[4] = 19.007f;
        float_arr[5] = 0.00009f;
        float_arr[6] = 1975.127f;

        result = pIEcoLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)float_arr, nmemb, elsize, cmp_float_asc_eco);
        
        if (result != 0){
            pIMem->pVTbl->Free(pIMem, float_arr);
            return ERR_ECO_FAIL;
        }

        check_is_sorted(float_arr, nmemb, elsize, cmp_float_asc_eco);

        pIMem->pVTbl->Free(pIMem, float_arr);
    }
    
    printf("%-30s", "Test 10: Long elements");
    {
        nmemb = 7;
        elsize = sizeof(long);

        long_arr = (long*)pIMem->pVTbl->Alloc(pIMem, nmemb * elsize);

        long_arr[0] = 123456;
        long_arr[1] = -99999;
        long_arr[2] = 500;
        long_arr[3] = 123;
        long_arr[4] = 987654321;
        long_arr[5] = -100;
        long_arr[6] = 42;

        result = pIEcoLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)long_arr, nmemb, elsize, cmp_long_asc_eco);
        
        if (result != 0){
            pIMem->pVTbl->Free(pIMem, long_arr);
            return ERR_ECO_FAIL;
        }

        check_is_sorted(long_arr, nmemb, elsize, cmp_long_asc_eco);

        pIMem->pVTbl->Free(pIMem, long_arr);
    }
    
    printf("%-30s", "Test 11: Long long elements");
    {
        nmemb = 7;
        elsize = sizeof(long long);

        long_long_arr = (long long*)pIMem->pVTbl->Alloc(pIMem, nmemb * elsize);

        /* Инициализация массива целыми числами */
        long_long_arr[0] = 1234567890123LL;
        long_long_arr[1] = -99999999999LL;
        long_long_arr[2] = 500LL;
        long_long_arr[3] = 123LL;
        long_long_arr[4] = 987654321987LL;
        long_long_arr[5] = -100LL;
        long_long_arr[6] = 42LL;

        result = pIEcoLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)long_long_arr, nmemb, elsize, cmp_long_long_asc_eco);
        
        if (result != 0){
            pIMem->pVTbl->Free(pIMem, long_long_arr);
            return ERR_ECO_FAIL;
        }

        check_is_sorted(long_long_arr, nmemb, elsize, cmp_long_long_asc_eco);

        pIMem->pVTbl->Free(pIMem, long_long_arr);
    }
    
    printf("%-30s", "Test 12: Long double elements");
    {
        nmemb = 7;
        elsize = sizeof(long double);

        long_double_arr = (long double*)pIMem->pVTbl->Alloc(pIMem, nmemb * elsize);

        long_double_arr[0] = 123456.7890123L;
        long_double_arr[1] = -99999.99999L;
        long_double_arr[2] = 500.0L;
        long_double_arr[3] = 123.456L;
        long_double_arr[4] = 987654.321987L;
        long_double_arr[5] = -100.001L;
        long_double_arr[6] = 42.42L;

        result = pIEcoLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)long_double_arr, nmemb, elsize, cmp_long_double_asc_eco);
        
        if (result != 0){
            pIMem->pVTbl->Free(pIMem, long_double_arr);
            return ERR_ECO_FAIL;
        }

        /* Проверка: массив должен быть неубывающим */
        check_is_sorted(long_double_arr, nmemb, elsize, cmp_long_double_asc_eco);

        pIMem->pVTbl->Free(pIMem, long_double_arr);
    }
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция сравнения скорости алгоритмов qsort и gnome sort (int)
 * </сводка>
 *
 */
static int16_t compare_qsort_gnome_int(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem, size_t nmemb) {
    size_t index;
    int16_t result;
    int* arr1;
    int* arr2;
    clock_t t1, t2;
    size_t elsize = sizeof(int);

    /* Выделяем память через Eco allocator */
    arr1 = (int*)pIMem->pVTbl->Alloc(pIMem, nmemb * elsize);
    arr2 = (int*)pIMem->pVTbl->Alloc(pIMem, nmemb * elsize);

    if (!arr1 || !arr2) {
        printf("Memory allocation failed\n");
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    /* Инициализация случайными числами (или любыми данными) */
    for (index = 0; index < nmemb; ++index) {
        int val = (int)(rand() % 100000);
        arr1[index] = val;
        arr2[index] = val;
    }

    /* Замер времени GnomeSort */
    t1 = clock();
    result = pIEcoLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)arr1, nmemb, elsize, cmp_int_asc_eco);
    t1 = clock() - t1;
    
    if (result != 0){
        pIMem->pVTbl->Free(pIMem, arr1);
        pIMem->pVTbl->Free(pIMem, arr2);
        return ERR_ECO_FAIL;
    }

    /* Замер времени qsort */
    t2 = clock();
    qsort(arr2, nmemb, elsize, cmp_int_asc);
    t2 = clock() - t2;

    printf("GnomeSort time: %.3f ms\n", ((double)t1) / CLOCKS_PER_SEC * 1000);
    printf("Qsort     time: %.3f ms\n", ((double)t2) / CLOCKS_PER_SEC * 1000);

    /* Освобождение памяти */
    pIMem->pVTbl->Free(pIMem, arr1);
    pIMem->pVTbl->Free(pIMem, arr2);
    
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция сравнения скорости алгоритмов qsort и gnome sort (double)
 * </сводка>
 *
 */
static int16_t compare_qsort_gnome_double(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem, size_t nmemb) {
    size_t index;
    int16_t result;
    double* arr1;
    double* arr2;
    clock_t t1, t2;
    size_t elsize = sizeof(double);
    double val;

    /* Выделяем память через Eco allocator */
    arr1 = (double*)pIMem->pVTbl->Alloc(pIMem, nmemb * elsize);
    arr2 = (double*)pIMem->pVTbl->Alloc(pIMem, nmemb * elsize);

    if (!arr1 || !arr2) {
        printf("Memory allocation failed\n");
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    /* Инициализация случайными вещественными числами */
    for (index = 0; index < nmemb; ++index) {
        val = ((double)rand() / (double)RAND_MAX) * 100000.0; /* от 0.0 до 100000.0 */
        arr1[index] = val;
        arr2[index] = val;
    }

    /* Замер времени GnomeSort */
    t1 = clock();
    result = pIEcoLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)arr1, nmemb, elsize, cmp_double_asc_eco);
    t1 = clock() - t1;
    
    if (result != 0){
        pIMem->pVTbl->Free(pIMem, arr1);
        pIMem->pVTbl->Free(pIMem, arr2);
        return ERR_ECO_FAIL;
    }

    /* Замер времени qsort */
    t2 = clock();
    qsort(arr2, nmemb, elsize, cmp_double_asc);
    t2 = clock() - t2;

    printf("GnomeSort time: %.6f ms\n", ((double)t1) / CLOCKS_PER_SEC * 1000);
    printf("Qsort     time: %.6f ms\n", ((double)t2) / CLOCKS_PER_SEC * 1000);

    /* Освобождение памяти */
    pIMem->pVTbl->Free(pIMem, arr1);
    pIMem->pVTbl->Free(pIMem, arr2);
    
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция сравнения скорости алгоритмов
 * </сводка>
 *
 */
static int16_t compare_sort_algorithms(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem){
    size_t count_sizes = 16;
    size_t index_size;
    size_t sizes[16];
    
    sizes[0] = 10;
    sizes[1] = 30;
    sizes[2] = 50;
    sizes[3] = 70;
    sizes[4] = 90;
    sizes[5] = 100;
    sizes[6] = 200;
    sizes[7] = 300;
    sizes[8] = 400;
    sizes[9] = 500;
    sizes[10] = 1000;
    sizes[11] = 2500;
    sizes[12] = 5000;
    sizes[13] = 7500;
    sizes[14] = 10000;
    sizes[15] = 20000;

    printf(" === INTEGER === \n");
    for (index_size = 0; index_size < count_sizes; ++index_size){
        printf("---Size %d---\n", sizes[index_size]);
        compare_qsort_gnome_int(pIEcoLab1, pIMem, sizes[index_size]);
    }
    
    printf(" === DOUBLE === \n");
    for (index_size = 0; index_size < count_sizes; ++index_size){
        printf("---Size %d---\n", sizes[index_size]);
        compare_qsort_gnome_double(pIEcoLab1, pIMem, sizes[index_size]);
    }
    return ERR_ECO_SUCCESES;
}


static int test_lab2(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    int32_t result;
    size_t arr[3];
    size_t elsize = sizeof(int);
    IEcoCalculatorX* pIX;
    IEcoCalculatorY* pIY;
    IEcoLab1* pLab1;
    void* tmp;
    IEcoUnknown* pUnk;

    pIX = (IEcoCalculatorX*)0;
    pIY = (IEcoCalculatorY*)0;
    pLab1 = (IEcoLab1*)0;

    result = pIEcoLab1->pVTbl->Addition(pIEcoLab1, 100, 101);
    printf("Addition: 10 + 101 = %d\n", (int)result);
    result = pIEcoLab1->pVTbl->Subtraction(pIEcoLab1, 19, 4);
    printf("Subtraction: 19 - 4 = %d\n", (int)result);
    result = pIEcoLab1->pVTbl->Multiplication(pIEcoLab1, 10, 15);
    printf("Multiplication: 10 * 15 = %d\n", (int)result);
    result = pIEcoLab1->pVTbl->Division(pIEcoLab1, 15, 5);
    printf("Division: 300 / 100 = %d\n", (int)result);


    if (pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX) == 0 && pIX) {
        result = pIX->pVTbl->Addition(pIX, 10, 19);
        printf("IEcoCalculatorX Addition: 10 + 19 = %d\n", (int)result);
        pIX->pVTbl->Release(pIX);
        pIX = (IEcoCalculatorX*)0;
    }
    else {
        printf("IEcoCalculatorX NOT AVAILABLE from Lab2\n");
    }

    if (pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIY) == 0 && pIY) {
        result = pIY->pVTbl->Multiplication(pIY, 15, 3);
        printf("IEcoCalculatorY Multiplication: 15 * 3 = %d\n", (int)result);
        pIY->pVTbl->Release(pIY);
        pIY = (IEcoCalculatorY*)0;
    }
    else {
        printf("IEcoCalculatorY NOT AVAILABLE from Lab2\n");
    }
    
    
    if (pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX) == 0 && pIX) {
        printf("%-35s", "Aggragation IEcoCalculatorX:");
        result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorX, &tmp);
        if (result == 0){
            pUnk = (IEcoUnknown*)tmp;
            pUnk->pVTbl->Release(pUnk);
            printf("PASS\n");
        }
        else {
            printf("FAIL\n");
        }
    }
    
        
    if (pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX) == 0 && pIX) {
        if (pIX->pVTbl->QueryInterface(pIX, &IID_IEcoLab1, (void**)&pLab1) == 0 && pLab1) {
            arr[0] = 10;
            arr[1] = 30;
            arr[2] = 50;
            result = pLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)arr, 3, elsize, cmp_int_asc_eco);
            printf("%-35s", "CalculatorX -> IEcoLab1(Lab2):");
            check_is_sorted(arr, 3, elsize, cmp_int_asc_eco);
        }
    }
    
    if (pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIY) == 0 && pIY) {
        if (pIY->pVTbl->QueryInterface(pIY, &IID_IEcoLab1, (void**)&pLab1) == 0 && pLab1) {
            arr[0] = 10;
            arr[1] = 30;
            arr[2] = 50;
            result = pLab1->pVTbl->GnomeSort(pIEcoLab1, (void*)arr, 3, elsize, cmp_int_asc_eco);
            printf("%-35s", "CalculatorY -> IEcoLab1(Lab2):");
            check_is_sorted(arr, 3, elsize, cmp_int_asc_eco);
        }
    }
    
    return 0;
}

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */

int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    printf("=== Lab1 ===\n");
    result = test_gnom_sort(pIEcoLab1, pIMem);
    if (result!=0){
        goto Release;
    }
    
    result = compare_sort_algorithms(pIEcoLab1, pIMem);
    if (result!=0){
        goto Release;
    }
    
    printf("=== Lab2 ===\n");
    test_lab2(pIEcoLab1, pIMem);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}
