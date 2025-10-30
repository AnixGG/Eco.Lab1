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
 *   Данный заголовок описывает реализацию компонента CEcoCalculatorB
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_CALCULATOR_B_H__
#define __C_ECO_CALCULATOR_B_H__

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoMemoryAllocator1.h"
#include "IEcoCalculatorX.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoCalculatorB {

    /* Таблица функций интерфейса IEcoCalculatorX */
    IEcoCalculatorXVTbl* m_pVTblIX;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    char_t* m_Name;

} CEcoCalculatorB, *CEcoCalculatorBPtr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoCalculatorB(/*in*/ struct IEcoCalculatorX* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoCalculatorB(/* in */ IEcoUnknown* pIUnkSystem, /* out */ IEcoCalculatorX** ppIEcoCalculatorX);
/* Удаление */
void ECOCALLMETHOD deleteCEcoCalculatorB(/* in */ IEcoCalculatorX* pIEcoCalculatorX);

#endif /* __C_ECO_CALCULATOR_B_H__ */