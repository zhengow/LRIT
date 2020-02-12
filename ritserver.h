#include<string>
#include<fstream>
#include<iostream>

using namespace std;

class Ticker{
	private:
		int tick;
		float last;
		int volume;
	public:
		Ticker(int tick, float last, int volume){
			this->tick = tick;
			this->last = last;
			this->volume = volume;
		}
		
		~Ticker(){
		}
};
