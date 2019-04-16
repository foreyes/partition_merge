#include <iostream>
using namespace std;

void test(int x, int y = 10){
	cout<<x<<" "<<y<<endl;
}

int main(){
	test(1);
}
