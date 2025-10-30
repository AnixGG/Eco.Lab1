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
 *   Данный заголовок описывает реализацию компонента CEcoCalculatorE
 *   с поддержкой агрегирования
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_CALCULATOR_E_H__
#define __C_ECO_CALCULATOR_E_H__

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoMemoryAllocator1.h"
#include "IEcoCalculatorY.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoCalculatorE {

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

} CEcoCalculatorE, *CEcoCalculatorEPtr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoCalculatorE(/*in*/ struct IEcoCalculatorY* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoCalculatorE(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoCalculatorY** ppIEcoCalculatorY);
/* Удаление */
void ECOCALLMETHOD deleteCEcoCalculatorE(/* in */ IEcoCalculatorY* pIEcoCalculatorY);

#endif /* __C_ECO_CALCULATOR_E_H__ */