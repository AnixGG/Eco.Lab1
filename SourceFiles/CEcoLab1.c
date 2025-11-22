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
#include "IEcoEnumConnections.h"

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

    /* Создаем перечислитель точек подключения */
    /* Передаем нашу точку подключения (m_pISinkCP), приводя её к интерфейсу */
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
        result = -1; /* CONNECT_E_NOCONNECTION */
    }

    return result;
}


static uint32_t ECOCALLMETHOD CEcoLab1_AddRef(/* in */ IEcoLab1Ptr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CalculatorX_AddRef(/* in */ IEcoCalculatorX* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(IEcoUnknownPtr_t));;

    /* Проверка указателя */
    if (me == 0) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CalculatorY_AddRef(/* in */ IEcoCalculatorY* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - 2 * sizeof(IEcoUnknownPtr_t));;

    /* Проверка указателя */
    if (me == 0) {
        return -1; /* ERR_ECO_POINTER */
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

    /* Уменьшение счетчика ссылок на компонент */
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
        while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
            if (cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void**)&pIEvents) == 0) {
                pIEvents->pVTbl->OnSortSwap(pIEvents, me, indexA, indexB);
                pIEvents->pVTbl->Release(pIEvents);
            }
            cd.pUnk->pVTbl->Release(cd.pUnk);
        }
        pEnum->pVTbl->Release(pEnum);
    }
}

/* Отправка события завершения сортировки */
void CEcoLab1_Fire_OnSortEnd(CEcoLab1* me) {
    IEcoEnumConnections* pEnum = 0;
    IEcoLab1Events* pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0 || me->m_pISinkCP == 0) {
        return;
    }

    if (me->m_pISinkCP->m_pVTblICP->EnumConnections((struct IEcoConnectionPoint*)me->m_pISinkCP, &pEnum) == 0) {
        while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
            if (cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void**)&pIEvents) == 0) {
                pIEvents->pVTbl->OnSortEnd(pIEvents, me);
                pIEvents->pVTbl->Release(pIEvents);
            }
            cd.pUnk->pVTbl->Release(cd.pUnk);
        }
        pEnum->pVTbl->Release(pEnum);
    }
}


/*
 *
 * <сводка>
 *   Функция GnomeSort
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */

static int16_t ECOCALLMETHOD CEcoLab1_GnomeSort(
                                             /* in */ IEcoLab1Ptr_t me,
                                             /* in */ void* base,
                                             /* in */ size_t nmemb,
                                             /* in */ size_t size,
                                             /* in */ int (*compar)(const void*, const void*)
                                             ) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoMemoryAllocator1* pIMem;
    char* arr = (char*)base;
    char_t* temp;
    size_t index = 0;
    void* p1;
    void* p2;
    

    /* Проверка указателей */
    if (me == 0 || base == 0 || compar == 0 || size == 0) {
        return ERR_ECO_POINTER;
    }
    
    if (nmemb < 2) {
        return ERR_ECO_SUCCESES;
    }
    
    pIMem = pCMe->m_pIMem;
    if (pIMem == 0 || pIMem->pVTbl == 0 || pIMem->pVTbl->Alloc == 0) {
        return ERR_ECO_POINTER;
    }
    
    temp = (char_t*)pIMem->pVTbl->Alloc(pIMem, size);
    if (temp == 0) {
        /* Нет памяти — выход */
        return ERR_ECO_POINTER;
    }

    /* Уведомление о начале сортировки */
    CEcoLab1_Fire_OnSortStart(pCMe);

    /* Запуск Gnome Sort */
    while (index < nmemb) {
        if (index==0) {
            index++;
        } else{
            p1 = (void*)(arr + index * size);
            p2 = (void*)(arr + (index - 1) * size);
            if (compar(p1, p2) >= 0){
                index++;
            } else{
                /* Обмен элементов */
                eco_memcpy(temp, p1, size);
                eco_memcpy(p1, p2, size);
                eco_memcpy(p2, temp, size);
                
                /* Уведомление о перестановке */
                CEcoLab1_Fire_OnSortSwap(pCMe, (uint32_t)index, (uint32_t)(index - 1));

                index--;
            }
            
        }
    }

    /* Уведомление о завершении сортировки */
    CEcoLab1_Fire_OnSortEnd(pCMe);

    /* Освобождаем временный буфер */
    pIMem->pVTbl->Free(pIMem, temp);
    return ERR_ECO_SUCCESES;
}

/* Create Virtual Table IEcoLab1 */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab1_QueryInterface,
    CEcoLab1_AddRef,
    CEcoLab1_Release,
    CEcoLab1_GnomeSort,
};

IEcoCalculatorXVTbl g_x9322111622484742AE0682819447843DVTbl = {
    CalculatorX_QueryInterface,
    CalculatorX_AddRef,
    CalculatorX_Release,
    CalculatorX_Addition,
    CalculatorX_Subtraction,
};

