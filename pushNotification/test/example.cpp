#include <stdio.h>
#include <string.h>
#include <iostream>

#include <arpa/inet.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

using namespace std;

/** #define SERVER_URL "gateway.sandbox.push.apple.com" */
#define SERVER_URL "gateway.push.apple.com"
#define SERVER_PORT 2195
#define DEVICE_BINARY_SIZE 32
#define MAXPAYLOAD_SIZE 256
#define SSL_ERROR_LEN 1024
#define MESSAGE_BUFF_LEN 1024

char m_szError[SSL_ERROR_LEN];
string m_strBuff;

SSL*      m_pSSL; /** SSL的对象指针，主要用于记录一些SSL中用到的算法和对象，以及最关键的SSL_CTX。 */
SSL_CTX*  m_pSSLCtx; /** SSL_CTX实际上就是一个SSL的上下文。这里可以记录和设置你的SSL一些状态，比如你采用的SSL协议格式（SSL2,SSL3或者TLS） */
BIO*      m_pSockBIO; /** BIO是一个标准的Socket对象封装，加解密算法在里面完成，并不暴露在外面，极大的减轻了开发人员的开发量 */

int Chr2Hex(char c)
{
	switch(c)
	{
		case '0'...'9':
			return c-'0';
		case 'a'...'f':
			return c - 'a' + 10;
		case 'A'...'F':
			return c - 'A' + 10;
		default:
			return 0;
	}

	return 0;
}

int Hex2Chr(char *DstStr,char *HexStr,int HexLen)
{
	int DesIndex = 0;

	for (int iSrcIndex=0; iSrcIndex<HexLen; iSrcIndex++)
	{
		/** 如果字符不属于十六进制值，跳到下一个字符 */
		if (*(HexStr+iSrcIndex)<'0' 
		|| (*(HexStr+iSrcIndex)>'9' && *(HexStr+iSrcIndex)<'A') 
		|| (*(HexStr+iSrcIndex)>'Z'&& *(HexStr+iSrcIndex)<'a') 
		|| *(HexStr+iSrcIndex)>'z')
		{
			iSrcIndex++;
			continue;
		}

		int iBig = Chr2Hex(*(HexStr+iSrcIndex));
		iSrcIndex++;
		int iSmall = Chr2Hex(*(HexStr+iSrcIndex));
		iSrcIndex++;

		*(DstStr+DesIndex) = iBig*16+iSmall;
		DesIndex++;
	}

	return DesIndex;
}

bool SSL_init()
{
	SSL_library_init(); /** SSL库初始化 */
	OpenSSL_add_all_algorithms(); /** 载入所有ssl算法 */
	SSL_load_error_strings(); /** 载入所有ssl错误消息 */

	return true;
}

int32_t CreateMessage(char *binaryMessageBuff,char *deviceTokenBinary, char *payloadBuff, size_t payloadLength)
{
	if (!deviceTokenBinary || !payloadBuff || !payloadLength)
	{
		return false;
	}

	printf("buff len: %d\n buff: %s\n",payloadLength,payloadBuff);

	uint8_t command = 0;

	char *binaryMessagePt = binaryMessageBuff;
	unsigned short networkOrderTokenLength = htons(DEVICE_BINARY_SIZE);
	unsigned short networkOrderPayloadLength = htons(payloadLength);

	*binaryMessagePt++ = command;

	memcpy(binaryMessagePt,&networkOrderTokenLength,sizeof(unsigned short));
	binaryMessagePt += sizeof(unsigned short);

	memcpy(binaryMessagePt, deviceTokenBinary, DEVICE_BINARY_SIZE);
	binaryMessagePt += DEVICE_BINARY_SIZE;

	memcpy(binaryMessagePt, &networkOrderPayloadLength, sizeof(unsigned short));
	binaryMessagePt += sizeof(unsigned short);

	memcpy(binaryMessagePt, payloadBuff, payloadLength);
	binaryMessagePt += payloadLength;

	return 1+sizeof(unsigned short)+DEVICE_BINARY_SIZE+sizeof(unsigned short)+payloadLength;
}

