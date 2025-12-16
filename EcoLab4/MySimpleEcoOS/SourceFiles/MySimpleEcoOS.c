/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoVFB1
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

#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoMemoryManager1Lab.h"
#include "IEcoVirtualMemory1.h"
#include "IEcoTaskScheduler1.h"
#include "IdEcoTaskScheduler1Lab.h"
#include "IdEcoTimer1.h"
#include "IEcoSystemTimer1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "IdEcoIPCCMailbox1.h"
#include "IdEcoVFB1.h"
#include "IEcoVBIOS1Video.h"
#include "IdEcoMutex1Lab.h"
#include "IdEcoSemaphore1Lab.h"

 /* Начало свободного участка памяти */
extern char_t __heap_start__;

/* Глобальные указатели */
IEcoVBIOS1Video* g_pIVideo = 0;

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
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoMemoryManager1* pIMemMgr = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoVFB1* pIVFB = 0;
    ECO_VFB_1_SCREEN_MODE xScreenMode = { 0 };
    IEcoVBIOS1Video* pIVideo = 0;

    /* Переменные для теста Best Fit */
    char_t* ptrHuge = 0;
    char_t* ptrBarrier1 = 0;
    char_t* ptrMedium = 0;
    char_t* ptrBarrier2 = 0;
    char_t* ptrResult = 0;
    char_t* ptrHugeAddrSaved = 0;
    char_t* ptrMediumAddrSaved = 0;

    /* Переменные для теста Coalescing */
    char_t* ptrPart1 = 0;
    char_t* ptrPart2 = 0;
    char_t* ptrMerged = 0;
    char_t* ptrPart1Saved = 0;

    /* Переменные для Stress test*/
    char_t* ptrs[20] = {0};
    int16_t i = 0;
    int16_t passed = 1;
    char_t* pBig = 0;
    char_t* pMid1 = 0;
    char_t* pMid2 = 0;
    
    /* Создание экземпляра интерфейсной шины */
    result = GetIEcoComponentFactoryPtr_00000000000000000000000042757331->pVTbl->Alloc(GetIEcoComponentFactoryPtr_00000000000000000000000042757331, 0, 0, &IID_IEcoInterfaceBus1, (void**)&pIBus);
    if (result != 0 && pIBus == 0) {
        goto Release;
    }

    /* Регистрация менеджера памяти Lab */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoMemoryManager1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_0000000000000000000000004D656D31);
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoMemoryManager1Lab, (IEcoUnknown*)GetIEcoComponentFactoryPtr_81589BFED0B84B1194524BEE623E1838);

    /* Регистрация VFB и IPCC */
    pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoIPCCMailbox1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_F10BC39A4F2143CF8A1E104650A2C302);
    pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoVFB1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_939B1DCDB6404F7D9C072291AF252188);

    /* Настройка расширения памяти */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        pIMemExt->pVTbl->set_Manager(pIMemExt, &CID_EcoMemoryManager1Lab);
        pIMemExt->pVTbl->set_ExpandPool(pIMemExt, 1);
    }

    /* Получение интерфейса управления памятью (LAB) */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1Lab, 0, &IID_IEcoMemoryManager1, (void**)&pIMemMgr);
    if (result != 0 || pIMemMgr == 0) {
        return result;
    }

    /* Инициализация кучи */
    pIMemMgr->pVTbl->Init(pIMemMgr, &__heap_start__, 0x080000);

    /* Получение интерфейса аллокатора */
    result = pIMemMgr->pVTbl->QueryInterface(pIMemMgr, &IID_IEcoMemoryAllocator1, (void**)&pIMem);
    if (result != 0 || pIMem == 0) {
        goto Release;
    }

    /* Инициализация Видео */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoVFB1, 0, &IID_IEcoVFB1, (void**)&pIVFB);
    if (result != 0 || pIVFB == 0) {
        goto Release;
    }
    result = pIVFB->pVTbl->get_Mode(pIVFB, &xScreenMode);
    pIVFB->pVTbl->Create(pIVFB, 0, 0, xScreenMode.Width, xScreenMode.Height);
    result = pIVFB->pVTbl->QueryInterface(pIVFB, &IID_IEcoVBIOS1Video, (void**)&pIVideo);
    g_pIVideo = pIVideo;


    pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 0, CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE, "=== TEST 1: Best Fit ===", 24);

    ptrHuge = (char_t*)pIMem->pVTbl->Alloc(pIMem, 512);     // Большая дырка
    ptrBarrier1 = (char_t*)pIMem->pVTbl->Alloc(pIMem, 64);  // Барьер
    ptrMedium = (char_t*)pIMem->pVTbl->Alloc(pIMem, 256);   // Средняя дырка (Идеальная для теста)
    ptrBarrier2 = (char_t*)pIMem->pVTbl->Alloc(pIMem, 64);  // Барьер

    if (!ptrHuge || !ptrBarrier1 || !ptrMedium || !ptrBarrier2) {
        pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 1, CHARACTER_ATTRIBUTE_FORE_COLOR_RED, "Setup Failed: Alloc returned NULL", 31);
        goto TestEnd;
    }

    ptrHugeAddrSaved = ptrHuge;
    ptrMediumAddrSaved = ptrMedium;


    pIMem->pVTbl->Free(pIMem, ptrHuge);
    pIMem->pVTbl->Free(pIMem, ptrMedium);

    ptrResult = (char_t*)pIMem->pVTbl->Alloc(pIMem, 128);

    if (ptrResult == 0) {
        pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 2, CHARACTER_ATTRIBUTE_FORE_COLOR_RED, "FAIL: Alloc(128) returned NULL", 28);
    }
    else if (ptrResult == ptrMediumAddrSaved) {
        pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 2, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, "SUCCESS: Selected 256 hole (Best Fit)", 37);
    }
    else if (ptrResult == ptrHugeAddrSaved) {
        pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 2, CHARACTER_ATTRIBUTE_FORE_COLOR_RED, "FAIL: Selected 512 hole (First Fit?)", 36);
    }
    else {
        pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 2, CHARACTER_ATTRIBUTE_FORE_COLOR_YELLOW, "WARNING: New address (Split working?)", 35);
    }

    if(ptrResult) pIMem->pVTbl->Free(pIMem, ptrResult);
    if(ptrBarrier1) pIMem->pVTbl->Free(pIMem, ptrBarrier1);
    if(ptrBarrier2) pIMem->pVTbl->Free(pIMem, ptrBarrier2);

    //Тест для проверки, что при освобождении двух соседних блоков они объединяются в один большой.
    pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 4, CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE, "=== TEST 2: Coalescing ===", 26);

    ptrPart1 = (char_t*)pIMem->pVTbl->Alloc(pIMem, 200);
    ptrPart2 = (char_t*)pIMem->pVTbl->Alloc(pIMem, 200);
    ptrBarrier1 = (char_t*)pIMem->pVTbl->Alloc(pIMem, 64);

    ptrPart1Saved = ptrPart1;

    pIMem->pVTbl->Free(pIMem, ptrPart1);
    pIMem->pVTbl->Free(pIMem, ptrPart2);


    ptrMerged = (char_t*)pIMem->pVTbl->Alloc(pIMem, 350);

    if (ptrMerged != 0) {
        pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 5, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, "SUCCESS: Alloc(350) ok (Merged!)", 32);
        
        if (ptrMerged == ptrPart1Saved) {
             pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 6, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, "Address match: Reuse verified.", 30);
        }
        pIMem->pVTbl->Free(pIMem, ptrMerged);
    } else {
        pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 5, CHARACTER_ATTRIBUTE_FORE_COLOR_RED, "FAIL: Alloc(350) failed (No Merge)", 34);
    }
    
    if(ptrBarrier1) pIMem->pVTbl->Free(pIMem, ptrBarrier1);
    
    pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 8, CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE, "=== TEST 3: Swiss Cheese ===", 26);
    
    passed = 1;
    /*Выделяем массив мелких блоков (20 штук по 64 байта) */
    for (i = 0; i < 20; i++) {
        ptrs[i] = (char_t*)pIMem->pVTbl->Alloc(pIMem, 64);
        if (ptrs[i] == 0) {
            passed = 0;
        } else {
            
            pIMem->pVTbl->Fill(pIMem, ptrs[i], (char_t)i, 64);
        }
    }

    if (passed) {
        pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 9, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, "Alloc 20x64: OK", 15);
    } else {
        pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 9, CHARACTER_ATTRIBUTE_FORE_COLOR_RED, "Alloc 20x64: FAIL", 17);
    }
    
    for (i = 0; i < 20; i += 2) {
            if (ptrs[i]) {
                pIMem->pVTbl->Free(pIMem, ptrs[i]);
                ptrs[i] = 0;
        }
    }
    
    pBig = (char_t*)pIMem->pVTbl->Alloc(pIMem, 128);
        
    if (pBig) {
        pIMem->pVTbl->Free(pIMem, pBig);
        pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 10, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, "Alloc > Hole size: OK", 21);
    } else {
        pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 10, CHARACTER_ATTRIBUTE_FORE_COLOR_RED, "Alloc > Hole size: FAIL", 23);
    }
    
    /* Освобождаем оставшиеся блоки */
    passed = 1;

    for (i = 1; i < 20; i += 2) {
        if (ptrs[i]) {
            if (*ptrs[i] != (char_t)i) {
                passed = 0;
            }
            pIMem->pVTbl->Free(pIMem, ptrs[i]);
            ptrs[i] = 0;
        }
    }

    if (passed) {
        pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 11, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, "Data Check & Free: OK", 21);
    } else {
        pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 11, CHARACTER_ATTRIBUTE_FORE_COLOR_RED, "Data Check & Free: FAIL", 23);
    }
    pBig = (char_t*)pIMem->pVTbl->Alloc(pIMem, 10240);
    
    /* Полная дефрагментация */
    if (pBig) {
        pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 12, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, "Full Coalescing: OK", 19);
        pIMem->pVTbl->Free(pIMem, pBig);
    } else {
        pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 12, CHARACTER_ATTRIBUTE_FORE_COLOR_RED, "Full Coalescing: FAIL", 21);
    }
    
    pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 14, CHARACTER_ATTRIBUTE_FORE_COLOR_WHITTE, "=== TEST 4: Realloc ===", 23);

    pMid1 = (char_t*)pIMem->pVTbl->Alloc(pIMem, 32);
    if (pMid1) {
        /* Заполняем 'X' */
        pIMem->pVTbl->Fill(pIMem, pMid1, 'X', 32);

        /* Expand (Расширение до 128 байт) */
        /* Должен выделиться новый блок, данные скопироваться, старый удалиться */
        pBig = (char_t*)pIMem->pVTbl->Realloc(pIMem, pMid1, 128);
        
        if (pBig) {
            /* Проверяем, сохранились ли данные */
            if (*pBig == 'X') {
                pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 15, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, "Expand & Copy: OK", 17);
            } else {
                pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 15, CHARACTER_ATTRIBUTE_FORE_COLOR_RED, "Expand: BAD DATA", 16);
            }
       

            /* Shrink (Сужение до 16 байт) */
            pMid2 = (char_t*)pIMem->pVTbl->Realloc(pIMem, pBig, 16);
            
            if (pMid2) {
                if (*pMid2 == 'X') {
                    pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 16, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, "Shrink: OK", 10);
                } else {
                    pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 16, CHARACTER_ATTRIBUTE_FORE_COLOR_RED, "Shrink: BAD DATA", 16);
                }
                pIMem->pVTbl->Free(pIMem, pMid2);
            } else {
                pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 16, CHARACTER_ATTRIBUTE_FORE_COLOR_RED, "Shrink: FAIL", 12);
                pIMem->pVTbl->Free(pIMem, pBig); /* Чистим старый, если shrink не удался */
            }
        } else {
            pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 16, CHARACTER_ATTRIBUTE_FORE_COLOR_RED, "Expand: FAIL", 12);
            pIMem->pVTbl->Free(pIMem, pMid1);
        }
    }
 

    pIVideo->pVTbl->WriteString(pIVideo, 0, 0, 0, 18, CHARACTER_ATTRIBUTE_FORE_COLOR_CYAN, "ALL TESTS COMPLETED.", 20);

    

TestEnd:
    while (1) {
        asm volatile ("NOP\n\t" ::: "memory");
    }

Release:
    if (pIBus != 0) pIBus->pVTbl->Release(pIBus);
    if (pIMem != 0) pIMem->pVTbl->Release(pIMem);
    if (pIMemMgr != 0) pIMemMgr->pVTbl->Release(pIMemMgr);
    if (pIVFB != 0) pIVFB->pVTbl->Release(pIVFB);
    if (pISys != 0) pISys->pVTbl->Release(pISys);

    return result;
}
