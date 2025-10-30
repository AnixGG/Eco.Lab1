/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   ILab2
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс ILab2
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2025 YourName. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_LAB2_H__
#define __I_LAB2_H__

#include "IEcoBase1.h"

/* ILab2 IID = {D39330A1-0657-4FC3-8508-EC1C37BBB18B} */
#ifndef __IID_ILab2
static const UGUID IID_ILab2 = {0x01, 0x10, 0xD3, 0x93, 0x30, 0xA1, 0x06, 0x57, 0x4F, 0xC3, 0x85, 0x08, 0xEC, 0x1C, 0x37, 0xBB, 0xB1, 0x8B};
#endif /* __IID_ILab2 */

typedef struct ILab2 ILab2;

/* typedef на указатель для методов VTBL */
typedef ILab2* ILab2Ptr_t;

typedef struct ILab2VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ struct ILab2* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ struct ILab2* me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ struct ILab2* me);

    /* ILab2 specific methods */
    int16_t (ECOCALLMETHOD *GnomeSort)(/* in */ struct ILab2* me, /* in */ void* base,
                                    /* in */ size_t nmemb, /* in */ size_t size,
                                    /* in */ int (*compar)(const void*, const void*));
    
    int32_t (ECOCALLMETHOD *Addition)(/* in */ struct ILab2* me, /* in */ int16_t a, /* in */ int16_t b);
    int16_t (ECOCALLMETHOD *Subtraction)(/* in */ struct ILab2* me, /* in */ int16_t a, /* in */ int16_t b);
    int32_t (ECOCALLMETHOD *Multiplication)(/* in */ struct ILab2* me, /* in */ int16_t a, /* in */ int16_t b);
    int16_t (ECOCALLMETHOD *Division)(/* in */ struct ILab2* me, /* in */ int16_t a, /* in */ int16_t b);

} ILab2VTbl, *ILab2VTblPtr;

interface ILab2 {
    struct ILab2VTbl *pVTbl;
} ILab2;


#endif /* __I_LAB2_H__ */