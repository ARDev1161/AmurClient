#ifndef PILOT_H
#define PILOT_H

#include <string>

#include "position.h"
#include "localPath.h"
#include "targetPath.h"
#include "motorControl.h"
#include "pilotBlackBox.h"
#include "pathChart.h"

// ***************************** Реактивный,перцепторно-моторный уровень *************************
// ** В данном классе для Робота с Differential Drive приводом осуществляется
// ** управление движением по заданной целевой траектории
// ***********************************************************************************************

class Pilot
{
    // Тестовые режимы, когда на моторы подаются ступеньки
    const double cReactionTest = 0;
    const int cReactionTestRotate = 0;
    const double cReactionTestTime = 1000;

    // Интервал времени(мСек) для тикера
    const int cTickerRate = 500;     // -- Реально это соответствует 500 мсек ------

    const bool cBlackBoxToBeOn = false; // Должен ли быть включен BlackBox
    const bool cShowPathChart = false; // Показывать ли форму PathChart
    const int cMaxGateCount = 50; // Макс число проходов в массиве Локальной траектории

    std::string varIniFile; // Config file

    // Настройка отладочной печати
    int varDebug;
    std::string varLogFile;
    std::string varLogDir;
    std::string varLog;

    bool isBlackBoxToBeOn; // Настройка включения режима Черного Ящика
    bool isBlackBoxOn; // Включен ли BlackBox
    int varPathID; // ID Локальной траектории
    bool showPathChart; // Показывать ли форму PathChart
    int varMotrID; // Phidgets ID, контроллера, управляющего моторами
    bool varManual; // Двигается ли Робот в режиме ручного управления
    bool varBlocked; // Признак блокировки вычисления управляющих команд пока загружается новая траектория

    // Индикаторы текущего состояния бамперов Робота
    bool bFL;          // -- bFL = True - препятствие впереди-слева
    bool bFR;          // -- bFR = True - препятствие впереди-справа
    bool bFSL;         // -- bFSL = True - препятствие впереди-сбоку-слева
    bool bFSR;         // -- bFSR = True - препятствие впереди-сбоку-справа
    bool bBL;          // -- bBL = True - препятствие позади-слева
    bool bBR;          // -- bBR = True - препятствие позади-справа
    bool bBSL;         // -- bBSL = True - препятствие позади-сбоку-слева
    bool bBSR;         // -- bBSR = True - препятствие позади-сбоку-справа

    // Индикаторы текущих расстояния до боковых препятствий в задней части робота
    int distBSL;      // -- bBSL = True - препятствие позади-сбоку-слева
    int distBSR;      // -- bBSR = True - препятствие позади-сбоку-справа

    // Индакаторы рабочего состояния
    bool isOn;

    // Тестовые режимы, когда на моторы подаются ступеньки
    double varReactionTest;
    int varReactionTestRotate;
    double varReactionTestTime;

    // Количество элементов в массиве проходов по Локальной траектории
    int varCount;

    // Массив проходов по Локальной траектории
    clsGate[] varGates;
    // Текущие координаты, угол положения, а также скорости тела Робота
    double rbtX;
    double rbtY;
    double rbtA;
    double rbtVel;
    double rbtOmg;

    // Текущие координаты, угол положения, а также скорости целевой траектории
    double trgX;
    double trgY;
    double trgA;
    double trgVel;
    double trgOmg;

    // Текущие управляющие линейная и угловая скорости
    double cntrVel;
    double cntrOmg;

    // Направление движения:  varForward = True - Движение вперед
    bool varForward;
    // *******************************************************************************************
    // -- Текущее состояние движения Робота
    // *******************************************************************************************
    int varMoving;     // -- Двигается ли Робот ------------------------------------
                               // -- -1 = cPilotSleep  - Робот стоит и ждет команды на начало движения
                               // --  0 = cPilotWait   - Робот готов к движению, ожидает Локальную траекторию
                               // --  1 = cPilotMove   - Робот двигается по Локальной траектории
                               // --  2 = cPilotFinish - Робот двигается по последнему сегменту Локальной траектории

    // Индикатор поворота
    int varTurnMode;
    // -- +2 - разворачивается на месте влево
    // -- +1 - поворачивает налево
    // --  0 - движется по прямой
    // -- -1 - поворачивает направо
    // -- -2 - разворачивается на месте вправо

    // Предыдущее направление движения:  varForward = True - Движение вперед
    bool prevForward;

