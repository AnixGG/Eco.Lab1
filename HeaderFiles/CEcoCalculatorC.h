/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoCalculatorC
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoCalculatorC
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_CALCULATOR_C_H__
#define __C_ECO_CALCULATOR_C_H__

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoMemoryAllocator1.h"
#include "IEcoCalculatorX.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoCalculatorC {

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

} CEcoCalculatorC, *CEcoCalculatorCPtr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoCalculatorC(/*in*/ struct IEcoCalculatorX* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoCalculatorC(/* in */ IEcoUnknown* pIUnkSystem, /* out */ IEcoCalculatorX** ppIEcoCalculatorX);
/* Удаление */
void ECOCALLMETHOD deleteCEcoCalculatorC(/* in */ IEcoCalculatorX* pIEcoCalculatorX);

#endif /* __C_ECO_CALCULATOR_C_H__ */