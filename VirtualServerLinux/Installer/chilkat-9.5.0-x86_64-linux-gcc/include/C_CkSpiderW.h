// This is a generated source file for Chilkat version 9.5.0.21
#ifndef _C_CkSpiderWH
#define _C_CkSpiderWH
#include "chilkatDefs.h"

#include "Chilkat_C.h"

HCkSpiderW CkSpiderW_Create(void);
HCkSpiderW CkSpiderW_Create2(BOOL bCallbackOwned);
void CkSpiderW_Dispose(HCkSpiderW handle);
BOOL CkSpiderW_getAvoidHttps(HCkSpiderW cHandle);
void CkSpiderW_putAvoidHttps(HCkSpiderW cHandle, BOOL newVal);
void CkSpiderW_getCacheDir(HCkSpiderW cHandle, HCkString retval);
void CkSpiderW_putCacheDir(HCkSpiderW cHandle, const wchar_t *newVal);
const wchar_t *CkSpiderW_cacheDir(HCkSpiderW cHandle);
BOOL CkSpiderW_getChopAtQuery(HCkSpiderW cHandle);
void CkSpiderW_putChopAtQuery(HCkSpiderW cHandle, BOOL newVal);
int CkSpiderW_getConnectTimeout(HCkSpiderW cHandle);
void CkSpiderW_putConnectTimeout(HCkSpiderW cHandle, int newVal);
void CkSpiderW_getDebugLogFilePath(HCkSpiderW cHandle, HCkString retval);
void CkSpiderW_putDebugLogFilePath(HCkSpiderW cHandle, const wchar_t *newVal);
const wchar_t *CkSpiderW_debugLogFilePath(HCkSpiderW cHandle);
void CkSpiderW_getDomain(HCkSpiderW cHandle, HCkString retval);
const wchar_t *CkSpiderW_domain(HCkSpiderW cHandle);
BOOL CkSpiderW_getFetchFromCache(HCkSpiderW cHandle);
void CkSpiderW_putFetchFromCache(HCkSpiderW cHandle, BOOL newVal);
int CkSpiderW_getHeartbeatMs(HCkSpiderW cHandle);
void CkSpiderW_putHeartbeatMs(HCkSpiderW cHandle, int newVal);
void CkSpiderW_getLastErrorHtml(HCkSpiderW cHandle, HCkString retval);
const wchar_t *CkSpiderW_lastErrorHtml(HCkSpiderW cHandle);
void CkSpiderW_getLastErrorText(HCkSpiderW cHandle, HCkString retval);
const wchar_t *CkSpiderW_lastErrorText(HCkSpiderW cHandle);
void CkSpiderW_getLastErrorXml(HCkSpiderW cHandle, HCkString retval);
const wchar_t *CkSpiderW_lastErrorXml(HCkSpiderW cHandle);
BOOL CkSpiderW_getLastFromCache(HCkSpiderW cHandle);
void CkSpiderW_getLastHtml(HCkSpiderW cHandle, HCkString retval);
const wchar_t *CkSpiderW_lastHtml(HCkSpiderW cHandle);
void CkSpiderW_getLastHtmlDescription(HCkSpiderW cHandle, HCkString retval);
const wchar_t *CkSpiderW_lastHtmlDescription(HCkSpiderW cHandle);
void CkSpiderW_getLastHtmlKeywords(HCkSpiderW cHandle, HCkString retval);
const wchar_t *CkSpiderW_lastHtmlKeywords(HCkSpiderW cHandle);
void CkSpiderW_getLastHtmlTitle(HCkSpiderW cHandle, HCkString retval);
const wchar_t *CkSpiderW_lastHtmlTitle(HCkSpiderW cHandle);
void CkSpiderW_getLastModDate(HCkSpiderW cHandle, SYSTEMTIME *retval);
void CkSpiderW_getLastModDateStr(HCkSpiderW cHandle, HCkString retval);
const wchar_t *CkSpiderW_lastModDateStr(HCkSpiderW cHandle);
void CkSpiderW_getLastUrl(HCkSpiderW cHandle, HCkString retval);
const wchar_t *CkSpiderW_lastUrl(HCkSpiderW cHandle);
int CkSpiderW_getMaxResponseSize(HCkSpiderW cHandle);
void CkSpiderW_putMaxResponseSize(HCkSpiderW cHandle, int newVal);
int CkSpiderW_getMaxUrlLen(HCkSpiderW cHandle);
void CkSpiderW_putMaxUrlLen(HCkSpiderW cHandle, int newVal);
int CkSpiderW_getNumAvoidPatterns(HCkSpiderW cHandle);
int CkSpiderW_getNumFailed(HCkSpiderW cHandle);
int CkSpiderW_getNumOutboundLinks(HCkSpiderW cHandle);
int CkSpiderW_getNumSpidered(HCkSpiderW cHandle);
int CkSpiderW_getNumUnspidered(HCkSpiderW cHandle);
void CkSpiderW_getProxyDomain(HCkSpiderW cHandle, HCkString retval);
void CkSpiderW_putProxyDomain(HCkSpiderW cHandle, const wchar_t *newVal);
const wchar_t *CkSpiderW_proxyDomain(HCkSpiderW cHandle);
void CkSpiderW_getProxyLogin(HCkSpiderW cHandle, HCkString retval);
void CkSpiderW_putProxyLogin(HCkSpiderW cHandle, const wchar_t *newVal);
const wchar_t *CkSpiderW_proxyLogin(HCkSpiderW cHandle);
void CkSpiderW_getProxyPassword(HCkSpiderW cHandle, HCkString retval);
void CkSpiderW_putProxyPassword(HCkSpiderW cHandle, const wchar_t *newVal);
const wchar_t *CkSpiderW_proxyPassword(HCkSpiderW cHandle);
int CkSpiderW_getProxyPort(HCkSpiderW cHandle);
void CkSpiderW_putProxyPort(HCkSpiderW cHandle, int newVal);
int CkSpiderW_getReadTimeout(HCkSpiderW cHandle);
void CkSpiderW_putReadTimeout(HCkSpiderW cHandle, int newVal);
BOOL CkSpiderW_getUpdateCache(HCkSpiderW cHandle);
void CkSpiderW_putUpdateCache(HCkSpiderW cHandle, BOOL newVal);
void CkSpiderW_getUserAgent(HCkSpiderW cHandle, HCkString retval);
void CkSpiderW_putUserAgent(HCkSpiderW cHandle, const wchar_t *newVal);
const wchar_t *CkSpiderW_userAgent(HCkSpiderW cHandle);
BOOL CkSpiderW_getVerboseLogging(HCkSpiderW cHandle);
void CkSpiderW_putVerboseLogging(HCkSpiderW cHandle, BOOL newVal);
void CkSpiderW_getVersion(HCkSpiderW cHandle, HCkString retval);
const wchar_t *CkSpiderW_version(HCkSpiderW cHandle);
int CkSpiderW_getWindDownCount(HCkSpiderW cHandle);
void CkSpiderW_putWindDownCount(HCkSpiderW cHandle, int newVal);
void CkSpiderW_AddAvoidOutboundLinkPattern(HCkSpiderW cHandle, const wchar_t *pattern);
void CkSpiderW_AddAvoidPattern(HCkSpiderW cHandle, const wchar_t *pattern);
void CkSpiderW_AddMustMatchPattern(HCkSpiderW cHandle, const wchar_t *pattern);
void CkSpiderW_AddUnspidered(HCkSpiderW cHandle, const wchar_t *url);
BOOL CkSpiderW_CanonicalizeUrl(HCkSpiderW cHandle, const wchar_t *url, HCkString outStr);
const wchar_t *CkSpiderW_canonicalizeUrl(HCkSpiderW cHandle, const wchar_t *url);
void CkSpiderW_ClearFailedUrls(HCkSpiderW cHandle);
void CkSpiderW_ClearOutboundLinks(HCkSpiderW cHandle);
void CkSpiderW_ClearSpideredUrls(HCkSpiderW cHandle);
BOOL CkSpiderW_CrawlNext(HCkSpiderW cHandle);
BOOL CkSpiderW_FetchRobotsText(HCkSpiderW cHandle, HCkString outStr);
const wchar_t *CkSpiderW_fetchRobotsText(HCkSpiderW cHandle);
BOOL CkSpiderW_GetAvoidPattern(HCkSpiderW cHandle, int index, HCkString outStr);
const wchar_t *CkSpiderW_getAvoidPattern(HCkSpiderW cHandle, int index);
BOOL CkSpiderW_GetBaseDomain(HCkSpiderW cHandle, const wchar_t *domain, HCkString outStr);
const wchar_t *CkSpiderW_getBaseDomain(HCkSpiderW cHandle, const wchar_t *domain);
BOOL CkSpiderW_GetFailedUrl(HCkSpiderW cHandle, int index, HCkString outStr);
const wchar_t *CkSpiderW_getFailedUrl(HCkSpiderW cHandle, int index);
BOOL CkSpiderW_GetOutboundLink(HCkSpiderW cHandle, int index, HCkString outStr);
const wchar_t *CkSpiderW_getOutboundLink(HCkSpiderW cHandle, int index);
BOOL CkSpiderW_GetSpideredUrl(HCkSpiderW cHandle, int index, HCkString outStr);
const wchar_t *CkSpiderW_getSpideredUrl(HCkSpiderW cHandle, int index);
BOOL CkSpiderW_GetUnspideredUrl(HCkSpiderW cHandle, int index, HCkString outStr);
const wchar_t *CkSpiderW_getUnspideredUrl(HCkSpiderW cHandle, int index);
BOOL CkSpiderW_GetUrlDomain(HCkSpiderW cHandle, const wchar_t *url, HCkString outStr);
const wchar_t *CkSpiderW_getUrlDomain(HCkSpiderW cHandle, const wchar_t *url);
void CkSpiderW_Initialize(HCkSpiderW cHandle, const wchar_t *domain);
BOOL CkSpiderW_RecrawlLast(HCkSpiderW cHandle);
BOOL CkSpiderW_SaveLastError(HCkSpiderW cHandle, const wchar_t *path);
void CkSpiderW_SkipUnspidered(HCkSpiderW cHandle, int index);
void CkSpiderW_SleepMs(HCkSpiderW cHandle, int numMilliseconds);
#endif