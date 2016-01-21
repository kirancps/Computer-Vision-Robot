#if !defined(__OLAPI__)
#define __OLAPI__

/*-----------------------------------------------------------------------

FILE NAME: oldaapi.h

ABSTRACT:

   This unit contains declarations for the Open Layers Data Acquisition
   Library.


10/13/92
---------------------------------------------------------------------------*/

#include <oltypes.h>
#include <oldadefs.h>
#include <olerrors.h>
#include <olmem.h>
#include <TedsApi.h>

#ifdef __cplusplus
extern "C" {
#endif

// Data Acquisition SubSystem

DECLARE_HANDLE (HDASS);

typedef HDASS *PHDASS;
#define LPHDASS PHDASS

DECLARE_HANDLE (HSSLIST);
typedef HSSLIST *PHSSLIST;
#define LPHSSLIST PHSSLIST

DECLARE_HANDLE (HDEV);
typedef HDEV *PHDEV;
#define LPHDEV PHDEV

// conversion macros for measure frequency

#define LongToFreq(l)    *(float*) &(l)
#define FreqToLong(f)    *(long*) &(f)

#define OLDA_SAMPLE_SIZE_IN_BYTES 2

typedef struct DASSInfotag {
   HDEV   hdev;
   OLSS   Olss;
   UINT   uiElement;
} DASSINFO, *PDASSINFO;

#define LPDASSINFO PDASSINFO

#ifdef STRICT
typedef BOOL (CALLBACK* DASSPROC)(PTSTR pszName, OLSS OlSs,
                               UINT uiElement, LPARAM lParam);
#else
typedef FARPROC DASSPROC;
#endif

#ifdef STRICT
typedef BOOL (CALLBACK* CAPSPROC)(UINT uiEnumCap, DBL dParam1,
                                 DBL dParam2, LPARAM lParam);
#else
typedef FARPROC CAPSPROC;
#endif

#ifdef STRICT
typedef BOOL (CALLBACK *DABRDPROC) (PTSTR pszBrdName, PTSTR pszEntry, LPARAM lParam);
#else
typedef FARPROC DABRDPROC;
#endif

#ifdef STRICT
typedef BOOL (CALLBACK *DABRDPROCEX) (PTSTR pszBrdName, PTSTR pszDriverName, HKEY hKeyDriver, LPARAM lParam);
#else
typedef FARPROC DABRDPROCEX;
#endif


#ifdef STRICT
typedef BOOL (CALLBACK *SSLISTPROC) (HSSLIST hSSList, HDASS hDass, LPARAM lParam);
#else
typedef FARPROC SSLISTPROC;
#endif


// parameters for olDaEnumSSCaps
#define OL_ENUM_FILTERS       100
#define OL_ENUM_RANGES        101
#define OL_ENUM_GAINS         102
#define OL_ENUM_RESOLUTIONS   103
#define OL_ENUM_EXCITATION_CURRENT_VALUES  104
#define OL_ENUM_THRESHOLD_START_TRIGGER_CHANNELS 105
#define OL_ENUM_THRESHOLD_REFERENCE_TRIGGER_CHANNELS 106




// simultaneous start stuff
typedef struct SSDASStag
{ 
   UINT        uiSizeSSDASS;
   VOID        *pSelf;
   HDASS       hDass;
   VOID        *pNext;
}
SSDASS;

typedef SSDASS *PSSDASS;

typedef struct SSLISTtag
{ 
   UINT      uiSizeSSLIST;
   UINT      uiCount;
   HSSLIST   hSelf;
   PSSDASS   pFirst;
   PSSDASS   pLast;
}
SSLIST;

typedef SSLIST *PSSLIST;

#define SSlFromHandle(h) (PSSLIST)(h)
#define HandleFromSSl(p) (HSSLIST)(p)

// macros for error checking Simultaneous Start stuff
#define IsBadHSSLIST(h) ( (IsBadReadPtr((SSLIST *)(h), sizeof (SSLIST))) ||\
                         ((h) == (HSSLIST) 0) ||\
                         (((SSLIST *)(h))->hSelf != (h)) )

