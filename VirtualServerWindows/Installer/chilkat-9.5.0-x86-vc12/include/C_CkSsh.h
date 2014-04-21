// This is a generated source file for Chilkat version 9.5.0.21
#ifndef _C_CkSsh_H
#define _C_CkSsh_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"

HCkSsh CkSsh_Create(void);
void CkSsh_Dispose(HCkSsh handle);
int CkSsh_getChannelOpenFailCode(HCkSsh cHandle);
void CkSsh_getChannelOpenFailReason(HCkSsh cHandle, HCkString retval);
const char *CkSsh_channelOpenFailReason(HCkSsh cHandle);
void CkSsh_getClientIdentifier(HCkSsh cHandle, HCkString retval);
void CkSsh_putClientIdentifier(HCkSsh cHandle, const char *newVal);
const char *CkSsh_clientIdentifier(HCkSsh cHandle);
void CkSsh_getClientIpAddress(HCkSsh cHandle, HCkString retval);
void CkSsh_putClientIpAddress(HCkSsh cHandle, const char *newVal);
const char *CkSsh_clientIpAddress(HCkSsh cHandle);
int CkSsh_getConnectTimeoutMs(HCkSsh cHandle);
void CkSsh_putConnectTimeoutMs(HCkSsh cHandle, int newVal);
void CkSsh_getDebugLogFilePath(HCkSsh cHandle, HCkString retval);
void CkSsh_putDebugLogFilePath(HCkSsh cHandle, const char *newVal);
const char *CkSsh_debugLogFilePath(HCkSsh cHandle);
int CkSsh_getDisconnectCode(HCkSsh cHandle);
void CkSsh_getDisconnectReason(HCkSsh cHandle, HCkString retval);
const char *CkSsh_disconnectReason(HCkSsh cHandle);
void CkSsh_getForceCipher(HCkSsh cHandle, HCkString retval);
void CkSsh_putForceCipher(HCkSsh cHandle, const char *newVal);
const char *CkSsh_forceCipher(HCkSsh cHandle);
int CkSsh_getHeartbeatMs(HCkSsh cHandle);
void CkSsh_putHeartbeatMs(HCkSsh cHandle, int newVal);
void CkSsh_getHostKeyAlg(HCkSsh cHandle, HCkString retval);
void CkSsh_putHostKeyAlg(HCkSsh cHandle, const char *newVal);
const char *CkSsh_hostKeyAlg(HCkSsh cHandle);
void CkSsh_getHostKeyFingerprint(HCkSsh cHandle, HCkString retval);
const char *CkSsh_hostKeyFingerprint(HCkSsh cHandle);
void CkSsh_getHttpProxyAuthMethod(HCkSsh cHandle, HCkString retval);
void CkSsh_putHttpProxyAuthMethod(HCkSsh cHandle, const char *newVal);
const char *CkSsh_httpProxyAuthMethod(HCkSsh cHandle);
void CkSsh_getHttpProxyDomain(HCkSsh cHandle, HCkString retval);
void CkSsh_putHttpProxyDomain(HCkSsh cHandle, const char *newVal);
const char *CkSsh_httpProxyDomain(HCkSsh cHandle);
void CkSsh_getHttpProxyHostname(HCkSsh cHandle, HCkString retval);
void CkSsh_putHttpProxyHostname(HCkSsh cHandle, const char *newVal);
const char *CkSsh_httpProxyHostname(HCkSsh cHandle);
void CkSsh_getHttpProxyPassword(HCkSsh cHandle, HCkString retval);
void CkSsh_putHttpProxyPassword(HCkSsh cHandle, const char *newVal);
const char *CkSsh_httpProxyPassword(HCkSsh cHandle);
int CkSsh_getHttpProxyPort(HCkSsh cHandle);
void CkSsh_putHttpProxyPort(HCkSsh cHandle, int newVal);
void CkSsh_getHttpProxyUsername(HCkSsh cHandle, HCkString retval);
void CkSsh_putHttpProxyUsername(HCkSsh cHandle, const char *newVal);
const char *CkSsh_httpProxyUsername(HCkSsh cHandle);
int CkSsh_getIdleTimeoutMs(HCkSsh cHandle);
void CkSsh_putIdleTimeoutMs(HCkSsh cHandle, int newVal);
BOOL CkSsh_getIsConnected(HCkSsh cHandle);
BOOL CkSsh_getKeepSessionLog(HCkSsh cHandle);
void CkSsh_putKeepSessionLog(HCkSsh cHandle, BOOL newVal);
void CkSsh_getLastErrorHtml(HCkSsh cHandle, HCkString retval);
const char *CkSsh_lastErrorHtml(HCkSsh cHandle);
void CkSsh_getLastErrorText(HCkSsh cHandle, HCkString retval);
const char *CkSsh_lastErrorText(HCkSsh cHandle);
void CkSsh_getLastErrorXml(HCkSsh cHandle, HCkString retval);
const char *CkSsh_lastErrorXml(HCkSsh cHandle);
int CkSsh_getMaxPacketSize(HCkSsh cHandle);
void CkSsh_putMaxPacketSize(HCkSsh cHandle, int newVal);
int CkSsh_getNumOpenChannels(HCkSsh cHandle);
BOOL CkSsh_getPasswordChangeRequested(HCkSsh cHandle);
int CkSsh_getReadTimeoutMs(HCkSsh cHandle);
void CkSsh_putReadTimeoutMs(HCkSsh cHandle, int newVal);
void CkSsh_getSessionLog(HCkSsh cHandle, HCkString retval);
const char *CkSsh_sessionLog(HCkSsh cHandle);
int CkSsh_getSoRcvBuf(HCkSsh cHandle);
void CkSsh_putSoRcvBuf(HCkSsh cHandle, int newVal);
int CkSsh_getSoSndBuf(HCkSsh cHandle);
void CkSsh_putSoSndBuf(HCkSsh cHandle, int newVal);
void CkSsh_getSocksHostname(HCkSsh cHandle, HCkString retval);
void CkSsh_putSocksHostname(HCkSsh cHandle, const char *newVal);
const char *CkSsh_socksHostname(HCkSsh cHandle);
void CkSsh_getSocksPassword(HCkSsh cHandle, HCkString retval);
void CkSsh_putSocksPassword(HCkSsh cHandle, const char *newVal);
const char *CkSsh_socksPassword(HCkSsh cHandle);
int CkSsh_getSocksPort(HCkSsh cHandle);
void CkSsh_putSocksPort(HCkSsh cHandle, int newVal);
void CkSsh_getSocksUsername(HCkSsh cHandle, HCkString retval);
void CkSsh_putSocksUsername(HCkSsh cHandle, const char *newVal);
const char *CkSsh_socksUsername(HCkSsh cHandle);
int CkSsh_getSocksVersion(HCkSsh cHandle);
void CkSsh_putSocksVersion(HCkSsh cHandle, int newVal);
BOOL CkSsh_getStderrToStdout(HCkSsh cHandle);
void CkSsh_putStderrToStdout(HCkSsh cHandle, BOOL newVal);
BOOL CkSsh_getTcpNoDelay(HCkSsh cHandle);
void CkSsh_putTcpNoDelay(HCkSsh cHandle, BOOL newVal);
BOOL CkSsh_getUtf8(HCkSsh cHandle);
void CkSsh_putUtf8(HCkSsh cHandle, BOOL newVal);
BOOL CkSsh_getVerboseLogging(HCkSsh cHandle);
void CkSsh_putVerboseLogging(HCkSsh cHandle, BOOL newVal);
void CkSsh_getVersion(HCkSsh cHandle, HCkString retval);
const char *CkSsh_version(HCkSsh cHandle);
BOOL CkSsh_AuthenticatePk(HCkSsh cHandle, const char *username, HCkSshKey privateKey);
BOOL CkSsh_AuthenticatePw(HCkSsh cHandle, const char *login, const char *password);
BOOL CkSsh_AuthenticatePwPk(HCkSsh cHandle, const char *username, const char *password, HCkSshKey privateKey);
BOOL CkSsh_ChannelIsOpen(HCkSsh cHandle, int channelNum);
int CkSsh_ChannelPoll(HCkSsh cHandle, int channelNum, int pollTimeoutMs);
int CkSsh_ChannelRead(HCkSsh cHandle, int channelNum);
int CkSsh_ChannelReadAndPoll(HCkSsh cHandle, int channelNum, int pollTimeoutMs);
int CkSsh_ChannelReadAndPoll2(HCkSsh cHandle, int channelNum, int pollTimeoutMs, int maxNumBytes);
BOOL CkSsh_ChannelReceiveToClose(HCkSsh cHandle, int channelNum);
BOOL CkSsh_ChannelReceiveUntilMatch(HCkSsh cHandle, int channelNum, const char *matchPattern, const char *charset, BOOL caseSensitive);
BOOL CkSsh_ChannelReceiveUntilMatchN(HCkSsh cHandle, int channelNum, HCkStringArray matchPatterns, const char *charset, BOOL caseSensitive);
BOOL CkSsh_ChannelReceivedClose(HCkSsh cHandle, int channelNum);
BOOL CkSsh_ChannelReceivedEof(HCkSsh cHandle, int channelNum);
BOOL CkSsh_ChannelReceivedExitStatus(HCkSsh cHandle, int channelNum);
BOOL CkSsh_ChannelSendClose(HCkSsh cHandle, int channelNum);
BOOL CkSsh_ChannelSendData(HCkSsh cHandle, int channelNum, HCkByteData byteData);
BOOL CkSsh_ChannelSendEof(HCkSsh cHandle, int channelNum);
BOOL CkSsh_ChannelSendString(HCkSsh cHandle, int channelNum, const char *textData, const char *charset);
void CkSsh_ClearTtyModes(HCkSsh cHandle);
BOOL CkSsh_Connect(HCkSsh cHandle, const char *domainName, int port);
void CkSsh_Disconnect(HCkSsh cHandle);
int CkSsh_GetChannelExitStatus(HCkSsh cHandle, int channelNum);
int CkSsh_GetChannelNumber(HCkSsh cHandle, int index);
BOOL CkSsh_GetChannelType(HCkSsh cHandle, int index, HCkString outStr);
const char *CkSsh_getChannelType(HCkSsh cHandle, int index);
BOOL CkSsh_GetReceivedData(HCkSsh cHandle, int channelNum, HCkByteData outBytes);
BOOL CkSsh_GetReceivedDataN(HCkSsh cHandle, int channelNum, int maxNumBytes, HCkByteData outBytes);
int CkSsh_GetReceivedNumBytes(HCkSsh cHandle, int channelNum);
BOOL CkSsh_GetReceivedStderr(HCkSsh cHandle, int channelNum, HCkByteData outBytes);
BOOL CkSsh_GetReceivedText(HCkSsh cHandle, int channelNum, const char *charset, HCkString outStr);
const char *CkSsh_getReceivedText(HCkSsh cHandle, int channelNum, const char *charset);
BOOL CkSsh_GetReceivedTextS(HCkSsh cHandle, int channelNum, const char *substr, const char *charset, HCkString outStr);
const char *CkSsh_getReceivedTextS(HCkSsh cHandle, int channelNum, const char *substr, const char *charset);
int CkSsh_OpenCustomChannel(HCkSsh cHandle, const char *channelType);
int CkSsh_OpenDirectTcpIpChannel(HCkSsh cHandle, const char *targetHostname, int targetPort);
int CkSsh_OpenSessionChannel(HCkSsh cHandle);
BOOL CkSsh_PeekReceivedText(HCkSsh cHandle, int channelNum, const char *charset, HCkString outStr);
const char *CkSsh_peekReceivedText(HCkSsh cHandle, int channelNum, const char *charset);
BOOL CkSsh_ReKey(HCkSsh cHandle);
BOOL CkSsh_SaveLastError(HCkSsh cHandle, const char *path);
BOOL CkSsh_SendIgnore(HCkSsh cHandle);
BOOL CkSsh_SendReqExec(HCkSsh cHandle, int channelNum, const char *commandLine);
BOOL CkSsh_SendReqPty(HCkSsh cHandle, int channelNum, const char *termType, int widthInChars, int heightInChars, int widthInPixels, int heightInPixels);
BOOL CkSsh_SendReqSetEnv(HCkSsh cHandle, int channelNum, const char *name, const char *value);
BOOL CkSsh_SendReqShell(HCkSsh cHandle, int channelNum);
BOOL CkSsh_SendReqSignal(HCkSsh cHandle, int channelNum, const char *signalName);
BOOL CkSsh_SendReqSubsystem(HCkSsh cHandle, int channelNum, const char *subsystemName);
BOOL CkSsh_SendReqWindowChange(HCkSsh cHandle, int channelNum, int widthInChars, int heightInRows, int pixWidth, int pixHeight);
BOOL CkSsh_SendReqX11Forwarding(HCkSsh cHandle, int channelNum, BOOL singleConnection, const char *authProt, const char *authCookie, int screenNum);
BOOL CkSsh_SendReqXonXoff(HCkSsh cHandle, int channelNum, BOOL clientCanDo);
BOOL CkSsh_SetTtyMode(HCkSsh cHandle, const char *ttyName, int ttyValue);
BOOL CkSsh_UnlockComponent(HCkSsh cHandle, const char *unlockCode);
#endif