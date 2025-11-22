/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1
 *   с поддержкой включения и агрегирования компонентов
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
#include "CEcoLab1.h"
#include "IEcoConnectionPointContainer.h"
#include "IEcoLab1Events.h"
#include "CEcoLab1ConnectionPoint.h"
#include "CEcoLab1EnumConnectionPoints.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab1
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_QueryInterface(/* in */ IEcoLab1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        if (pCMe->m_pInnerUnknown != 0) {
            return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
        }
        *ppv = &pCMe->m_pVTblIEcoCalculatorX;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY) ) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorY;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoConnectionPointContainer) ) {
        /* Поддержка интерфейса точки подключения */
        *ppv = &pCMe->m_pVTblICPC;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

/* --- Реализация вспомогательных интерфейсов --- */

static int16_t ECOCALLMETHOD CalculatorX_QueryInterface(/* in */ IEcoCalculatorX* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoUnknownPtr_t));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Делегируем основному QI */
    return CEcoLab1_QueryInterface((IEcoLab1*)pCMe, riid, ppv);
}

static int16_t ECOCALLMETHOD CalculatorY_QueryInterface(/* in */ IEcoCalculatorY* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 2 * sizeof(IEcoUnknownPtr_t));

    if (me == 0 || ppv == 0) {
        return -1;
    }

    return CEcoLab1_QueryInterface((IEcoLab1*)pCMe, riid, ppv);
}

/* Реализация IEcoConnectionPointContainer (CPC) */
static int16_t ECOCALLMETHOD CEcoLab1_CPC_QueryInterface(struct IEcoConnectionPointContainer* me, const UGUID* riid, void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 3 * sizeof(IEcoUnknownPtr_t));
    return CEcoLab1_QueryInterface((IEcoLab1*)pCMe, riid, ppv);
}

static uint32_t ECOCALLMETHOD CEcoLab1_CPC_AddRef(struct IEcoConnectionPointContainer* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 3 * sizeof(IEcoUnknownPtr_t));
    return pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
}

static uint32_t ECOCALLMETHOD CEcoLab1_CPC_Release(struct IEcoConnectionPointContainer* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 3 * sizeof(IEcoUnknownPtr_t));
    return pCMe->m_pVTblIEcoLab1->Release((IEcoLab1*)pCMe);
}

static int16_t ECOCALLMETHOD CEcoLab1_CPC_EnumConnectionPoints(struct IEcoConnectionPointContainer* me, struct IEcoEnumConnectionPoints **ppEnum) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 3 * sizeof(IEcoUnknownPtr_t));
    int16_t result = 0;

    if (me == 0 || ppEnum == 0) {
        return ERR_ECO_POINTER;
    }

    result = createCEcoLab1EnumConnectionPoints((IEcoUnknown*)pCMe->m_pISys,
                                              (struct IEcoConnectionPoint*)pCMe->m_pISinkCP,
                                              ppEnum);

    return result;
}

static int16_t ECOCALLMETHOD CEcoLab1_CPC_FindConnectionPoint(struct IEcoConnectionPointContainer* me, const UGUID* riid, struct IEcoConnectionPoint **ppCP) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 3 * sizeof(IEcoUnknownPtr_t));
    int16_t result = 0;

    if (me == 0 || ppCP == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверяем, запрашивают ли точку подключения для нашего интерфейса событий */
    if (IsEqualUGUID(riid, &IID_IEcoLab1Events)) {
        *ppCP = (struct IEcoConnectionPoint*)pCMe->m_pISinkCP;
        (*ppCP)->pVTbl->AddRef(*ppCP);
        result = 0;
    }
    else {
        *ppCP = 0;
        result = -1;
    }

    return result;
}


