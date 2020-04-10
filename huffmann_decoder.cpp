#include<iostream>
#include<fstream>
#include<string.h>
#include"unbwt.h"


using namespace std;

 int main()
{
	int k=0;
	int major_index;
    FILE* f = fopen("output.txt", "r");

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    char* compressed_data = new char[size];
    rewind(f);
    fread(compressed_data, sizeof(char), size, f);
    compressed_data[size]='\0';
    string str(compressed_data);

    cout<<compressed_data<<endl;
    cout<<str<<endl;

    pair <char, string> code[100] ;
    char character;
    string cod;
    char *final=new char[size];

    ifstream file("encoded.txt");
    int checker=1;

    file>>major_index;
    cout<<major_index<<endl;
	while(file>>noskipws>>character)   	
    {
		if(character==' ' && checker!=1)
		{
			//cout<<"inside if ";
			file>>cod;	
			//cout<<cod<<endl;
			checker=2;
			code[k++].second=cod; 
		}
		else if(character=='\n' && checker!=1 ){checker= 1;}

		else
		{
		//cout<<"outside if"<<character<<endl;
    	code[k].first=character;
    	checker=2;
    	//code[k++].second=cod;
		}
    }
 
    cout<<"k= "<<k<<endl;
    for(int i=0;i<10;i++)
		cout<<code[i].first<<" "<<code[i].second<<endl;

	//cout<<"came here "<<str.length()<<" "<<k<<endl;

	int position=0;
	int len=1;
	int k1=0;
	for(int i=0;i<str.length();i++)
	{
		//cout<<"code received at i="<<i<<" "<<str.substr(position,len)<<" "<<position<<endl;
		for(int j=0;j<k;j++)
		{
			//cout<<code[j].second<<" ";
			if(str.substr(position,len)==code[j].second)
			{
				cout<<code[j].first;
				final[k1++]=code[j].first;
				len=0;
				position=i+1;
			}
			//cout<<endl;
		}
		len=len+1;
	}
	cout<<endl;
	final[k1]='\0';
	cout<<final;
	invert(final,major_index);
    delete[] compressed_data;
}
