#include "Book.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;
//构造函数
CBook::CBook(char* cName,char* cIsbn,char* cPrice,char* cAuthor)
{
	strncpy(m_cName,cName,NUM1);
	strncpy(m_cIsbn,cIsbn,NUM1);
	strncpy(m_cPrice,cPrice,NUM2);
	strncpy(m_cAuthor,cAuthor,NUM2);
}

char* CBook::GetName()
{
	return m_cName;
}

void CBook::SetName(char* cName)
{
	strncpy(m_cName,cName,NUM1);
}

char* CBook::GetIsbn()
{
	return m_cIsbn;
}

void CBook::SetIsbn(char* cIsbn)
{
	strncpy(m_cIsbn,cIsbn,NUM1);
}

char* CBook::GetPrice()
{
	return m_cPrice;
}

void CBook::SetPrice(char* cPrice)
{
	strncpy(m_cPrice,cPrice,NUM2);
}

char* CBook::GetAuthor()
{
	return m_cAuthor;
}

void CBook::SetAuthor(char* cAuthor)
{
	strncpy(m_cAuthor,cAuthor,NUM2);
}

//写入图书信息到文件中
void CBook::WriteData()
{
	ofstream ofile;
	ofile.open("book.dat",ios::binary|ios::app);//以二进制输出方式打开book.dat，输出附加到文件末尾
	try
	{
		ofile.write(m_cName,NUM1);
		ofile.write(m_cIsbn,NUM1);
		ofile.write(m_cPrice,NUM2);
		ofile.write(m_cAuthor,NUM2);
	}
	catch(...)
	{
		throw "file error occurred";
		ofile.close();
	}
	ofile.close();	
}

//从文件中获得数据
void CBook::GetBookFromFile(int iCount)
{
	char cName[NUM1];
	char cIsbn[NUM1];
	char cPrice[NUM2];
	char cAuthor[NUM2];
	ifstream ifile;
	ifile.open("book.dat",ios::binary);//以二进制输入方式打开文件book.dat
	try
	{
		ifile.seekg(iCount*(NUM1+NUM1+NUM2+NUM2),ios::beg);//改变定位指针的位置，指向从流开始位置位移iCount*(NUM!+NUM1+NUM2+NUM2)个字节的位置
		ifile.read(cName,NUM1);
		if(ifile.tellg()>0)//tellg()返回当前定位指针的位置，代表输入流的大小
			strncpy(m_cName,cName,NUM1);
		ifile.read(cIsbn,NUM1);
		if(ifile.tellg()>0)
			strncpy(m_cIsbn,cIsbn,NUM1);
		ifile.read(cPrice,NUM2);
		if(ifile.tellg()>0)
			strncpy(m_cIsbn,cIsbn,NUM2);
		ifile.read(cAuthor,NUM2);
		if(ifile.tellg()>0)
			strncpy(m_cAuthor,cAuthor,NUM2);
	}
	catch(...)
	{
		throw "file error occurred";
		ifile.close();
	}
	ifile.close();
}

//删除第iCount个图书信息
void CBook::DeleteData(int iCount)//iCount为图书idex
{
	long respos;
	int iDataCount=0;
	fstream file;
	fstream tmpfile;
	ofstream ofile;
	char cTempBuf[NUM1+NUM1+NUM2+NUM2];
	file.open("book.dat",ios::binary|ios::in|ios::out);//二进制输入输出的方式打开文件book.dat
	tmpfile.open("temp.dat",ios::binary|ios::in|ios::out|ios::trunc);//二进制输入输出的方式打开文件temp.dat，如果文件存在，把文件长度设为0
	file.seekg(0,ios::end);//当前指针定位在文件末尾
	respos=file.tellg();//返回定位指针当前指向的文件位置，即输入流的大小
	iDataCount=respos/(NUM1+NUM1+NUM2+NUM2);//共有的图书数
	if(iCount < 0 && iCount > iDataCount)
	{
		throw "Input number error";
	}
	else
	{
		file.seekg((iCount)*(NUM1+NUM1+NUM2+NUM2),ios::beg);//当前指针定位到下一个图书信息的开头
		for(int j=0;j<(iDataCount-iCount);j++)
		{
			memset(cTempBuf,0,NUM1+NUM1+NUM2+NUM2);//初始化cTempBuf内存空间
			file.read(cTempBuf,NUM1+NUM1+NUM2+NUM2);//从文件中读取NUM1+NUM1+NUM2+NUM2个字符放到cTmepBuf指向的缓存中
			tmpfile.write(cTempBuf,NUM1+NUM1+NUM2+NUM2);//从cTmepBuf指向的缓存写NUM1+NUM1+NUM2+NUM2个字符到文件中
		}
		file.close();
		tmpfile.seekg(0,ios::beg);
		ofile.open("book.dat");
		ofile.seekp((iCount-1)*(NUM1+NUM1+NUM2+NUM2),ios::beg);
		for(int i=0;i<(iDataCount-iCount);i++)
		{
			memset(cTempBuf,0,NUM1+NUM1+NUM2+NUM2);
			tmpfile.read(cTempBuf,NUM1+NUM1+NUM2+NUM2);
			ofile.write(cTempBuf,NUM1+NUM1+NUM2+NUM2);
		}
	}
	tmpfile.close();
	ofile.close();
	remove("temp.dat");//删除文件temp.dat
}