static uint32_t ECOCALLMETHOD CEcoLab1_AddRef(/* in */ IEcoLab1Ptr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CalculatorX_AddRef(/* in */ IEcoCalculatorX* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoUnknownPtr_t));;

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CalculatorY_AddRef(/* in */ IEcoCalculatorY* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 2 * sizeof(IEcoUnknownPtr_t));;

    /* Проверка указателя */
    if (me == 0) {
        return -1;
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
 *   Функция Release для интерфейса IEcoLab1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_Release(/* in */ IEcoLab1Ptr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CalculatorX_Release(/* in */ IEcoCalculatorX* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoUnknownPtr_t));

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CalculatorY_Release(/* in */ IEcoCalculatorY* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 2 * sizeof(IEcoUnknownPtr_t));

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/* --- Делегирование методов калькулятора (как в исходнике) --- */

static int32_t ECOCALLMETHOD CalculatorX_Addition(IEcoCalculatorX* me, int16_t x, int16_t y) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoUnknownPtr_t));
    int32_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return result;
    }

    if (pCMe->m_pIEcoCalculatorX != NULL) {
        return pCMe->m_pIEcoCalculatorX->pVTbl->Addition(pCMe->m_pIEcoCalculatorX, x, y);
    }
    return result;
}

static int16_t ECOCALLMETHOD CalculatorX_Subtraction(IEcoCalculatorX* me, int16_t x, int16_t y) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoUnknownPtr_t));
    int32_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return result;
    }

    if (pCMe->m_pIEcoCalculatorX != NULL) {
        return pCMe->m_pIEcoCalculatorX->pVTbl->Subtraction(pCMe->m_pIEcoCalculatorX, x, y);
    }
    return result;
}

static int32_t ECOCALLMETHOD CalculatorY_Multiplication(/* in */ IEcoCalculatorY* me, /* in */ int16_t x, /* in */ int16_t y) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 2 * sizeof(IEcoUnknownPtr_t));
    int32_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return result;
    }

    if (pCMe->m_pIEcoCalculatorY != NULL) {
        return pCMe->m_pIEcoCalculatorY->pVTbl->Multiplication(pCMe->m_pIEcoCalculatorY, x, y);
    }
    return result;
}

static int16_t ECOCALLMETHOD CalculatorY_Division(/* in */ IEcoCalculatorY* me, /* in */ int16_t x, /* in */ int16_t y) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 2 * sizeof(IEcoUnknownPtr_t));
    int32_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return result;
    }

    if (pCMe->m_pIEcoCalculatorY != NULL) {
        return pCMe->m_pIEcoCalculatorY->pVTbl->Division(pCMe->m_pIEcoCalculatorY, x, y);
    }
    return result;
}


/*
 *
 * <сводка>
 *   Функция побайтового копирования
 * </сводка>
 *
 */
static void ECOCALLMETHOD eco_memcpy(char_t* dest, const char_t* src, size_t n) {
    while (n != 0) {
        *dest++ = *src++;
        --n;
    }
}


/* --- Вспомогательные функции отправки событий (Fire Events) --- */

/* Отправка события начала сортировки */
void CEcoLab1_Fire_OnSortStart(CEcoLab1* me) {
    IEcoEnumConnections* pEnum = 0;
    IEcoLab1Events* pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0 || me->m_pISinkCP == 0) {
        return;
    }

    if (me->m_pISinkCP->m_pVTblICP->EnumConnections((struct IEcoConnectionPoint*)me->m_pISinkCP, &pEnum) == 0) {
        while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
            if (cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void**)&pIEvents) == 0) {
                pIEvents->pVTbl->OnSortStart(pIEvents, me);
                pIEvents->pVTbl->Release(pIEvents);
            }
            cd.pUnk->pVTbl->Release(cd.pUnk);
        }
        pEnum->pVTbl->Release(pEnum);
    }
}

/* Отправка события обмена элементов */
void CEcoLab1_Fire_OnSortSwap(CEcoLab1* me, uint32_t indexA, uint32_t indexB) {
    IEcoEnumConnections* pEnum = 0;
    IEcoLab1Events* pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0 || me->m_pISinkCP == 0) {
        return;
    }

    if (me->m_pISinkCP->m_pVTblICP->EnumConnections((struct IEcoConnectionPoint*)me->m_pISinkCP, &pEnum) == 0) {
