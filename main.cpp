/************************************************************
参考URL
	http://blpr.net/?p=263
	
description
	vectorで、
	"ポインタではなく"、
	オブジェクト自体を取り扱う場合、push_backしたときに次のことが行われています。
		*	push_backの対象となるオブジェクトをコピーコンストラクタでコピー
		*	既にpush_back済みのものがあれば、再びコピーコンストラクタでそのコピーを作り、元々コピーしてあったものをデストラクタで始末する。
	
Consideration
	vectorでオブジェクト自体を持つのは避けるのが良いかもしれない。
	vectorが廃棄される時に、自動でobjectのdestructorが呼ばれる、と言うメリットはあるものの、
	vectorの「気遣い」であるコピーコンストラクタ、デストラクタに、反って戸惑わされる恐れがあるからです。
	それよりも「後始末をしっかりする」ことさえ注意していればよい「ポインタを持つ」方が楽なのでは、と考えています。
************************************************************/
#include <stdio.h>
#include <vector>

using std::vector;

/************************************************************
************************************************************/
class HOGE{
private:
	int num;
	
public:
	HOGE(int _num) : num(_num)
	{
		printf("constructor:%d\n", num);
	}
	
	HOGE(const HOGE& org) : num(org.num)
	{
		printf("copy constructer:%d\n", num);
	}
	
	~HOGE()
	{
		printf("destructor:%d\n", num);
	}
	
	HOGE& operator=(const HOGE& org)
	{
		num = org.num;
		printf("ope=\n");
		
		return *this;
	}
};

/************************************************************
0----------
constructor:0
1----------
constructor:1
2----------
3----------
copy constructer:0		push_backで渡された変数をcopy constructorでcopy.
4----------
copy constructer:1		push_backで渡された変数をcopy constructorでcopy.
copy constructer:0		すでにpush_back済みの変数をcopy constructorでcopy.
destructor:0			同 push_back済みの変数をdestruct.
5----------
destructor:1			vectorにpush_backされた変数のdestruct.
destructor:0
destructor:1			main関数内の変数をdestruct.
destructor:0
************************************************************/
int main()
{
	int point = 0;
	
	printf("%d----------\n", point++);
	HOGE Hoge1(0);
	printf("%d----------\n", point++);
	HOGE Hoge2(1);
	printf("%d----------\n", point++);
	vector<HOGE> Array;
	printf("%d----------\n", point++);
	
	Array.push_back(Hoge1);
	printf("%d----------\n", point++);
	Array.push_back(Hoge2);
	printf("%d----------\n", point++);
	
	return 0;
}
