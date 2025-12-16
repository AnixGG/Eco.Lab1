/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoMemoryAllocator1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов IEcoMemoryAllocator1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "CEcoMemoryManager1Lab.h"


/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoMemoryAllocator1
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_QueryInterface(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));

    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoMemoryManager1) ) {
        *ppv = &pCMe->m_pVTblIMgr;
        pCMe->m_pVTblIMgr->AddRef((IEcoMemoryManager1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoMemoryAllocator1) ) {
        *ppv = &pCMe->m_pVTblIMem;
        pCMe->m_pVTblIMgr->AddRef((IEcoMemoryManager1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoVirtualMemory1) ) {
        *ppv = &pCMe->m_pVTblIVirtual;
        pCMe->m_pVTblIMgr->AddRef((IEcoMemoryManager1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIMgr;
        pCMe->m_pVTblIMgr->AddRef((IEcoMemoryManager1*)pCMe);
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
 *   Функция AddRef для интерфейса IEcoMemoryAllocator1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_AddRef(/* in */ IEcoMemoryAllocator1Ptr_t me) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));

    if (me == 0 ) {
        return -1;
    }

    return atomicincrement_int32_t(&pCMe->m_cRef);
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoMemoryAllocator1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_Release(/* in */ IEcoMemoryAllocator1Ptr_t me) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));

    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    atomicdecrement_int32_t(&pCMe->m_cRef);

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoMemoryManager1Lab_623E1838((IEcoMemoryManager1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Alloc
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void* ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_Alloc(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ uint32_t size) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));
    
    MemoryHeader* pCurr = 0;
    MemoryHeader* pBestFit = 0;
    MemoryHeader* pNewBlock = 0;
    uint32_t bestSize = 0xFFFFFFFF; /* Инициализируем максимальным значением */
    
    
    if (me == 0 || size == 0 || pCMe->m_pHeapStart == 0) {
        return 0;
    }


    if (size % sizeof(voidptr_t) != 0) {
        size += (sizeof(voidptr_t) - (size % sizeof(voidptr_t)));
    }
    
    pCurr = (MemoryHeader*)pCMe->m_pHeapStart;
    
    while (pCurr != 0) {
        /* Если блок свободен и его размер достаточен */
        if (pCurr->bFree && pCurr->size >= size) {
            
            if (pCurr->size == size) {
                pBestFit = pCurr;
                break;
            }
            
            if (pCurr->size < bestSize) {
                pBestFit = pCurr;
                bestSize = pCurr->size;
            }
        }
        pCurr = pCurr->pNext;
    }
    
    if (pBestFit == 0) {
            return 0;
    }
    
    
    if (pBestFit->size >= size + sizeof(MemoryHeader) + 4) {
        char_t* pNextBlockAddr = (char_t*)((char_t*)pBestFit + sizeof(MemoryHeader) + size);
        
        pNewBlock = (MemoryHeader*)pNextBlockAddr;
        

        pNewBlock->bFree = 1;
        pNewBlock->pNext = pBestFit->pNext;
        pNewBlock->size = pBestFit->size - size - sizeof(MemoryHeader);
        
    
        pBestFit->size = size;
        pBestFit->pNext = pNewBlock;
    }
    
    
    pBestFit->bFree = 0;
    pCMe->m_iAllocSize += pBestFit->size;
    

    return (void*)((char_t*)pBestFit + sizeof(MemoryHeader));
    //return pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, size);

}

/*
 *
 * <сводка>
 *   Функция Free
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_Free(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pv) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));
    
    MemoryHeader* pHeader = 0;
    MemoryHeader* pCurr = 0;

    if (me == 0 || pv == 0 || pCMe->m_pHeapStart == 0) {
        return;
    }
    
    pHeader = (MemoryHeader*)((char_t*)pv - sizeof(MemoryHeader));

    
    if (pHeader->bFree) {
        
        return;
    }
    
    
    pHeader->bFree = 1;
    pCMe->m_iAllocSize -= pHeader->size;

    /* Склейка соседних свободных блоков */
    pCurr = (MemoryHeader*)pCMe->m_pHeapStart;
    
    while (pCurr != 0 && pCurr->pNext != 0) {
        if (pCurr->bFree && pCurr->pNext->bFree) {
            pCurr->size += sizeof(MemoryHeader) + pCurr->pNext->size;
            pCurr->pNext = pCurr->pNext->pNext;
            
            } else {
            pCurr = pCurr->pNext;
        }
    }
    
    //pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pv);
}

void* ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_Copy(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pvDst, /* in */ voidptr_t pvSrc, /* in */ uint32_t size) {
    /*CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));*/
    char_t* dst = (char_t*)pvDst;
    char_t* src = (char_t*)pvSrc;
    uint32_t i;

    if (pvDst == 0 || pvSrc == 0) {
        return 0;
    }

    /* Простое побайтовое копирование */
    for (i = 0; i < size; i++) {
        dst[i] = src[i];
    }

    return pvDst;
}

void* ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_Realloc(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pv, /* in */ uint32_t size) {
    /*CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));*/
    void* newPtr = 0;
    MemoryHeader* pOldHeader = 0;
    uint32_t copySize = 0;

    if (pv == 0) {
        return CEcoMemoryAllocator1Lab_623E1838_Alloc(me, size);
    }

    if (size == 0) {
        CEcoMemoryAllocator1Lab_623E1838_Free(me, pv);
        return 0;
    }

    
    pOldHeader = (MemoryHeader*)((char_t*)pv - sizeof(MemoryHeader));

    newPtr = CEcoMemoryAllocator1Lab_623E1838_Alloc(me, size);

    if (newPtr != 0) {
        if (pOldHeader->size < size) {
            copySize = pOldHeader->size;
        } else {
            copySize = size;
        }


        CEcoMemoryAllocator1Lab_623E1838_Copy(me, newPtr, pv, copySize);

        CEcoMemoryAllocator1Lab_623E1838_Free(me, pv);
    }

    return newPtr;
}

void* ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_Fill(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pvDst, /* in */ char_t Fill, /* in */ uint32_t size) {
    /*CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));*/
    char_t* dst = (char_t*)pvDst;
    uint32_t i;

    if (pvDst == 0) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        dst[i] = Fill;
    }

    return pvDst;
}

int16_t ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_Compare(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pv1, /* in */ voidptr_t pv2, /* in */ uint32_t size) {
    /*CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));*/
    char_t* p1 = (char_t*)pv1;
    char_t* p2 = (char_t*)pv2;
    uint32_t i;

    if (pv1 == 0 || pv2 == 0) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        if (p1[i] != p2[i]) {
            return (p1[i] < p2[i]) ? -1 : 1;
        }
    }

    return 0;
}
