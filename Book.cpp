#include "Book.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;
//���캯��
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

//д��ͼ����Ϣ���ļ���
void CBook::WriteData()
{
	ofstream ofile;
	ofile.open("book.dat",ios::binary|ios::app);//�Զ����������ʽ��book.dat��������ӵ��ļ�ĩβ
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

//���ļ��л������
void CBook::GetBookFromFile(int iCount)
{
	char cName[NUM1];
	char cIsbn[NUM1];
	char cPrice[NUM2];
	char cAuthor[NUM2];
	ifstream ifile;
	ifile.open("book.dat",ios::binary);//�Զ��������뷽ʽ���ļ�book.dat
	try
	{
		ifile.seekg(iCount*(NUM1+NUM1+NUM2+NUM2),ios::beg);//�ı䶨λָ���λ�ã�ָ�������ʼλ��λ��iCount*(NUM!+NUM1+NUM2+NUM2)���ֽڵ�λ��
		ifile.read(cName,NUM1);
		if(ifile.tellg()>0)//tellg()���ص�ǰ��λָ���λ�ã������������Ĵ�С
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

//ɾ����iCount��ͼ����Ϣ
void CBook::DeleteData(int iCount)//iCountΪͼ��idex
{
	long respos;
	int iDataCount=0;
	fstream file;
	fstream tmpfile;
	ofstream ofile;
	char cTempBuf[NUM1+NUM1+NUM2+NUM2];
	file.open("book.dat",ios::binary|ios::in|ios::out);//��������������ķ�ʽ���ļ�book.dat
	tmpfile.open("temp.dat",ios::binary|ios::in|ios::out|ios::trunc);//��������������ķ�ʽ���ļ�temp.dat������ļ����ڣ����ļ�������Ϊ0
	file.seekg(0,ios::end);//��ǰָ�붨λ���ļ�ĩβ
	respos=file.tellg();//���ض�λָ�뵱ǰָ����ļ�λ�ã����������Ĵ�С
	iDataCount=respos/(NUM1+NUM1+NUM2+NUM2);//���е�ͼ����
	if(iCount < 0 && iCount > iDataCount)
	{
		throw "Input number error";
	}
	else
	{
		file.seekg((iCount)*(NUM1+NUM1+NUM2+NUM2),ios::beg);//��ǰָ�붨λ����һ��ͼ����Ϣ�Ŀ�ͷ
		for(int j=0;j<(iDataCount-iCount);j++)
		{
			memset(cTempBuf,0,NUM1+NUM1+NUM2+NUM2);//��ʼ��cTempBuf�ڴ�ռ�
			file.read(cTempBuf,NUM1+NUM1+NUM2+NUM2);//���ļ��ж�ȡNUM1+NUM1+NUM2+NUM2���ַ��ŵ�cTmepBufָ��Ļ�����
			tmpfile.write(cTempBuf,NUM1+NUM1+NUM2+NUM2);//��cTmepBufָ��Ļ���дNUM1+NUM1+NUM2+NUM2���ַ����ļ���
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
	remove("temp.dat");//ɾ���ļ�temp.dat
}


