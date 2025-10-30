/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoCalculatorA
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoCalculatorA
 *   с поддержкой агрегирования
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2025 YourName. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoCalculatorA.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для агрегированного компонента
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoCalculatorA_QueryInterface(/* in */ IEcoCalculatorX* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoCalculatorA* pCMe = (CEcoCalculatorA*)((uint8_t*)me - offsetof(CEcoCalculatorA, m_pVTblIX));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoCalculatorX) ) {
        if (pCMe->m_pIUnkOuter != 0) {
            return pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
        } else {
            *ppv = &pCMe->m_pVTblIX;
            pCMe->m_pVTblIX->AddRef((IEcoCalculatorX*)pCMe);
        }
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoCalculatorY) ) {
        if (pCMe->m_pIUnkOuter != 0) {
            return pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
        } else {
            *ppv = &pCMe->m_pVTblIY;
            pCMe->m_pVTblIY->AddRef((IEcoCalculatorY*)pCMe);
        }
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        if (pCMe->m_pIUnkOuter != 0) {
            return pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
        } else {
            *ppv = &pCMe->m_pVTblIX;
            pCMe->m_pVTblIX->AddRef((IEcoCalculatorX*)pCMe);
        }
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
 *   Функция AddRef для агрегированного компонента
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoCalculatorA_AddRef(/* in */ IEcoCalculatorX* me) {
    CEcoCalculatorA* pCMe = (CEcoCalculatorA*)((uint8_t*)me - offsetof(CEcoCalculatorA, m_pVTblIX));

    /* Проверка указателя */
    if (me == 0 ) {
        return 0;
    }

    if (pCMe->m_pIUnkOuter != 0) {
        return pCMe->m_pIUnkOuter->pVTbl->AddRef(pCMe->m_pIUnkOuter);
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
 *   Функция Release для агрегированного компонента
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoCalculatorA_Release(/* in */ IEcoCalculatorX* me) {
    CEcoCalculatorA* pCMe = (CEcoCalculatorA*)((uint8_t*)me - offsetof(CEcoCalculatorA, m_pVTblIX));

    /* Проверка указателя */
    if (me == 0 ) {
        return 0;
    }

    if (pCMe->m_pIUnkOuter != 0) {
        return pCMe->m_pIUnkOuter->pVTbl->Release(pCMe->m_pIUnkOuter);
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoCalculatorA((IEcoCalculatorX*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция QueryInterface для IEcoCalculatorY
 * </сводка>
 *
 */
static int16_t ECOCALLMETHOD CEcoCalculatorA_Y_QueryInterface(/* in */ IEcoCalculatorY* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoCalculatorA* pCMe = (CEcoCalculatorA*)((uint8_t*)me - offsetof(CEcoCalculatorA, m_pVTblIY));
    return CEcoCalculatorA_QueryInterface((IEcoCalculatorX*)me, riid, ppv);
}

/*
 *
 * <сводка>
 *   Функция AddRef для IEcoCalculatorY
 * </сводка>
 *
 */
static uint32_t ECOCALLMETHOD CEcoCalculatorA_Y_AddRef(/* in */ IEcoCalculatorY* me) {
    CEcoCalculatorA* pCMe = (CEcoCalculatorA*)((uint8_t*)me - offsetof(CEcoCalculatorA, m_pVTblIY));
    return CEcoCalculatorA_AddRef((IEcoCalculatorX*)me);
}

/*
 *
 * <сводка>
 *   Функция Release для IEcoCalculatorY
 * </сводка>
 *
 */
static uint32_t ECOCALLMETHOD CEcoCalculatorA_Y_Release(/* in */ IEcoCalculatorY* me) {
    CEcoCalculatorA* pCMe = (CEcoCalculatorA*)((uint8_t*)me - offsetof(CEcoCalculatorA, m_pVTblIY));
    return CEcoCalculatorA_Release((IEcoCalculatorX*)me);
}

/*
 *
 * <сводка>
 *   Функция Addition
 * </сводка>
 *
 */
static int32_t ECOCALLMETHOD CEcoCalculatorA_Addition(/* in */ IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoCalculatorA* pCMe = (CEcoCalculatorA*)((uint8_t*)me - offsetof(CEcoCalculatorA, m_pVTblIX));
    
    if (me == 0 ) {
        return -1;
    }
    
    printf("EcoCalculatorA: Addition called with %d + %d\n", a, b);
    return (int32_t)a + b;
}

/*
 *
 * <сводка>
 *   Функция Subtraction
 * </сводка>
 *
 */
static int16_t ECOCALLMETHOD CEcoCalculatorA_Subtraction(/* in */ IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoCalculatorA* pCMe = (CEcoCalculatorA*)((uint8_t*)me - offsetof(CEcoCalculatorA, m_pVTblIX));
    
    if (me == 0 ) {
        return -1;
    }
    
    printf("EcoCalculatorA: Subtraction called with %d - %d\n", a, b);
    return (int16_t)(a - b);
}

/*
 *
 * <сводка>
 *   Функция Multiplication
 * </сводка>
 *
 */
static int32_t ECOCALLMETHOD CEcoCalculatorA_Multiplication(/* in */ IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoCalculatorA* pCMe = (CEcoCalculatorA*)((uint8_t*)me - offsetof(CEcoCalculatorA, m_pVTblIY));
    
    if (me == 0 ) {
        return -1;
    }
    
    printf("EcoCalculatorA: Multiplication called with %d * %d\n", a, b);
    return (int32_t)a * b;
}

/*
 *
 * <сводка>
 *   Функция Division
 * </сводка>
 *
 */
static int16_t ECOCALLMETHOD CEcoCalculatorA_Division(/* in */ IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoCalculatorA* pCMe = (CEcoCalculatorA*)((uint8_t*)me - offsetof(CEcoCalculatorA, m_pVTblIY));
    
    if (me == 0 ) {
        return -1;
    }
    
    if (b == 0) {
        printf("EcoCalculatorA: Division by zero error\n");
        return 0;
    }
    
    printf("EcoCalculatorA: Division called with %d / %d\n", a, b);
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
int16_t ECOCALLMETHOD initCEcoCalculatorA(/*in*/ IEcoCalculatorX* me, /* in */ IEcoUnknown *pIUnkSystem) {
    CEcoCalculatorA* pCMe = (CEcoCalculatorA*)((uint8_t*)me - offsetof(CEcoCalculatorA, m_pVTblIX));

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
    CEcoCalculatorA_QueryInterface,
    CEcoCalculatorA_AddRef,
    CEcoCalculatorA_Release,
    CEcoCalculatorA_Addition,
    CEcoCalculatorA_Subtraction
};

/* Create Virtual Table IEcoCalculatorY */
static IEcoCalculatorYVTbl g_xBD6414C29096423EA90C04D77AFD1CADVTbl = {
    CEcoCalculatorA_Y_QueryInterface,
    CEcoCalculatorA_Y_AddRef,
    CEcoCalculatorA_Y_Release,
    CEcoCalculatorA_Multiplication,
    CEcoCalculatorA_Division
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
int16_t ECOCALLMETHOD createCEcoCalculatorA(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoCalculatorX** ppIEcoCalculatorX) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoCalculatorA* pCMe = 0;
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
    pCMe = (CEcoCalculatorA*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoCalculatorA));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблиц функций интерфейсов */
    pCMe->m_pVTblIX = &g_x9322111622484742AE0682819447843DVTbl;
    pCMe->m_pVTblIY = &g_xBD6414C29096423EA90C04D77AFD1CADVTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;
    pCMe->m_pIUnkOuter = pIUnkOuter;  // Сохраняем внешний объект для агрегации

    result = initCEcoCalculatorA((IEcoCalculatorX*)pCMe, pIUnkSystem);
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
void ECOCALLMETHOD deleteCEcoCalculatorA(/* in */ IEcoCalculatorX* pIEcoCalculatorX) {
    CEcoCalculatorA* pCMe = (CEcoCalculatorA*)((uint8_t*)pIEcoCalculatorX - offsetof(CEcoCalculatorA, m_pVTblIX));
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