#define IsBadHDASS(h) ( (IsBadReadPtr((DEVICE_DATA *)(h), sizeof (DEVICE_DATA))) ||\
                        ((h) == (HDASS) 0) ||\
                        (((DEVICE_DATA *)(h))->pSelf != (h)) )



// function prototypes
ECODE WINAPI olDaInitialize (PTSTR pszName, PHDEV phDev);
ECODE WINAPI olDaTerminate (HDEV hDev);
ECODE WINAPI olDaGetVersion(PTSTR pszVersion,UINT uiMaxChars);
ECODE WINAPI olDaGetDriverVersion(HDEV hDev, PTSTR pszVersion, UINT uiMaxChars);
ECODE WINAPI olDaGetWndHandle (HDASS hDass, HWND* phWnd);
ECODE WINAPI olDaPutBuffer (HDASS hDass, HBUF hBuf);
ECODE WINAPI olDaGetBuffer (HDASS hDass, PHBUF phBuf);

ECODE WINAPI olDaGetDeviceName (HDEV hDev, PTSTR lpszName, UINT uiMaxChars);
ECODE WINAPI olDaEnumBoards (DABRDPROC pfnDaBrdProc, LPARAM lParam);
ECODE WINAPI olDaEnumBoardsEx (DABRDPROCEX pfnDaBrdProcEx, LPARAM lParam);
ECODE WINAPI olDaEnumSubSystems (HDEV hDev, DASSPROC pfnDaProc, LPARAM lParam);
ECODE WINAPI olDaGetDASS (HDEV hDev, OLSS OlSs, UINT uiElement, PHDASS phDass);
ECODE WINAPI olDaReleaseDASS (HDASS hDass);
ECODE WINAPI olDaGetDASSInfo(HDASS hDass, PDASSINFO pDassInfo);
ECODE WINAPI olDaGetDevCaps (HDEV hDev, OLDC OlDc, PUINT puiCap);
ECODE WINAPI olDaGetSSCaps (HDASS hDass, OLSSC OlSSc, PUINT puiCap);
ECODE WINAPI olDaGetSSCapsEx (HDASS hDass, OLSSC OlSSc, PDBL pdCap);
ECODE WINAPI olDaEnumSSCaps (HDASS hDass, UINT uiEnumCap, CAPSPROC pfnCapsProc, LPARAM lParam);
ECODE WINAPI olDaSetDmaUsage (HDASS hDass, UINT uiUse);
ECODE WINAPI olDaGetDmaUsage (HDASS hDass, PUINT puiUse);
ECODE WINAPI olDaSetTriggeredScanUsage (HDASS hDass, BOOL fUse);
ECODE WINAPI olDaGetTriggeredScanUsage (HDASS hDass, PBOOL pfUse);
ECODE WINAPI olDaSetChannelType (HDASS hDass, UINT uiType);
ECODE WINAPI olDaGetChannelType (HDASS hDass, PUINT puiType);
ECODE WINAPI olDaSetChannelListSize (HDASS hDass, UINT uiSize);
ECODE WINAPI olDaGetChannelListSize (HDASS hDass, PUINT puiSize);
ECODE WINAPI olDaSetChannelListEntry (HDASS hDass, UINT uiEntry, UINT uiChan);
ECODE WINAPI olDaGetChannelListEntry (HDASS hDass, UINT uiEntry, PUINT puiChan);
ECODE WINAPI olDaSetGainListEntry (HDASS hDass, UINT uiEntry, DBL dGain);
ECODE WINAPI olDaGetGainListEntry (HDASS hDass, UINT uiEntry, PDBL pdGain);
ECODE WINAPI olDaSetChannelFilter (HDASS hDass, UINT uiChan, DBL dCutOffFreq);
ECODE WINAPI olDaGetChannelFilter (HDASS hDass, UINT uiChan, PDBL pdCutOffFreq);
ECODE WINAPI olDaSetEncoding (HDASS hDass, UINT uiEnc);
ECODE WINAPI olDaGetEncoding (HDASS hDass, PUINT puiEnc);
ECODE WINAPI olDaSetTrigger (HDASS hDass, UINT uiTrig);
ECODE WINAPI olDaGetTrigger (HDASS hDass, PUINT puiTrig);
ECODE WINAPI olDaSetResolution (HDASS hDass, UINT uiBits);
ECODE WINAPI olDaGetResolution (HDASS hDass, PUINT puiBits);
ECODE WINAPI olDaSetRange (HDASS hDass, DBL dMaxVoltage, DBL dMinVoltage);
ECODE WINAPI olDaGetRange (HDASS hDass, PDBL pdMaxVoltage, PDBL pdMinVoltage);
ECODE WINAPI olDaSetClockSource (HDASS hDass, UINT uiClk);
ECODE WINAPI olDaGetClockSource (HDASS hDass, PUINT puiClk);
ECODE WINAPI olDaSetClockFrequency (HDASS hDass, DBL dfFreq);
ECODE WINAPI olDaGetClockFrequency (HDASS hDass, PDBL pdfFreq);
ECODE WINAPI olDaSetRetriggerFrequency (HDASS hDass, DBL dfFreq);
ECODE WINAPI olDaGetRetriggerFrequency (HDASS hDass, PDBL pdfFreq);
ECODE WINAPI olDaSetExternalClockDivider(HDASS hDass, ULNG ulDivider);
ECODE WINAPI olDaGetExternalClockDivider(HDASS hDass, PULNG pulDivider);
ECODE WINAPI olDaSetGateType (HDASS hDass, UINT uiGate);
ECODE WINAPI olDaGetGateType (HDASS hDass, PUINT puiGate);
ECODE WINAPI olDaSetPulseType (HDASS hDass, UINT uiPulse);
ECODE WINAPI olDaGetPulseType (HDASS hDass, PUINT puiPulse);
ECODE WINAPI olDaSetPulseWidth (HDASS hDass, DBL dfPulseWidthPercent);
ECODE WINAPI olDaGetPulseWidth (HDASS hDass, PDBL pdfPulseWidthPercent);
ECODE WINAPI olDaSetCTMode (HDASS hDass, UINT uiCTMode);
ECODE WINAPI olDaGetCTMode (HDASS hDass, PUINT puiCTMode);
ECODE WINAPI olDaSetCascadeMode (HDASS hDass, UINT uiCascadeMode);
ECODE WINAPI olDaGetCascadeMode (HDASS hDass, PUINT puiCascadeMode);
ECODE WINAPI olDaReadEvents (HDASS hDass, PULNG pulEvents);
ECODE WINAPI olDaConfig (HDASS hDass);
ECODE WINAPI olDaStart (HDASS hDass);
ECODE WINAPI olDaStop (HDASS hDass);
ECODE WINAPI olDaContinue (HDASS hDass);
ECODE WINAPI olDaReset (HDASS hDass);
ECODE WINAPI olDaFlushBuffers (HDASS hDass);
LPSTR WINAPI olDaGetErrorString (ECODE eCode, PTSTR pStr, UINT uiMaxSize);
ECODE WINAPI olDaSetWndHandle (HDASS hDass, HWND hWnd, LPARAM lParam);
ECODE WINAPI olDaPutSingleValue(HDASS hDass, LNG lValue, UINT uiChannel, DBL dGain);
ECODE WINAPI olDaPutSingleValues(HDASS hDass, PLNG plValues, DBL dGain);
ECODE WINAPI olDaGetSingleValue(HDASS hDass, PLNG plValue, UINT uiChannel, DBL dGain);
ECODE WINAPI olDaGetSingleValues(HDASS hDass, PLNG plValues, DBL dGain);
ECODE WINAPI olDaGetDataFlow(HDASS hDass, PUINT puiDataFlow);
ECODE WINAPI olDaSetDataFlow(HDASS hDass, UINT uiDataFlow);
ECODE WINAPI olDaGetWrapMode (HDASS hDass, PUINT puiWrapMode);
ECODE WINAPI olDaSetWrapMode (HDASS hDass, UINT uiWrapMode);
ECODE WINAPI olDaPause (HDASS hDass);
ECODE WINAPI olDaAbort (HDASS hDass);
ECODE WINAPI olDaMeasureFrequency (HDASS hDass, HWND  hWnd, DBL dfCount_Duration);
ECODE WINAPI olDaGetQueueSize (HDASS hDass, UINT uiQueue, PUINT puiSize);
ECODE WINAPI olDaDTConnectBurst (HDASS hDass, UINT uiTransferSize, UINT uiTransferCount);
ECODE WINAPI olDaSetChannelListEntryInhibit (HDASS hDass, UINT uiEntry, BOOL fInhibit);
ECODE WINAPI olDaGetChannelListEntryInhibit (HDASS hDass, UINT uiEntry, PBOOL pfInhibit);
ECODE WINAPI olDaSetDigitalIOListEntry (HDASS hDass, UINT uiEntry, UINT uiValue);
ECODE WINAPI olDaGetDigitalIOListEntry (HDASS hDass, UINT uiEntry, PUINT puiValue);
ECODE WINAPI olDaSetSynchronousDigitalIOUsage (HDASS hDass, BOOL fUse);
ECODE WINAPI olDaGetSynchronousDigitalIOUsage (HDASS hDass, PBOOL pfUse);
ECODE WINAPI olDaGetSSList (PHSSLIST phSSList);
ECODE WINAPI olDaReleaseSSList (HSSLIST hSSList);
ECODE WINAPI olDaPutDassToSSList (HSSLIST hSSList, HDASS hDass);
ECODE WINAPI olDaSimultaneousPrestart (HSSLIST hSSList);
ECODE WINAPI olDaSimultaneousStart (HSSLIST hSSList);
ECODE WINAPI olDaEnumSSList (HSSLIST hSSList, SSLISTPROC pfnSSListProc, LPARAM lParam);
ECODE WINAPI olDaFlushFromBufferInprocess (HDASS hDass, HBUF hBuf, ULNG ulNumSamples);
ECODE WINAPI olDaSetNotificationProcedure (HDASS hDass, OLNOTIFYPROC pfnNotifyProc, LPARAM lParam);
ECODE WINAPI olDaGetNotificationProcedure (HDASS hDass, OLNOTIFYPROC* pfnNotifyProc);
ECODE WINAPI olDaSetDTConnectTransferSize (HDASS hDass, UINT uiTransferSize);
ECODE WINAPI olDaGetDTConnectTransferSize (HDASS hDass, PUINT puiTransferSize);
ECODE WINAPI olDaSetDTConnectTransferCount (HDASS hDass, UINT uiTransferCount);
ECODE WINAPI olDaGetDTConnectTransferCount (HDASS hDass, PUINT puiTransferCount);
ECODE WINAPI olDaSetChannelRange (HDASS hDass, UINT uiChan, DBL dMaxVoltage, DBL dMinVoltage);
ECODE WINAPI olDaGetChannelRange (HDASS hDass, UINT uiChan, PDBL pdMaxVoltage, PDBL pdMinVoltage);
ECODE WINAPI olDaSetRetriggerMode (HDASS hDass, UINT uiRetriggerMode);
ECODE WINAPI olDaGetRetriggerMode (HDASS hDass, LPUINT lpuiRetriggerMode);

