#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void Generate(float *price);

int main(){
	string filename;
	cout << "Input filename:";
	cin >> filename;
	for(int i=0;i<10;i++){
		string tmp = filename + '_' + (char)(i+'0') + ".csv";
		ofstream outFile;
		outFile.open(tmp);
		
		float price[600];
		Generate(price);
		for(int j = 0; j < 600; j++){
			outFile << price[j] << '\n';
		}

		outFile.close();
	}

	return 0;
}

void Generate(float *price){
	price[0] = 50;
	for(int i=1;i<600;i++){
		price[i] = price[i-1] + (float)(rand()%10-4)/100;
	}
	return;
}
