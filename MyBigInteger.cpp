#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <windows.h>
#define RED    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED)
#define BLUE   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE)
#define GREEN  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN)
#define WHITE  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN)
#define CYAN   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_GREEN)
#define PURPLE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE)
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN)
using namespace std;
class LongNum
{
	private:
		int a[1000];
		bool fuhao;
		int leng;
		void jinwei()       //进位
		{
			for(int i=0; i<500-1; i++)
			{
				if(a[i]>=10)
				{
					a[i+1] += a[i]/10;
					a[i] %= 10;
				}
			}
			leng = getLeng();
		}
		void jiewei()    //借位
		{
			int i,j;
			leng = getLeng();
			for(i=0; i<leng-1; i++)
			{
				while(a[i]<0)
				{
					a[i] += 10;
					a[i+1]--;
				}
			}
			leng = getLeng();
		}
	public:
		LongNum()
		{
			memset(a,0,sizeof(a));
			fuhao = false;
			leng = 0;
		}
		LongNum(int t)
		{
			fuhao = false;
			int temp = t;
			memset(a,0,sizeof(a));
			int i = 0;
			if(t<0)
			{
				fuhao = true;
				t *= -1;
			}
			while(t)
			{
				a[i++] = t%10;
				t /= 10;
			}
			leng = i;
			if(temp==0) leng = 1;
			//leng = getLeng();
		}
		LongNum(long long t)
		{
			fuhao = false;
			long long temp = t;
			memset(a,0,sizeof(a));
			int i = 0;
			if(t<0)
			{
				fuhao = true;
				t *= -1;
			}
			while(t)
			{
				a[i++] = t%10;
				t /= 10;
			}
			leng = i;
			if(temp==0) leng = 1;
			//leng = getLeng();
		}
		LongNum(const LongNum& p)
		{
			leng = p.leng;
			fuhao = p.fuhao;
			memset(a,0,sizeof(a));
			for(int i=0; i<leng; i++)
				a[i] = p.a[i];
		}
		void getLongNum(void)
		{
			int i;
			memset(a,0,sizeof(a));
			fuhao = false;
			char s[501];
			printf("请输入大整数：\n");
			scanf("%s",s);
			int lengs = strlen(s);
			if(s[0]!='-')
			{
				leng = lengs;
				for(i=0; i<lengs; i++)
					a[lengs-i-1] = s[i]-'0';
			}
			else
			{
				fuhao = true;
				leng = lengs-1;
				for(i=1; i<lengs; i++)
					a[leng-i] = s[i] - '0';
			}

		}
		void showLongNum(int flag=0)
		{
			if(flag) printf("(");
			if(fuhao) putchar('-');
			for(int i=leng-1; i>=0; i--)
				printf("%d",a[i]);
			if(flag) printf(")");
		}
		void addNum(LongNum A,LongNum B)   //两正数相加 A + B
		{
			LongNum C;
			int i,j,len = max(A.leng,B.leng);
			for(int i=0; i<len; i++)
			{
				C.a[i] = A.a[i] + B.a[i];
			}
			C.jinwei();
			C.showLongNum();
		}
		void addLongNum(LongNum A,LongNum B)
		{
			if(!A.fuhao&&!B.fuhao)
			{
				addNum(A,B);
				return;
			}
			if(!A.fuhao&&B.fuhao)
			{
				B.fuhao = false;
				difNum(A,B);
				B.fuhao = true;
				return;
			}
			if(A.fuhao &&B.fuhao)
			{
				printf("-");
				addNum(A,B);
				return;
			}
			if(A.fuhao&&!B.fuhao)
			{
				A.fuhao = false;
				difNum(B,A);
				A.fuhao = true;
				return;
			}

		}
		void difNum(LongNum A,LongNum B)   //两数相减 A - B
		{
			if(!A.fuhao&&!B.fuhao)   //A B 均为正数
			{
				int com = cmpLongNum(A,B);
				if(com==0)
				{
					puts("0");    //A==B
					return;
				}
				if(com<0)        //   A < B
				{
					printf("-");
					difPostiveLongNum(B,A);
					return;
				}
				if(com>0)
				{
					difPostiveLongNum(A,B);
					return;
				}
			}
			if(!A.fuhao&&B.fuhao)      //A>0  B<0
			{
				addNum(A,B);
				return;
			}
			if(A.fuhao&&!B.fuhao)     //A<0 B>0
			{
				printf("-");
				addNum(A,B);
				return;
			}
			if(A.fuhao&&B.fuhao)   //A<0  B<0  -(B-A)
			{
				int com = cmpLongNum(B,A);
				if(com==0)
				{
					puts("0");    //A==B
					return;
				}
				if(com<0)        //   A < B
				{
					printf("-");
					difPostiveLongNum(A,B);
					return;
				}
				if(com>0)
				{
					difPostiveLongNum(B,A);
					return;
				}
			}

		}
		void difPostiveLongNum(LongNum A,LongNum B)   //A-B  (A>B)
		{
			LongNum C;
			int len = A.getLeng(),i,j;
			for(i=0; i<len; i++)
				C.a[i] = A.a[i] - B.a[i];
			C.leng = len;
			C.jiewei();
			C.showLongNum();
		}
		int cmpLongNum(LongNum A,LongNum B)     //比较两个数A,B的大小(不考虑符号)
		{
			int lenga = A.getLeng(),lengb = B.getLeng();
			if(lenga<lengb)
			{
				return -1;
			}
			if(lenga>lengb) return 1;
			for(int i=lenga; i>=0; i--)
			{
				if(A.a[i]>B.a[i]) return 1;
				else if(A.a[i]<B.a[i]) return -1;
				else continue;
			}
			return 0;
		}
		int getLeng()
		{
			int i;
			for(i=499; i>0; i--)
			{
				if(a[i]!=0) break;
			}
			return i+1;
		}

