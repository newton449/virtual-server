// This is a generated source file for Chilkat version 9.5.0.21
#ifndef _C_CkString_H
#define _C_CkString_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"

HCkString CkString_Create(void);
void CkString_Dispose(HCkString handle);
const char *CkString_getEnc(HCkString cHandle, const char *encoding);
const char *CkString_getString(HCkString cHandle);
const char *CkString_getStringAnsi(HCkString cHandle);
const char *CkString_getStringUtf8(HCkString cHandle);
void CkString_append(HCkString cHandle, const char *str);
void CkString_appendAnsi(HCkString cHandle, const char *str);
void CkString_appendChar(HCkString cHandle, char c);
void CkString_appendCurrentDateRfc822(HCkString cHandle);
void CkString_appendDateRfc822(HCkString cHandle, SYSTEMTIME *dateTime);
void CkString_appendDateRfc822Gmt(HCkString cHandle, SYSTEMTIME *dateTime);
void CkString_appendEnc(HCkString cHandle, const char *str, const char *charsetEncoding);
void CkString_appendHexData(HCkString cHandle, const unsigned char *byteData, unsigned long numBytes);
void CkString_appendInt(HCkString cHandle, int n);
#ifdef WIN32
void CkString_appendLastWindowsError(HCkString cHandle);
#endif
void CkString_appendN(HCkString cHandle, const char *str, unsigned long numBytes);
void CkString_appendNU(HCkString cHandle, const wchar_t *wideStr, int numChars);
void CkString_appendRandom(HCkString cHandle, int numBytes, const char *encoding);
void CkString_appendStr(HCkString cHandle, HCkString strObj);
void CkString_appendU(HCkString cHandle, const wchar_t *unicode);
void CkString_appendUtf8(HCkString cHandle, const char *str);
void CkString_base64Decode(HCkString cHandle, const char *charsetEncoding);
void CkString_base64DecodeW(HCkString cHandle, const wchar_t *charsetEncoding);
void CkString_base64Encode(HCkString cHandle, const char *charsetEncoding);
void CkString_base64EncodeW(HCkString cHandle, const wchar_t *charsetEncoding);
BOOL CkString_beginsWith(HCkString cHandle, const char *substr);
BOOL CkString_beginsWithStr(HCkString cHandle, HCkString strObj);
BOOL CkString_beginsWithW(HCkString cHandle, const wchar_t *str);
char CkString_charAt(HCkString cHandle, int idx);
wchar_t CkString_charAtU(HCkString cHandle, int idx);
void CkString_chopAtFirstChar(HCkString cHandle, char ch);
void CkString_chopAtStr(HCkString cHandle, HCkString subStrObj);
void CkString_clear(HCkString cHandle);
HCkString CkString_clone(HCkString cHandle);
int CkString_compareStr(HCkString cHandle, HCkString str);
BOOL CkString_containsSubstring(HCkString cHandle, const char *substr);
BOOL CkString_containsSubstringNoCase(HCkString cHandle, const char *substr);
BOOL CkString_containsSubstringNoCaseW(HCkString cHandle, const wchar_t *substr);
BOOL CkString_containsSubstringW(HCkString cHandle, const wchar_t *substr);
int CkString_countCharOccurances(HCkString cHandle, char ch);
void CkString_decodeXMLSpecial(HCkString cHandle);
double CkString_doubleValue(HCkString cHandle);
void CkString_eliminateChar(HCkString cHandle, char ansiChar, int startIndex);
void CkString_encodeXMLSpecial(HCkString cHandle);
BOOL CkString_endsWith(HCkString cHandle, const char *substr);
BOOL CkString_endsWithStr(HCkString cHandle, HCkString substrObj);
BOOL CkString_endsWithW(HCkString cHandle, const wchar_t *s);
void CkString_entityDecode(HCkString cHandle);
void CkString_entityEncode(HCkString cHandle);
BOOL CkString_equals(HCkString cHandle, const char *str);
BOOL CkString_equalsIgnoreCase(HCkString cHandle, const char *str);
BOOL CkString_equalsIgnoreCaseStr(HCkString cHandle, HCkString strObj);
BOOL CkString_equalsIgnoreCaseW(HCkString cHandle, const wchar_t *s);
BOOL CkString_equalsStr(HCkString cHandle, HCkString strObj);
BOOL CkString_equalsW(HCkString cHandle, const wchar_t *s);
HCkString CkString_getChar(HCkString cHandle, int idx);
int CkString_getNumChars(HCkString cHandle);
int CkString_getSizeAnsi(HCkString cHandle);
int CkString_getSizeUnicode(HCkString cHandle);
int CkString_getSizeUtf8(HCkString cHandle);
const wchar_t *CkString_getUnicode(HCkString cHandle);
void CkString_hexDecode(HCkString cHandle, const char *charsetEncoding);
void CkString_hexDecodeW(HCkString cHandle, const wchar_t *charsetEncoding);
void CkString_hexEncode(HCkString cHandle, const char *charsetEncoding);
void CkString_hexEncodeW(HCkString cHandle, const wchar_t *charsetEncoding);
int CkString_indexOf(HCkString cHandle, const char *substr);
int CkString_indexOfStr(HCkString cHandle, HCkString substrObj);
int CkString_indexOfW(HCkString cHandle, const wchar_t *s);
int CkString_intValue(HCkString cHandle);
BOOL CkString_isEmpty(HCkString cHandle);
char CkString_lastChar(HCkString cHandle);
BOOL CkString_loadFile(HCkString cHandle, const char *path, const char *charsetEncoding);
BOOL CkString_loadFileW(HCkString cHandle, const wchar_t *path, const wchar_t *charsetEncoding);
BOOL CkString_matches(HCkString cHandle, const char *strPattern);
BOOL CkString_matchesNoCase(HCkString cHandle, const char *strPattern);
BOOL CkString_matchesNoCaseW(HCkString cHandle, const wchar_t *s);
BOOL CkString_matchesStr(HCkString cHandle, HCkString strPatternObj);
BOOL CkString_matchesW(HCkString cHandle, const wchar_t *s);
void CkString_minimizeMemory(HCkString cHandle);
void CkString_obfuscate(HCkString cHandle);
void CkString_prepend(HCkString cHandle, const char *str);
void CkString_prependW(HCkString cHandle, const wchar_t *s);
void CkString_qpDecode(HCkString cHandle, const char *charsetEncoding);
void CkString_qpDecodeW(HCkString cHandle, const wchar_t *charset);
void CkString_qpEncode(HCkString cHandle, const char *charsetEncoding);
void CkString_qpEncodeW(HCkString cHandle, const wchar_t *charset);
int CkString_removeAll(HCkString cHandle, HCkString substr);
void CkString_removeCharOccurances(HCkString cHandle, char ch);
void CkString_removeChunk(HCkString cHandle, int charStartPos, int numChars);
BOOL CkString_removeFirst(HCkString cHandle, HCkString substr);
int CkString_replaceAll(HCkString cHandle, HCkString findStrObj, HCkString replaceStrObj);
int CkString_replaceAllOccurances(HCkString cHandle, const char *findStr, const char *replaceStr);
int CkString_replaceAllOccurancesW(HCkString cHandle, const wchar_t *pattern, const wchar_t *replacement);
void CkString_replaceChar(HCkString cHandle, char findCh, char replaceCh);
BOOL CkString_replaceFirst(HCkString cHandle, HCkString findStrObj, HCkString replaceStrObj);
BOOL CkString_replaceFirstOccurance(HCkString cHandle, const char *findStr, const char *replaceStr);
BOOL CkString_replaceFirstOccuranceW(HCkString cHandle, const wchar_t *pattern, const wchar_t *replacement);
BOOL CkString_saveToFile(HCkString cHandle, const char *path, const char *charsetEncoding);
BOOL CkString_saveToFileW(HCkString cHandle, const wchar_t *path, const wchar_t *charset);
void CkString_setStr(HCkString cHandle, HCkString s);
void CkString_setString(HCkString cHandle, const char *str);
void CkString_setStringAnsi(HCkString cHandle, const char *s);
void CkString_setStringU(HCkString cHandle, const wchar_t *unicode);
void CkString_setStringUtf8(HCkString cHandle, const char *s);
void CkString_shorten(HCkString cHandle, int n);
HCkStringArray CkString_split(HCkString cHandle, char delimiterChar, BOOL exceptDoubleQuoted, BOOL exceptEscaped, BOOL keepEmpty);
HCkStringArray CkString_split2(HCkString cHandle, const char *delimiterChars, BOOL exceptDoubleQuoted, BOOL exceptEscaped, BOOL keepEmpty);
HCkStringArray CkString_split2W(HCkString cHandle, const wchar_t *splitCharSet, BOOL exceptDoubleQuoted, BOOL exceptEscaped, BOOL keepEmpty);
HCkStringArray CkString_splitAtWS(HCkString cHandle);
HCkString CkString_substring(HCkString cHandle, int startCharIndex, int numChars);
void CkString_toCRLF(HCkString cHandle);
void CkString_toLF(HCkString cHandle);
void CkString_toLowerCase(HCkString cHandle);
void CkString_toUpperCase(HCkString cHandle);
HCkStringArray CkString_tokenize(HCkString cHandle, const char *punctuation);
HCkStringArray CkString_tokenizeW(HCkString cHandle, const wchar_t *punctuation);
void CkString_trim(HCkString cHandle);
void CkString_trim2(HCkString cHandle);
void CkString_trimInsideSpaces(HCkString cHandle);
void CkString_unobfuscate(HCkString cHandle);
void CkString_urlDecode(HCkString cHandle, const char *charsetEncoding);
void CkString_urlDecodeW(HCkString cHandle, const wchar_t *charsetEncoding);
void CkString_urlEncode(HCkString cHandle, const char *charsetEncoding);
void CkString_urlEncodeW(HCkString cHandle, const wchar_t *charsetEncoding);
#endif