ECODE WINAPI olDaGetSystemMetrics(HDASS hDass,LPDWORD lpUserLatency,LPDWORD lpKernelLatency);
ECODE WINAPI olDaEnableSystemMetrics(HDASS hDass, BOOLEAN bEnable, BOOLEAN bClear);
ECODE WINAPI olDaEnableHighResolutionTiming(BOOLEAN bEnable);

ECODE WINAPI olDaSetPretriggerSource (HDASS hDass, UINT uiTrig);
ECODE WINAPI olDaGetPretriggerSource (HDASS hDass, PUINT puiTrig);
ECODE WINAPI olDaSetMultiscanCount (HDASS hDass, UINT uiCount);
ECODE WINAPI olDaGetMultiscanCount (HDASS hDass, PUINT puiCount);

ECODE WINAPI olDaSetRetrigger (HDASS hDass, UINT uiTrig);
ECODE WINAPI olDaGetRetrigger (HDASS hDass, PUINT puiTrig);   

ECODE WINAPI olDaGetSingleValueEx( HDASS hDass, UINT uiChannel, BOOL bAutoRange, PDBL pdfGain, PLNG plValueCounts, PDBL pdfValueVolts );
ECODE WINAPI olDaSetMeasureStartEdge (HDASS hDass, UINT uiStartEdge);
ECODE WINAPI olDaGetMeasureStartEdge (HDASS hDass, PUINT puiStartEdge);
ECODE WINAPI olDaSetMeasureStopEdge (HDASS hDass, UINT uiStopEdge);
ECODE WINAPI olDaGetMeasureStopEdge (HDASS hDass, PUINT puiStopEdge);
ECODE WINAPI olDaSetCouplingType (HDASS hDass, UINT uiChan, COUPLING_TYPE eCouplingType );
ECODE WINAPI olDaGetCouplingType (HDASS hDass, UINT uiChan, PCOUPLING_TYPE pCouplingType);
ECODE WINAPI olDaSetExcitationCurrentSource (HDASS hDass, UINT uiChan, EXCITATION_CURRENT_SRC ExcitationCurrentSource);
ECODE WINAPI olDaGetExcitationCurrentSource (HDASS hDass, UINT uiChan, PEXCITATION_CURRENT_SRC pExcitationCurrentSource);
ECODE WINAPI olDaSetExcitationCurrentValue (HDASS hDass, UINT uiChan, DBL dExcitationCurrentValue);
ECODE WINAPI olDaGetExcitationCurrentValue (HDASS hDass, UINT uiChan, PDBL pdExcitationCurrentValue);