		void zijia(LongNum B)   // A += B
		{
			int i;
			for(int i=0; i<500; i++)
				a[i] += B.a[i];
			//	this->jinwei();
		}
		void product(LongNum A,LongNum B)  //A比B长度长
		{
			int i,j;
			LongNum ans;
			int la = A.getLeng(),lb = B.getLeng();
			for(i=0; i<lb; i++)
			{
				LongNum temp;
				for(j=0; j<la; j++)
				{
					temp.a[i+j] = A.a[j] * B.a[i];
				}
				//temp.jinwei();
				//temp.leng = temp.getLeng();
				//temp.showLongNum();cout<<endl;
				ans.zijia(temp);
			}
			ans.jinwei();
			ans.showLongNum();
		}
		void productLongNum(LongNum A,LongNum B)
		{
			if(!A.fuhao&&B.fuhao||!B.fuhao&&A.fuhao) printf("-");
			if(A.leng>B.leng) product(A,B);
			else product(B,A);
		}
		bool operator < (const LongNum& q)const
		{
			if(q.fuhao&&!fuhao) return false;
			if(!q.fuhao&&fuhao) return true;
			int len = leng,lenq = q.leng;
			int i,j,maxlen = max(len,lenq);
			bool yes=false;
			if(len<lenq) yes = true;
			else if(len>lenq) yes = false;
			else
			{
				for(i=maxlen-1; i>=0; i--)
				{
					if(a[i]<q.a[i])
					{
						yes = true;
						break;
					}
					if(a[i]>q.a[i])
					{
						yes = false;
						break;
					}
				}
			}
			if(!fuhao&&!q.fuhao) return yes;
			if(fuhao&&q.fuhao)
			{
				if(i==-1) return false;
				if(yes) return false;
				else return true;
			}
		}
		LongNum divLongNum(LongNum A,LongNum B,LongNum& mod)
		{

			if(cmpLongNum(A,B)<0)
			{
				mod = A;
				return (LongNum)0;
			}
			if(cmpLongNum(A,B)==0)
			{
				mod = (LongNum)0;
				LongNum C(1);
				if(A.fuhao!=B.fuhao) C.fuhao = true;
				return C;
			}
			int diflen = A.leng - B.leng;
			LongNum temp(1),C;
			if(diflen>1)
				temp.a[diflen-1] = 1,temp.a[0] = 0,temp.leng = diflen;
			//C = temp * B;
			while(temp * B < A)
			{
				temp = temp + (LongNum)1;
				//cout<<"temp = "<<temp<<endl;
				//cout<<temp<<" * "<<B<<" = "<<temp*B<<endl;
			}
			temp = temp - (LongNum)1;
			mod = A - temp * B;
			if(mod==B) mod = (LongNum)0,temp = temp + (LongNum)1;
			if(A.fuhao) mod.fuhao = true;
			return temp;

		}
		LongNum absLongNum()
		{
			LongNum tt = *this;
			tt.fuhao = false;
			return tt;
		}
		void showDivandRemainder(LongNum A,LongNum B)
		{
			LongNum mod;
			if(cmpLongNum(A,B)<0)
			{
				cout<<A<<" / "<<B<<" = 0"<<" …… "<<A<<endl;
				return;
			}
			if(cmpLongNum(A,B)==0)
			{
				mod = (LongNum)0;
				LongNum C(1);
				if(A.fuhao!=B.fuhao) C.fuhao = true;
				cout<<"("<<A<<") / ("<<B<<") = "<<C<<" …… "<<0<<endl;
				return;
			}
			int diflen = A.leng - B.leng;
			LongNum temp(1),C;
			if(diflen>1)
				temp.a[diflen-1] = 1,temp.a[0] = 0,temp.leng = diflen;
			while(cmpLongNum(temp*B,A)<0)
			{
				temp = temp + (LongNum)1;
			}
			if(cmpLongNum(A,temp*B)<0)
				temp = temp - (LongNum)1;
			mod = A.absLongNum() - temp * B.absLongNum();
			if(mod==B) mod = (LongNum)0,temp = temp + (LongNum)1;
			if(A.fuhao) mod.fuhao = true;
			if(A.fuhao!=B.fuhao) temp.fuhao = true;
			cout<<A<<" / "<<B<<" = "<<temp<<" …… "<<mod<<endl;


		}




