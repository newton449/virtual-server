// This is a generated source file for Chilkat version 9.5.0.21
#ifndef _C_CkCrypt2WH
#define _C_CkCrypt2WH
#include "chilkatDefs.h"

#include "Chilkat_C.h"

HCkCrypt2W CkCrypt2W_Create(void);
HCkCrypt2W CkCrypt2W_Create2(BOOL bCallbackOwned);
void CkCrypt2W_Dispose(HCkCrypt2W handle);
int CkCrypt2W_getBlockSize(HCkCrypt2W cHandle);
BOOL CkCrypt2W_getCadesEnabled(HCkCrypt2W cHandle);
void CkCrypt2W_putCadesEnabled(HCkCrypt2W cHandle, BOOL newVal);
void CkCrypt2W_getCadesSigPolicyHash(HCkCrypt2W cHandle, HCkString retval);
void CkCrypt2W_putCadesSigPolicyHash(HCkCrypt2W cHandle, const wchar_t *newVal);
const wchar_t *CkCrypt2W_cadesSigPolicyHash(HCkCrypt2W cHandle);
void CkCrypt2W_getCadesSigPolicyId(HCkCrypt2W cHandle, HCkString retval);
void CkCrypt2W_putCadesSigPolicyId(HCkCrypt2W cHandle, const wchar_t *newVal);
const wchar_t *CkCrypt2W_cadesSigPolicyId(HCkCrypt2W cHandle);
void CkCrypt2W_getCadesSigPolicyUri(HCkCrypt2W cHandle, HCkString retval);
void CkCrypt2W_putCadesSigPolicyUri(HCkCrypt2W cHandle, const wchar_t *newVal);
const wchar_t *CkCrypt2W_cadesSigPolicyUri(HCkCrypt2W cHandle);
void CkCrypt2W_getCharset(HCkCrypt2W cHandle, HCkString retval);
void CkCrypt2W_putCharset(HCkCrypt2W cHandle, const wchar_t *newVal);
const wchar_t *CkCrypt2W_charset(HCkCrypt2W cHandle);
void CkCrypt2W_getCipherMode(HCkCrypt2W cHandle, HCkString retval);
void CkCrypt2W_putCipherMode(HCkCrypt2W cHandle, const wchar_t *newVal);
const wchar_t *CkCrypt2W_cipherMode(HCkCrypt2W cHandle);
void CkCrypt2W_getCompressionAlgorithm(HCkCrypt2W cHandle, HCkString retval);
void CkCrypt2W_putCompressionAlgorithm(HCkCrypt2W cHandle, const wchar_t *newVal);
const wchar_t *CkCrypt2W_compressionAlgorithm(HCkCrypt2W cHandle);
void CkCrypt2W_getCryptAlgorithm(HCkCrypt2W cHandle, HCkString retval);
void CkCrypt2W_putCryptAlgorithm(HCkCrypt2W cHandle, const wchar_t *newVal);
const wchar_t *CkCrypt2W_cryptAlgorithm(HCkCrypt2W cHandle);
void CkCrypt2W_getDebugLogFilePath(HCkCrypt2W cHandle, HCkString retval);
void CkCrypt2W_putDebugLogFilePath(HCkCrypt2W cHandle, const wchar_t *newVal);
const wchar_t *CkCrypt2W_debugLogFilePath(HCkCrypt2W cHandle);
void CkCrypt2W_getEncodingMode(HCkCrypt2W cHandle, HCkString retval);
void CkCrypt2W_putEncodingMode(HCkCrypt2W cHandle, const wchar_t *newVal);
const wchar_t *CkCrypt2W_encodingMode(HCkCrypt2W cHandle);
BOOL CkCrypt2W_getFirstChunk(HCkCrypt2W cHandle);
void CkCrypt2W_putFirstChunk(HCkCrypt2W cHandle, BOOL newVal);
void CkCrypt2W_getHashAlgorithm(HCkCrypt2W cHandle, HCkString retval);
void CkCrypt2W_putHashAlgorithm(HCkCrypt2W cHandle, const wchar_t *newVal);
const wchar_t *CkCrypt2W_hashAlgorithm(HCkCrypt2W cHandle);
int CkCrypt2W_getHavalRounds(HCkCrypt2W cHandle);
void CkCrypt2W_putHavalRounds(HCkCrypt2W cHandle, int newVal);
int CkCrypt2W_getHeartbeatMs(HCkCrypt2W cHandle);
void CkCrypt2W_putHeartbeatMs(HCkCrypt2W cHandle, int newVal);
void CkCrypt2W_getIV(HCkCrypt2W cHandle, HCkByteData retval);
void CkCrypt2W_putIV(HCkCrypt2W cHandle, HCkByteData  newVal);
BOOL CkCrypt2W_getIncludeCertChain(HCkCrypt2W cHandle);
void CkCrypt2W_putIncludeCertChain(HCkCrypt2W cHandle, BOOL newVal);
int CkCrypt2W_getIterationCount(HCkCrypt2W cHandle);
void CkCrypt2W_putIterationCount(HCkCrypt2W cHandle, int newVal);
int CkCrypt2W_getKeyLength(HCkCrypt2W cHandle);
void CkCrypt2W_putKeyLength(HCkCrypt2W cHandle, int newVal);
BOOL CkCrypt2W_getLastChunk(HCkCrypt2W cHandle);
void CkCrypt2W_putLastChunk(HCkCrypt2W cHandle, BOOL newVal);
void CkCrypt2W_getLastErrorHtml(HCkCrypt2W cHandle, HCkString retval);
const wchar_t *CkCrypt2W_lastErrorHtml(HCkCrypt2W cHandle);
void CkCrypt2W_getLastErrorText(HCkCrypt2W cHandle, HCkString retval);
const wchar_t *CkCrypt2W_lastErrorText(HCkCrypt2W cHandle);
void CkCrypt2W_getLastErrorXml(HCkCrypt2W cHandle, HCkString retval);
const wchar_t *CkCrypt2W_lastErrorXml(HCkCrypt2W cHandle);
int CkCrypt2W_getNumSignerCerts(HCkCrypt2W cHandle);
int CkCrypt2W_getPaddingScheme(HCkCrypt2W cHandle);
void CkCrypt2W_putPaddingScheme(HCkCrypt2W cHandle, int newVal);
void CkCrypt2W_getPbesAlgorithm(HCkCrypt2W cHandle, HCkString retval);
void CkCrypt2W_putPbesAlgorithm(HCkCrypt2W cHandle, const wchar_t *newVal);
const wchar_t *CkCrypt2W_pbesAlgorithm(HCkCrypt2W cHandle);
void CkCrypt2W_getPbesPassword(HCkCrypt2W cHandle, HCkString retval);
void CkCrypt2W_putPbesPassword(HCkCrypt2W cHandle, const wchar_t *newVal);
const wchar_t *CkCrypt2W_pbesPassword(HCkCrypt2W cHandle);
void CkCrypt2W_getPkcs7CryptAlg(HCkCrypt2W cHandle, HCkString retval);
void CkCrypt2W_putPkcs7CryptAlg(HCkCrypt2W cHandle, const wchar_t *newVal);
const wchar_t *CkCrypt2W_pkcs7CryptAlg(HCkCrypt2W cHandle);
int CkCrypt2W_getRc2EffectiveKeyLength(HCkCrypt2W cHandle);
void CkCrypt2W_putRc2EffectiveKeyLength(HCkCrypt2W cHandle, int newVal);
void CkCrypt2W_getSalt(HCkCrypt2W cHandle, HCkByteData retval);
void CkCrypt2W_putSalt(HCkCrypt2W cHandle, HCkByteData  newVal);
void CkCrypt2W_getSecretKey(HCkCrypt2W cHandle, HCkByteData retval);
void CkCrypt2W_putSecretKey(HCkCrypt2W cHandle, HCkByteData  newVal);
void CkCrypt2W_getUuFilename(HCkCrypt2W cHandle, HCkString retval);
void CkCrypt2W_putUuFilename(HCkCrypt2W cHandle, const wchar_t *newVal);
const wchar_t *CkCrypt2W_uuFilename(HCkCrypt2W cHandle);
void CkCrypt2W_getUuMode(HCkCrypt2W cHandle, HCkString retval);
void CkCrypt2W_putUuMode(HCkCrypt2W cHandle, const wchar_t *newVal);
const wchar_t *CkCrypt2W_uuMode(HCkCrypt2W cHandle);
BOOL CkCrypt2W_getVerboseLogging(HCkCrypt2W cHandle);
void CkCrypt2W_putVerboseLogging(HCkCrypt2W cHandle, BOOL newVal);
void CkCrypt2W_getVersion(HCkCrypt2W cHandle, HCkString retval);
const wchar_t *CkCrypt2W_version(HCkCrypt2W cHandle);
void CkCrypt2W_AddEncryptCert(HCkCrypt2W cHandle, HCkCertW cert);
BOOL CkCrypt2W_AddPfxSourceData(HCkCrypt2W cHandle, HCkByteData pfxBytes, const wchar_t *pfxPassword);
BOOL CkCrypt2W_AddPfxSourceFile(HCkCrypt2W cHandle, const wchar_t *pfxFilePath, const wchar_t *pfxPassword);
BOOL CkCrypt2W_ByteSwap4321(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outBytes);
BOOL CkCrypt2W_BytesToString(HCkCrypt2W cHandle, HCkByteData inData, const wchar_t *charset, HCkString outStr);
const wchar_t *CkCrypt2W_bytesToString(HCkCrypt2W cHandle, HCkByteData inData, const wchar_t *charset);
BOOL CkCrypt2W_CkDecryptFile(HCkCrypt2W cHandle, const wchar_t *srcFile, const wchar_t *destFile);
BOOL CkCrypt2W_CkEncryptFile(HCkCrypt2W cHandle, const wchar_t *srcFile, const wchar_t *destFile);
void CkCrypt2W_ClearEncryptCerts(HCkCrypt2W cHandle);
BOOL CkCrypt2W_CompressBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outData);
BOOL CkCrypt2W_CompressBytesENC(HCkCrypt2W cHandle, HCkByteData data, HCkString outStr);
const wchar_t *CkCrypt2W_compressBytesENC(HCkCrypt2W cHandle, HCkByteData data);
BOOL CkCrypt2W_CompressString(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData outData);
BOOL CkCrypt2W_CompressStringENC(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
const wchar_t *CkCrypt2W_compressStringENC(HCkCrypt2W cHandle, const wchar_t *str);
BOOL CkCrypt2W_CreateDetachedSignature(HCkCrypt2W cHandle, const wchar_t *inFilePath, const wchar_t *outSigFilePath);
BOOL CkCrypt2W_CreateP7M(HCkCrypt2W cHandle, const wchar_t *inFilename, const wchar_t *p7mFilename);
BOOL CkCrypt2W_CreateP7S(HCkCrypt2W cHandle, const wchar_t *inFilename, const wchar_t *outP7sFilename);
BOOL CkCrypt2W_Decode(HCkCrypt2W cHandle, const wchar_t *str, const wchar_t *encoding, HCkByteData outData);
BOOL CkCrypt2W_DecodeString(HCkCrypt2W cHandle, const wchar_t *inStr, const wchar_t *charset, const wchar_t *encoding, HCkString outStr);
const wchar_t *CkCrypt2W_decodeString(HCkCrypt2W cHandle, const wchar_t *inStr, const wchar_t *charset, const wchar_t *encoding);
BOOL CkCrypt2W_DecryptBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outData);
BOOL CkCrypt2W_DecryptBytesENC(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData outData);
BOOL CkCrypt2W_DecryptEncoded(HCkCrypt2W cHandle, const wchar_t *encodedEncryptedData, HCkString outStr);
const wchar_t *CkCrypt2W_decryptEncoded(HCkCrypt2W cHandle, const wchar_t *encodedEncryptedData);
BOOL CkCrypt2W_DecryptString(HCkCrypt2W cHandle, HCkByteData data, HCkString outStr);
const wchar_t *CkCrypt2W_decryptString(HCkCrypt2W cHandle, HCkByteData data);
BOOL CkCrypt2W_DecryptStringENC(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
const wchar_t *CkCrypt2W_decryptStringENC(HCkCrypt2W cHandle, const wchar_t *str);
BOOL CkCrypt2W_Encode(HCkCrypt2W cHandle, HCkByteData byteData, const wchar_t *encoding, HCkString outStr);
const wchar_t *CkCrypt2W_encode(HCkCrypt2W cHandle, HCkByteData byteData, const wchar_t *encoding);
BOOL CkCrypt2W_EncodeBytes(HCkCrypt2W cHandle, const void *pByteData, unsigned long szByteData, const wchar_t *encoding, HCkString outStr);
const wchar_t *CkCrypt2W_encodeBytes(HCkCrypt2W cHandle, const void *pByteData, unsigned long szByteData, const wchar_t *encoding);
BOOL CkCrypt2W_EncodeString(HCkCrypt2W cHandle, const wchar_t *strToEncode, const wchar_t *charsetName, const wchar_t *toEncodingName, HCkString outStr);
const wchar_t *CkCrypt2W_encodeString(HCkCrypt2W cHandle, const wchar_t *strToEncode, const wchar_t *charsetName, const wchar_t *toEncodingName);
BOOL CkCrypt2W_EncryptBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outData);
BOOL CkCrypt2W_EncryptBytesENC(HCkCrypt2W cHandle, HCkByteData data, HCkString outStr);
const wchar_t *CkCrypt2W_encryptBytesENC(HCkCrypt2W cHandle, HCkByteData data);
BOOL CkCrypt2W_EncryptEncoded(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
const wchar_t *CkCrypt2W_encryptEncoded(HCkCrypt2W cHandle, const wchar_t *str);
BOOL CkCrypt2W_EncryptString(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData outData);
BOOL CkCrypt2W_EncryptStringENC(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
const wchar_t *CkCrypt2W_encryptStringENC(HCkCrypt2W cHandle, const wchar_t *str);
BOOL CkCrypt2W_GenEncodedSecretKey(HCkCrypt2W cHandle, const wchar_t *password, const wchar_t *encoding, HCkString outStr);
const wchar_t *CkCrypt2W_genEncodedSecretKey(HCkCrypt2W cHandle, const wchar_t *password, const wchar_t *encoding);
BOOL CkCrypt2W_GenRandomBytesENC(HCkCrypt2W cHandle, int numBytes, HCkString outStr);
const wchar_t *CkCrypt2W_genRandomBytesENC(HCkCrypt2W cHandle, int numBytes);
BOOL CkCrypt2W_GenerateSecretKey(HCkCrypt2W cHandle, const wchar_t *password, HCkByteData outData);
BOOL CkCrypt2W_GetEncodedIV(HCkCrypt2W cHandle, const wchar_t *encoding, HCkString outIV);
const wchar_t *CkCrypt2W_getEncodedIV(HCkCrypt2W cHandle, const wchar_t *encoding);
BOOL CkCrypt2W_GetEncodedKey(HCkCrypt2W cHandle, const wchar_t *encoding, HCkString outKey);
const wchar_t *CkCrypt2W_getEncodedKey(HCkCrypt2W cHandle, const wchar_t *encoding);
BOOL CkCrypt2W_GetEncodedSalt(HCkCrypt2W cHandle, const wchar_t *encoding, HCkString outStr);
const wchar_t *CkCrypt2W_getEncodedSalt(HCkCrypt2W cHandle, const wchar_t *encoding);
HCkCertW CkCrypt2W_GetLastCert(HCkCrypt2W cHandle);
BOOL CkCrypt2W_GetSignatureSigningTime(HCkCrypt2W cHandle, int index, SYSTEMTIME *outSysTime);
BOOL CkCrypt2W_GetSignatureSigningTimeStr(HCkCrypt2W cHandle, int index, HCkString outStr);
const wchar_t *CkCrypt2W_getSignatureSigningTimeStr(HCkCrypt2W cHandle, int index);
HCkCertW CkCrypt2W_GetSignerCert(HCkCrypt2W cHandle, int index);
BOOL CkCrypt2W_HasSignatureSigningTime(HCkCrypt2W cHandle, int index);
BOOL CkCrypt2W_HashBeginBytes(HCkCrypt2W cHandle, HCkByteData data);
BOOL CkCrypt2W_HashBeginString(HCkCrypt2W cHandle, const wchar_t *strData);
BOOL CkCrypt2W_HashBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outData);
BOOL CkCrypt2W_HashBytesENC(HCkCrypt2W cHandle, HCkByteData data, HCkString outStr);
const wchar_t *CkCrypt2W_hashBytesENC(HCkCrypt2W cHandle, HCkByteData data);
BOOL CkCrypt2W_HashFile(HCkCrypt2W cHandle, const wchar_t *filename, HCkByteData outData);
BOOL CkCrypt2W_HashFileENC(HCkCrypt2W cHandle, const wchar_t *filename, HCkString outStr);
const wchar_t *CkCrypt2W_hashFileENC(HCkCrypt2W cHandle, const wchar_t *filename);
BOOL CkCrypt2W_HashFinal(HCkCrypt2W cHandle, HCkByteData outBytes);
BOOL CkCrypt2W_HashFinalENC(HCkCrypt2W cHandle, HCkString outStr);
const wchar_t *CkCrypt2W_hashFinalENC(HCkCrypt2W cHandle);
BOOL CkCrypt2W_HashMoreBytes(HCkCrypt2W cHandle, HCkByteData data);
BOOL CkCrypt2W_HashMoreString(HCkCrypt2W cHandle, const wchar_t *strData);
BOOL CkCrypt2W_HashString(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData outData);
BOOL CkCrypt2W_HashStringENC(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
const wchar_t *CkCrypt2W_hashStringENC(HCkCrypt2W cHandle, const wchar_t *str);
BOOL CkCrypt2W_HmacBytes(HCkCrypt2W cHandle, HCkByteData inBytes, HCkByteData outHmac);
BOOL CkCrypt2W_HmacBytesENC(HCkCrypt2W cHandle, HCkByteData inBytes, HCkString outEncodedHmac);
const wchar_t *CkCrypt2W_hmacBytesENC(HCkCrypt2W cHandle, HCkByteData inBytes);
BOOL CkCrypt2W_HmacString(HCkCrypt2W cHandle, const wchar_t *inText, HCkByteData outHmac);
BOOL CkCrypt2W_HmacStringENC(HCkCrypt2W cHandle, const wchar_t *inText, HCkString outEncodedHmac);
const wchar_t *CkCrypt2W_hmacStringENC(HCkCrypt2W cHandle, const wchar_t *inText);
BOOL CkCrypt2W_InflateBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outData);
BOOL CkCrypt2W_InflateBytesENC(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData outData);
BOOL CkCrypt2W_InflateString(HCkCrypt2W cHandle, HCkByteData data, HCkString outStr);
const wchar_t *CkCrypt2W_inflateString(HCkCrypt2W cHandle, HCkByteData data);
BOOL CkCrypt2W_InflateStringENC(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
const wchar_t *CkCrypt2W_inflateStringENC(HCkCrypt2W cHandle, const wchar_t *str);
BOOL CkCrypt2W_IsUnlocked(HCkCrypt2W cHandle);
BOOL CkCrypt2W_MySqlAesDecrypt(HCkCrypt2W cHandle, const wchar_t *strEncryptedHex, const wchar_t *strPassword, HCkString outStr);
const wchar_t *CkCrypt2W_mySqlAesDecrypt(HCkCrypt2W cHandle, const wchar_t *strEncryptedHex, const wchar_t *strPassword);
BOOL CkCrypt2W_MySqlAesEncrypt(HCkCrypt2W cHandle, const wchar_t *strData, const wchar_t *strPassword, HCkString outStr);
const wchar_t *CkCrypt2W_mySqlAesEncrypt(HCkCrypt2W cHandle, const wchar_t *strData, const wchar_t *strPassword);
BOOL CkCrypt2W_OpaqueSignBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outData);
BOOL CkCrypt2W_OpaqueSignBytesENC(HCkCrypt2W cHandle, HCkByteData data, HCkString outStr);
const wchar_t *CkCrypt2W_opaqueSignBytesENC(HCkCrypt2W cHandle, HCkByteData data);
BOOL CkCrypt2W_OpaqueSignString(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData outData);
BOOL CkCrypt2W_OpaqueSignStringENC(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
const wchar_t *CkCrypt2W_opaqueSignStringENC(HCkCrypt2W cHandle, const wchar_t *str);
BOOL CkCrypt2W_OpaqueVerifyBytes(HCkCrypt2W cHandle, HCkByteData p7s, HCkByteData outOriginal);
BOOL CkCrypt2W_OpaqueVerifyBytesENC(HCkCrypt2W cHandle, const wchar_t *p7s, HCkByteData outOriginal);
BOOL CkCrypt2W_OpaqueVerifyString(HCkCrypt2W cHandle, HCkByteData p7s, HCkString outOriginal);
const wchar_t *CkCrypt2W_opaqueVerifyString(HCkCrypt2W cHandle, HCkByteData p7s);
BOOL CkCrypt2W_OpaqueVerifyStringENC(HCkCrypt2W cHandle, const wchar_t *p7s, HCkString outOriginal);
const wchar_t *CkCrypt2W_opaqueVerifyStringENC(HCkCrypt2W cHandle, const wchar_t *p7s);
BOOL CkCrypt2W_Pbkdf1(HCkCrypt2W cHandle, const wchar_t *password, const wchar_t *charset, const wchar_t *hashAlg, const wchar_t *salt, int iterationCount, int outputKeyBitLen, const wchar_t *encoding, HCkString outStr);
const wchar_t *CkCrypt2W_pbkdf1(HCkCrypt2W cHandle, const wchar_t *password, const wchar_t *charset, const wchar_t *hashAlg, const wchar_t *salt, int iterationCount, int outputKeyBitLen, const wchar_t *encoding);
BOOL CkCrypt2W_Pbkdf2(HCkCrypt2W cHandle, const wchar_t *password, const wchar_t *charset, const wchar_t *hashAlg, const wchar_t *salt, int iterationCount, int outputKeyBitLen, const wchar_t *encoding, HCkString outStr);
const wchar_t *CkCrypt2W_pbkdf2(HCkCrypt2W cHandle, const wchar_t *password, const wchar_t *charset, const wchar_t *hashAlg, const wchar_t *salt, int iterationCount, int outputKeyBitLen, const wchar_t *encoding);
void CkCrypt2W_RandomizeIV(HCkCrypt2W cHandle);
void CkCrypt2W_RandomizeKey(HCkCrypt2W cHandle);
BOOL CkCrypt2W_ReEncode(HCkCrypt2W cHandle, const wchar_t *encodedData, const wchar_t *fromEncoding, const wchar_t *toEncoding, HCkString outStr);
const wchar_t *CkCrypt2W_reEncode(HCkCrypt2W cHandle, const wchar_t *encodedData, const wchar_t *fromEncoding, const wchar_t *toEncoding);
BOOL CkCrypt2W_ReadFile(HCkCrypt2W cHandle, const wchar_t *filename, HCkByteData outBytes);
BOOL CkCrypt2W_SaveLastError(HCkCrypt2W cHandle, const wchar_t *path);
#if defined(CK_CSP_INCLUDED)
BOOL CkCrypt2W_SetCSP(HCkCrypt2W cHandle, HCkCspW csp);
#endif
BOOL CkCrypt2W_SetDecryptCert(HCkCrypt2W cHandle, HCkCertW cert);
BOOL CkCrypt2W_SetDecryptCert2(HCkCrypt2W cHandle, HCkCertW cert, HCkPrivateKeyW key);
void CkCrypt2W_SetEncodedIV(HCkCrypt2W cHandle, const wchar_t *ivStr, const wchar_t *encoding);
void CkCrypt2W_SetEncodedKey(HCkCrypt2W cHandle, const wchar_t *keyStr, const wchar_t *encoding);
void CkCrypt2W_SetEncodedSalt(HCkCrypt2W cHandle, const wchar_t *saltStr, const wchar_t *encoding);
BOOL CkCrypt2W_SetEncryptCert(HCkCrypt2W cHandle, HCkCertW cert);
void CkCrypt2W_SetHmacKeyBytes(HCkCrypt2W cHandle, HCkByteData keyBytes);
void CkCrypt2W_SetHmacKeyEncoded(HCkCrypt2W cHandle, const wchar_t *key, const wchar_t *encoding);
void CkCrypt2W_SetHmacKeyString(HCkCrypt2W cHandle, const wchar_t *key);
void CkCrypt2W_SetIV(HCkCrypt2W cHandle, const unsigned char *pByteData, unsigned long szByteData);
void CkCrypt2W_SetSecretKey(HCkCrypt2W cHandle, const unsigned char *pByteData, unsigned long szByteData);
void CkCrypt2W_SetSecretKeyViaPassword(HCkCrypt2W cHandle, const wchar_t *password);
BOOL CkCrypt2W_SetSigningCert(HCkCrypt2W cHandle, HCkCertW cert);
BOOL CkCrypt2W_SetSigningCert2(HCkCrypt2W cHandle, HCkCertW cert, HCkPrivateKeyW privateKey);
BOOL CkCrypt2W_SetVerifyCert(HCkCrypt2W cHandle, HCkCertW cert);
BOOL CkCrypt2W_SignBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData outData);
BOOL CkCrypt2W_SignBytesENC(HCkCrypt2W cHandle, HCkByteData data, HCkString outStr);
const wchar_t *CkCrypt2W_signBytesENC(HCkCrypt2W cHandle, HCkByteData data);
BOOL CkCrypt2W_SignString(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData outData);
BOOL CkCrypt2W_SignStringENC(HCkCrypt2W cHandle, const wchar_t *str, HCkString outStr);
const wchar_t *CkCrypt2W_signStringENC(HCkCrypt2W cHandle, const wchar_t *str);
BOOL CkCrypt2W_StringToBytes(HCkCrypt2W cHandle, const wchar_t *inStr, const wchar_t *charset, HCkByteData outBytes);
BOOL CkCrypt2W_TrimEndingWith(HCkCrypt2W cHandle, const wchar_t *inStr, const wchar_t *ending, HCkString outStr);
const wchar_t *CkCrypt2W_trimEndingWith(HCkCrypt2W cHandle, const wchar_t *inStr, const wchar_t *ending);
BOOL CkCrypt2W_UnlockComponent(HCkCrypt2W cHandle, const wchar_t *b1);
BOOL CkCrypt2W_VerifyBytes(HCkCrypt2W cHandle, HCkByteData data, HCkByteData sig);
BOOL CkCrypt2W_VerifyBytesENC(HCkCrypt2W cHandle, HCkByteData data, const wchar_t *encodedSig);
BOOL CkCrypt2W_VerifyDetachedSignature(HCkCrypt2W cHandle, const wchar_t *inFilename, const wchar_t *p7sFilename);
BOOL CkCrypt2W_VerifyP7M(HCkCrypt2W cHandle, const wchar_t *p7mFilename, const wchar_t *outFilename);
BOOL CkCrypt2W_VerifyP7S(HCkCrypt2W cHandle, const wchar_t *inFilename, const wchar_t *p7sFilename);
BOOL CkCrypt2W_VerifyString(HCkCrypt2W cHandle, const wchar_t *str, HCkByteData sig);
BOOL CkCrypt2W_VerifyStringENC(HCkCrypt2W cHandle, const wchar_t *str, const wchar_t *encodedSig);
BOOL CkCrypt2W_WriteFile(HCkCrypt2W cHandle, const wchar_t *filename, HCkByteData fileData);
#endif