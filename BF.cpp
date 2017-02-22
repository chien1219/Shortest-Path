#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<cmath>

using namespace std;

double dist(double,double,double,double);
int detect_number(char* buffer){
	int sum = 0;
	for (int i = 0; buffer[i] >= '0' && buffer[i] <= '9'; i++){
		sum = sum * 10 + buffer[i] - '0';
	}
	return sum;
}
int main(int argc,char* argv[])
{
	
	if (argc != 2){
		printf("Input error: You have to key the [input filename]!!\n");
		exit(1);
	}

	FILE *input_file;

	if ((input_file = fopen(argv[1], "r")) == NULL){
		cout << "Cannot open input file!!\n";
		exit(1);
	}
	char a[5];
	int num_of_input;
	if(fgets(a,5,input_file)!=NULL)
	num_of_input = detect_number(a);			///////handling input_number
	vector<double> x,y;

	ifstream ifs(argv[1],ifstream::in);
	for(int i=0;i<=num_of_input;i++){                           ///////handling coorx,y
		string str;
		//fscanf(input_file, "%*[^\n]");
		if(i==0)getline(ifs,str);
		else{ 
			double temp_x,temp_y;
			getline(ifs,str);
			stringstream iss;
			iss<<str;
			iss>>temp_x>>temp_y;
			x.push_back(temp_x);
			y.push_back(temp_y);
		}
	}
	double min_dist=dist(x[0],y[0],x[1],y[1]);
	for(int i=0;i<num_of_input-1;i++){				////////start computing
		for(int j=i+1;j<num_of_input;j++){
			if(dist(x[i],y[i],x[j],y[j])<min_dist)
				min_dist = dist(x[i],y[i],x[j],y[j]);
		}		
	}
	cout<<"Sortest distance:"<<min_dist<<endl;
	fclose(input_file);
	return 0;
}

double dist(double x1,double y1,double x2, double y2){
	
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		
}