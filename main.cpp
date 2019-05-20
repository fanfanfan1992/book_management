#include <iostream>
#include <iomanip>//�ṩsetw()����ԭ��
#include <stdlib.h>
#include <conio.h>//����̨�������
#include <string.h>
#include <fstream>
#include "Book.h"

#define CMD_COLS 80
#define CMD_LINES 25
using namespace std;

void SetScreenGrid();//������ʾ����
void ClearScreen();//����
void SetSysCaption();//����˵��
void SetSysCaption( const char *pText);//��������
void ShowWelcome();//��ӭ����
void ShowRootMenu();//��ʾ��Ŀ¼
void WaitView(int  iCurPage);
void WaitUser();
void GuideInput();
int GetSelect();
long GetFileLength(ifstream & ifs);
void ViewData(int iSelPage );
void DeleteBookFromFile();
void mainloop();

void SetScreenGrid()
{
	char sysSetBuf[80];
	sprintf(sysSetBuf,"mode con cols=%d lines=%d",CMD_COLS,CMD_LINES);//�ȼ���sysSetBuf = "mode con cols=80 lines=50",����д����ַ�����
	system(sysSetBuf);//����ϵͳConsole����̨��ʾ�Ŀ�ȸ߶ȣ�����һ��DOS����
}
void ClearScreen()
{
	system("cls");
} 
void SetSysCaption()
{
	system("title Sample");
}
void SetSysCaption( const char *pText)
{
	char sysSetBuf[80];
	sprintf(sysSetBuf,"title %s",pText);
	system(sysSetBuf);
}
void ShowWelcome()
{
	for(int i=0;i<7;i++)
	{
		cout << endl;
	}
	cout << setw(40);//**************��ռ40���ֽڣ�ǰ���������Ϊ�ո�
	cout << "**************" << endl;
	cout << setw(40);
	cout << "*ͼ�����ϵͳ*" << endl;
	cout << setw(40);
	cout << "**************" << endl;
}
void ShowRootMenu()
{
	cout << setw(40);
	cout << "��ѡ���ܣ�" << endl;
	cout << endl;
	cout << setw(38);
	cout << "1 �������" << endl;
	cout << endl;
	cout << setw(38);
	cout << "2 ���ȫ��" << endl;
	cout << endl;
	cout << setw(38);
	cout << "3 ɾ��ͼ��" << endl;
}


void WaitView(int  iCurPage)
{
	char buf[256];
	gets(buf);
	if(buf[0]=='q')
		system("exit");
	if(buf[0]=='m')
		mainloop();
	if(buf[0]=='n')
		ViewData(iCurPage);
}
void WaitUser()
{
	int iInputPage=0;
	cout << "enter�������˵���q�˳�" << endl;
	char buf[256];
	gets(buf);
	if(buf[0]=='q')
		system("exit");
}
void GuideInput()
{
	char inName[NUM1];
	char inIsdn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];

	cout << "��������" << endl;
		cin >> inName;
	cout << "����ISDN" << endl;
		cin >> inIsdn;
	cout << "����۸�" << endl;
		cin >> inPrice;
	cout << "��������" << endl;
		cin >> inAuthor;
	CBook book(inName,inIsdn,inPrice,inAuthor);
	book.WriteData();
	cout << "Write Finish" << endl;
	WaitUser();
}

int GetSelect()
{
	char buf[256];
	gets(buf);
	return atoi(buf);//atoi()���ַ���ת��������
}
long GetFileLength(ifstream & ifs)
{
	long tmppos;
	long respos;
	tmppos=ifs.tellg();//��õ�ǰλ��
	ifs.seekg(0,ios::end);
	respos=ifs.tellg();//����ļ�ĩβλ��
	ifs.seekg(tmppos,ios::beg);//�ָ���ǰλ��
	return respos;
}


void ViewData(int iSelPage = 1)
{
	int iPage=0;
	int iCurPage=0;
	int iDataCount=0;
	char inName[NUM1];
	char inIsbn[NUM1];
	char price[NUM2];
	char inAuthor[NUM2];
	bool bIndex=false;
	int iFileLength;
	iCurPage=iSelPage;
	ifstream ifile;
	ifile.open("book.dat",ios::binary);//|ios::nocreate
	iFileLength=GetFileLength(ifile);
	iDataCount=iFileLength/(NUM1+NUM1+NUM2+NUM2);
	if(iDataCount>=1)
		bIndex=true;
	iPage=iDataCount / 20+1; //ÿҳ20����¼

	
	ClearScreen();

	cout << " ���м�¼" << iDataCount <<" ";
	cout << " ����ҳ��" << iPage << " ";
	cout << " ��ǰҳ��" << iCurPage << " ";
	cout << " n��ʾ��һҳ m����" << endl;
	cout << setw(5)<<"Index" ;
	cout << setw(22) << "Name" << setw(22) << "Isbn" ;
	cout << setw(15) << "Price" << setw(15) << "Author";
	cout << endl;
	try
	{
		ifile.seekg((iCurPage-1)*20*(NUM1+NUM1+NUM2+NUM2),ios::beg);
		if(!ifile.fail())
		{
			for(int i=1;i<21;i++)
			{
				memset(inName,0,128);
				memset(inIsbn,0,128);
				memset(price,0,50);
				memset(inAuthor,0,50);
				if(bIndex)
					cout <<setw(3)<< ((iCurPage-1)*20+i);
				ifile.read(inName,NUM1);
				cout <<setw(24)<< inName;
				ifile.read(inIsbn,NUM1);
				cout <<setw(24)<< inIsbn;
				ifile.read(price,NUM2);
				cout <<setw(12)<< price;
				ifile.read(inAuthor,NUM2);
				cout <<setw(12)<< inAuthor;
				cout << endl;//һ����¼
				if( ifile.tellg()<0)
					bIndex=false;
				else
					bIndex=true;
				}
		}
	}
	catch(...)
	{
		cout << "throw file exception" << endl;
		throw "file error occurred";
		ifile.close();
	}
	if(iCurPage<iPage)
	{
		iCurPage=iCurPage+1;
		WaitView(iCurPage);
	}
	else
	{
		WaitView(iCurPage);
	}
	ifile.close();
}


void DeleteBookFromFile()
{
	int iDelCount;
	cout << "Input delete index" << endl;
	cin >> iDelCount;
	CBook tmpbook;
	tmpbook.DeleteData(iDelCount);
	cout << "Delete Finish" << endl;
	WaitUser();
}
void mainloop()
{
	ShowWelcome();
	while(1)
	{
		ClearScreen();
		ShowWelcome();
		ShowRootMenu();
		switch(GetSelect())
		{
		case 1:
			ClearScreen();
			GuideInput();
			break;
		case 2:
			ClearScreen();
			ViewData();
			break;
		case 3:
			ClearScreen();
			DeleteBookFromFile();
			break;
		}
	}
}
void main()
{
	
	SetScreenGrid();
	SetSysCaption("ͼ�����ϵͳ");
	mainloop();
}