    // Предыдущее состояние движения Робота и индикатор поворота (для индикации)
    int prevMoving;
    // -- -1 = cPilotSleep  - Робот стоит и ждет команды на начало движения
    // --  0 = cPilotWait   - Робот готов к движению, ожидает Локальную траекторию
    // --  1 = cPilotMove   - Робот двигается по Локальной траектории
    // --  2 = cPilotFinish - Робот двигается по последнему сегменту Локальной траектории
    int prevTurnMode;
    // -- +2 - разворачивается на месте влево
    // -- +1 - поворачивает налево
    // --  0 - движется по прямой
    // -- -1 - поворачивает направо
    // -- -2 - разворачивается на месте вправо

    // Предыдущая метка времени
    double prevTimeStamp;

    LocalPath localPath;
    Position position;
    TargetPath targetPath;
    MotorControl motorControl;
    PilotBlackBox blackBox;
    frmPathChart pathChart;

    void MotorControl_Error(string aDesc);
    void MotorControl_Status(bool aStatus);
    void Simulator_Status();
    bool BumpersOff();
    void GetParamsFromIniFile();
    void SaveParamsToIniFile();
    void WriteLogData(double aX, double aY, double aA, double aVel, double aOmg, double tX, double tY, double tA, double tVel, double tOmg, ref double cVel, double cOmg, double aTS, double calcTime);
    void WriteReactionTestData(double aX, double aY, double aA, double aVel, double aOmg, double cVel, double cOmg, double cVelL, double cVelR, double mVelL, double mVelR, double odoTS, double currTS);
    // ** PrintEndMoving - Отладочная печать - Конец движения ************************************
    void PrintEndMoving(int Reason);
    void PrintHeader(string aHead);
    void PrintFooter(string aFoot);
    void Write1Line();
    void Write2Line();
    void WriteLog(string aMes);
    void WriteEventLog(string aMes);

public:
    // Надо ли прогнозировать позицию Робота на cDelTime по времени
    bool varPredictPose;
    // Упреждение по времени для прогнозирования позиции Робота
    double varDelTime;

    Pilot();
    ~Pilot();

    bool PilotStatus();
    bool Open(ref clsPosition aPosition, ref clsLocalPath aLocalPath)
    void Close();
    void CheckStatus();
    void StopMoving(int Reason = 1);
    void StopAndWait(int Reason = 1);
    int PrepareToMove();
    void SetForward(bool Val);
    bool IsForward();
    void UpdateLocalPath(double aX, double aY, double aA); // UpdateLocalPath - Пришла новая Локальная траектория
    void Move(double aX, double aY, double aA, double aVel, double aOmg, double aTS);
    void SetControlVels(double cntrVel, double cntrOmg, ref double cntrVelL, ref double cntrVelR);
    void ReactionTest(double odoTimeStamp, double currTimeStamp);
    void SetPathParams(double ak1, double ak2, double akVel, double akOmg, double akTurn);
    void ResetPathChart();
    void SetBumpers(string aDir, bool aVal);
    void WriteReactionTestHeader();
    void WriteLogHeader();
    void SetObstDist(string aDir, int aVal);
    void SetManual(bool aVal);
    void ExecManual(string aDirection, bool varTrue);
    void ShowDirection();









//    event ErrorAriseEventHandler ErrorArise;
//    delegate void ErrorAriseEventHandler(string aDesc);

//    event StatusEventHandler Status;
//    delegate void StatusEventHandler(bool aStatus);

//    event SetInitTurnEventHandler SetInitTurn;
//    delegate void SetInitTurnEventHandler(bool aEnable);

//    event MovingDirEventHandler MovingDir;
//    delegate void MovingDirEventHandler(string aDir);

//    event StoppedEventHandler Stopped;
//    delegate void StoppedEventHandler(int Reason);
    // Reason = 0  - Все в порядке
    // 1  - Остановлен внешней командой
    // 2  - Уже двигаемся, хотя еще не стартовали
    // 3  - Не все необходимые объекты в рабочем состоянии
    // 4  - Отсутствует Локальный маршрут
    // 5  - Некорректно задана скорость
    // 6  - Режим ручного управления
    // 7  - Некорректно задан угол поворота
    // 8  - Препятствия на пути движения
    // 9  - Двигатели перемещения не включены
    // 10 - Целевой маршрут пройден

};

#endif // PILOT_H