ECODE WINAPI olDaSetThermocoupleType (HDASS hDass, UINT uiChan, UINT uiThermType);
ECODE WINAPI olDaGetThermocoupleType (HDASS hDass, UINT uiChan, PUINT puiThermType);
ECODE WINAPI olDaSetReturnCjcTemperatureInStream (HDASS hDass, BOOL bReturnCjc);
ECODE WINAPI olDaGetReturnCjcTemperatureInStream (HDASS hDass, PBOOL pbReturnCjc);
ECODE WINAPI olDaGetSingleFloat (HDASS hDass, PFLOAT pfValue, UINT uiChannel, DBL dGain);
ECODE WINAPI olDaGetSingleFloats (HDASS hDass, PFLOAT pfValue, DBL dGain);
ECODE WINAPI olDaGetCjcTemperature (HDASS hDass, PFLOAT pfValue, UINT uiChannel);
ECODE WINAPI olDaGetCjcTemperatures (HDASS hDass, PFLOAT pfValue);
ECODE WINAPI olDaIsRunning (HDASS hDass, PBOOL pbIsRunning);
ECODE WINAPI olDaAutoCalibrate (HDASS hDass);
ECODE WINAPI olDaSetRtdType (HDASS hDass, UINT uiChan, UINT uiRtdType);
ECODE WINAPI olDaGetRtdType (HDASS hDass, UINT uiChan, PUINT puiRtdType);
ECODE WINAPI olDaSetChanVoltageRange (HDASS hDass, UINT uiChan, UINT uiRange);
ECODE WINAPI olDaGetChannelVoltageRange (HDASS hDass, UINT uiChan, PUINT puiRange);
ECODE WINAPI olDaSetSyncMode(HDASS hDass, UINT uiSyncMode);
ECODE WINAPI olDaGetSyncMode(HDASS hDass, PUINT puiSyncMode);
ECODE WINAPI olDaSetDataFilterType(HDASS hDass, UINT uiFilterType);
ECODE WINAPI olDaGetDataFilterType(HDASS hDass, PUINT puiFilterType);
ECODE WINAPI olDaSetStaleDataFlagEnabled (HDASS hDass, BOOL bEnabled);
ECODE WINAPI olDaGetStaleDataFlagEnabled (HDASS hDass, PBOOL pbEnabled);
ECODE WINAPI olDaSetEdgeType (HDASS hDass, UINT uiEdge);
ECODE WINAPI olDaGetEdgeType (HDASS hDass, PUINT puiEdge);
ECODE WINAPI olDaGetPowerSource (HDEV hDev, PPOWER_SOURCE pPowerSource);
ECODE WINAPI olDaSetTriggerThresholdLevel (HDASS hDass, DBL dfLevel);
ECODE WINAPI olDaGetTriggerThresholdLevel(HDASS hDass, PDBL pdLevel);
ECODE WINAPI olDaSetTriggerThresholdChannel (HDASS hDass, INT iChan);
ECODE WINAPI olDaGetTriggerThresholdChannel (HDASS hDass, PINT piChan);
ECODE WINAPI olDaSetReferenceTrigger (HDASS hDass, UINT uiReferenceTrig);
ECODE WINAPI olDaGetReferenceTrigger (HDASS hDass, PUINT puiReferenceTrig);
ECODE WINAPI olDaSetReferenceTriggerThresholdLevel(HDASS hDass, DBL dfLevel);
ECODE WINAPI olDaGetReferenceTriggerThresholdLevel (HDASS hDass, PDBL pdLevel);
ECODE WINAPI olDaSetReferenceTriggerThresholdChannel (HDASS hDass, INT iChan);
ECODE WINAPI olDaGetReferenceTriggerThresholdChannel (HDASS hDass, PINT piChan);
ECODE WINAPI olDaSetReferenceTriggerPostScanCount (HDASS hDass, INT iscanCount);
ECODE WINAPI olDaGetReferenceTriggerPostScanCount (HDASS hDass, PINT piScanCount);

