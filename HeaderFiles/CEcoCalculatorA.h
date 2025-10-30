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
 *   Данный заголовок описывает реализацию компонента EcoCalculatorA
 *   с поддержкой агрегирования
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2025 YourName. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_CALCULATOR_A_H__
#define __C_ECO_CALCULATOR_A_H__

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoMemoryAllocator1.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoCalculatorA {

    /* Таблица функций интерфейса IEcoCalculatorX */
    IEcoCalculatorXVTbl* m_pVTblIX;

    /* Таблица функций интерфейса IEcoCalculatorY */
    IEcoCalculatorYVTbl* m_pVTblIY;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Внешний объект при агрегации */
    IEcoUnknown* m_pIUnkOuter;

    /* Данные экземпляра */
    char_t* m_Name;

} CEcoCalculatorA, *CEcoCalculatorAPtr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoCalculatorA(/*in*/ struct IEcoCalculatorX* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoCalculatorA(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoCalculatorX** ppIEcoCalculatorX);
/* Удаление */
void ECOCALLMETHOD deleteCEcoCalculatorA(/* in */ IEcoCalculatorX* pIEcoCalculatorX);

#endif /* __C_ECO_CALCULATOR_A_H__ */