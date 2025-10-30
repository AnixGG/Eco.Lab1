/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoCalculatorD
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoCalculatorD
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoCalculatorD.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoCalculatorY
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoCalculatorD_QueryInterface(/* in */ IEcoCalculatorY* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoCalculatorD* pCMe = (CEcoCalculatorD*)((uint8_t*)me - offsetof(CEcoCalculatorD, m_pVTblIY));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoCalculatorY) ) {
        *ppv = &pCMe->m_pVTblIY;
        pCMe->m_pVTblIY->AddRef((IEcoCalculatorY*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIY;
        pCMe->m_pVTblIY->AddRef((IEcoCalculatorY*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoCalculatorY
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoCalculatorD_AddRef(/* in */ IEcoCalculatorY* me) {
    CEcoCalculatorD* pCMe = (CEcoCalculatorD*)((uint8_t*)me - offsetof(CEcoCalculatorD, m_pVTblIY));

    /* Проверка указателя */
    if (me == 0 ) {
        return 0;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoCalculatorY
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoCalculatorD_Release(/* in */ IEcoCalculatorY* me) {
    CEcoCalculatorD* pCMe = (CEcoCalculatorD*)((uint8_t*)me - offsetof(CEcoCalculatorD, m_pVTblIY));

    /* Проверка указателя */
    if (me == 0 ) {
        return 0;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoCalculatorD((IEcoCalculatorY*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Multiplication
 * </сводка>
 *
 */
static int32_t ECOCALLMETHOD CEcoCalculatorD_Multiplication(/* in */ IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoCalculatorD* pCMe = (CEcoCalculatorD*)((uint8_t*)me - offsetof(CEcoCalculatorD, m_pVTblIY));
    
    if (me == 0 ) {
        return -1;
    }
    
    printf("EcoCalculatorD: Multiplication called with %d * %d\n", a, b);
    return (int32_t)a * b;
}

/*
 *
 * <сводка>
 *   Функция Division
 * </сводка>
 *
 */
static int16_t ECOCALLMETHOD CEcoCalculatorD_Division(/* in */ IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoCalculatorD* pCMe = (CEcoCalculatorD*)((uint8_t*)me - offsetof(CEcoCalculatorD, m_pVTblIY));
    
    if (me == 0 ) {
        return -1;
    }
    
    if (b == 0) {
        printf("EcoCalculatorD: Division by zero error\n");
        return 0;
    }
    
    printf("EcoCalculatorD: Division called with %d / %d\n", a, b);
    return (int16_t)(a / b);
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoCalculatorD(/*in*/ IEcoCalculatorY* me, /* in */ IEcoUnknown *pIUnkSystem) {
    CEcoCalculatorD* pCMe = (CEcoCalculatorD*)((uint8_t*)me - offsetof(CEcoCalculatorD, m_pVTblIY));

    /* Проверка указателей */
    if (me == 0 || pIUnkSystem == 0) {
        return -1;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    return ERR_ECO_SUCCESES;
}

/* Create Virtual Table IEcoCalculatorY */
static IEcoCalculatorYVTbl g_xBD6414C29096423EA90C04D77AFD1CADVTbl = {
    CEcoCalculatorD_QueryInterface,
    CEcoCalculatorD_AddRef,
    CEcoCalculatorD_Release,
    CEcoCalculatorD_Multiplication,
    CEcoCalculatorD_Division
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoCalculatorD(/* in */ IEcoUnknown* pIUnkSystem, /* out */ IEcoCalculatorY** ppIEcoCalculatorY) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoCalculatorD* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    /* Проверка указателей */
    if (ppIEcoCalculatorY == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoCalculatorD*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoCalculatorD));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса */
    pCMe->m_pVTblIY = &g_xBD6414C29096423EA90C04D77AFD1CADVTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    result = initCEcoCalculatorD((IEcoCalculatorY*)pCMe, pIUnkSystem);
    if (result != 0) {
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Возврат указателя на интерфейс */
    *ppIEcoCalculatorY = (IEcoCalculatorY*)&pCMe->m_pVTblIY;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoCalculatorD(/* in */ IEcoCalculatorY* pIEcoCalculatorY) {
    CEcoCalculatorD* pCMe = (CEcoCalculatorD*)((uint8_t*)pIEcoCalculatorY - offsetof(CEcoCalculatorD, m_pVTblIY));
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoCalculatorY != 0 ) {
        pIMem = pCMe->m_pIMem;
        
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}