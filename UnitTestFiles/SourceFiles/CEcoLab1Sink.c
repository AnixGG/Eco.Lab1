/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1Sink
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1Sink
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */
/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1Sink
 * </сводка>
 */

#include "CEcoLab1Sink.h"
#include "IEcoConnectionPointContainer.h"
#include <stdio.h>

/*
 * Функция QueryInterface
 */
int16_t ECOCALLMETHOD CEcoLab1Sink_QueryInterface(/* in */ struct IEcoLab1Events* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    if (IsEqualUGUID(riid, &IID_IEcoLab1Events) || IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return 0;
    }
    *ppv = 0;
    return -1;
}

/*
 * Функция AddRef
 */
uint32_t ECOCALLMETHOD CEcoLab1Sink_AddRef(/* in */ struct IEcoLab1Events* me) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;
    if (me == 0) return -1;
    return ++pCMe->m_cRef;
}

/*
 * Функция Release
 */
uint32_t ECOCALLMETHOD CEcoLab1Sink_Release(/* in */ struct IEcoLab1Events* me) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;
    if (me == 0) return -1;
    if (--pCMe->m_cRef == 0) {
        deleteCEcoLab1Sink(me);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 * Реализация методов интерфейса событий
 */

int16_t ECOCALLMETHOD CEcoLab1Sink_OnSortStart(struct IEcoLab1Events* me, void* sender) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;
    printf("[%s] Event: OnSortStart\n", pCMe->m_Name);
    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1Sink_OnSortSwap(struct IEcoLab1Events* me, void* sender, uint32_t indexA, uint32_t indexB) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;
    printf("[%s] Event: OnSortSwap. Swapped indexes: %d <-> %d\n", pCMe->m_Name, indexA, indexB);
    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1Sink_OnSortEnd(struct IEcoLab1Events* me, void* sender) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;
    printf("[%s] Event: OnSortEnd\n", pCMe->m_Name);
    return 0;
}

/* Таблица функций */
IEcoLab1EventsVTbl g_xSinkVTbl = {
    CEcoLab1Sink_QueryInterface,
    CEcoLab1Sink_AddRef,
    CEcoLab1Sink_Release,
    CEcoLab1Sink_OnSortStart,
    CEcoLab1Sink_OnSortSwap,
    CEcoLab1Sink_OnSortEnd
};

/*
 * Функция Create
 */
int16_t ECOCALLMETHOD createCEcoLab1Sink(IEcoMemoryAllocator1* pIMem, char_t* Name, IEcoLab1Events** ppIEcoLab1Events) {
    CEcoLab1Sink* pCMe = 0;

    if (ppIEcoLab1Events == 0 || pIMem == 0) return -1;

    pCMe = (CEcoLab1Sink*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1Sink));
    pCMe->m_pIMem = pIMem;
    pCMe->m_pIMem->pVTbl->AddRef(pCMe->m_pIMem);
    pCMe->m_cRef = 1;
    pCMe->m_pVTblIEcoLab1Events = &g_xSinkVTbl;
    pCMe->m_Name = Name;

    *ppIEcoLab1Events = (IEcoLab1Events*)pCMe;

    return 0;
};

/*
 * Функция Delete
 */
void ECOCALLMETHOD deleteCEcoLab1Sink(IEcoLab1Events* pIEcoLab1Events) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)pIEcoLab1Events;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1Events != 0) {
        pIMem = pCMe->m_pIMem;
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
};
