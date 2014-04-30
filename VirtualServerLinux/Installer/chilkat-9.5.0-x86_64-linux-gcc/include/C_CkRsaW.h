// This is a generated source file for Chilkat version 9.5.0.21
#ifndef _C_CkRsaWH
#define _C_CkRsaWH
#include "chilkatDefs.h"

#include "Chilkat_C.h"

HCkRsaW CkRsaW_Create(void);
void CkRsaW_Dispose(HCkRsaW handle);
void CkRsaW_getCharset(HCkRsaW cHandle, HCkString retval);
void CkRsaW_putCharset(HCkRsaW cHandle, const wchar_t *newVal);
const wchar_t *CkRsaW_charset(HCkRsaW cHandle);
void CkRsaW_getDebugLogFilePath(HCkRsaW cHandle, HCkString retval);
void CkRsaW_putDebugLogFilePath(HCkRsaW cHandle, const wchar_t *newVal);
const wchar_t *CkRsaW_debugLogFilePath(HCkRsaW cHandle);
void CkRsaW_getEncodingMode(HCkRsaW cHandle, HCkString retval);
void CkRsaW_putEncodingMode(HCkRsaW cHandle, const wchar_t *newVal);
const wchar_t *CkRsaW_encodingMode(HCkRsaW cHandle);
void CkRsaW_getLastErrorHtml(HCkRsaW cHandle, HCkString retval);
const wchar_t *CkRsaW_lastErrorHtml(HCkRsaW cHandle);
void CkRsaW_getLastErrorText(HCkRsaW cHandle, HCkString retval);
const wchar_t *CkRsaW_lastErrorText(HCkRsaW cHandle);
void CkRsaW_getLastErrorXml(HCkRsaW cHandle, HCkString retval);
const wchar_t *CkRsaW_lastErrorXml(HCkRsaW cHandle);
BOOL CkRsaW_getLittleEndian(HCkRsaW cHandle);
void CkRsaW_putLittleEndian(HCkRsaW cHandle, BOOL newVal);
BOOL CkRsaW_getNoUnpad(HCkRsaW cHandle);
void CkRsaW_putNoUnpad(HCkRsaW cHandle, BOOL newVal);
int CkRsaW_getNumBits(HCkRsaW cHandle);
BOOL CkRsaW_getOaepPadding(HCkRsaW cHandle);
void CkRsaW_putOaepPadding(HCkRsaW cHandle, BOOL newVal);
BOOL CkRsaW_getVerboseLogging(HCkRsaW cHandle);
void CkRsaW_putVerboseLogging(HCkRsaW cHandle, BOOL newVal);
void CkRsaW_getVersion(HCkRsaW cHandle, HCkString retval);
const wchar_t *CkRsaW_version(HCkRsaW cHandle);
BOOL CkRsaW_DecryptBytes(HCkRsaW cHandle, HCkByteData inData, BOOL usePrivateKey, HCkByteData outData);
BOOL CkRsaW_DecryptBytesENC(HCkRsaW cHandle, const wchar_t *str, BOOL bUsePrivateKey, HCkByteData outData);
BOOL CkRsaW_DecryptString(HCkRsaW cHandle, HCkByteData binarySig, BOOL usePrivateKey, HCkString outStr);
const wchar_t *CkRsaW_decryptString(HCkRsaW cHandle, HCkByteData binarySig, BOOL usePrivateKey);
BOOL CkRsaW_DecryptStringENC(HCkRsaW cHandle, const wchar_t *encodedSig, BOOL usePrivateKey, HCkString outStr);
const wchar_t *CkRsaW_decryptStringENC(HCkRsaW cHandle, const wchar_t *encodedSig, BOOL usePrivateKey);
BOOL CkRsaW_EncryptBytes(HCkRsaW cHandle, HCkByteData binaryData, BOOL usePrivateKey, HCkByteData outData);
BOOL CkRsaW_EncryptBytesENC(HCkRsaW cHandle, HCkByteData data, BOOL bUsePrivateKey, HCkString outStr);
const wchar_t *CkRsaW_encryptBytesENC(HCkRsaW cHandle, HCkByteData data, BOOL bUsePrivateKey);
BOOL CkRsaW_EncryptString(HCkRsaW cHandle, const wchar_t *stringToSign, BOOL usePrivateKey, HCkByteData outData);
BOOL CkRsaW_EncryptStringENC(HCkRsaW cHandle, const wchar_t *str, BOOL bUsePrivateKey, HCkString outStr);
const wchar_t *CkRsaW_encryptStringENC(HCkRsaW cHandle, const wchar_t *str, BOOL bUsePrivateKey);
BOOL CkRsaW_ExportPrivateKey(HCkRsaW cHandle, HCkString outStr);
const wchar_t *CkRsaW_exportPrivateKey(HCkRsaW cHandle);
BOOL CkRsaW_ExportPublicKey(HCkRsaW cHandle, HCkString outStr);
const wchar_t *CkRsaW_exportPublicKey(HCkRsaW cHandle);
BOOL CkRsaW_GenerateKey(HCkRsaW cHandle, int numBits);
BOOL CkRsaW_ImportPrivateKey(HCkRsaW cHandle, const wchar_t *xmlKey);
BOOL CkRsaW_ImportPublicKey(HCkRsaW cHandle, const wchar_t *xmlKey);
BOOL CkRsaW_OpenSslSignBytes(HCkRsaW cHandle, HCkByteData data, HCkByteData outBytes);
BOOL CkRsaW_OpenSslSignBytesENC(HCkRsaW cHandle, HCkByteData data, HCkString outStr);
const wchar_t *CkRsaW_openSslSignBytesENC(HCkRsaW cHandle, HCkByteData data);
BOOL CkRsaW_OpenSslSignString(HCkRsaW cHandle, const wchar_t *str, HCkByteData outBytes);
BOOL CkRsaW_OpenSslSignStringENC(HCkRsaW cHandle, const wchar_t *str, HCkString outStr);
const wchar_t *CkRsaW_openSslSignStringENC(HCkRsaW cHandle, const wchar_t *str);
BOOL CkRsaW_OpenSslVerifyBytes(HCkRsaW cHandle, HCkByteData signature, HCkByteData outBytes);
BOOL CkRsaW_OpenSslVerifyBytesENC(HCkRsaW cHandle, const wchar_t *str, HCkByteData outBytes);
BOOL CkRsaW_OpenSslVerifyString(HCkRsaW cHandle, HCkByteData data, HCkString outStr);
const wchar_t *CkRsaW_openSslVerifyString(HCkRsaW cHandle, HCkByteData data);
BOOL CkRsaW_OpenSslVerifyStringENC(HCkRsaW cHandle, const wchar_t *str, HCkString outStr);
const wchar_t *CkRsaW_openSslVerifyStringENC(HCkRsaW cHandle, const wchar_t *str);
BOOL CkRsaW_SaveLastError(HCkRsaW cHandle, const wchar_t *path);
BOOL CkRsaW_SignBytes(HCkRsaW cHandle, HCkByteData binaryData, const wchar_t *hashAlgorithm, HCkByteData outData);
BOOL CkRsaW_SignBytesENC(HCkRsaW cHandle, HCkByteData binaryData, const wchar_t *hashAlgorithm, HCkString outStr);
const wchar_t *CkRsaW_signBytesENC(HCkRsaW cHandle, HCkByteData binaryData, const wchar_t *hashAlgorithm);
BOOL CkRsaW_SignHash(HCkRsaW cHandle, HCkByteData hashBytes, const wchar_t *hashAlg, HCkByteData outBytes);
BOOL CkRsaW_SignHashENC(HCkRsaW cHandle, const wchar_t *encodedHash, const wchar_t *hashAlg, HCkString outStr);
const wchar_t *CkRsaW_signHashENC(HCkRsaW cHandle, const wchar_t *encodedHash, const wchar_t *hashAlg);
BOOL CkRsaW_SignString(HCkRsaW cHandle, const wchar_t *strToBeHashed, const wchar_t *hashAlgorithm, HCkByteData outData);
BOOL CkRsaW_SignStringENC(HCkRsaW cHandle, const wchar_t *strToBeHashed, const wchar_t *hashAlgorithm, HCkString outStr);
const wchar_t *CkRsaW_signStringENC(HCkRsaW cHandle, const wchar_t *strToBeHashed, const wchar_t *hashAlgorithm);
BOOL CkRsaW_SnkToXml(HCkRsaW cHandle, const wchar_t *filename, HCkString outStr);
const wchar_t *CkRsaW_snkToXml(HCkRsaW cHandle, const wchar_t *filename);
BOOL CkRsaW_UnlockComponent(HCkRsaW cHandle, const wchar_t *unlockCode);
BOOL CkRsaW_VerifyBytes(HCkRsaW cHandle, HCkByteData originalData, const wchar_t *hashAlgorithm, HCkByteData signatureBytes);
BOOL CkRsaW_VerifyBytesENC(HCkRsaW cHandle, HCkByteData originalData, const wchar_t *hashAlgorithm, const wchar_t *encodedSig);
BOOL CkRsaW_VerifyHash(HCkRsaW cHandle, HCkByteData hashBytes, const wchar_t *hashAlg, HCkByteData sigBytes);
BOOL CkRsaW_VerifyHashENC(HCkRsaW cHandle, const wchar_t *encodedHash, const wchar_t *hashAlg, const wchar_t *encodedSig);
BOOL CkRsaW_VerifyPrivateKey(HCkRsaW cHandle, const wchar_t *xml);
BOOL CkRsaW_VerifyString(HCkRsaW cHandle, const wchar_t *originalString, const wchar_t *hashAlgorithm, HCkByteData binarySig);
BOOL CkRsaW_VerifyStringENC(HCkRsaW cHandle, const wchar_t *originalString, const wchar_t *hashAlgorithm, const wchar_t *encodedSig);
#endif
