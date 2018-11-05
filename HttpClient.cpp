#include "stdafx.h"
#include "HttpClient.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
namespace http = boost::beast::http;    // from <boost/beast/http.hpp>

const char SAFE[] =
{
	/*      0 1 2 3  4 5 6 7  8 9 A B  C D E F */
	/* 0 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 1 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 2 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 3 */ 1,1,1,1, 1,1,1,1, 1,1,0,0, 0,0,0,0,
	/* 4 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
	/* 5 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,
	/* 6 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
	/* 7 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,
	/* 8 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 9 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* A */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* B */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* C */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* D */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* E */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* F */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
};

const char HEX2DEC[] = 
{
	/*       0  1  2  3   4  5  6  7   8  9  A  B   C  D  E  F */
	/* 0 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* 1 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* 2 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* 3 */  0, 1, 2, 3,  4, 5, 6, 7,  8, 9,-1,-1, -1,-1,-1,-1,
	/* 4 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* 5 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* 6 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* 7 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* 8 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* 9 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* A */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* B */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* C */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* D */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* E */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* F */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1
};

const char DEC2HEX[16 + 1] = "0123456789ABCDEF";

HttpClient::HttpClient()
{

}

std::string HttpClient::LoadFileFromDisk(char *szFileName)
{
	std::ifstream ClipboardFile(szFileName, std::ios::in | std::ios::binary);
	std::string file_content;

	if( ClipboardFile.is_open() )
	{
		ClipboardFile.seekg(0, std::ios::end);
		int length = ClipboardFile.tellg();
		ClipboardFile.seekg(0, std::ios::beg);

		char *lpBuffer = new char[length];

		ClipboardFile.read(lpBuffer, length);
		ClipboardFile.close();

		file_content.insert(0, lpBuffer, length);

		delete[] lpBuffer;
	}

	return file_content;
}

std::string HttpClient::Upload()
{
	auto const host = (const char *)this->m_Address;
	auto const port = std::to_string(this->m_Port);
	auto const target = this->m_Target.c_str();
	int version = 11; //HTTP 1.1

	// The io_context is required for all I/O
	boost::asio::io_context ioc;

	// These objects perform our I/O
	tcp::resolver resolver{ ioc };
	tcp::socket socket{ ioc };
	
	// Look up the domain name
	auto const results = resolver.resolve(host, port);

	// Make the connection on the IP address we get from a lookup
	boost::asio::connect(socket, results.begin(), results.end());

	// Set up an HTTP GET request message
	http::request<http::string_body> req{ http::verb::post, target, version };
	req.set(http::field::content_type, this->m_ContentType);
	req.set(http::field::host, host);
	req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

	req.body() = this->m_PostData;
	req.prepare_payload();

	std::cout << req << std::endl;

	// Send the HTTP request to the remote host
	http::write(socket, req);

	// This buffer is used for reading and must be persisted
	boost::beast::flat_buffer buffer;

	// Declare a container to hold the response
	http::response<http::string_body> res;

	// Receive the HTTP response
	http::read(socket, buffer, res);

	// Write the message to standard out
	std::cout << res << std::endl;

	// Gracefully close the socket
	boost::system::error_code ec;
	socket.shutdown(tcp::socket::shutdown_both, ec);

	// not_connected happens sometimes
	// so don't bother reporting it.
	//
	if (ec && ec != boost::system::errc::not_connected)
		throw boost::system::system_error{ ec };

	std::string link = ParseResult((char*)res.body().c_str());

	return link;
}

std::string HttpClient::UrlEncode(const std::string & sSrc)
{
	const unsigned char * pSrc = (const unsigned char *)sSrc.c_str();
	const int SRC_LEN = sSrc.length();
	unsigned char * const pStart = new unsigned char[SRC_LEN * 3];
	unsigned char * pEnd = pStart;
	const unsigned char * const SRC_END = pSrc + SRC_LEN;
 
	for (; pSrc < SRC_END; ++pSrc)
	{
		if (SAFE[*pSrc])
			*pEnd++ = *pSrc;
		else
		{
			// escape this char
			*pEnd++ = '%';
			*pEnd++ = DEC2HEX[*pSrc >> 4];
			*pEnd++ = DEC2HEX[*pSrc & 0x0F];
		}
	}
 
	std::string sResult((char *)pStart, (char *)pEnd);
	delete [] pStart;
	return sResult;
}

std::string HttpClient::UrlDecode(const std::string & sSrc)
{
	// Note from RFC1630:  "Sequences which start with a percent sign
	// but are not followed by two hexadecimal characters (0-9, A-F) are reserved
	// for future extension"
	const unsigned char * pSrc = (const unsigned char *)sSrc.c_str();
	const int SRC_LEN = sSrc.length();
	const unsigned char * const SRC_END = pSrc + SRC_LEN;
	const unsigned char * const SRC_LAST_DEC = SRC_END - 2; // last decodable '%' 
	
	char * const pStart = new char[SRC_LEN];
	char * pEnd = pStart;
	
	while (pSrc < SRC_LAST_DEC)
	{
		if (*pSrc == '%')
		{
			char dec1; char dec2;
			if (-1 != (dec1 = HEX2DEC[*(pSrc + 1)])
				&& -1 != (dec2 = HEX2DEC[*(pSrc + 2)]))
			{
				*pEnd++ = (dec1 << 4) + dec2;
				pSrc += 3;
				continue;
			}
		}

		*pEnd++ = *pSrc++;
	}

	// the last 2- chars
	while (pSrc < SRC_END)
		*pEnd++ = *pSrc++;

	std::string sResult(pStart, pEnd);
	delete [] pStart;
	return sResult;
}

HttpClient::~HttpClient()
{

}