		LongNum addP(LongNum A,LongNum B)   //两正数相加 A + B
		{
			LongNum C;
			int i,j,len = max(A.leng,B.leng);
			for(int i=0; i<len; i++)
			{
				C.a[i] = A.a[i] + B.a[i];
			}
			C.jinwei();
			return C;
		}
		LongNum add(LongNum A,LongNum B)
		{
			if(!A.fuhao&&!B.fuhao)
			{
				return addP(A,B);
			}
			if(A.fuhao &&B.fuhao)
			{
				LongNum C = addP(A,B);
				C.fuhao = true;
				return C;
			}
			if(!A.fuhao&&B.fuhao)
			{
				LongNum C;
				B.fuhao=false;
				C = dif(A,B);
				B.fuhao = true;
				return C;
			}
			if(A.fuhao&&!B.fuhao)
			{
				LongNum C;
				A.fuhao=false;
				C = dif(B,A);
				A.fuhao = true;
				return C;
			}

		}

		LongNum difP(LongNum A,LongNum B)   //A-B  (A>B)
		{
			LongNum C;
			int len = A.getLeng(),i,j;
			for(i=0; i<len; i++)
				C.a[i] = A.a[i] - B.a[i];
			C.leng = len;
			C.jiewei();
			return C;
		}




		LongNum dif(LongNum A,LongNum B)   //两数相减 A - B
		{
			if(!A.fuhao&&!B.fuhao)   //A B 均为正数
			{
				int com = cmpLongNum(A,B);
				LongNum C;
				if(com==0)
				{
					C.leng = 1;    //A==B
					return C;
				}
				if(com<0)        //   A < B
				{
					C = difP(B,A);
					C.fuhao = true;
					return C;
				}
				if(com>0)
				{
					C = difP(A,B);
					return C;
				}
			}
			if(!A.fuhao&&B.fuhao)      //A>0  B<0
			{
				LongNum C = addP(A,B);
				return C;
			}
			if(A.fuhao&&!B.fuhao)     //A<0 B>0
			{
				LongNum C = addP(A,B);
				C.fuhao = true;
				return C;
			}
			if(A.fuhao&&B.fuhao)   //A<0  B<0  -(B-A)
			{
				int com = cmpLongNum(B,A);
				if(com==0)
				{
					LongNum C;    //A==B
					C.leng = 0;
					return C;
				}
				if(com<0)        //   A < B
				{
					LongNum C = difP(A,B);
					C.fuhao = true;
					return C;
				}
				if(com>0)
				{
					LongNum C;
					C = difP(B,A);
					return C;
				}
			}

		}








