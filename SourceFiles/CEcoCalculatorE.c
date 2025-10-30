/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoCalculatorE
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoCalculatorE
 *   с поддержкой агрегирования
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
#include "CEcoCalculatorE.h"

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
static int16_t ECOCALLMETHOD CEcoCalculatorE_QueryInterface(/* in */ IEcoCalculatorY* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoCalculatorE* pCMe = (CEcoCalculatorE*)((uint8_t*)me - offsetof(CEcoCalculatorE, m_pVTblIY));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoCalculatorY) ) {
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
            *ppv = &pCMe->m_pVTblIY;
            pCMe->m_pVTblIY->AddRef((IEcoCalculatorY*)pCMe);
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
static uint32_t ECOCALLMETHOD CEcoCalculatorE_AddRef(/* in */ IEcoCalculatorY* me) {
    CEcoCalculatorE* pCMe = (CEcoCalculatorE*)((uint8_t*)me - offsetof(CEcoCalculatorE, m_pVTblIY));

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
static uint32_t ECOCALLMETHOD CEcoCalculatorE_Release(/* in */ IEcoCalculatorY* me) {
    CEcoCalculatorE* pCMe = (CEcoCalculatorE*)((uint8_t*)me - offsetof(CEcoCalculatorE, m_pVTblIY));

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
        deleteCEcoCalculatorE((IEcoCalculatorY*)pCMe);
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
static int32_t ECOCALLMETHOD CEcoCalculatorE_Multiplication(/* in */ IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoCalculatorE* pCMe = (CEcoCalculatorE*)((uint8_t*)me - offsetof(CEcoCalculatorE, m_pVTblIY));
    
    if (me == 0 ) {
        return -1;
    }
    
    printf("EcoCalculatorE: Multiplication called with %d * %d\n", a, b);
    return (int32_t)a * b;
}

/*
 *
 * <сводка>
 *   Функция Division
 * </сводка>
 *
 */
static int16_t ECOCALLMETHOD CEcoCalculatorE_Division(/* in */ IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoCalculatorE* pCMe = (CEcoCalculatorE*)((uint8_t*)me - offsetof(CEcoCalculatorE, m_pVTblIY));
    
    if (me == 0 ) {
        return -1;
    }
    
    if (b == 0) {
        printf("EcoCalculatorE: Division by zero error\n");
        return 0;
    }
    
    printf("EcoCalculatorE: Division called with %d / %d\n", a, b);
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
int16_t ECOCALLMETHOD initCEcoCalculatorE(/*in*/ IEcoCalculatorY* me, /* in */ IEcoUnknown *pIUnkSystem) {
    CEcoCalculatorE* pCMe = (CEcoCalculatorE*)((uint8_t*)me - offsetof(CEcoCalculatorE, m_pVTblIY));

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
    CEcoCalculatorE_QueryInterface,
    CEcoCalculatorE_AddRef,
    CEcoCalculatorE_Release,
    CEcoCalculatorE_Multiplication,
    CEcoCalculatorE_Division
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
int16_t ECOCALLMETHOD createCEcoCalculatorE(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoCalculatorY** ppIEcoCalculatorY) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoCalculatorE* pCMe = 0;
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
    pCMe = (CEcoCalculatorE*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoCalculatorE));

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
    pCMe->m_pIUnkOuter = pIUnkOuter;  // Сохраняем внешний объект для агрегации

    result = initCEcoCalculatorE((IEcoCalculatorY*)pCMe, pIUnkSystem);
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
void ECOCALLMETHOD deleteCEcoCalculatorE(/* in */ IEcoCalculatorY* pIEcoCalculatorY) {
    CEcoCalculatorE* pCMe = (CEcoCalculatorE*)((uint8_t*)pIEcoCalculatorY - offsetof(CEcoCalculatorE, m_pVTblIY));
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