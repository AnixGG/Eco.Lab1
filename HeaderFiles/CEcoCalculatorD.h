/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoCalculatorD
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoCalculatorD
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_CALCULATOR_D_H__
#define __C_ECO_CALCULATOR_D_H__

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoMemoryAllocator1.h"
#include "IEcoCalculatorY.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoCalculatorD {

    /* Таблица функций интерфейса IEcoCalculatorY */
    IEcoCalculatorYVTbl* m_pVTblIY;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    char_t* m_Name;

} CEcoCalculatorD, *CEcoCalculatorDPtr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoCalculatorD(/*in*/ struct IEcoCalculatorY* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoCalculatorD(/* in */ IEcoUnknown* pIUnkSystem, /* out */ IEcoCalculatorY** ppIEcoCalculatorY);
/* Удаление */
void ECOCALLMETHOD deleteCEcoCalculatorD(/* in */ IEcoCalculatorY* pIEcoCalculatorY);

#endif /* __C_ECO_CALCULATOR_D_H__ */