ECODE WINAPI olDaSetStrainExcitationVoltageSource (HDASS hDass, STRAIN_EXCITATION_VOLTAGE_SRC eVoltageSource);
ECODE WINAPI olDaGetStrainExcitationVoltageSource (HDASS hDass, PSTRAIN_EXCITATION_VOLTAGE_SRC peVoltageSource);
ECODE WINAPI olDaSetStrainExcitationVoltage (HDASS hDass, DBL dExcitationVoltage);
ECODE WINAPI olDaGetStrainExcitationVoltage (HDASS hDass, PDBL pdExcitationVoltage);
ECODE WINAPI olDaSetStrainBridgeConfiguration (HDASS hDass, UINT uiChan, STRAIN_GAGE_CONFIGURATION eBridgeConfiguration);
ECODE WINAPI olDaGetStrainBridgeConfiguration (HDASS hDass, UINT uiChan, PSTRAIN_GAGE_CONFIGURATION peBridgeConfiguration);
ECODE WINAPI olDaSetStrainShuntResistor (HDASS hDass, UINT uiChan, BOOL bShuntEnabled);
ECODE WINAPI olDaGetStrainShuntResistor (HDASS hDass,UINT uiChan, BOOL * pbShuntEnabled);
ECODE WINAPI olDaReadBridgeSensorVirtualTeds (PCHAR virtualTedsFileName,PBRIDGE_SENSOR_TEDS pVirtualTeds);
ECODE WINAPI olDaReadBridgeSensorHardwareTeds (HDASS hDass,UINT uiChan,PBRIDGE_SENSOR_TEDS pHardwareTeds);
ECODE WINAPI olDaReadStrainGageVirtualTeds (PCHAR virtualTedsFileName,PSTRAIN_GAGE_TEDS pVirtualTeds);
ECODE WINAPI olDaReadStrainGageHardwareTeds (HDASS hDass,UINT uiChan,PSTRAIN_GAGE_TEDS pHardwareTeds);

