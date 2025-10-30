/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CLab2
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CLab2
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2025 YourName. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_LAB2_H__
#define __C_LAB2_H__

#include "ILab2.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include "IEcoLab1.h"

typedef struct CLab2 {

    /* Таблица функций интерфейса ILab2 */
    ILab2VTbl* m_pVTblILab2;

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

    /* ВКЛЮЧЕННЫЕ компоненты (владеем и управлям жизненным циклом) */
    IEcoCalculatorX* m_pIXCalculatorB;  /* Включенный компонент B */
    IEcoCalculatorX* m_pIXCalculatorC;  /* Включенный компонент C */
    IEcoCalculatorY* m_pIYCalculatorD;  /* Включенный компонент D */

    /* АГРЕГИРОВАННЫЕ компоненты (владеет внешний объект, но мы к ним получаем доступ) */
    IEcoUnknown* m_pInnerUnknownA;      /* Агрегированный компонент A */
    IEcoUnknown* m_pInnerUnknownE;      /* Агрегированный компонент E */
    IEcoUnknown* m_pInnerUnknownLab1;   /* Агрегированный компонент Eco.Lab1 */

    /* Данные экземпляра */
    char_t* m_Name;

} CLab2, *CLab2Ptr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCLab2(/*in*/ struct ILab2* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCLab2(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ ILab2** ppILab2);
/* Удаление */
void ECOCALLMETHOD deleteCLab2(/* in */ ILab2* pILab2);

#endif /* __C_LAB2_H__ */