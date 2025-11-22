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
 *   Данный заголовок описывает реализацию компонента CEcoLab1Sink
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

#ifndef __C_ECOLAB1_SINK_H__
#define __C_ECOLAB1_SINK_H__

#include "IEcoLab1Events.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab1Sink {

    /* Таблица функций интерфейса IEcoLab1Events */
    IEcoLab1EventsVTbl* m_pVTblIEcoLab1Events;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Имя приемника для логов */
    char_t* m_Name;

} CEcoLab1Sink;

/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoLab1Sink(
    /* in */ IEcoMemoryAllocator1* pIMem,
    /* in */ char_t* Name,
    /* out */ IEcoLab1Events** ppIEcoLab1Events);

/* Удаление */
void ECOCALLMETHOD deleteCEcoLab1Sink(/* in */ IEcoLab1Events* pIEcoLab1Events);

#endif /* __C_ECOLAB1_SINK_H__ */
