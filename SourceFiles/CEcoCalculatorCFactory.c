/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoCalculatorCFactory
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию фабрики для компонента
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "CEcoCalculatorC.h"
#include "CEcoCalculatorCFactory.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция возвращает указатель на интерфейс
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoCalculatorCFactory_QueryInterface(IEcoComponentFactory* me, const UGUID* riid, void** ppv) {
    if ( IsEqualUGUID(riid, &IID_IEcoUnknown) || IsEqualUGUID(riid, &IID_IEcoComponentFactory) ) {
        *ppv = me;
    }
    else {
        *ppv = 0;
        return -1;
    }
    ((IEcoUnknown*)(*ppv))->pVTbl->AddRef((IEcoUnknown*)*ppv);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция увеличивает количество ссылок на интерфейс
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoCalculatorCFactory_AddRef(/* in */ IEcoComponentFactory* me) {
    CEcoCalculatorCFactory* pCMe = (CEcoCalculatorCFactory*)me;

    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция уменьшает количество ссылок на интерфейс
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoCalculatorCFactory_Release(/* in */ IEcoComponentFactory* me) {
    CEcoCalculatorCFactory* pCMe = (CEcoCalculatorCFactory*)me;

    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        //deleteCEcoCalculatorCFactory(&pCMe->m_VtblICF);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализирует компонент с параметрами
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoCalculatorCFactory_Init(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pIUnkSystem, /* in */ void* pv) {
    CEcoCalculatorCFactory* pCMe = (CEcoCalculatorCFactory*)me;
    int16_t result = -1;

    if (me == 0 ) {
        return -1;
    }

    /* Инициализация компонента */
    result = pCMe->m_pInitInstance(pv, pIUnkSystem);

    return result;
}

/*
 *
 * <сводка>
 *   Функция Alloc
 * </сводка>
 *
 * <описание>
 *   Функция создает компонент
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoCalculatorCFactory_Alloc(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pISystem, /* in */ struct IEcoUnknown *pIUnknownOuter, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoCalculatorCFactory* pCMe = (CEcoCalculatorCFactory*)me;
    IEcoUnknown* pIUnk = 0;
    int16_t result = -1;

    if (me == 0 ) {
        return -1;
    }

    /* Агрегирование при условии если IID это IID_IEcoUnknown */
    if ( ( pIUnknownOuter != 0 ) && !IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        /* не поддерживает агрегирование */
        return -1;
    }

    /* Создание компонента */
    result = pCMe->m_pInstance(pISystem, 0, (void**)&pIUnk);  // CalculatorC does not support aggregation
    if ( result != 0 || pIUnk == 0) {
        return -1;
    }

    /* Инициализация компонента */
    result = me->pVTbl->Init(me, pISystem, pIUnk);
    
    /* Получение указателя на интерфейс */
    result = pIUnk->pVTbl->QueryInterface(pIUnk, riid, ppv);

    /* Уменьшение ссылки запрошенной Фабрикой компонентов */
    pIUnk->pVTbl->Release(pIUnk);

    return result;
}

/*
 *
 * <сводка>
 *   Функция get_Name
 * </сводка>
 *
 * <описание>
 *   Функция возвращает наименование компонента
 * </описание>
 *
 */
char_t* ECOCALLMETHOD CEcoCalculatorCFactory_get_Name(/* in */ struct IEcoComponentFactory* me) {
    CEcoCalculatorCFactory* pCMe = (CEcoCalculatorCFactory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Name;
}

/*
 *
 * <сводка>
 *   Функция get_Version
 * </сводка>
 *
 * <описание>
 *   Функция возвращает версию компонента
 * </описание>
 *
 */
char_t* ECOCALLMETHOD CEcoCalculatorCFactory_get_Version(/* in */ struct IEcoComponentFactory* me) {
    CEcoCalculatorCFactory* pCMe = (CEcoCalculatorCFactory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Version;
}

/*
 *
 * <сводка>
 *   Функция get_Manufacturer
 * </сводка>
 *
 * <описание>
 *   Функция возвращает наименование производителя компонента
 * </описание>
 *
 */
char_t* ECOCALLMETHOD CEcoCalculatorCFactory_get_Manufacturer(/* in */ struct IEcoComponentFactory* me) {
    CEcoCalculatorCFactory* pCMe = (CEcoCalculatorCFactory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Manufacturer;
}

/* Create Virtual Table */
IEcoComponentFactoryVTbl g_x3A8E44677E82475CB4A3719ED8397E61FactoryVTbl = {
    CEcoCalculatorCFactory_QueryInterface,
    CEcoCalculatorCFactory_AddRef,
    CEcoCalculatorCFactory_Release,
    CEcoCalculatorCFactory_Alloc,
    CEcoCalculatorCFactory_Init,
    CEcoCalculatorCFactory_get_Name,
    CEcoCalculatorCFactory_get_Version,
    CEcoCalculatorCFactory_get_Manufacturer
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
CEcoCalculatorCFactory g_x3A8E44677E82475CB4A3719ED8397E61Factory = {
    &g_x3A8E44677E82475CB4A3719ED8397E61FactoryVTbl,
    0,
    (CreateInstance)createCEcoCalculatorC,
    (InitInstance)initCEcoCalculatorC,
    "EcoCalculatorC\0",
    "1.0.0.0\0",
    "CompanyName\0"
};

#ifdef ECO_DLL
// В одном проекте с Eco.Lab1 экспорт не нужен, чтобы избежать конфликта
// ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr() {
//     return (IEcoComponentFactory*)&g_x3A8E44677E82475CB4A3719ED8397E61Factory;
// };
#endif

#if defined(ECO_LIB) || defined(ECO_DLL)
IEcoComponentFactory* GetIEcoComponentFactoryPtr_3A8E44677E82475CB4A3719ED8397E61 = (IEcoComponentFactory*)&g_x3A8E44677E82475CB4A3719ED8397E61Factory;
#endif