// This is a generated source file for Chilkat version 9.5.0.21
#ifndef _C_CkZipEntryWH
#define _C_CkZipEntryWH
#include "chilkatDefs.h"

#include "Chilkat_C.h"

HCkZipEntryW CkZipEntryW_Create(void);
HCkZipEntryW CkZipEntryW_Create2(BOOL bCallbackOwned);
void CkZipEntryW_Dispose(HCkZipEntryW handle);
void CkZipEntryW_getComment(HCkZipEntryW cHandle, HCkString retval);
void CkZipEntryW_putComment(HCkZipEntryW cHandle, const wchar_t *newVal);
const wchar_t *CkZipEntryW_comment(HCkZipEntryW cHandle);
unsigned long CkZipEntryW_getCompressedLength(HCkZipEntryW cHandle);
__int64 CkZipEntryW_getCompressedLength64(HCkZipEntryW cHandle);
void CkZipEntryW_getCompressedLengthStr(HCkZipEntryW cHandle, HCkString retval);
const wchar_t *CkZipEntryW_compressedLengthStr(HCkZipEntryW cHandle);
int CkZipEntryW_getCompressionLevel(HCkZipEntryW cHandle);
void CkZipEntryW_putCompressionLevel(HCkZipEntryW cHandle, int newVal);
int CkZipEntryW_getCompressionMethod(HCkZipEntryW cHandle);
void CkZipEntryW_putCompressionMethod(HCkZipEntryW cHandle, int newVal);
int CkZipEntryW_getCrc(HCkZipEntryW cHandle);
void CkZipEntryW_getDebugLogFilePath(HCkZipEntryW cHandle, HCkString retval);
void CkZipEntryW_putDebugLogFilePath(HCkZipEntryW cHandle, const wchar_t *newVal);
const wchar_t *CkZipEntryW_debugLogFilePath(HCkZipEntryW cHandle);
int CkZipEntryW_getEntryID(HCkZipEntryW cHandle);
int CkZipEntryW_getEntryType(HCkZipEntryW cHandle);
void CkZipEntryW_getFileDateTime(HCkZipEntryW cHandle, SYSTEMTIME *retval);
void CkZipEntryW_putFileDateTime(HCkZipEntryW cHandle, SYSTEMTIME *newVal);
void CkZipEntryW_getFileDateTimeStr(HCkZipEntryW cHandle, HCkString retval);
void CkZipEntryW_putFileDateTimeStr(HCkZipEntryW cHandle, const wchar_t *newVal);
const wchar_t *CkZipEntryW_fileDateTimeStr(HCkZipEntryW cHandle);
void CkZipEntryW_getFileName(HCkZipEntryW cHandle, HCkString retval);
void CkZipEntryW_putFileName(HCkZipEntryW cHandle, const wchar_t *newVal);
const wchar_t *CkZipEntryW_fileName(HCkZipEntryW cHandle);
void CkZipEntryW_getFileNameHex(HCkZipEntryW cHandle, HCkString retval);
const wchar_t *CkZipEntryW_fileNameHex(HCkZipEntryW cHandle);
int CkZipEntryW_getHeartbeatMs(HCkZipEntryW cHandle);
void CkZipEntryW_putHeartbeatMs(HCkZipEntryW cHandle, int newVal);
BOOL CkZipEntryW_getIsDirectory(HCkZipEntryW cHandle);
void CkZipEntryW_getLastErrorHtml(HCkZipEntryW cHandle, HCkString retval);
const wchar_t *CkZipEntryW_lastErrorHtml(HCkZipEntryW cHandle);
void CkZipEntryW_getLastErrorText(HCkZipEntryW cHandle, HCkString retval);
const wchar_t *CkZipEntryW_lastErrorText(HCkZipEntryW cHandle);
void CkZipEntryW_getLastErrorXml(HCkZipEntryW cHandle, HCkString retval);
const wchar_t *CkZipEntryW_lastErrorXml(HCkZipEntryW cHandle);
BOOL CkZipEntryW_getTextFlag(HCkZipEntryW cHandle);
void CkZipEntryW_putTextFlag(HCkZipEntryW cHandle, BOOL newVal);
unsigned long CkZipEntryW_getUncompressedLength(HCkZipEntryW cHandle);
__int64 CkZipEntryW_getUncompressedLength64(HCkZipEntryW cHandle);
void CkZipEntryW_getUncompressedLengthStr(HCkZipEntryW cHandle, HCkString retval);
const wchar_t *CkZipEntryW_uncompressedLengthStr(HCkZipEntryW cHandle);
BOOL CkZipEntryW_getVerboseLogging(HCkZipEntryW cHandle);
void CkZipEntryW_putVerboseLogging(HCkZipEntryW cHandle, BOOL newVal);
void CkZipEntryW_getVersion(HCkZipEntryW cHandle, HCkString retval);
const wchar_t *CkZipEntryW_version(HCkZipEntryW cHandle);
BOOL CkZipEntryW_AppendData(HCkZipEntryW cHandle, HCkByteData inData);
BOOL CkZipEntryW_AppendString(HCkZipEntryW cHandle, const wchar_t *strContent, const wchar_t *charset);
BOOL CkZipEntryW_Copy(HCkZipEntryW cHandle, HCkByteData outData);
BOOL CkZipEntryW_CopyToBase64(HCkZipEntryW cHandle, HCkString outStr);
const wchar_t *CkZipEntryW_copyToBase64(HCkZipEntryW cHandle);
BOOL CkZipEntryW_CopyToHex(HCkZipEntryW cHandle, HCkString outStr);
const wchar_t *CkZipEntryW_copyToHex(HCkZipEntryW cHandle);
BOOL CkZipEntryW_Extract(HCkZipEntryW cHandle, const wchar_t *dirPath);
BOOL CkZipEntryW_ExtractInto(HCkZipEntryW cHandle, const wchar_t *dirPath);
HCkDateTimeW CkZipEntryW_GetDt(HCkZipEntryW cHandle);
BOOL CkZipEntryW_Inflate(HCkZipEntryW cHandle, HCkByteData outData);
HCkZipEntryW CkZipEntryW_NextEntry(HCkZipEntryW cHandle);
BOOL CkZipEntryW_ReplaceData(HCkZipEntryW cHandle, HCkByteData inData);
BOOL CkZipEntryW_ReplaceString(HCkZipEntryW cHandle, const wchar_t *strContent, const wchar_t *charset);
BOOL CkZipEntryW_SaveLastError(HCkZipEntryW cHandle, const wchar_t *path);
void CkZipEntryW_SetDt(HCkZipEntryW cHandle, HCkDateTimeW dt);
BOOL CkZipEntryW_UnzipToString(HCkZipEntryW cHandle, int lineEndingBehavior, const wchar_t *srcCharset, HCkString outStr);
const wchar_t *CkZipEntryW_unzipToString(HCkZipEntryW cHandle, int lineEndingBehavior, const wchar_t *srcCharset);
#endif
