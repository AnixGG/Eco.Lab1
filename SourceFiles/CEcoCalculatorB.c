/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoCalculatorB
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoCalculatorB
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
#include "CEcoCalculatorB.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoCalculatorX
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoCalculatorB_QueryInterface(/* in */ IEcoCalculatorX* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoCalculatorB* pCMe = (CEcoCalculatorB*)((uint8_t*)me - offsetof(CEcoCalculatorB, m_pVTblIX));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoCalculatorX) ) {
        *ppv = &pCMe->m_pVTblIX;
        pCMe->m_pVTblIX->AddRef((IEcoCalculatorX*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIX;
        pCMe->m_pVTblIX->AddRef((IEcoCalculatorX*)pCMe);
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
 *   Функция AddRef для интерфейса IEcoCalculatorX
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoCalculatorB_AddRef(/* in */ IEcoCalculatorX* me) {
    CEcoCalculatorB* pCMe = (CEcoCalculatorB*)((uint8_t*)me - offsetof(CEcoCalculatorB, m_pVTblIX));

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
 *   Функция Release для интерфейса IEcoCalculatorX
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoCalculatorB_Release(/* in */ IEcoCalculatorX* me) {
    CEcoCalculatorB* pCMe = (CEcoCalculatorB*)((uint8_t*)me - offsetof(CEcoCalculatorB, m_pVTblIX));

    /* Проверка указателя */
    if (me == 0 ) {
        return 0;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoCalculatorB((IEcoCalculatorX*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Addition
 * </сводка>
 *
 */
static int32_t ECOCALLMETHOD CEcoCalculatorB_Addition(/* in */ IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoCalculatorB* pCMe = (CEcoCalculatorB*)((uint8_t*)me - offsetof(CEcoCalculatorB, m_pVTblIX));
    
    if (me == 0 ) {
        return -1;
    }
    
    printf("EcoCalculatorB: Addition called with %d + %d\n", a, b);
    return (int32_t)a + b;
}

/*
 *
 * <сводка>
 *   Функция Subtraction
 * </сводка>
 *
 */
static int16_t ECOCALLMETHOD CEcoCalculatorB_Subtraction(/* in */ IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoCalculatorB* pCMe = (CEcoCalculatorB*)((uint8_t*)me - offsetof(CEcoCalculatorB, m_pVTblIX));
    
    if (me == 0 ) {
        return -1;
    }
    
    printf("EcoCalculatorB: Subtraction called with %d - %d\n", a, b);
    return (int16_t)(a - b);
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
int16_t ECOCALLMETHOD initCEcoCalculatorB(/*in*/ IEcoCalculatorX* me, /* in */ IEcoUnknown *pIUnkSystem) {
    CEcoCalculatorB* pCMe = (CEcoCalculatorB*)((uint8_t*)me - offsetof(CEcoCalculatorB, m_pVTblIX));

    /* Проверка указателей */
    if (me == 0 || pIUnkSystem == 0) {
        return -1;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    return ERR_ECO_SUCCESES;
}

/* Create Virtual Table IEcoCalculatorX */
static IEcoCalculatorXVTbl g_x9322111622484742AE0682819447843DVTbl = {
    CEcoCalculatorB_QueryInterface,
    CEcoCalculatorB_AddRef,
    CEcoCalculatorB_Release,
    CEcoCalculatorB_Addition,
    CEcoCalculatorB_Subtraction
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
int16_t ECOCALLMETHOD createCEcoCalculatorB(/* in */ IEcoUnknown* pIUnkSystem, /* out */ IEcoCalculatorX** ppIEcoCalculatorX) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoCalculatorB* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    /* Проверка указателей */
    if (ppIEcoCalculatorX == 0 || pIUnkSystem == 0) {
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
    pCMe = (CEcoCalculatorB*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoCalculatorB));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса */
    pCMe->m_pVTblIX = &g_x9322111622484742AE0682819447843DVTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    result = initCEcoCalculatorB((IEcoCalculatorX*)pCMe, pIUnkSystem);
    if (result != 0) {
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Возврат указателя на интерфейс */
    *ppIEcoCalculatorX = (IEcoCalculatorX*)&pCMe->m_pVTblIX;

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
void ECOCALLMETHOD deleteCEcoCalculatorB(/* in */ IEcoCalculatorX* pIEcoCalculatorX) {
    CEcoCalculatorB* pCMe = (CEcoCalculatorB*)((uint8_t*)pIEcoCalculatorX - offsetof(CEcoCalculatorB, m_pVTblIX));
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoCalculatorX != 0 ) {
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