IEcoCalculatorYVTbl g_xBD6414C29096423EA90C04D77AFD1CADVTbl = {
    CalculatorY_QueryInterface,
    CalculatorY_AddRef,
    CalculatorY_Release,
    CalculatorY_Multiplication,
    CalculatorY_Division
};

IEcoConnectionPointContainerVTbl g_xCPC_VTbl = {
    CEcoLab1_CPC_QueryInterface,
    CEcoLab1_CPC_AddRef,
    CEcoLab1_CPC_Release,
    CEcoLab1_CPC_EnumConnectionPoints,
    CEcoLab1_CPC_FindConnectionPoint
};

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
int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ IEcoLab1Ptr_t me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoInterfaceBus1* pIBus = (IEcoInterfaceBus1*)0;
    int16_t result = -1;
    IEcoUnknown* pOuterUnknown = (IEcoUnknown*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    
    /* Включение IEcoCalculatorX  */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**)&pCMe->m_pIEcoCalculatorX);
    if (result != 0 || pCMe->m_pIEcoCalculatorX == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, 0, &IID_IEcoCalculatorX, (void**)&pCMe->m_pIEcoCalculatorX);
    }
    if (result != 0 || pCMe->m_pIEcoCalculatorX == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorC, 0, &IID_IEcoCalculatorX, (void**)&pCMe->m_pIEcoCalculatorX);
    }

    /* Включение IEcoCalculatorY  */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**)&pCMe->m_pIEcoCalculatorY);
    if (result != 0 || pCMe->m_pIEcoCalculatorY == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**)&pCMe->m_pIEcoCalculatorY);
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, pOuterUnknown, &IID_IEcoUnknown, (void**)&pCMe->m_pInnerUnknown);
    
    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return result;
}


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
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab1* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;
    
    /* Проверка указателей */
    if (ppIEcoLab1 == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void **)&pISys);

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
    pCMe = (CEcoLab1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLab1 */
    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;
    pCMe->m_pVTblIEcoCalculatorX = &g_x9322111622484742AE0682819447843DVTbl;
    pCMe->m_pVTblIEcoCalculatorY = &g_xBD6414C29096423EA90C04D77AFD1CADVTbl;
    
    /* Инициализация таблицы функций интерфейса IEcoConnectionPointContainer */
    pCMe->m_pVTblICPC = &g_xCPC_VTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    /* Создание точки подключения для интерфейса событий */
    /* Передаем адрес переменной m_pISinkCP (тип CEcoLab1ConnectionPoint*) */
    /* Функция createCEcoLab1ConnectionPoint принимает (IEcoConnectionPoint**), поэтому кастим */
    result = createCEcoLab1ConnectionPoint((IEcoUnknown*)pCMe->m_pISys,
                                           (IEcoConnectionPointContainer*)&pCMe->m_pVTblICPC,
                                           &IID_IEcoLab1Events,
                                           (IEcoConnectionPoint**)&pCMe->m_pISinkCP);

    /* Возврат указателя на интерфейс */
    *ppIEcoLab1 = (IEcoLab1*)pCMe;

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
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1* pIEcoLab1) {
    CEcoLab1* pCMe = (CEcoLab1*)pIEcoLab1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1 != 0 ) {
        pIMem = pCMe->m_pIMem;

        /* Освобождение точки подключения */
        if (pCMe->m_pISinkCP != 0) {
            /* Приводим к интерфейсу IUnknown для освобождения */
            ((IEcoUnknown*)pCMe->m_pISinkCP)->pVTbl->Release((IEcoUnknown*)pCMe->m_pISinkCP);
            pCMe->m_pISinkCP = 0;
        }

        /* Освобождение внешнего компонента X */
        if (pCMe->m_pIEcoCalculatorX != 0) {
            pCMe->m_pIEcoCalculatorX->pVTbl->Release(pCMe->m_pIEcoCalculatorX);
            pCMe->m_pIEcoCalculatorX = 0;
        }
        /* Освобождение внешнего компонента Y */
        if (pCMe->m_pIEcoCalculatorY != 0) {
            pCMe->m_pIEcoCalculatorY->pVTbl->Release(pCMe->m_pIEcoCalculatorY);
            pCMe->m_pIEcoCalculatorY = 0;
        }
        /* Освобождение агрегированного объекта B (его IUnknown) */
        if (pCMe->m_pInnerUnknown != 0) {
            pCMe->m_pInnerUnknown->pVTbl->Release(pCMe->m_pInnerUnknown);
            pCMe->m_pInnerUnknown = 0;
        }

        /* Освобождение остальных ресурсов */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        if (pIMem != 0) {
            pIMem->pVTbl->Free(pIMem, pCMe);
            pIMem->pVTbl->Release(pIMem);
        }
    }
}
