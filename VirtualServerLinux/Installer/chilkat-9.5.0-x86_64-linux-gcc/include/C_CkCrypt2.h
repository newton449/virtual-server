// This is a generated source file for Chilkat version 9.5.0.21
#ifndef _C_CkCrypt2_H
#define _C_CkCrypt2_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"

HCkCrypt2 CkCrypt2_Create(void);
void CkCrypt2_Dispose(HCkCrypt2 handle);
int CkCrypt2_getBlockSize(HCkCrypt2 cHandle);
BOOL CkCrypt2_getCadesEnabled(HCkCrypt2 cHandle);
void CkCrypt2_putCadesEnabled(HCkCrypt2 cHandle, BOOL newVal);
void CkCrypt2_getCadesSigPolicyHash(HCkCrypt2 cHandle, HCkString retval);
void CkCrypt2_putCadesSigPolicyHash(HCkCrypt2 cHandle, const char *newVal);
const char *CkCrypt2_cadesSigPolicyHash(HCkCrypt2 cHandle);
void CkCrypt2_getCadesSigPolicyId(HCkCrypt2 cHandle, HCkString retval);
void CkCrypt2_putCadesSigPolicyId(HCkCrypt2 cHandle, const char *newVal);
const char *CkCrypt2_cadesSigPolicyId(HCkCrypt2 cHandle);
void CkCrypt2_getCadesSigPolicyUri(HCkCrypt2 cHandle, HCkString retval);
void CkCrypt2_putCadesSigPolicyUri(HCkCrypt2 cHandle, const char *newVal);
const char *CkCrypt2_cadesSigPolicyUri(HCkCrypt2 cHandle);
void CkCrypt2_getCharset(HCkCrypt2 cHandle, HCkString retval);
void CkCrypt2_putCharset(HCkCrypt2 cHandle, const char *newVal);
const char *CkCrypt2_charset(HCkCrypt2 cHandle);
void CkCrypt2_getCipherMode(HCkCrypt2 cHandle, HCkString retval);
void CkCrypt2_putCipherMode(HCkCrypt2 cHandle, const char *newVal);
const char *CkCrypt2_cipherMode(HCkCrypt2 cHandle);
void CkCrypt2_getCompressionAlgorithm(HCkCrypt2 cHandle, HCkString retval);
void CkCrypt2_putCompressionAlgorithm(HCkCrypt2 cHandle, const char *newVal);
const char *CkCrypt2_compressionAlgorithm(HCkCrypt2 cHandle);
void CkCrypt2_getCryptAlgorithm(HCkCrypt2 cHandle, HCkString retval);
void CkCrypt2_putCryptAlgorithm(HCkCrypt2 cHandle, const char *newVal);
const char *CkCrypt2_cryptAlgorithm(HCkCrypt2 cHandle);
void CkCrypt2_getDebugLogFilePath(HCkCrypt2 cHandle, HCkString retval);
void CkCrypt2_putDebugLogFilePath(HCkCrypt2 cHandle, const char *newVal);
const char *CkCrypt2_debugLogFilePath(HCkCrypt2 cHandle);
void CkCrypt2_getEncodingMode(HCkCrypt2 cHandle, HCkString retval);
void CkCrypt2_putEncodingMode(HCkCrypt2 cHandle, const char *newVal);
const char *CkCrypt2_encodingMode(HCkCrypt2 cHandle);
BOOL CkCrypt2_getFirstChunk(HCkCrypt2 cHandle);
void CkCrypt2_putFirstChunk(HCkCrypt2 cHandle, BOOL newVal);
void CkCrypt2_getHashAlgorithm(HCkCrypt2 cHandle, HCkString retval);
void CkCrypt2_putHashAlgorithm(HCkCrypt2 cHandle, const char *newVal);
const char *CkCrypt2_hashAlgorithm(HCkCrypt2 cHandle);
int CkCrypt2_getHavalRounds(HCkCrypt2 cHandle);
void CkCrypt2_putHavalRounds(HCkCrypt2 cHandle, int newVal);
int CkCrypt2_getHeartbeatMs(HCkCrypt2 cHandle);
void CkCrypt2_putHeartbeatMs(HCkCrypt2 cHandle, int newVal);
void CkCrypt2_getIV(HCkCrypt2 cHandle, HCkByteData retval);
void CkCrypt2_putIV(HCkCrypt2 cHandle, HCkByteData  newVal);
BOOL CkCrypt2_getIncludeCertChain(HCkCrypt2 cHandle);
void CkCrypt2_putIncludeCertChain(HCkCrypt2 cHandle, BOOL newVal);
int CkCrypt2_getIterationCount(HCkCrypt2 cHandle);
void CkCrypt2_putIterationCount(HCkCrypt2 cHandle, int newVal);
int CkCrypt2_getKeyLength(HCkCrypt2 cHandle);
void CkCrypt2_putKeyLength(HCkCrypt2 cHandle, int newVal);
BOOL CkCrypt2_getLastChunk(HCkCrypt2 cHandle);
void CkCrypt2_putLastChunk(HCkCrypt2 cHandle, BOOL newVal);
void CkCrypt2_getLastErrorHtml(HCkCrypt2 cHandle, HCkString retval);
const char *CkCrypt2_lastErrorHtml(HCkCrypt2 cHandle);
void CkCrypt2_getLastErrorText(HCkCrypt2 cHandle, HCkString retval);
const char *CkCrypt2_lastErrorText(HCkCrypt2 cHandle);
void CkCrypt2_getLastErrorXml(HCkCrypt2 cHandle, HCkString retval);
const char *CkCrypt2_lastErrorXml(HCkCrypt2 cHandle);
int CkCrypt2_getNumSignerCerts(HCkCrypt2 cHandle);
int CkCrypt2_getPaddingScheme(HCkCrypt2 cHandle);
void CkCrypt2_putPaddingScheme(HCkCrypt2 cHandle, int newVal);
void CkCrypt2_getPbesAlgorithm(HCkCrypt2 cHandle, HCkString retval);
void CkCrypt2_putPbesAlgorithm(HCkCrypt2 cHandle, const char *newVal);
const char *CkCrypt2_pbesAlgorithm(HCkCrypt2 cHandle);
void CkCrypt2_getPbesPassword(HCkCrypt2 cHandle, HCkString retval);
void CkCrypt2_putPbesPassword(HCkCrypt2 cHandle, const char *newVal);
const char *CkCrypt2_pbesPassword(HCkCrypt2 cHandle);
void CkCrypt2_getPkcs7CryptAlg(HCkCrypt2 cHandle, HCkString retval);
void CkCrypt2_putPkcs7CryptAlg(HCkCrypt2 cHandle, const char *newVal);
const char *CkCrypt2_pkcs7CryptAlg(HCkCrypt2 cHandle);
int CkCrypt2_getRc2EffectiveKeyLength(HCkCrypt2 cHandle);
void CkCrypt2_putRc2EffectiveKeyLength(HCkCrypt2 cHandle, int newVal);
void CkCrypt2_getSalt(HCkCrypt2 cHandle, HCkByteData retval);
void CkCrypt2_putSalt(HCkCrypt2 cHandle, HCkByteData  newVal);
void CkCrypt2_getSecretKey(HCkCrypt2 cHandle, HCkByteData retval);
void CkCrypt2_putSecretKey(HCkCrypt2 cHandle, HCkByteData  newVal);
BOOL CkCrypt2_getUtf8(HCkCrypt2 cHandle);
void CkCrypt2_putUtf8(HCkCrypt2 cHandle, BOOL newVal);
void CkCrypt2_getUuFilename(HCkCrypt2 cHandle, HCkString retval);
void CkCrypt2_putUuFilename(HCkCrypt2 cHandle, const char *newVal);
const char *CkCrypt2_uuFilename(HCkCrypt2 cHandle);
void CkCrypt2_getUuMode(HCkCrypt2 cHandle, HCkString retval);
void CkCrypt2_putUuMode(HCkCrypt2 cHandle, const char *newVal);
const char *CkCrypt2_uuMode(HCkCrypt2 cHandle);
BOOL CkCrypt2_getVerboseLogging(HCkCrypt2 cHandle);
void CkCrypt2_putVerboseLogging(HCkCrypt2 cHandle, BOOL newVal);
void CkCrypt2_getVersion(HCkCrypt2 cHandle, HCkString retval);
const char *CkCrypt2_version(HCkCrypt2 cHandle);
void CkCrypt2_AddEncryptCert(HCkCrypt2 cHandle, HCkCert cert);
BOOL CkCrypt2_AddPfxSourceData(HCkCrypt2 cHandle, HCkByteData pfxBytes, const char *pfxPassword);
BOOL CkCrypt2_AddPfxSourceFile(HCkCrypt2 cHandle, const char *pfxFilePath, const char *pfxPassword);
BOOL CkCrypt2_ByteSwap4321(HCkCrypt2 cHandle, HCkByteData data, HCkByteData outBytes);
BOOL CkCrypt2_BytesToString(HCkCrypt2 cHandle, HCkByteData inData, const char *charset, HCkString outStr);
const char *CkCrypt2_bytesToString(HCkCrypt2 cHandle, HCkByteData inData, const char *charset);
BOOL CkCrypt2_CkDecryptFile(HCkCrypt2 cHandle, const char *srcFile, const char *destFile);
BOOL CkCrypt2_CkEncryptFile(HCkCrypt2 cHandle, const char *srcFile, const char *destFile);
void CkCrypt2_ClearEncryptCerts(HCkCrypt2 cHandle);
BOOL CkCrypt2_CompressBytes(HCkCrypt2 cHandle, HCkByteData data, HCkByteData outData);
BOOL CkCrypt2_CompressBytesENC(HCkCrypt2 cHandle, HCkByteData data, HCkString outStr);
const char *CkCrypt2_compressBytesENC(HCkCrypt2 cHandle, HCkByteData data);
BOOL CkCrypt2_CompressString(HCkCrypt2 cHandle, const char *str, HCkByteData outData);
BOOL CkCrypt2_CompressStringENC(HCkCrypt2 cHandle, const char *str, HCkString outStr);
const char *CkCrypt2_compressStringENC(HCkCrypt2 cHandle, const char *str);
BOOL CkCrypt2_CreateDetachedSignature(HCkCrypt2 cHandle, const char *inFilePath, const char *outSigFilePath);
BOOL CkCrypt2_CreateP7M(HCkCrypt2 cHandle, const char *inFilename, const char *p7mFilename);
BOOL CkCrypt2_CreateP7S(HCkCrypt2 cHandle, const char *inFilename, const char *outP7sFilename);
BOOL CkCrypt2_Decode(HCkCrypt2 cHandle, const char *str, const char *encoding, HCkByteData outData);
BOOL CkCrypt2_DecodeString(HCkCrypt2 cHandle, const char *inStr, const char *charset, const char *encoding, HCkString outStr);
const char *CkCrypt2_decodeString(HCkCrypt2 cHandle, const char *inStr, const char *charset, const char *encoding);
BOOL CkCrypt2_DecryptBytes(HCkCrypt2 cHandle, HCkByteData data, HCkByteData outData);
BOOL CkCrypt2_DecryptBytesENC(HCkCrypt2 cHandle, const char *str, HCkByteData outData);
BOOL CkCrypt2_DecryptEncoded(HCkCrypt2 cHandle, const char *encodedEncryptedData, HCkString outStr);
const char *CkCrypt2_decryptEncoded(HCkCrypt2 cHandle, const char *encodedEncryptedData);
BOOL CkCrypt2_DecryptString(HCkCrypt2 cHandle, HCkByteData data, HCkString outStr);
const char *CkCrypt2_decryptString(HCkCrypt2 cHandle, HCkByteData data);
BOOL CkCrypt2_DecryptStringENC(HCkCrypt2 cHandle, const char *str, HCkString outStr);
const char *CkCrypt2_decryptStringENC(HCkCrypt2 cHandle, const char *str);
BOOL CkCrypt2_Encode(HCkCrypt2 cHandle, HCkByteData byteData, const char *encoding, HCkString outStr);
const char *CkCrypt2_encode(HCkCrypt2 cHandle, HCkByteData byteData, const char *encoding);
BOOL CkCrypt2_EncodeBytes(HCkCrypt2 cHandle, const void *pByteData, unsigned long szByteData, const char *encoding, HCkString outStr);
const char *CkCrypt2_encodeBytes(HCkCrypt2 cHandle, const void *pByteData, unsigned long szByteData, const char *encoding);
BOOL CkCrypt2_EncodeString(HCkCrypt2 cHandle, const char *strToEncode, const char *charsetName, const char *toEncodingName, HCkString outStr);
const char *CkCrypt2_encodeString(HCkCrypt2 cHandle, const char *strToEncode, const char *charsetName, const char *toEncodingName);
BOOL CkCrypt2_EncryptBytes(HCkCrypt2 cHandle, HCkByteData data, HCkByteData outData);
BOOL CkCrypt2_EncryptBytesENC(HCkCrypt2 cHandle, HCkByteData data, HCkString outStr);
const char *CkCrypt2_encryptBytesENC(HCkCrypt2 cHandle, HCkByteData data);
BOOL CkCrypt2_EncryptEncoded(HCkCrypt2 cHandle, const char *str, HCkString outStr);
const char *CkCrypt2_encryptEncoded(HCkCrypt2 cHandle, const char *str);
BOOL CkCrypt2_EncryptString(HCkCrypt2 cHandle, const char *str, HCkByteData outData);
BOOL CkCrypt2_EncryptStringENC(HCkCrypt2 cHandle, const char *str, HCkString outStr);
const char *CkCrypt2_encryptStringENC(HCkCrypt2 cHandle, const char *str);
BOOL CkCrypt2_GenEncodedSecretKey(HCkCrypt2 cHandle, const char *password, const char *encoding, HCkString outStr);
const char *CkCrypt2_genEncodedSecretKey(HCkCrypt2 cHandle, const char *password, const char *encoding);
BOOL CkCrypt2_GenRandomBytesENC(HCkCrypt2 cHandle, int numBytes, HCkString outStr);
const char *CkCrypt2_genRandomBytesENC(HCkCrypt2 cHandle, int numBytes);
BOOL CkCrypt2_GenerateSecretKey(HCkCrypt2 cHandle, const char *password, HCkByteData outData);
BOOL CkCrypt2_GetEncodedIV(HCkCrypt2 cHandle, const char *encoding, HCkString outIV);
const char *CkCrypt2_getEncodedIV(HCkCrypt2 cHandle, const char *encoding);
BOOL CkCrypt2_GetEncodedKey(HCkCrypt2 cHandle, const char *encoding, HCkString outKey);
const char *CkCrypt2_getEncodedKey(HCkCrypt2 cHandle, const char *encoding);
BOOL CkCrypt2_GetEncodedSalt(HCkCrypt2 cHandle, const char *encoding, HCkString outStr);
const char *CkCrypt2_getEncodedSalt(HCkCrypt2 cHandle, const char *encoding);
HCkCert CkCrypt2_GetLastCert(HCkCrypt2 cHandle);
BOOL CkCrypt2_GetSignatureSigningTime(HCkCrypt2 cHandle, int index, SYSTEMTIME *outSysTime);
BOOL CkCrypt2_GetSignatureSigningTimeStr(HCkCrypt2 cHandle, int index, HCkString outStr);
const char *CkCrypt2_getSignatureSigningTimeStr(HCkCrypt2 cHandle, int index);
HCkCert CkCrypt2_GetSignerCert(HCkCrypt2 cHandle, int index);
BOOL CkCrypt2_HasSignatureSigningTime(HCkCrypt2 cHandle, int index);
BOOL CkCrypt2_HashBeginBytes(HCkCrypt2 cHandle, HCkByteData data);
BOOL CkCrypt2_HashBeginString(HCkCrypt2 cHandle, const char *strData);
BOOL CkCrypt2_HashBytes(HCkCrypt2 cHandle, HCkByteData data, HCkByteData outData);
BOOL CkCrypt2_HashBytesENC(HCkCrypt2 cHandle, HCkByteData data, HCkString outStr);
const char *CkCrypt2_hashBytesENC(HCkCrypt2 cHandle, HCkByteData data);
BOOL CkCrypt2_HashFile(HCkCrypt2 cHandle, const char *filename, HCkByteData outData);
BOOL CkCrypt2_HashFileENC(HCkCrypt2 cHandle, const char *filename, HCkString outStr);
const char *CkCrypt2_hashFileENC(HCkCrypt2 cHandle, const char *filename);
BOOL CkCrypt2_HashFinal(HCkCrypt2 cHandle, HCkByteData outBytes);
BOOL CkCrypt2_HashFinalENC(HCkCrypt2 cHandle, HCkString outStr);
const char *CkCrypt2_hashFinalENC(HCkCrypt2 cHandle);
BOOL CkCrypt2_HashMoreBytes(HCkCrypt2 cHandle, HCkByteData data);
BOOL CkCrypt2_HashMoreString(HCkCrypt2 cHandle, const char *strData);
BOOL CkCrypt2_HashString(HCkCrypt2 cHandle, const char *str, HCkByteData outData);
BOOL CkCrypt2_HashStringENC(HCkCrypt2 cHandle, const char *str, HCkString outStr);
const char *CkCrypt2_hashStringENC(HCkCrypt2 cHandle, const char *str);
BOOL CkCrypt2_HmacBytes(HCkCrypt2 cHandle, HCkByteData inBytes, HCkByteData outHmac);
BOOL CkCrypt2_HmacBytesENC(HCkCrypt2 cHandle, HCkByteData inBytes, HCkString outEncodedHmac);
const char *CkCrypt2_hmacBytesENC(HCkCrypt2 cHandle, HCkByteData inBytes);
BOOL CkCrypt2_HmacString(HCkCrypt2 cHandle, const char *inText, HCkByteData outHmac);
BOOL CkCrypt2_HmacStringENC(HCkCrypt2 cHandle, const char *inText, HCkString outEncodedHmac);
const char *CkCrypt2_hmacStringENC(HCkCrypt2 cHandle, const char *inText);
BOOL CkCrypt2_InflateBytes(HCkCrypt2 cHandle, HCkByteData data, HCkByteData outData);
BOOL CkCrypt2_InflateBytesENC(HCkCrypt2 cHandle, const char *str, HCkByteData outData);
BOOL CkCrypt2_InflateString(HCkCrypt2 cHandle, HCkByteData data, HCkString outStr);
const char *CkCrypt2_inflateString(HCkCrypt2 cHandle, HCkByteData data);
BOOL CkCrypt2_InflateStringENC(HCkCrypt2 cHandle, const char *str, HCkString outStr);
const char *CkCrypt2_inflateStringENC(HCkCrypt2 cHandle, const char *str);
BOOL CkCrypt2_IsUnlocked(HCkCrypt2 cHandle);
BOOL CkCrypt2_MySqlAesDecrypt(HCkCrypt2 cHandle, const char *strEncryptedHex, const char *strPassword, HCkString outStr);
const char *CkCrypt2_mySqlAesDecrypt(HCkCrypt2 cHandle, const char *strEncryptedHex, const char *strPassword);
BOOL CkCrypt2_MySqlAesEncrypt(HCkCrypt2 cHandle, const char *strData, const char *strPassword, HCkString outStr);
const char *CkCrypt2_mySqlAesEncrypt(HCkCrypt2 cHandle, const char *strData, const char *strPassword);
BOOL CkCrypt2_OpaqueSignBytes(HCkCrypt2 cHandle, HCkByteData data, HCkByteData outData);
BOOL CkCrypt2_OpaqueSignBytesENC(HCkCrypt2 cHandle, HCkByteData data, HCkString outStr);
const char *CkCrypt2_opaqueSignBytesENC(HCkCrypt2 cHandle, HCkByteData data);
BOOL CkCrypt2_OpaqueSignString(HCkCrypt2 cHandle, const char *str, HCkByteData outData);
BOOL CkCrypt2_OpaqueSignStringENC(HCkCrypt2 cHandle, const char *str, HCkString outStr);
const char *CkCrypt2_opaqueSignStringENC(HCkCrypt2 cHandle, const char *str);
BOOL CkCrypt2_OpaqueVerifyBytes(HCkCrypt2 cHandle, HCkByteData p7s, HCkByteData outOriginal);
BOOL CkCrypt2_OpaqueVerifyBytesENC(HCkCrypt2 cHandle, const char *p7s, HCkByteData outOriginal);
BOOL CkCrypt2_OpaqueVerifyString(HCkCrypt2 cHandle, HCkByteData p7s, HCkString outOriginal);
const char *CkCrypt2_opaqueVerifyString(HCkCrypt2 cHandle, HCkByteData p7s);
BOOL CkCrypt2_OpaqueVerifyStringENC(HCkCrypt2 cHandle, const char *p7s, HCkString outOriginal);
const char *CkCrypt2_opaqueVerifyStringENC(HCkCrypt2 cHandle, const char *p7s);
BOOL CkCrypt2_Pbkdf1(HCkCrypt2 cHandle, const char *password, const char *charset, const char *hashAlg, const char *salt, int iterationCount, int outputKeyBitLen, const char *encoding, HCkString outStr);
const char *CkCrypt2_pbkdf1(HCkCrypt2 cHandle, const char *password, const char *charset, const char *hashAlg, const char *salt, int iterationCount, int outputKeyBitLen, const char *encoding);
BOOL CkCrypt2_Pbkdf2(HCkCrypt2 cHandle, const char *password, const char *charset, const char *hashAlg, const char *salt, int iterationCount, int outputKeyBitLen, const char *encoding, HCkString outStr);
const char *CkCrypt2_pbkdf2(HCkCrypt2 cHandle, const char *password, const char *charset, const char *hashAlg, const char *salt, int iterationCount, int outputKeyBitLen, const char *encoding);
void CkCrypt2_RandomizeIV(HCkCrypt2 cHandle);
void CkCrypt2_RandomizeKey(HCkCrypt2 cHandle);
BOOL CkCrypt2_ReEncode(HCkCrypt2 cHandle, const char *encodedData, const char *fromEncoding, const char *toEncoding, HCkString outStr);
const char *CkCrypt2_reEncode(HCkCrypt2 cHandle, const char *encodedData, const char *fromEncoding, const char *toEncoding);
BOOL CkCrypt2_ReadFile(HCkCrypt2 cHandle, const char *filename, HCkByteData outBytes);
BOOL CkCrypt2_SaveLastError(HCkCrypt2 cHandle, const char *path);
#if defined(CK_CSP_INCLUDED)
BOOL CkCrypt2_SetCSP(HCkCrypt2 cHandle, HCkCsp csp);
#endif
BOOL CkCrypt2_SetDecryptCert(HCkCrypt2 cHandle, HCkCert cert);
BOOL CkCrypt2_SetDecryptCert2(HCkCrypt2 cHandle, HCkCert cert, HCkPrivateKey key);
void CkCrypt2_SetEncodedIV(HCkCrypt2 cHandle, const char *ivStr, const char *encoding);
void CkCrypt2_SetEncodedKey(HCkCrypt2 cHandle, const char *keyStr, const char *encoding);
void CkCrypt2_SetEncodedSalt(HCkCrypt2 cHandle, const char *saltStr, const char *encoding);
BOOL CkCrypt2_SetEncryptCert(HCkCrypt2 cHandle, HCkCert cert);
void CkCrypt2_SetHmacKeyBytes(HCkCrypt2 cHandle, HCkByteData keyBytes);
void CkCrypt2_SetHmacKeyEncoded(HCkCrypt2 cHandle, const char *key, const char *encoding);
void CkCrypt2_SetHmacKeyString(HCkCrypt2 cHandle, const char *key);
void CkCrypt2_SetIV(HCkCrypt2 cHandle, const unsigned char *pByteData, unsigned long szByteData);
void CkCrypt2_SetSecretKey(HCkCrypt2 cHandle, const unsigned char *pByteData, unsigned long szByteData);
void CkCrypt2_SetSecretKeyViaPassword(HCkCrypt2 cHandle, const char *password);
BOOL CkCrypt2_SetSigningCert(HCkCrypt2 cHandle, HCkCert cert);
BOOL CkCrypt2_SetSigningCert2(HCkCrypt2 cHandle, HCkCert cert, HCkPrivateKey privateKey);
BOOL CkCrypt2_SetVerifyCert(HCkCrypt2 cHandle, HCkCert cert);
BOOL CkCrypt2_SignBytes(HCkCrypt2 cHandle, HCkByteData data, HCkByteData outData);
BOOL CkCrypt2_SignBytesENC(HCkCrypt2 cHandle, HCkByteData data, HCkString outStr);
const char *CkCrypt2_signBytesENC(HCkCrypt2 cHandle, HCkByteData data);
BOOL CkCrypt2_SignString(HCkCrypt2 cHandle, const char *str, HCkByteData outData);
BOOL CkCrypt2_SignStringENC(HCkCrypt2 cHandle, const char *str, HCkString outStr);
const char *CkCrypt2_signStringENC(HCkCrypt2 cHandle, const char *str);
BOOL CkCrypt2_StringToBytes(HCkCrypt2 cHandle, const char *inStr, const char *charset, HCkByteData outBytes);
BOOL CkCrypt2_TrimEndingWith(HCkCrypt2 cHandle, const char *inStr, const char *ending, HCkString outStr);
const char *CkCrypt2_trimEndingWith(HCkCrypt2 cHandle, const char *inStr, const char *ending);
BOOL CkCrypt2_UnlockComponent(HCkCrypt2 cHandle, const char *b1);
BOOL CkCrypt2_VerifyBytes(HCkCrypt2 cHandle, HCkByteData data, HCkByteData sig);
BOOL CkCrypt2_VerifyBytesENC(HCkCrypt2 cHandle, HCkByteData data, const char *encodedSig);
BOOL CkCrypt2_VerifyDetachedSignature(HCkCrypt2 cHandle, const char *inFilename, const char *p7sFilename);
BOOL CkCrypt2_VerifyP7M(HCkCrypt2 cHandle, const char *p7mFilename, const char *outFilename);
BOOL CkCrypt2_VerifyP7S(HCkCrypt2 cHandle, const char *inFilename, const char *p7sFilename);
BOOL CkCrypt2_VerifyString(HCkCrypt2 cHandle, const char *str, HCkByteData sig);
BOOL CkCrypt2_VerifyStringENC(HCkCrypt2 cHandle, const char *str, const char *encodedSig);
BOOL CkCrypt2_WriteFile(HCkCrypt2 cHandle, const char *filename, HCkByteData fileData);
#endif
