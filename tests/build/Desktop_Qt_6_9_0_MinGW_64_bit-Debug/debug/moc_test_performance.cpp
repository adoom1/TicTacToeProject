/****************************************************************************
** Meta object code from reading C++ file 'test_performance.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../test_performance.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'test_performance.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15TestPerformanceE_t {};
} // unnamed namespace

template <> constexpr inline auto TestPerformance::qt_create_metaobjectdata<qt_meta_tag_ZN15TestPerformanceE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TestPerformance",
        "initTestCase",
        "",
        "cleanupTestCase",
        "init",
        "cleanup",
        "benchmarkAIMoveEasy",
        "benchmarkAIMoveMedium",
        "benchmarkAIMoveHard",
        "benchmarkAIMoveImpossible",
        "benchmarkGameTreeBuilding",
        "benchmarkMinimaxCalculation",
        "benchmarkBoardEvaluation",
        "benchmarkBoardEvaluationBatch",
        "benchmarkFullGameSimulation",
        "benchmarkMultipleGameSimulations",
        "benchmarkMemoryUsage",
        "benchmarkMemoryLeakTest",
        "benchmarkConcurrentGames",
        "performanceStressTest",
        "performanceScalabilityTest",
        "performanceCPUIntensiveTest",
        "compareAIDifficultyPerformance",
        "compareAlgorithmEfficiency"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'initTestCase'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'cleanupTestCase'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'init'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'cleanup'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'benchmarkAIMoveEasy'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'benchmarkAIMoveMedium'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'benchmarkAIMoveHard'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'benchmarkAIMoveImpossible'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'benchmarkGameTreeBuilding'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'benchmarkMinimaxCalculation'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'benchmarkBoardEvaluation'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'benchmarkBoardEvaluationBatch'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'benchmarkFullGameSimulation'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'benchmarkMultipleGameSimulations'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'benchmarkMemoryUsage'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'benchmarkMemoryLeakTest'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'benchmarkConcurrentGames'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'performanceStressTest'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'performanceScalabilityTest'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'performanceCPUIntensiveTest'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'compareAIDifficultyPerformance'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'compareAlgorithmEfficiency'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TestPerformance, qt_meta_tag_ZN15TestPerformanceE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TestPerformance::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15TestPerformanceE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15TestPerformanceE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15TestPerformanceE_t>.metaTypes,
    nullptr
} };

void TestPerformance::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TestPerformance *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->cleanupTestCase(); break;
        case 2: _t->init(); break;
        case 3: _t->cleanup(); break;
        case 4: _t->benchmarkAIMoveEasy(); break;
        case 5: _t->benchmarkAIMoveMedium(); break;
        case 6: _t->benchmarkAIMoveHard(); break;
        case 7: _t->benchmarkAIMoveImpossible(); break;
        case 8: _t->benchmarkGameTreeBuilding(); break;
        case 9: _t->benchmarkMinimaxCalculation(); break;
        case 10: _t->benchmarkBoardEvaluation(); break;
        case 11: _t->benchmarkBoardEvaluationBatch(); break;
        case 12: _t->benchmarkFullGameSimulation(); break;
        case 13: _t->benchmarkMultipleGameSimulations(); break;
        case 14: _t->benchmarkMemoryUsage(); break;
        case 15: _t->benchmarkMemoryLeakTest(); break;
        case 16: _t->benchmarkConcurrentGames(); break;
        case 17: _t->performanceStressTest(); break;
        case 18: _t->performanceScalabilityTest(); break;
        case 19: _t->performanceCPUIntensiveTest(); break;
        case 20: _t->compareAIDifficultyPerformance(); break;
        case 21: _t->compareAlgorithmEfficiency(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *TestPerformance::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TestPerformance::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15TestPerformanceE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TestPerformance::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 22;
    }
    return _id;
}
QT_WARNING_POP