ECODE WINAPI olDaMute (HDASS hDass);
ECODE WINAPI olDaUnMute (HDASS hDass);













// Utilitarian functions..taking no device or subsysten handle
//

ECODE WINAPI olDaCodeToVolts( DBL  dfMinRangeVolts,
                              DBL  dfMaxRangeVolts,
                              DBL  dfGain,
                              UINT uiBitsResolution,
                              UINT uiEncoding,
                              LNG  lCode,
                              PDBL pdfVoltage );

ECODE WINAPI olDaVoltsToCode( DBL  dfMinRangeVolts,
                              DBL  dfMaxRangeVolts,
                              DBL  dfGain,
                              UINT uiBitsResolution,
                              UINT uiEncoding,
                              DBL  dfVoltage, 
                              PLNG plCode );

ECODE WINAPI olDaVoltsToStrain(	STRAIN_GAGE_CONFIGURATION	uiBridgeConfig,	
								DBL							dfVu,	
								DBL							dfVs,
								DBL							dfVex,	
								DBL							dfGF,
								DBL							dfRg,
								DBL							dfRl,
								DBL							dfPr,
								DBL							dfMSShuntCorrection,
								DBL	*						pdfE);


ECODE WINAPI olDaVoltsToBridgeBasedSensor(DBL	dfVu,
								DBL							dfVs,
								DBL							dfVex,
								DBL							dfTc,
								DBL							dfRg,
								DBL							dfRl,
								DBL							dfRoInmV_V,
								DBL							dfMSShuntCorrection,
								DBL*							pdfE);