		/////////////////////////////////////////////运算符重载
		LongNum operator + (LongNum B)
		{
			LongNum C = add(*this,B);
			/*int i,j,len = max(leng,B.leng);
			for(int i=0;i<len;i++){
				C.a[i] = a[i] + B.a[i];
			}
			C.jinwei();*/
			return C;
		}
		LongNum operator - (LongNum B)
		{
			LongNum C = dif(*this,B);
			return C;
		}
		LongNum operator / (LongNum B)
		{
			LongNum mod,ans;
			ans = divLongNum(*this,B,mod);
			return ans;
		}
		LongNum operator % (LongNum B)
		{
			LongNum mod,ans;
			ans = divLongNum(*this,B,mod);
			return mod;
		}
		LongNum& operator = (LongNum B)
		{
			this->leng = B.leng;
			this->fuhao = B.fuhao;
			memset(a,0,sizeof(a));
			for(int i=0; i<leng; i++)
				a[i] = B.a[i];
			return (*this);
		}
		bool operator == (const LongNum& p)const
		{
			if(leng!=p.leng||fuhao!=p.fuhao) return false;
			for(int i=0; i<leng; i++)
			{
				if(a[i]!=p.a[i]) return false;
			}
			return true;
		}
		LongNum operator * (LongNum B)
		{
			int i,j;
			LongNum ans;
			int la = this->getLeng(),lb = B.getLeng();
			for(i=0; i<lb; i++)
			{
				LongNum temp;
				for(j=0; j<la; j++)
				{
					temp.a[i+j] = a[j] * B.a[i];
				}
				temp.jinwei();
				//temp.showLongNum();
				//cout<<endl;
				ans.zijia(temp);
			}
			ans.jinwei();
			if(fuhao&&!B.fuhao||!fuhao&&B.fuhao) ans.fuhao = true;
			if(ans.leng==1&&ans.a[0]==0) ans.fuhao = false;
			return ans;
		}
		friend ostream& operator << (ostream& out,const LongNum& q)
		{
			if(q.fuhao&&!(q==(LongNum)0)) out<<"-";
			for(int i=q.leng-1; i>=0; i--)
				out<<q.a[i];
			return out;
		}
		friend istream& operator >>(istream& input,LongNum& p)
		{
			memset(p.a,0,sizeof(p.a));
			p.fuhao = false;
			char s[501];
			scanf("%s",s);
			int i;
			int lengs = strlen(s);
			if(s[0]!='-')
			{
				p.leng = lengs;
				for(i=0; i<lengs; i++)
					p.a[lengs-i-1] = s[i]-'0';
			}
			else
			{
				p.fuhao = true;
				p.leng = lengs-1;
				for(i=1; i<lengs; i++)
					p.a[lengs-i-1] = s[i] - '0';
			}
			return input;
		}
		LongNum powLongNum(int b)
		{
			LongNum temp(1),a(*this);
			while(b)
			{
				if(b&1) temp = temp * a;
				a = a * a;
				b >>= 1;
			}
			return temp;
		}

