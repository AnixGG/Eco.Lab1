/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdLab2
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdLab2
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2025 YourName. All rights reserved.
 * </автор>
 *
 */

#ifndef __ID_LAB2_H__
#define __ID_LAB2_H__

#include "IEcoBase1.h"
#include "ILab2.h"

/* Lab2 CID = {D39330A1-0657-4FC3-8508-EC1C37BBB18A} */
#ifndef __CID_Lab2
static const UGUID CID_Lab2 = {0x01, 0x10, {0xD3, 0x93, 0x30, 0xA1, 0x06, 0x57, 0x4F, 0xC3, 0x85, 0x08, 0xEC, 0x1C, 0x37, 0xBB, 0xB1, 0x8A}};
#endif /* __CID_Lab2 */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_D39330A106574FC38508EC1C37BBB18A;
#endif

#endif /* __ID_LAB2_H__ */