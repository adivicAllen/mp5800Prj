#ifndef ADIVIC_TCLIENT_H
#define ADIVIC_TCLIENT_H

#ifdef _WINDLL
	#define ADIVIC_TCLIENT_API __declspec(dllexport)
#else
	#define ADIVIC_TCLIENT_API __declspec(dllimport)
#endif

#include <string>
#include <fstream>

using namespace std;

/*
#include "BoostClient.h"
#include <string>

#define TLENET_TIME_OUT_MS 10000 //10 seconds
#define TLENET_TIME_OUT_MS_INTERVAL 10 //ms

struct TelnetImpl;
*/

struct TelnetImpl;


class Telnet_log {
    private:
        std::ofstream pLog;
		char buff[1024];
    public:
        inline Telnet_log(const std::string filename)
        {
            // create the file
            WriteOpen( filename );
        };
        inline ~Telnet_log(void)
        {
            // close the file
            WriteClose();
        };
        inline bool WriteOpen( const std::string filename )
        {
			pLog.open( filename , std::ofstream::out);
			return pLog.is_open();
        };
        inline bool WriteClose()
        {
            pLog.close();
            return true;
        };
        inline bool WriteLine(const char* message)
        {
            SYSTEMTIME st, lt;
            GetSystemTime(&st);
            GetLocalTime(&lt);
            sprintf (buff , "[%02d:%02d:%02d:%03d]:[%s]\n" ,
                     lt.wHour ,
                     lt.wMinute ,
                     lt.wSecond ,
                     lt.wMilliseconds ,
                     message
                    );
			pLog << buff;
			pLog.flush();
            return true;
        };
};




class  AdivicTClient{
	
public:
	AdivicTClient(const char* logFileName );
	~AdivicTClient(void);
	bool Open(const char * host, const char * port = "5499", unsigned int timeout = 30);
    void Close(void);
    void Send(const char * msg);
    void Send(const std::string & msg);
	void Send(const char * msg, const int len);
    void ReadAllBuffer( std::string & msg);
    bool WaitToRead( std::string & msg);
    bool IsWaitTillReadToken(char * buf, const char * token, unsigned int timeout_ms = 10000);
	bool IsWaitTillReadTokenForSpectrum( char* buf, unsigned int buffLens ,const char * token);
    bool IsWaitTillReadToken(std::string & msg, const std::string & token);
	bool IsConnected();
	//void Test();
	const char* ip; //
private:
	bool m_isConnected;
	TelnetImpl *pTelnetImpl;

	 Telnet_log* m_Log;
};



#endif