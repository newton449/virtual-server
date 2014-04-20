// This is a generated source file for Chilkat version 9.5.0.21
#ifndef _C_CkRsa_H
#define _C_CkRsa_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"

HCkRsa CkRsa_Create(void);
void CkRsa_Dispose(HCkRsa handle);
void CkRsa_getCharset(HCkRsa cHandle, HCkString retval);
void CkRsa_putCharset(HCkRsa cHandle, const char *newVal);
const char *CkRsa_charset(HCkRsa cHandle);
void CkRsa_getDebugLogFilePath(HCkRsa cHandle, HCkString retval);
void CkRsa_putDebugLogFilePath(HCkRsa cHandle, const char *newVal);
const char *CkRsa_debugLogFilePath(HCkRsa cHandle);
void CkRsa_getEncodingMode(HCkRsa cHandle, HCkString retval);
void CkRsa_putEncodingMode(HCkRsa cHandle, const char *newVal);
const char *CkRsa_encodingMode(HCkRsa cHandle);
void CkRsa_getLastErrorHtml(HCkRsa cHandle, HCkString retval);
const char *CkRsa_lastErrorHtml(HCkRsa cHandle);
void CkRsa_getLastErrorText(HCkRsa cHandle, HCkString retval);
const char *CkRsa_lastErrorText(HCkRsa cHandle);
void CkRsa_getLastErrorXml(HCkRsa cHandle, HCkString retval);
const char *CkRsa_lastErrorXml(HCkRsa cHandle);
BOOL CkRsa_getLittleEndian(HCkRsa cHandle);
void CkRsa_putLittleEndian(HCkRsa cHandle, BOOL newVal);
BOOL CkRsa_getNoUnpad(HCkRsa cHandle);
void CkRsa_putNoUnpad(HCkRsa cHandle, BOOL newVal);
int CkRsa_getNumBits(HCkRsa cHandle);
BOOL CkRsa_getOaepPadding(HCkRsa cHandle);
void CkRsa_putOaepPadding(HCkRsa cHandle, BOOL newVal);
BOOL CkRsa_getUtf8(HCkRsa cHandle);
void CkRsa_putUtf8(HCkRsa cHandle, BOOL newVal);
BOOL CkRsa_getVerboseLogging(HCkRsa cHandle);
void CkRsa_putVerboseLogging(HCkRsa cHandle, BOOL newVal);
void CkRsa_getVersion(HCkRsa cHandle, HCkString retval);
const char *CkRsa_version(HCkRsa cHandle);
BOOL CkRsa_DecryptBytes(HCkRsa cHandle, HCkByteData inData, BOOL usePrivateKey, HCkByteData outData);
BOOL CkRsa_DecryptBytesENC(HCkRsa cHandle, const char *str, BOOL bUsePrivateKey, HCkByteData outData);
BOOL CkRsa_DecryptString(HCkRsa cHandle, HCkByteData binarySig, BOOL usePrivateKey, HCkString outStr);
const char *CkRsa_decryptString(HCkRsa cHandle, HCkByteData binarySig, BOOL usePrivateKey);
BOOL CkRsa_DecryptStringENC(HCkRsa cHandle, const char *encodedSig, BOOL usePrivateKey, HCkString outStr);
const char *CkRsa_decryptStringENC(HCkRsa cHandle, const char *encodedSig, BOOL usePrivateKey);
BOOL CkRsa_EncryptBytes(HCkRsa cHandle, HCkByteData binaryData, BOOL usePrivateKey, HCkByteData outData);
BOOL CkRsa_EncryptBytesENC(HCkRsa cHandle, HCkByteData data, BOOL bUsePrivateKey, HCkString outStr);
const char *CkRsa_encryptBytesENC(HCkRsa cHandle, HCkByteData data, BOOL bUsePrivateKey);
BOOL CkRsa_EncryptString(HCkRsa cHandle, const char *stringToSign, BOOL usePrivateKey, HCkByteData outData);
BOOL CkRsa_EncryptStringENC(HCkRsa cHandle, const char *str, BOOL bUsePrivateKey, HCkString outStr);
const char *CkRsa_encryptStringENC(HCkRsa cHandle, const char *str, BOOL bUsePrivateKey);
BOOL CkRsa_ExportPrivateKey(HCkRsa cHandle, HCkString outStr);
const char *CkRsa_exportPrivateKey(HCkRsa cHandle);
BOOL CkRsa_ExportPublicKey(HCkRsa cHandle, HCkString outStr);
const char *CkRsa_exportPublicKey(HCkRsa cHandle);
BOOL CkRsa_GenerateKey(HCkRsa cHandle, int numBits);
BOOL CkRsa_ImportPrivateKey(HCkRsa cHandle, const char *xmlKey);
BOOL CkRsa_ImportPublicKey(HCkRsa cHandle, const char *xmlKey);
BOOL CkRsa_OpenSslSignBytes(HCkRsa cHandle, HCkByteData data, HCkByteData outBytes);
BOOL CkRsa_OpenSslSignBytesENC(HCkRsa cHandle, HCkByteData data, HCkString outStr);
const char *CkRsa_openSslSignBytesENC(HCkRsa cHandle, HCkByteData data);
BOOL CkRsa_OpenSslSignString(HCkRsa cHandle, const char *str, HCkByteData outBytes);
BOOL CkRsa_OpenSslSignStringENC(HCkRsa cHandle, const char *str, HCkString outStr);
const char *CkRsa_openSslSignStringENC(HCkRsa cHandle, const char *str);
BOOL CkRsa_OpenSslVerifyBytes(HCkRsa cHandle, HCkByteData signature, HCkByteData outBytes);
BOOL CkRsa_OpenSslVerifyBytesENC(HCkRsa cHandle, const char *str, HCkByteData outBytes);
BOOL CkRsa_OpenSslVerifyString(HCkRsa cHandle, HCkByteData data, HCkString outStr);
const char *CkRsa_openSslVerifyString(HCkRsa cHandle, HCkByteData data);
BOOL CkRsa_OpenSslVerifyStringENC(HCkRsa cHandle, const char *str, HCkString outStr);
const char *CkRsa_openSslVerifyStringENC(HCkRsa cHandle, const char *str);
BOOL CkRsa_SaveLastError(HCkRsa cHandle, const char *path);
BOOL CkRsa_SignBytes(HCkRsa cHandle, HCkByteData binaryData, const char *hashAlgorithm, HCkByteData outData);
BOOL CkRsa_SignBytesENC(HCkRsa cHandle, HCkByteData binaryData, const char *hashAlgorithm, HCkString outStr);
const char *CkRsa_signBytesENC(HCkRsa cHandle, HCkByteData binaryData, const char *hashAlgorithm);
BOOL CkRsa_SignHash(HCkRsa cHandle, HCkByteData hashBytes, const char *hashAlg, HCkByteData outBytes);
BOOL CkRsa_SignHashENC(HCkRsa cHandle, const char *encodedHash, const char *hashAlg, HCkString outStr);
const char *CkRsa_signHashENC(HCkRsa cHandle, const char *encodedHash, const char *hashAlg);
BOOL CkRsa_SignString(HCkRsa cHandle, const char *strToBeHashed, const char *hashAlgorithm, HCkByteData outData);
BOOL CkRsa_SignStringENC(HCkRsa cHandle, const char *strToBeHashed, const char *hashAlgorithm, HCkString outStr);
const char *CkRsa_signStringENC(HCkRsa cHandle, const char *strToBeHashed, const char *hashAlgorithm);
BOOL CkRsa_SnkToXml(HCkRsa cHandle, const char *filename, HCkString outStr);
const char *CkRsa_snkToXml(HCkRsa cHandle, const char *filename);
BOOL CkRsa_UnlockComponent(HCkRsa cHandle, const char *unlockCode);
BOOL CkRsa_VerifyBytes(HCkRsa cHandle, HCkByteData originalData, const char *hashAlgorithm, HCkByteData signatureBytes);
BOOL CkRsa_VerifyBytesENC(HCkRsa cHandle, HCkByteData originalData, const char *hashAlgorithm, const char *encodedSig);
BOOL CkRsa_VerifyHash(HCkRsa cHandle, HCkByteData hashBytes, const char *hashAlg, HCkByteData sigBytes);
BOOL CkRsa_VerifyHashENC(HCkRsa cHandle, const char *encodedHash, const char *hashAlg, const char *encodedSig);
BOOL CkRsa_VerifyPrivateKey(HCkRsa cHandle, const char *xml);
BOOL CkRsa_VerifyString(HCkRsa cHandle, const char *originalString, const char *hashAlgorithm, HCkByteData binarySig);
BOOL CkRsa_VerifyStringENC(HCkRsa cHandle, const char *originalString, const char *hashAlgorithm, const char *encodedSig);
#endif
