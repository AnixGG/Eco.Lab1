/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoCalculatorE
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoCalculatorE
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

#ifndef __ID_ECO_CALCULATOR_E_H__
#define __ID_ECO_CALCULATOR_E_H__

#include "IEcoBase1.h"
#include "IEcoCalculatorY.h"

/* EcoCalculatorE CID = {4828F655-2E45-40E7-8121-EBD220DC360F} */
#ifndef __CID_EcoCalculatorE
static const UGUID CID_EcoCalculatorE = {0x01, 0x10, {0x48, 0x28, 0xF6, 0x55, 0x2E, 0x45, 0x40, 0xE7, 0x81, 0x21, 0xEB, 0xD2, 0x20, 0xDC, 0x36, 0x0F}};
#endif /* __CID_EcoCalculatorE */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_872FEF1DE3314B87AD44D1E7C232C2F0;
#endif

#endif /* __ID_ECO_CALCULATOR_E_H__ */
