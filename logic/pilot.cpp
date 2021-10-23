#include "pilot.h"

Pilot::Pilot()
{
    // --
    // ---------------------------------------------------------------------------------------
    varIniFile = modGlobal.cIniFile;
    varLogDir = modGlobal.cLogDir;
    varDebug = 0;
    // ---------------------------------------------------------------------------------------
    isBlackBoxToBeOn = cBlackBoxToBeOn;
    isBlackBoxOn = false;
    varPathID = 0;
    // ---------------------------------------------------------------------------------------
    showPathChart = cShowPathChart;
    // ---------------------------------------------------------------------------------------
    varMotrID = modGlobal.cMotrID;
    // ---------------------------------------------------------------------------------------
    varManual = false;
    varBlocked = false;
    // ---------------------------------------------------------------------------------------
    rbtX = 0d;
    rbtY = 0d;
    rbtA = 0d;
    // --
    rbtVel = 0d;
    rbtOmg = 0d;
    // ---------------------------------------------------------------------------------------
    varReactionTest = cReactionTest;
    varReactionTestRotate = cReactionTestRotate;
    varReactionTestTime = cReactionTestTime;
    // ---------------------------------------------------------------------------------------
    cntrVel = 0;
    cntrOmg = 0;
    // ---------------------------------------------------------------------------------------
    varForward = true;
    varMoving = modGlobal.cPilotSleep;
    varTurnMode = 0;
    // ---------------------------------------------------------------------------------------
    prevForward = false;
    prevMoving = modGlobal.cPilotSleep;
    prevTurnMode = 0;
    // ---------------------------------------------------------------------------------------
    prevTimeStamp = 0d;
    // ---------------------------------------------------------------------------------------
    varPredictPose = modGlobal.cPredictPose;
    varDelTime = modGlobal.cDelTime;
    // ---------------------------------------------------------------------------------------
    varGates = new clsGate[51];
    for (int i = 0; i <= cMaxGateCount; i++)
        varGates[i] = new clsGate();
    // ---------------------------------------------------------------------------------------
    bFL = false;
    bFR = false;
    bFSL = false;
    bFSR = false;
    bBL = false;
    bBR = false;
    bBSL = false;
    bBSR = false;
    // ---------------------------------------------------------------------------------------
    isOn = false;
    // --
}
