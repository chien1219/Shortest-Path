#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<cmath>
#include <stdio.h>
#include <stdlib.h>
#include<cfloat>

using namespace std;

/*找closest pair：

輸入：n 個平面上的點

輸出：closest pair之距離

依X及Y軸大小作排序

若只有2個點，傳回此2點的距離

找出一個中間線L將之分成左右兩邊左(SL)右(SR)

以遞迴的方法去做步驟2及3以找出在左右兩邊的closest pair，let d = min(dL, dR)

如果在其中一點在L-d及另一點在L+d，且其距離小於d則closet pair為此2點*/

struct point{double x,y;};					///function declare
double min(double,double );
double brute(point [],int );
int compare_x (const void * , const void * );
int compare_y (const void * , const void * );
double stripclosest(point [], int, double );
double closestone(point [], int);
double closest(point [], int);
double dist(point , point );
int detect_number(char* buffer){
	int sum = 0;
	for (int i = 0; buffer[i] >= '0' && buffer[i] <= '9'; i++){
		sum = sum * 10 + buffer[i] - '0';
	}
	return sum;
}
int main(int argc,char* argv[]){
	
	if (argc != 2){
		printf("You have to key in the [input filename]!!\n");
		exit(1);
	}

	FILE *input_file;

	if ((input_file = fopen(argv[1], "r")) == NULL){
		cout << "Can't open input file!!\n";
		exit(1);
	}
	char a[5];
	int num_of_input;
	if(fgets(a,5,input_file)!=NULL)
	num_of_input = detect_number(a);			///////handling input_number
	ifstream ifs(argv[1],ifstream::in);
	point P[num_of_input];
	for(int i=0;i<=num_of_input;i++){           ///////handling coorx,y
		string str;
		//fscanf(input_file, "%*[^\n]");
		if(i==0)getline(ifs,str);
		else{ 	int k=i-1;
			double temp_x,temp_y;
			getline(ifs,str);
			stringstream iss;
			iss<<str;
			iss>>temp_x>>temp_y;
			P[k].x=temp_x;
			P[k].y=temp_y;
		}
	}
	int n = sizeof(P)/sizeof(P[0]);
	cout<<"Sortest distance:"<<closest(P,n)<<endl;
	
	fclose(input_file);
	return 0;
}
double dist(point p1, point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y)
               );
}
double brute(point p[],int n){
	double min = DBL_MAX;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(dist(p[i],p[j])<min)
				min = dist(p[i],p[j]);
		}
	}
	return min;
}
double min(double x,double y){
	return (x<y) ? x: y;	
}
int compare_x (const void * a, const void * b)
{
	point *p = (point *)a, *pp = (point *)b;
  return ( p->x - pp->x );
}
int compare_y (const void * a, const void * b)
{
	point *p = (point *)a, *pp = (point *)b;
  return ( p->y - pp->y );
}
double stripclosest(point strip[], int size, double d)
{
    double min = d; 
 
    qsort(strip, size, sizeof(point), compare_y);
    
    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i],strip[j]) < min)
                min = dist(strip[i], strip[j]);
 
    return min;
}
double closestone(point P[], int n)
{
    if (n <= 3)
        return brute(P, n);

    int mid = n/2;
    point midpoint = P[mid];
 
    double min_distl = closestone(P, mid);
    double min_distr = closestone(P + mid, n-mid);
 
    double d = min(min_distl, min_distr);
 
    point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(P[i].x - midpoint.x) < d)
            strip[j] = P[i], j++;

    return min(d, stripclosest(strip, j, d) );
}
 
double closest(point P[], int n)
{
    qsort(P, n, sizeof(point), compare_x);
    return closestone(P, n);
}

