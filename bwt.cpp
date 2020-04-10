
#include<iostream>
#include <bits/stdc++.h>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<map>
#include<algorithm>
#include"huffmann.h"
#include"unbwt.h"

using namespace std;


int major_index; //index which stores the original text in sorted arrangement of strings

//helping structure to compute suffix array
struct rotation
{
    int index;
    char *suffix;
};


//compare function to sort suffix matrix
int cmpfunc (const void *x, const void *y)
{
    struct rotation *rx=(struct rotation *)x;
    struct rotation *ry=(struct rotation *)y;
    return strcmp(rx -> suffix, ry -> suffix);
}
 
//create suffix array to perform burrows wheeler transform using input_text[(suffix_arr[i] – 1 + n ) % n]
int *computeSuffixArray(char *input_text, int len_text)
{

    struct rotation suff[len_text];
    for(int i=0;i<len_text;i++)
    {
        suff[i].index=i;
        suff[i].suffix=(input_text+i);
    }
 
    qsort(suff,len_text,sizeof(struct rotation),cmpfunc);
 

    int *suffix_arr =(int *) malloc(len_text * sizeof(int));
    for (int i = 0;i<len_text;i++)
        suffix_arr[i]=suff[i].index;
 

    return suffix_arr;
}
 
//find the last character in every row sorted strings
char *findLastChar(char *input_text, int *suffix_arr, int n)
{
    
    char *bwt_arr=(char *)malloc (n * sizeof(char));
    int i;
    for (i=0;i<n;i++)
    {
        // computes the last char which is given by input_text[(suffix_arr[i] + n - 1) % n]
        int j=suffix_arr[i]-1;
        if (j<0)
        { 
             
            j=j + n;
        }

    //storing the index of original string in the list of sorted strings using the dollar
        

        bwt_arr[i] = input_text[j];
        if(input_text[j]=='$')
            major_index=i;  
}
 
    bwt_arr[i] = '\0';
 
    return bwt_arr;
}


 int main()
{
    //data.txt contains the data to be compressed.
    FILE* f = fopen("data.txt", "r");
    string encoded="";

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);

    char* data = new char[size+1];
    //pointer which stores the entire input data.
    
    rewind(f);
    fread(data, sizeof(char), size, f);
    //ending the last character of the input to be $ to find majpr_index
    data[size-1]='$';
    data[size]='\0';
    
    //cout<<(int)data[5]<<endl;
    int len_text = strlen(data);
    //cout<<len_text<<endl;

    int *suffix_arr = computeSuffixArray(data, len_text);
 

    char *bwt_arr = findLastChar(data, suffix_arr, len_text);

    
    printf("Input text : %s\n", data);
    printf("Burrows - Wheeler Transform : %s\n", bwt_arr);


    //find out the distinct characters and frequeny to compute
    vector<char> character;
    vector<int> freq;
    vector <char> :: iterator it;
    int index;
    
    

    for(int i=0;i<len_text;i++)
    {
        //check whether the character is already available in the vector
        it=find(character.begin(), character.end(), bwt_arr[i]);
        if (it != character.end())
        {
        
            index=distance(character.begin(),it);
            //cout<<i<<" inside if "<<index<<endl;
            freq[index]+=1;
        }
        //else push it into the vector
        else
        {
            character.push_back(bwt_arr[i]);
            //cout<<i<<" inside else "<<endl;
            freq.push_back(1);
        }


    }
    //cout<<freq.size()<<endl;
    /*for(int i=0;i<character.size();i++)
    {
        cout<<character[i]<<" "<<freq[i]<<endl;
    }*/

    cout<<"major_index "<<major_index<<endl;

    int size_c=character.size();

    pair <char, string> code[size_c] ;
 
    HuffmanCodes(character, freq, size_c,code);

    for(int i=0;i<size_c;i++)
    {
        cout<<code[i].first<<" "<<code[i].second<<endl;
    } 

   // cout<<"came here";
    cout<<"huffmann codes are written into ";

    int pos=0;
    for(int i=0;i<=size;i++)
    {
        for(int j=(bwt_arr[i]==code[pos].first?pos:0);j<size_c;j++)
        {
            if(bwt_arr[i]==code[j].first)
            {
                //cout<<code[j].second<<endl;
                encoded.append(code[j].second);
                pos=j;
            }
        }
    }

    invert(bwt_arr,major_index);

    cout<<endl;
    cout<<"compressed text is written into output.txt "<<encoded<<endl;

    ofstream fil("huffman_map.txt");
    fil<<major_index<<endl;
    for(int i=0;i<size_c;i++)
        fil<<code[i].first<<" "<<code[i].second<<endl;
    fil.close();

    ofstream out("compressed_text.txt");
    out<<encoded;
    out.close();
    

    delete[] data;
    return 0;
}
