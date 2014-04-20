// This is a generated source file for Chilkat version 9.5.0.21
#ifndef _C_CkEmail_H
#define _C_CkEmail_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"

HCkEmail CkEmail_Create(void);
void CkEmail_Dispose(HCkEmail handle);
void CkEmail_getBody(HCkEmail cHandle, HCkString retval);
void CkEmail_putBody(HCkEmail cHandle, const char *newVal);
const char *CkEmail_body(HCkEmail cHandle);
void CkEmail_getBounceAddress(HCkEmail cHandle, HCkString retval);
void CkEmail_putBounceAddress(HCkEmail cHandle, const char *newVal);
const char *CkEmail_bounceAddress(HCkEmail cHandle);
void CkEmail_getCharset(HCkEmail cHandle, HCkString retval);
void CkEmail_putCharset(HCkEmail cHandle, const char *newVal);
const char *CkEmail_charset(HCkEmail cHandle);
void CkEmail_getDebugLogFilePath(HCkEmail cHandle, HCkString retval);
void CkEmail_putDebugLogFilePath(HCkEmail cHandle, const char *newVal);
const char *CkEmail_debugLogFilePath(HCkEmail cHandle);
BOOL CkEmail_getDecrypted(HCkEmail cHandle);
void CkEmail_getEmailDate(HCkEmail cHandle, SYSTEMTIME *retval);
void CkEmail_putEmailDate(HCkEmail cHandle, SYSTEMTIME *newVal);
void CkEmail_getEmailDateStr(HCkEmail cHandle, HCkString retval);
void CkEmail_putEmailDateStr(HCkEmail cHandle, const char *newVal);
const char *CkEmail_emailDateStr(HCkEmail cHandle);
void CkEmail_getEncryptedBy(HCkEmail cHandle, HCkString retval);
const char *CkEmail_encryptedBy(HCkEmail cHandle);
void CkEmail_getFileDistList(HCkEmail cHandle, HCkString retval);
void CkEmail_putFileDistList(HCkEmail cHandle, const char *newVal);
const char *CkEmail_fileDistList(HCkEmail cHandle);
void CkEmail_getFrom(HCkEmail cHandle, HCkString retval);
void CkEmail_putFrom(HCkEmail cHandle, const char *newVal);
const char *CkEmail_ck_from(HCkEmail cHandle);
void CkEmail_getFromAddress(HCkEmail cHandle, HCkString retval);
void CkEmail_putFromAddress(HCkEmail cHandle, const char *newVal);
const char *CkEmail_fromAddress(HCkEmail cHandle);
void CkEmail_getFromName(HCkEmail cHandle, HCkString retval);
void CkEmail_putFromName(HCkEmail cHandle, const char *newVal);
const char *CkEmail_fromName(HCkEmail cHandle);
void CkEmail_getHeader(HCkEmail cHandle, HCkString retval);
const char *CkEmail_header(HCkEmail cHandle);
void CkEmail_getLanguage(HCkEmail cHandle, HCkString retval);
const char *CkEmail_language(HCkEmail cHandle);
void CkEmail_getLastErrorHtml(HCkEmail cHandle, HCkString retval);
const char *CkEmail_lastErrorHtml(HCkEmail cHandle);
void CkEmail_getLastErrorText(HCkEmail cHandle, HCkString retval);
const char *CkEmail_lastErrorText(HCkEmail cHandle);
void CkEmail_getLastErrorXml(HCkEmail cHandle, HCkString retval);
const char *CkEmail_lastErrorXml(HCkEmail cHandle);
void CkEmail_getLocalDate(HCkEmail cHandle, SYSTEMTIME *retval);
void CkEmail_putLocalDate(HCkEmail cHandle, SYSTEMTIME *newVal);
void CkEmail_getLocalDateStr(HCkEmail cHandle, HCkString retval);
void CkEmail_putLocalDateStr(HCkEmail cHandle, const char *newVal);
const char *CkEmail_localDateStr(HCkEmail cHandle);
void CkEmail_getMailer(HCkEmail cHandle, HCkString retval);
void CkEmail_putMailer(HCkEmail cHandle, const char *newVal);
const char *CkEmail_mailer(HCkEmail cHandle);
int CkEmail_getNumAlternatives(HCkEmail cHandle);
int CkEmail_getNumAttachedMessages(HCkEmail cHandle);
int CkEmail_getNumAttachments(HCkEmail cHandle);
int CkEmail_getNumBcc(HCkEmail cHandle);
int CkEmail_getNumCC(HCkEmail cHandle);
int CkEmail_getNumDaysOld(HCkEmail cHandle);
int CkEmail_getNumHeaderFields(HCkEmail cHandle);
int CkEmail_getNumRelatedItems(HCkEmail cHandle);
int CkEmail_getNumReplacePatterns(HCkEmail cHandle);
int CkEmail_getNumReports(HCkEmail cHandle);
int CkEmail_getNumTo(HCkEmail cHandle);
BOOL CkEmail_getOverwriteExisting(HCkEmail cHandle);
void CkEmail_putOverwriteExisting(HCkEmail cHandle, BOOL newVal);
void CkEmail_getPkcs7CryptAlg(HCkEmail cHandle, HCkString retval);
void CkEmail_putPkcs7CryptAlg(HCkEmail cHandle, const char *newVal);
const char *CkEmail_pkcs7CryptAlg(HCkEmail cHandle);
int CkEmail_getPkcs7KeyLength(HCkEmail cHandle);
void CkEmail_putPkcs7KeyLength(HCkEmail cHandle, int newVal);
void CkEmail_getPreferredCharset(HCkEmail cHandle, HCkString retval);
void CkEmail_putPreferredCharset(HCkEmail cHandle, const char *newVal);
const char *CkEmail_preferredCharset(HCkEmail cHandle);
BOOL CkEmail_getPrependHeaders(HCkEmail cHandle);
void CkEmail_putPrependHeaders(HCkEmail cHandle, BOOL newVal);
BOOL CkEmail_getReceivedEncrypted(HCkEmail cHandle);
BOOL CkEmail_getReceivedSigned(HCkEmail cHandle);
void CkEmail_getReplyTo(HCkEmail cHandle, HCkString retval);
void CkEmail_putReplyTo(HCkEmail cHandle, const char *newVal);
const char *CkEmail_replyTo(HCkEmail cHandle);
BOOL CkEmail_getReturnReceipt(HCkEmail cHandle);
void CkEmail_putReturnReceipt(HCkEmail cHandle, BOOL newVal);
BOOL CkEmail_getSendEncrypted(HCkEmail cHandle);
void CkEmail_putSendEncrypted(HCkEmail cHandle, BOOL newVal);
BOOL CkEmail_getSendSigned(HCkEmail cHandle);
void CkEmail_putSendSigned(HCkEmail cHandle, BOOL newVal);
BOOL CkEmail_getSignaturesValid(HCkEmail cHandle);
void CkEmail_getSignedBy(HCkEmail cHandle, HCkString retval);
const char *CkEmail_signedBy(HCkEmail cHandle);
void CkEmail_getSigningHashAlg(HCkEmail cHandle, HCkString retval);
void CkEmail_putSigningHashAlg(HCkEmail cHandle, const char *newVal);
const char *CkEmail_signingHashAlg(HCkEmail cHandle);
int CkEmail_getSize(HCkEmail cHandle);
void CkEmail_getSubject(HCkEmail cHandle, HCkString retval);
void CkEmail_putSubject(HCkEmail cHandle, const char *newVal);
const char *CkEmail_subject(HCkEmail cHandle);
void CkEmail_getUidl(HCkEmail cHandle, HCkString retval);
const char *CkEmail_uidl(HCkEmail cHandle);
BOOL CkEmail_getUnpackUseRelPaths(HCkEmail cHandle);
void CkEmail_putUnpackUseRelPaths(HCkEmail cHandle, BOOL newVal);
BOOL CkEmail_getUtf8(HCkEmail cHandle);
void CkEmail_putUtf8(HCkEmail cHandle, BOOL newVal);
BOOL CkEmail_getVerboseLogging(HCkEmail cHandle);
void CkEmail_putVerboseLogging(HCkEmail cHandle, BOOL newVal);
void CkEmail_getVersion(HCkEmail cHandle, HCkString retval);
const char *CkEmail_version(HCkEmail cHandle);
void CkEmail_AddAttachmentHeader(HCkEmail cHandle, int index, const char *fieldName, const char *fieldValue);
BOOL CkEmail_AddBcc(HCkEmail cHandle, const char *friendlyName, const char *emailAddress);
BOOL CkEmail_AddCC(HCkEmail cHandle, const char *friendlyName, const char *emailAddress);
BOOL CkEmail_AddDataAttachment(HCkEmail cHandle, const char *filePath, HCkByteData content);
BOOL CkEmail_AddDataAttachment2(HCkEmail cHandle, const char *path, HCkByteData content, const char *contentType);
BOOL CkEmail_AddEncryptCert(HCkEmail cHandle, HCkCert cert);
BOOL CkEmail_AddFileAttachment(HCkEmail cHandle, const char *path, HCkString outStrContentType);
const char *CkEmail_addFileAttachment(HCkEmail cHandle, const char *path);
BOOL CkEmail_AddFileAttachment2(HCkEmail cHandle, const char *path, const char *contentType);
void CkEmail_AddHeaderField(HCkEmail cHandle, const char *fieldName, const char *fieldValue);
void CkEmail_AddHeaderField2(HCkEmail cHandle, const char *fieldName, const char *fieldValue);
BOOL CkEmail_AddHtmlAlternativeBody(HCkEmail cHandle, const char *body);
BOOL CkEmail_AddMultipleBcc(HCkEmail cHandle, const char *commaSeparatedAddresses);
BOOL CkEmail_AddMultipleCC(HCkEmail cHandle, const char *commaSeparatedAddresses);
BOOL CkEmail_AddMultipleTo(HCkEmail cHandle, const char *commaSeparatedAddresses);
BOOL CkEmail_AddPfxSourceData(HCkEmail cHandle, HCkByteData pfxBytes, const char *pfxPassword);
BOOL CkEmail_AddPfxSourceFile(HCkEmail cHandle, const char *pfxFilePath, const char *pfxPassword);
BOOL CkEmail_AddPlainTextAlternativeBody(HCkEmail cHandle, const char *body);
BOOL CkEmail_AddRelatedData(HCkEmail cHandle, const char *path, HCkByteData inData, HCkString outStr);
const char *CkEmail_addRelatedData(HCkEmail cHandle, const char *path, HCkByteData inData);
void CkEmail_AddRelatedData2(HCkEmail cHandle, HCkByteData inData, const char *fileNameInHtml);
#if !defined(CHILKAT_MONO)
void CkEmail_AddRelatedData2P(HCkEmail cHandle, const unsigned char *pBytes, unsigned long szBytes, const char *fileNameInHtml);
#endif
#if !defined(CHILKAT_MONO)
BOOL CkEmail_AddRelatedDataP(HCkEmail cHandle, const char *nameInHtml, const unsigned char *pBytes, unsigned long szBytes, HCkString outStrContentId);
#endif
#if !defined(CHILKAT_MONO)
const char *CkEmail_addRelatedDataP(HCkEmail cHandle, const char *nameInHtml, const unsigned char *pBytes, unsigned long szBytes);
#endif
BOOL CkEmail_AddRelatedFile(HCkEmail cHandle, const char *path, HCkString outStrContentID);
const char *CkEmail_addRelatedFile(HCkEmail cHandle, const char *path);
BOOL CkEmail_AddRelatedFile2(HCkEmail cHandle, const char *filenameOnDisk, const char *filenameInHtml);
void CkEmail_AddRelatedHeader(HCkEmail cHandle, int index, const char *fieldName, const char *fieldValue);
BOOL CkEmail_AddRelatedString(HCkEmail cHandle, const char *nameInHtml, const char *str, const char *charset, HCkString outCid);
const char *CkEmail_addRelatedString(HCkEmail cHandle, const char *nameInHtml, const char *str, const char *charset);
void CkEmail_AddRelatedString2(HCkEmail cHandle, const char *content, const char *charset, const char *fileNameInHtml);
BOOL CkEmail_AddStringAttachment(HCkEmail cHandle, const char *path, const char *content);
BOOL CkEmail_AddStringAttachment2(HCkEmail cHandle, const char *path, const char *content, const char *charset);
BOOL CkEmail_AddTo(HCkEmail cHandle, const char *friendlyName, const char *emailAddress);
BOOL CkEmail_AddiCalendarAlternativeBody(HCkEmail cHandle, const char *icalContent, const char *methodName);
BOOL CkEmail_AesDecrypt(HCkEmail cHandle, const char *password);
BOOL CkEmail_AesEncrypt(HCkEmail cHandle, const char *password);
void CkEmail_AppendToBody(HCkEmail cHandle, const char *str);
BOOL CkEmail_AspUnpack(HCkEmail cHandle, const char *prefix, const char *saveDir, const char *urlPath, BOOL cleanFiles);
BOOL CkEmail_AspUnpack2(HCkEmail cHandle, const char *prefix, const char *saveDir, const char *urlPath, BOOL cleanFiles, HCkByteData outHtml);
BOOL CkEmail_AttachMessage(HCkEmail cHandle, HCkByteData mimeBytes);
BOOL CkEmail_BEncodeBytes(HCkEmail cHandle, HCkByteData inData, const char *charset, HCkString outEncodedStr);
const char *CkEmail_bEncodeBytes(HCkEmail cHandle, HCkByteData inData, const char *charset);
BOOL CkEmail_BEncodeString(HCkEmail cHandle, const char *str, const char *charset, HCkString outEncodedStr);
const char *CkEmail_bEncodeString(HCkEmail cHandle, const char *str, const char *charset);
void CkEmail_ClearBcc(HCkEmail cHandle);
void CkEmail_ClearCC(HCkEmail cHandle);
void CkEmail_ClearEncryptCerts(HCkEmail cHandle);
void CkEmail_ClearTo(HCkEmail cHandle);
HCkEmail CkEmail_Clone(HCkEmail cHandle);
BOOL CkEmail_ComputeGlobalKey(HCkEmail cHandle, const char *encoding, BOOL bFold, HCkString outStr);
const char *CkEmail_computeGlobalKey(HCkEmail cHandle, const char *encoding, BOOL bFold);
HCkEmail CkEmail_CreateDsn(HCkEmail cHandle, const char *humanReadableMessage, const char *xmlStatusFields, BOOL bHeaderOnly);
HCkEmail CkEmail_CreateForward(HCkEmail cHandle);
HCkEmail CkEmail_CreateMdn(HCkEmail cHandle, const char *humanReadableMessage, const char *xmlStatusFields, BOOL bHeaderOnly);
HCkEmail CkEmail_CreateReply(HCkEmail cHandle);
BOOL CkEmail_CreateTempMht(HCkEmail cHandle, const char *inFilename, HCkString outPath);
const char *CkEmail_createTempMht(HCkEmail cHandle, const char *inFilename);
void CkEmail_DropAttachments(HCkEmail cHandle);
void CkEmail_DropRelatedItem(HCkEmail cHandle, int index);
void CkEmail_DropRelatedItems(HCkEmail cHandle);
BOOL CkEmail_DropSingleAttachment(HCkEmail cHandle, int index);
HCkCert CkEmail_FindIssuer(HCkEmail cHandle, HCkCert cert);
BOOL CkEmail_GenerateFilename(HCkEmail cHandle, HCkString outStrFilename);
const char *CkEmail_generateFilename(HCkEmail cHandle);
BOOL CkEmail_GetAltHeaderField(HCkEmail cHandle, int index, const char *fieldName, HCkString outStr);
const char *CkEmail_getAltHeaderField(HCkEmail cHandle, int index, const char *fieldName);
BOOL CkEmail_GetAlternativeBody(HCkEmail cHandle, int index, HCkString outStrBody);
const char *CkEmail_getAlternativeBody(HCkEmail cHandle, int index);
BOOL CkEmail_GetAlternativeBodyByContentType(HCkEmail cHandle, const char *contentType, HCkString outStr);
const char *CkEmail_getAlternativeBodyByContentType(HCkEmail cHandle, const char *contentType);
BOOL CkEmail_GetAlternativeContentType(HCkEmail cHandle, int index, HCkString outStrContentType);
const char *CkEmail_getAlternativeContentType(HCkEmail cHandle, int index);
HCkEmail CkEmail_GetAttachedMessage(HCkEmail cHandle, int index);
BOOL CkEmail_GetAttachedMessageFilename(HCkEmail cHandle, int index, HCkString outStr);
const char *CkEmail_getAttachedMessageFilename(HCkEmail cHandle, int index);
BOOL CkEmail_GetAttachmentContentID(HCkEmail cHandle, int index, HCkString outStrContentID);
const char *CkEmail_getAttachmentContentID(HCkEmail cHandle, int index);
BOOL CkEmail_GetAttachmentContentType(HCkEmail cHandle, int index, HCkString outStrContentType);
const char *CkEmail_getAttachmentContentType(HCkEmail cHandle, int index);
BOOL CkEmail_GetAttachmentData(HCkEmail cHandle, int index, HCkByteData outData);
BOOL CkEmail_GetAttachmentFilename(HCkEmail cHandle, int index, HCkString outStrFilename);
const char *CkEmail_getAttachmentFilename(HCkEmail cHandle, int index);
BOOL CkEmail_GetAttachmentHeader(HCkEmail cHandle, int attachIndex, const char *fieldName, HCkString outFieldValue);
const char *CkEmail_getAttachmentHeader(HCkEmail cHandle, int attachIndex, const char *fieldName);
int CkEmail_GetAttachmentSize(HCkEmail cHandle, int index);
BOOL CkEmail_GetAttachmentString(HCkEmail cHandle, int index, const char *charset, HCkString outStr);
const char *CkEmail_getAttachmentString(HCkEmail cHandle, int index, const char *charset);
BOOL CkEmail_GetAttachmentStringCrLf(HCkEmail cHandle, int index, const char *charset, HCkString outStrData);
const char *CkEmail_getAttachmentStringCrLf(HCkEmail cHandle, int index, const char *charset);
BOOL CkEmail_GetBcc(HCkEmail cHandle, int index, HCkString outStr);
const char *CkEmail_getBcc(HCkEmail cHandle, int index);
BOOL CkEmail_GetBccAddr(HCkEmail cHandle, int index, HCkString outStr);
const char *CkEmail_getBccAddr(HCkEmail cHandle, int index);
BOOL CkEmail_GetBccName(HCkEmail cHandle, int index, HCkString outStr);
const char *CkEmail_getBccName(HCkEmail cHandle, int index);
BOOL CkEmail_GetCC(HCkEmail cHandle, int index, HCkString outStr);
const char *CkEmail_getCC(HCkEmail cHandle, int index);
BOOL CkEmail_GetCcAddr(HCkEmail cHandle, int index, HCkString outStr);
const char *CkEmail_getCcAddr(HCkEmail cHandle, int index);
BOOL CkEmail_GetCcName(HCkEmail cHandle, int index, HCkString outStr);
const char *CkEmail_getCcName(HCkEmail cHandle, int index);
BOOL CkEmail_GetDeliveryStatusInfo(HCkEmail cHandle, const char *fieldName, HCkString outFieldValue);
const char *CkEmail_getDeliveryStatusInfo(HCkEmail cHandle, const char *fieldName);
HCkStringArray CkEmail_GetDsnFinalRecipients(HCkEmail cHandle);
HCkDateTime CkEmail_GetDt(HCkEmail cHandle);
HCkCert CkEmail_GetEncryptCert(HCkEmail cHandle);
HCkCert CkEmail_GetEncryptedByCert(HCkEmail cHandle);
BOOL CkEmail_GetFileContent(HCkEmail cHandle, const char *path, HCkByteData outData);
BOOL CkEmail_GetHeaderField(HCkEmail cHandle, const char *fieldName, HCkString outStrFieldData);
const char *CkEmail_getHeaderField(HCkEmail cHandle, const char *fieldName);
BOOL CkEmail_GetHeaderFieldName(HCkEmail cHandle, int index, HCkString outStrFieldName);
const char *CkEmail_getHeaderFieldName(HCkEmail cHandle, int index);
BOOL CkEmail_GetHeaderFieldValue(HCkEmail cHandle, int index, HCkString outStrFieldValue);
const char *CkEmail_getHeaderFieldValue(HCkEmail cHandle, int index);
BOOL CkEmail_GetHtmlBody(HCkEmail cHandle, HCkString outStrBody);
const char *CkEmail_getHtmlBody(HCkEmail cHandle);
int CkEmail_GetImapUid(HCkEmail cHandle);
HCkStringArray CkEmail_GetLinkedDomains(HCkEmail cHandle);
BOOL CkEmail_GetMbHeaderField(HCkEmail cHandle, const char *fieldName, const char *charset, HCkByteData outBytes);
BOOL CkEmail_GetMbHtmlBody(HCkEmail cHandle, const char *charset, HCkByteData outData);
BOOL CkEmail_GetMbPlainTextBody(HCkEmail cHandle, const char *charset, HCkByteData outData);
BOOL CkEmail_GetMime(HCkEmail cHandle, HCkString outStrMime);
const char *CkEmail_getMime(HCkEmail cHandle);
BOOL CkEmail_GetMimeBinary(HCkEmail cHandle, HCkByteData outBytes);
BOOL CkEmail_GetPlainTextBody(HCkEmail cHandle, HCkString outStrBody);
const char *CkEmail_getPlainTextBody(HCkEmail cHandle);
BOOL CkEmail_GetRelatedContentID(HCkEmail cHandle, int index, HCkString outStrContentID);
const char *CkEmail_getRelatedContentID(HCkEmail cHandle, int index);
BOOL CkEmail_GetRelatedContentLocation(HCkEmail cHandle, int index, HCkString outStr);
const char *CkEmail_getRelatedContentLocation(HCkEmail cHandle, int index);
BOOL CkEmail_GetRelatedContentType(HCkEmail cHandle, int index, HCkString outStrContentType);
const char *CkEmail_getRelatedContentType(HCkEmail cHandle, int index);
BOOL CkEmail_GetRelatedData(HCkEmail cHandle, int index, HCkByteData outBuffer);
BOOL CkEmail_GetRelatedFilename(HCkEmail cHandle, int index, HCkString outStrFilename);
const char *CkEmail_getRelatedFilename(HCkEmail cHandle, int index);
BOOL CkEmail_GetRelatedString(HCkEmail cHandle, int index, const char *charset, HCkString outStrData);
const char *CkEmail_getRelatedString(HCkEmail cHandle, int index, const char *charset);
BOOL CkEmail_GetRelatedStringCrLf(HCkEmail cHandle, int index, const char *charset, HCkString outStr);
const char *CkEmail_getRelatedStringCrLf(HCkEmail cHandle, int index, const char *charset);
BOOL CkEmail_GetReplacePattern(HCkEmail cHandle, int index, HCkString outStrPattern);
const char *CkEmail_getReplacePattern(HCkEmail cHandle, int index);
BOOL CkEmail_GetReplaceString(HCkEmail cHandle, int index, HCkString outStr);
const char *CkEmail_getReplaceString(HCkEmail cHandle, int index);
BOOL CkEmail_GetReplaceString2(HCkEmail cHandle, const char *pattern, HCkString outStr);
const char *CkEmail_getReplaceString2(HCkEmail cHandle, const char *pattern);
BOOL CkEmail_GetReport(HCkEmail cHandle, int index, HCkString outStr);
const char *CkEmail_getReport(HCkEmail cHandle, int index);
HCkCert CkEmail_GetSignedByCert(HCkEmail cHandle);
HCkCert CkEmail_GetSigningCert(HCkEmail cHandle);
BOOL CkEmail_GetTo(HCkEmail cHandle, int index, HCkString outStr);
const char *CkEmail_getTo(HCkEmail cHandle, int index);
BOOL CkEmail_GetToAddr(HCkEmail cHandle, int index, HCkString outStr);
const char *CkEmail_getToAddr(HCkEmail cHandle, int index);
BOOL CkEmail_GetToName(HCkEmail cHandle, int index, HCkString outStr);
const char *CkEmail_getToName(HCkEmail cHandle, int index);
BOOL CkEmail_GetXml(HCkEmail cHandle, HCkString outStrXml);
const char *CkEmail_getXml(HCkEmail cHandle);
BOOL CkEmail_HasHeaderMatching(HCkEmail cHandle, const char *fieldName, const char *valuePattern, BOOL caseSensitive);
BOOL CkEmail_HasHtmlBody(HCkEmail cHandle);
BOOL CkEmail_HasPlainTextBody(HCkEmail cHandle);
BOOL CkEmail_IsMultipartReport(HCkEmail cHandle);
BOOL CkEmail_LoadEml(HCkEmail cHandle, const char *mimePath);
BOOL CkEmail_LoadXml(HCkEmail cHandle, const char *xmlPath);
BOOL CkEmail_LoadXmlString(HCkEmail cHandle, const char *xmlStr);
BOOL CkEmail_QEncodeBytes(HCkEmail cHandle, HCkByteData inData, const char *charset, HCkString outEncodedStr);
const char *CkEmail_qEncodeBytes(HCkEmail cHandle, HCkByteData inData, const char *charset);
BOOL CkEmail_QEncodeString(HCkEmail cHandle, const char *str, const char *charset, HCkString outEncodedStr);
const char *CkEmail_qEncodeString(HCkEmail cHandle, const char *str, const char *charset);
void CkEmail_RemoveAttachedMessage(HCkEmail cHandle, int idx);
void CkEmail_RemoveAttachedMessages(HCkEmail cHandle);
void CkEmail_RemoveAttachmentPaths(HCkEmail cHandle);
void CkEmail_RemoveHeaderField(HCkEmail cHandle, const char *fieldName);
void CkEmail_RemoveHtmlAlternative(HCkEmail cHandle);
void CkEmail_RemovePlainTextAlternative(HCkEmail cHandle);
BOOL CkEmail_SaveAllAttachments(HCkEmail cHandle, const char *dirPath);
BOOL CkEmail_SaveAttachedFile(HCkEmail cHandle, int index, const char *dirPath);
BOOL CkEmail_SaveEml(HCkEmail cHandle, const char *emlFilePath);
BOOL CkEmail_SaveLastError(HCkEmail cHandle, const char *path);
BOOL CkEmail_SaveRelatedItem(HCkEmail cHandle, int index, const char *dirPath);
BOOL CkEmail_SaveXml(HCkEmail cHandle, const char *path);
BOOL CkEmail_SetAttachmentCharset(HCkEmail cHandle, int index, const char *charset);
BOOL CkEmail_SetAttachmentDisposition(HCkEmail cHandle, int index, const char *disposition);
BOOL CkEmail_SetAttachmentFilename(HCkEmail cHandle, int index, const char *filename);
#if defined(CK_CSP_INCLUDED)
BOOL CkEmail_SetCSP(HCkEmail cHandle, HCkCsp csp);
#endif
BOOL CkEmail_SetDecryptCert2(HCkEmail cHandle, HCkCert cert, HCkPrivateKey key);
BOOL CkEmail_SetDt(HCkEmail cHandle, HCkDateTime dt);
BOOL CkEmail_SetEncryptCert(HCkEmail cHandle, HCkCert cert);
BOOL CkEmail_SetFromMimeBytes(HCkEmail cHandle, HCkByteData mimeBytes);
BOOL CkEmail_SetFromMimeBytes2(HCkEmail cHandle, HCkByteData mimeBytes, const char *charset);
BOOL CkEmail_SetFromMimeText(HCkEmail cHandle, const char *mimeText);
BOOL CkEmail_SetFromXmlText(HCkEmail cHandle, const char *xmlStr);
void CkEmail_SetHtmlBody(HCkEmail cHandle, const char *html);
BOOL CkEmail_SetMbHtmlBody(HCkEmail cHandle, const char *charset, HCkByteData inData);
BOOL CkEmail_SetMbPlainTextBody(HCkEmail cHandle, const char *charset, HCkByteData inData);
BOOL CkEmail_SetRelatedFilename(HCkEmail cHandle, int index, const char *path);
BOOL CkEmail_SetReplacePattern(HCkEmail cHandle, const char *pattern, const char *replaceString);
BOOL CkEmail_SetSigningCert(HCkEmail cHandle, HCkCert cert);
BOOL CkEmail_SetSigningCert2(HCkEmail cHandle, HCkCert cert, HCkPrivateKey key);
void CkEmail_SetTextBody(HCkEmail cHandle, const char *bodyText, const char *contentType);
BOOL CkEmail_UidlEquals(HCkEmail cHandle, HCkEmail e);
void CkEmail_UnSpamify(HCkEmail cHandle);
BOOL CkEmail_UnpackHtml(HCkEmail cHandle, const char *unpackDir, const char *htmlFilename, const char *partsSubdir);
BOOL CkEmail_UnzipAttachments(HCkEmail cHandle);
BOOL CkEmail_ZipAttachments(HCkEmail cHandle, const char *zipFilename);
#endif
