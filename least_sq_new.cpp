#include<bits/stdc++.h>
using namespace std;
float* x;
float* y;
int n;
float c;

/**
 * Calculates a and b for best fit line for a set of points [p..q]
 * @param p Index of pth point in sorted coordinate array
 * @param q Index of qth point in sorted coordinate array
 * @param a Address to store computed parameter a
 * @param a Address to store computed parameter b
 */
void getCoeffs(int p, int q, float *a, float *b){
	float xsum = 0, ysum = 0, sqxsum = 0, xysum = 0;
	int l = q-p+1;
	for(int i=p; i<=q; i++){
		xsum += x[i];
		ysum += y[i];
		sqxsum += pow(x[i],2);
		xysum += x[i]*y[i];
	}
	*a = (l*xysum-xsum*ysum)/(l*sqxsum - pow(xsum,2));
	*b = (ysum - *a*xsum)/l;
	return;
}

/**
 * Computes square error for best fit line for a set of points [p..q]
 * @param p Index of pth point in sorted coordinate array
 * @param q Index of qth point in sorted coordinate array
 * @return Square error
 */
float squareError(int p, int q){
	float error = 0;
	float a, b;
	int flag = 0;
	if(p==q || p==q-1)
		return error;
	for(int i=p; i<=q; i++)
		if(x[i]!=x[q])
			flag = 1;
	if(flag == 0)
		return error;
	getCoeffs(p,q,&a,&b);
	for(int i=p; i<=q; i++)
		error += pow((y[i]-a*x[i]-b),2);
	return error;
}

/**
 * Computes the optimal cost for fitting every point incrementally 
 * @param m Pointer to array containing optimal cost for each point
 * @param im Pointer to array containing the start point of segment ending with each point
 * @param errors Pointer to matrix containing square errors for each pair of points 
 */
void createCostArray(float *m, float *im, float *errors){
	m[0] = 0;
	im[0] = 0;
	for(int j=1; j<n+1; j++){
		for(int i=1; i<=j; i++){
			*((errors+j*(n+1)) + i) = squareError(i-1,j-1);
		}	
	}
	for(int j=1; j<n+1; j++){
		float mincost = c*j;
		int mini = 1;
		for(int i=1; i<=j; i++){
			float cost = *((errors+j*(n+1)) + i)+c+m[i-1];
			if(cost<mincost){
				mincost = cost;
				mini = i;
			}
			m[j] = mincost;
			im[j] = mini;
		}
	}
	return;
}

/**
 * Selects segments which give least error for fitting all points 
 * @param m Pointer to array containing optimal cost for each point
 * @param im Pointer to array containing the start point of segment ending with each point
 * @param errors Pointer to matrix containing square errors for each pair of points 
 * @param j Index of rightmost point which hasn't been assigned a segment
 */
void findSegment(float *m, float *im, float *errors, int j){
	float mincost = j*c;
	float mini = j;
	if(j==0)
		return;
	for(int i=1; i<=j; i++){
		float cost = *((errors+j*(n+1)) + i)+c+m[i-1];
		if(cost<mincost){
			mincost = cost;
			mini = i;
		}
	}
	float a, b;
	getCoeffs(mini-1,j-1,&a,&b);
	cout<<j<<" "<<mini<<" "<<mincost<<" "<<a<<" "<<b<<"\n";
	ofstream fout;
	fout.open("output.txt",ios::app);
	fout<<j<<" "<<mini<<" "<<mincost<<" "<<a<<" "<<b<<"\n";
	fout.close();
	findSegment(m,im,errors,mini-1);
	return;
}

/**
 * Swaps two points for sorting 
 * @param i Index of ith point in input coordinate array
 * @param j Index of jth point in input coordinate array
 */
void swap(int i, int j){
	float temp = x[i];
	x[i] = x[j];
	x[j] = temp;
	temp = y[i];
	y[i] = y[j];
	y[j] = temp;
}

/**
 * Driver Function
 */
int main(){
	ifstream fin;
	ofstream fout;
	
	fout.open("output.txt");
	fout<<0<<" "<<0<<" "<<0<<" "<<0<<" "<<0<<"\n";
	fout.close();
	
	fin.open("input.txt");
	fin>>n>>c;
	x = new float[n];
	y = new float[n];
	cout<<"\nInput:\n";
	for(int i=0; i<n; i++){
		fin>>x[i]>>y[i];
		cout<<x[i]<<" "<<y[i]<<"\n";
	}	
	fin.close();	
	
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++){
			if(x[i]>x[j])
				swap(i,j);
			else if(x[i]==x[j] && y[i]>y[j])
				swap(i,j);	
		}		
	
	fout.open("sorted_input.txt");
	cout<<"\nSorted Input:\n";
	for(int i=0; i<n; i++){
		fin>>x[i]>>y[i];
		fout<<x[i]<<" "<<y[i]<<"\n";
		cout<<x[i]<<" "<<y[i]<<"\n";
	}
	fout.close();
	
	float m[n+1], im[n+1];
	float errors[n+1][n+1];
	for(int i=0; i<n+1; i++){
		m[i] = 0;
		im[i] = 0;
		for(int j=0; j<n+1; j++)
			errors[i][j] = 0;
	}
	
	cout<<"\nOutput:\n";
	createCostArray(m,im,(float *)errors);
	findSegment(m,im,(float *)errors,n);
	
	cout<<"\nM:\n";
	for(int i=0; i<n+1; i++)
		cout<<m[i]<<" ";
			
	cout<<"\nError Matrix:\n";
	for(int i=0; i<n+1; i++){
		for(int j=0; j<n+1; j++)
			cout<<errors[i][j]<<" ";
		cout<<"\n";	
	}	
	
	delete[] x;
	delete[] y;
	return 0;
}
