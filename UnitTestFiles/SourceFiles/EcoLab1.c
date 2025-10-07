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

/* Eco OS */
#include "IEcoSystem1.h"

#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"

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
    
    result = test_gnom_sort(pIEcoLab1, pIMem);
    if (result!=0){
        goto Release;
    }
    
    result = compare_sort_algorithms(pIEcoLab1, pIMem);
    if (result!=0){
        goto Release;
    }
    

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
