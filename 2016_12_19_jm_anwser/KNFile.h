#pragma once
#include <string>
#include <stdio.h>
using namespace std;
//파일 입출력을 담당 하낟.
#define  _BUFFSIZE_ 1024
class KNFile
{
private:
	FILE* m_pfile;
	char m_buff[_BUFFSIZE_];
public:
	KNFile(void);
	virtual ~KNFile(void);
	
	
	bool Open(string fileName,string mode);
	int  Read(void *buffer ,int size,int cnt);
	int  Write(const void* buffer , int size,int count);
	bool ReadLine(string& str);
	bool WriteLine(string& str);
	bool IsEOF();

	//bool fopen(const char *path, const char *mode);
	//size_t fread(void *buffer,  size_t size,  size_t count,  FILE *stream   );  
	//size_t fwrite(    const void *buffer,    size_t size,    size_t count,    FILE *stream  );
	//char *fgets(   char *str,  int n,  FILE *stream   );
	//int fputs(   const char *str,  FILE *stream   );  


	



};

