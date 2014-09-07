#include "vectorarray.h"
vectorarray::vectorarray(){
	vectorarray::reset(0);
	return;
}
vectorarray::vectorarray(int n){
	vectorarray::reset(n);
	return;
}
vectorarray::vectorarray(const vectorarray &u){
	vectorarray::reset(u.v.size());
	for(int i=0;i<u.v.size();i++){
		v[i] = u.v[i];
	}
	return;
}
vectorarray::vectorarray(const double *array,int size){
	if(size == 0){
		return;
	}
	vectorarray::reset(size);
	for(int i=0;i<size;i++){
		v[i] = array[i];
	}
	return;
}
void vectorarray::reset(int n = 0){
	v.clear();
	if(n == 0){
		return;
	}
	v.resize(n);
	for(int i=0;i<n;i++){
		v[i] = 0;
	}
	return;
}
vectorarray vectorarray::operator= (const vectorarray &u){
	if(&u == this){
		return *this;
	}
	vectorarray::reset(u.v.size());
	for(int i=0;i<u.v.size();i++){
		v[i] = u.v[i];
	}
	return *this;
}
vectorarray vectorarray::operator+(const vectorarray &a){
	if(a.v.size()!=v.size()){
		printf("\nError: Adding vectors of different sizes\n");
		exit(-1);
	}
	vectorarray sum = vectorarray(v.size());
	for(int i=0;i<v.size();i++){
		sum.v[i] = a.v[i] + v[i];
	}
	return sum;
}
vectorarray vectorarray::operator-(const vectorarray &a){
	if(a.v.size()!=v.size()){
		printf("\nError: Substracting vectors of different sizes\n");
		exit(-1);
	}
	vectorarray sum = vectorarray(v.size());
	for(int i=0;i<v.size();i++){
		sum.v[i] = v[i] - a.v[i];
	}
	return sum;
}
int vectorarray::getSize(){
	return v.size();
}
void vectorarray::print(){
	printf("\n{");
	for(int i=0;i<v.size();i++){
		printf(" %lf ",v[i]);
	}
	printf("}\n");
	return;
}
double vectorarray::get(int i){
	if(i<0||i>=v.size()){
		printf("ERROR: invalid get\n");
		exit(-1);
	}
	return v[i];
}
void vectorarray::set(int i,double x){
	if(i<0||i>=v.size()){
		printf("ERROR: invalid set\n");
		exit(-1);
	}
	v[i] = x;
	return;
}
vectorarray vectorarray::operator*(const double &x){
	vectorarray result = vectorarray(v.size());
	for(int i=0;i<v.size();i++){
		result.set(i,v[i] * x);
	}
	return result;
}
double vectorarray::operator*(const vectorarray &x){
	double sum = 0;
	if(v.size()!=x.v.size()){
		printf("ERROR in DOT PRODUCT !!\n");
		exit(0);
	}
	for(int i=0;i<v.size();i++){
		sum = sum + (v[i]*x.v[i]);
	}
	return sum;
}
vectorarray vectorarray::operator/(const double &x){
	if(x<0.0000001){
		printf("\nDIVIDING VECTORARAAY BY VERY LOW VALUE !!\n");
		exit(-1);
	}
	vectorarray result = vectorarray(v.size());
	for(int i=0;i<v.size();i++){
		result.set(i,v[i] / x);
	}
	return result;
}
void vectorarray::set(double x){
	for(int i=0;i<v.size();i++){
		v[i] = x;
	}
	return;
}