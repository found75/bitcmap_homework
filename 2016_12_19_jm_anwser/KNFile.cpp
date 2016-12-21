#include "KNFile.h"
#include <iostream>
#include <string>

using namespace std;

KNFile::KNFile(void)
	:m_pfile (NULL)
{

}

KNFile::~KNFile(void)
{
	if(m_pfile != NULL)
	{
		fclose(m_pfile);
		m_pfile = NULL;
	}
}

bool KNFile::Open(string fileName,string mode)
{
	if(m_pfile != NULL)
	{
		return false; //이미 열려 있는 파일 입니다.,
	}
	m_pfile = fopen(fileName.c_str(),mode.c_str());

	if(m_pfile == NULL)
	{
		return false; //파일열기 실패.
	}
	return true;
}
int KNFile::Read(void* buffer ,int size,int count)
{
	int readCnt = 0;
	if(m_pfile != NULL)
	{
		readCnt = fread(buffer,size,count,m_pfile);
	}
	return readCnt ;
}
int KNFile::Write(const void* buffer , int size,int count)
{
	int wCnt = 0;
	if(m_pfile != NULL)
	{
		wCnt = fwrite(buffer,size,count,m_pfile);
	}
	return wCnt;
}
bool KNFile::ReadLine(string& pStr)
{
	fscanf(m_pfile,"%s",m_buff);
	pStr = string(m_buff);
	return true;
	return false;
}
bool KNFile::WriteLine(string& pStr)
{
	//if(fputs(pStr.c_str(),m_pfile) != EOF)
	fprintf(m_pfile,"%s\n",pStr.c_str());
	/*{
		return true;
	}*/
	return true;
}

bool KNFile::IsEOF()
{
	return (feof(m_pfile) != 0);
}