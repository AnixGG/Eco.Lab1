/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoCalculatorD
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoCalculatorD
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

#ifndef __ID_ECO_CALCULATOR_D_H__
#define __ID_ECO_CALCULATOR_D_H__

#include "IEcoBase1.h"
#include "IEcoCalculatorY.h"

/* EcoCalculatorD CID = {872FEF1D-E331-4B87-AD44-D1E7C232C2F0} */
#ifndef __CID_EcoCalculatorD
static const UGUID CID_EcoCalculatorD = {0x01, 0x10, {0x87, 0x2F, 0xEF, 0x1D, 0xE3, 0x31, 0x4B, 0x87, 0xAD, 0x44, 0xD1, 0xE7, 0xC2, 0x32, 0xC2, 0xF0}};
#endif /* __CID_EcoCalculatorD */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_3A8E44677E82475CB4A3719ED8397E61;
#endif

#endif /* __ID_ECO_CALCULATOR_D_H__ */
