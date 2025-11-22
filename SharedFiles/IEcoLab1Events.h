/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoLab1
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */
#ifndef __I_ECOLAB1EVENTS_H__
#define __I_ECOLAB1EVENTS_H__

#include "IEcoBase1.h"

#ifndef __IID_IEcoLab1Events
static const UGUID IID_IEcoLab1Events = {0x01, 0x10, 0xB6, 0xD3, 0x86, 0x61, 0x68, 0x27, 0x46, 0xD9, 0x91, 0x35, 0xFD, 0x4B, 0x20, 0x4A, 0x68, 0xD7};
#endif /* __IID_IEcoLab1Events */

typedef struct IEcoLab1EventsVTbl {
    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface )(struct IEcoLab1Events* me, const UGUID* riid, void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef )(struct IEcoLab1Events* me);
    uint32_t (ECOCALLMETHOD *Release )(struct IEcoLab1Events* me);

    /* События */
    // 1. Событие начала сортировки
    int16_t (ECOCALLMETHOD *OnSortStart)(struct IEcoLab1Events* me, void* sender);
    
    // 2. Событие перестановки (самое важное для визуализации)
    int16_t (ECOCALLMETHOD *OnSortSwap)(struct IEcoLab1Events* me, void* sender, uint32_t indexA, uint32_t indexB);
    
    // 3. Событие завершения
    int16_t (ECOCALLMETHOD *OnSortEnd)(struct IEcoLab1Events* me, void* sender);

} IEcoLab1EventsVTbl;

interface IEcoLab1Events {
    struct IEcoLab1EventsVTbl *pVTbl;
} IEcoLab1Events;

#endif /* __I_ECOLAB1EVENTS_H__ */
