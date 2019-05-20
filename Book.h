#define NUM1 128
#define NUM2 50
class CBook
{
public:
	CBook(){}
	CBook(char* cName,char* cIsbn,char* cPrice,char* cAuthor);
	~CBook(){}
public:
	char* GetName();
	void SetName(char* cName);
	char* GetIsbn();
	void SetIsbn(char* cIsbn);
	char* GetPrice();
	void SetPrice(char* cPrice);
	char* GetAuthor();
	void SetAuthor(char* cAuthor);
	void WriteData();
	void DeleteData(int iCount);
	void GetBookFromFile(int iCount);
protected:
	char m_cName[NUM1];
	char m_cIsbn[NUM1];
	char m_cPrice[NUM2];
	char m_cAuthor[NUM2];

};