#define olWriteReg(hDev,Address,DataVal) \
   olDiagWriteReg(hDev,Address,DataVal,4)

#define olReadReg(hDev, Address, DataVal) \
 olDiagReadReg (hDev, Address, DataVal, 4)

ECODE WINAPI olDaSetQuadDecoder (HDASS hDass, 
								UINT ClockPreScale, 
								BOOL X4Scaling, 
								UINT IndexMode);


// Undocumented corner
//

ECODE WINAPI olDiagWriteReg( HDEV hDev, ULNG Offset, ULNG Data, UINT Size );
ECODE WINAPI olDiagReadReg( HDEV hDev, ULNG Offset, PULNG pData, UINT Size );

ECODE WINAPI olDiagWriteMem( HDEV hDev, ULNG Address, PULNG pData, UINT NumBytes );
ECODE WINAPI olDiagReadMem( HDEV hDev, ULNG Address, PULNG pData, UINT NumBytes );

ECODE WINAPI olDiagCloseAllBoards ();

ECODE WINAPI olDaSetHardwareInfo( HDEV hDev, 
                                  USHORT VendorId, 
                                  USHORT DeviceId, 
                                  USHORT ProductId, 
                                  ULNG SerialNumber,
                                  ULNG Reserved,
                                  PDRIVER_SPECIFIC_INFO pDriverSpecificInfo );

ECODE WINAPI olDaGetHardwareInfo( HDEV  hDev, 
                                  DTBUS_TYPE *pBusType, 
                                  PUSHORT pVendorId, 
                                  PUSHORT pDeviceId, 
                                  PUSHORT pProductId, 
                                  PULNG	  pSerialNumber,
                                  PULNG   pReserved,
                                  PDRIVER_SPECIFIC_INFO pDriverSpecificInfo );

ECODE WINAPI olDaSetDriverSpecificInfo( HDEV hDev,
                                        PVOID pData,
                                        ULONG Length );
 
ECODE WINAPI olDaGetDriverSpecificInfo( HDEV hDev, 
                                        PVOID pData,
                                        ULONG BuffSize );

ECODE WINAPI olDaGetBoardInfo( PTSTR pszName, 
                               PTSTR pDriverName,
							   PTSTR pModelName,
							   UINT	 MaxStrLens, 
							   UINT  *pInstanceNum);

ECODE WINAPI olDaModifyOpenLayersBoardName( PTSTR pszOldName, PTSTR pszNewName );

ECODE WINAPI olDiagWriteCalPot( HDEV hDev, ULONG ChipNum, ULONG PotNum, ULONG RegNum, ULONG Data);
ECODE WINAPI olDiagReadCalPot( HDEV hDev, ULONG ChipNum, ULONG PotNum, ULONG RegNum, PULONG pData);

ECODE WINAPI olDaGetDASSForQuery (HDEV hDev, OLSS OlSs, UINT uiElement, PHDASS phDass);
ECODE WINAPI olDaGetSSChanMap (HDASS hDass, UINT ChanIndex, CHANNELMAP *pChanMap);

ECODE WINAPI olDaSetThermocoupleTypeEprom (HDASS hDass, UINT uiChan, UINT uiThermType);

#ifdef __cplusplus
}
#endif


#endif