		LongNum powLongNum(LongNum b)
		{
			b.fuhao = false;
			LongNum temp(1),a(*this);
			while(!(b.absLongNum()==(LongNum)0))
			{
				if(b.a[0]&1) temp = temp * a;
				a = a * a;
				b = b / (LongNum)2;
			}
			return temp;
		}
		void squareRoot()   //平方根
		{
			/*LongNum b = *this;
			b.fuhao = false;
			b = b % 10000;*/
			LongNum b(10000);
			for(int i=0; i<5; i++)
				b.a[i] = this->a[i];
			b.fuhao = false;
			b.leng = b.getLeng();
			LongNum left = (LongNum)0,right = b,mid;
			while(left<right||left==right)
			{
				mid = (left + right) / 2;
				if(mid*mid<b) left = mid + 1;
				else right = mid - 1;
			}
			if(left*left==b)
			{
				cout<<b<<"的算术平方根为：";
				cout<<left;
				cout<<endl;
				return;
			}
			cout<<b<<"的算术平方根介于";
			cout<<right;
			cout<<"和";
			cout<<left;
			cout<<"之间。\n";
		}

};

int main()
{
	system("title 我的大整数类 by 许智超");
	LongNum n(0),n1(1538624856321789ll),n2,n3;
	int T = 20,x;
	//cout<<n<<endl;
	//cout<<n1<<endl;
	YELLOW;
	printf("Design by xzc. Enjoy it!\n\n");
	while(T--)
	{

		//n1.getLongNum();
		//n2.getLongNum();
		/*n1.showLongNum(1); printf(" - ");
		n2.showLongNum(1); printf(" = ");
		n.difNum(n1,n2);
		puts("");
		n1.showLongNum(1); printf(" + ");
		n2.showLongNum(1); printf(" = ");
		n.addLongNum(n1,n2);
		puts("");
		n1.showLongNum(1); printf(" * ");
		n2.showLongNum(1); printf(" = ");
		n.productLongNum(n1,n2);
		puts("");
		/*if(n1<n2) n1.showLongNum(1),printf(" < "),n2.showLongNum(1),puts("");
		else n1.showLongNum(1),printf(" >= "),n2.showLongNum(1),puts("");*/
		WHITE;
		cout<<"请输入一个500位之内的大整数(可负)：\n";
		CYAN;
		cin>>n1;
		WHITE;
		cout<<"请输入一个500位之内的大整数(可负)：\n";
		CYAN;
		cin>>n2;
		WHITE;
		cout<<"请输入一个100以内的正整数:_\b";
		CYAN;
		cin>>x;
		YELLOW;
		cout<<"请输入一个100000以内的整数：\n";
		CYAN;
		cin>>n3;
		x %= 100;
		YELLOW;
		cout<<"("<<n1<<") + ("<<n2<<") = ";
		PURPLE;
		cout<<n1+n2<<endl<<endl;
		YELLOW;
		cout<<"("<<n1<<") - ("<<n2<<") = ";
		GREEN;
		cout<<n1-n2<<endl<<endl;
		YELLOW;
		cout<<"("<<n1<<") * ("<<n2<<") = ";
		PURPLE;
		cout<<n1*n2<<endl<<endl;
		GREEN;
		n.showDivandRemainder(n1,n2);
		YELLOW;
		cout<<n1<<" ^ "<<x<<" = ";
		PURPLE;
		cout<<n1.powLongNum(x)<<endl<<endl;
		GREEN;
		n3.squareRoot();
		cout<<endl<<endl;
	}


	return 0;
}