bool ConnectSSL(const char* pPassword, const char* pCmd, int32_t nCmdLen)
{
	char szURL[200]   = {'\0'};

	snprintf(szURL, sizeof(szURL), "%s:%d", SERVER_URL, SERVER_PORT);

	/** 初始化SSLCtx */
	m_pSSLCtx = SSL_CTX_new(SSLv23_client_method());
	if(m_pSSLCtx == NULL)
	{
		printf("SSL CTX new Fail.\n");
		return false;
	}

	SSL_CTX_set_options(m_pSSLCtx, SSL_OP_ALL);

	/** 验证证书文件目录 */
	if(SSL_CTX_load_verify_locations(m_pSSLCtx, NULL, "./") <= 0)
	{
		printf("Failed to set CA location...\n");
		ERR_print_errors_fp(stderr);
		return false;
	}

	/** 验证证书文件 */
	if (SSL_CTX_use_certificate_file(m_pSSLCtx, "../cert/520086631/push.pem", SSL_FILETYPE_PEM) <= 0)
	{
		printf("Cannot use Certificate File\n");
		ERR_print_errors_fp(stderr);
		return false;
	}

	/** 验证密码文件 */
	BIO* pKeyBuff = BIO_new_file("../cert/520086631/siyao.key", "r");
	if(NULL == pKeyBuff)
	{
		printf("[CSSLConnect::new file] \n Load key file Fail.\n");
		return false;
	}

	EVP_PKEY *pkey=PEM_read_bio_PrivateKey(pKeyBuff,NULL,NULL,(char *)pPassword);
	if(pkey==NULL)
	{
		printf("PEM_read_bio_PrivateKey err");

		return false;
	}

	if (SSL_CTX_use_PrivateKey(m_pSSLCtx,pkey) <= 0)
	{
		printf("SSL_CTX_use_PrivateKey err\n");
		return false;
	}

	/** 检查证书是否有效 */
	m_pSockBIO = BIO_new_ssl_connect(m_pSSLCtx);
	if(m_pSockBIO == NULL)
	{
		printf("aaaa\n");
		/** 没有正确的获得BIO */
		ERR_error_string(ERR_get_error(), (char* )m_szError);
		printf("[CSSLConnect::new connect] \n pSockBIO ERROR: %s.\n", m_szError);
		return false;
	}

	BIO_get_ssl(m_pSockBIO, &m_pSSL);
	if(m_pSSL == NULL)
	{
		/** 没有正确的获得BIO */
		ERR_error_string(ERR_get_error(), (char* )m_szError);
		printf("[CSSLConnect::get ssl] \n m_pSSL ERROR: %s.\n", m_szError);
		return false;
	}

	if(SSL_get_verify_result(m_pSSL) != X509_V_OK)
	{
		/** X509证书无效 */
		ERR_error_string(ERR_get_error(), (char* )m_szError);
		printf("[CSSLConnect::get result] \n SSL_get_verify_result ERROR: %s.\n", m_szError);
		return false;
	}

	SSL_set_mode(m_pSSL, SSL_MODE_AUTO_RETRY);

	BIO_set_conn_hostname(m_pSockBIO, szURL);
	if (NULL == m_pSockBIO)
	{
		ERR_error_string(ERR_get_error(), (char* )m_szError);
		printf("[CSSLConnect::set host] \n pSockBIO Connect ERROR: %s.\n", m_szError);
	}

	int nRet= BIO_do_connect(m_pSockBIO);
	if(nRet <= 0)
	{
		/** 没有正确连接 */
		ERR_error_string(ERR_get_error(), (char* )m_szError);
		printf("[CSSLConnect::Connect] \n pSockBIO Connect ERROR: %s.\n", m_szError);
		return false;
	}
	printf("connect success\n");

	int nPos    = 0;

	while(true)
	{
		if(nPos == nCmdLen )
		{
			break;
		}

		int nLen = BIO_write(m_pSockBIO, &pCmd[nPos], nCmdLen-nPos);
		if(nLen <= 0)
		{
			break;
		}
		else
		{
			nPos += nLen;
		}
		printf("write: %s, pos %d, nlen %d\n ",pCmd,nPos,nLen);
	}

	BIO_free_all(m_pSockBIO);
	SSL_CTX_free(m_pSSLCtx);

	return true;
} 

int main(int argc,char *argv[])
{
	char nType[] = "";
	char DeviceToken[] = "47d555b9569370be8e5fbfed980fc084b86fcd75b40ce6d8c27b749653217726";
	char sDeviceToken[DEVICE_BINARY_SIZE+1];

	char PayLoadBuff[] = "{\"aps\":{\"alert\":\"This is some fancy message.\",\"badge\":0}}";
	int PayLoadLen = strlen(PayLoadBuff);
	char MessageBuff[MESSAGE_BUFF_LEN];

	SSL_init();

	memset(sDeviceToken,0,DEVICE_BINARY_SIZE+1);
	Hex2Chr(sDeviceToken,DeviceToken,strlen(DeviceToken));

	int MessageLen = CreateMessage(MessageBuff,sDeviceToken,PayLoadBuff,PayLoadLen);
	ConnectSSL(nType,MessageBuff,MessageLen);

	return 0;
}
