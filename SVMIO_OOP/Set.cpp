#include "Set.h"
#include "other.h"

Set::Set(){
	reset();
	return;
}
Set::Set(const Set &S){
	reset();
	for(int i=0;i<S.v.size();i++){
		v.push_back(S.v[i]);
	}
	return;
}
void Set::fillRandom(int n,int randMax = 1000){
	Set::reset();
	for(int i = 0;i<n;i++){
		v.push_back(rand()%randMax);
	}
	return;
}
Set::Set(const char *filename){
	Set::reset();
	FILE *f = fopen(filename,"r");
	if(f == NULL){
		printf("\nERROR: Can not Find Query File\n");
		exit(-1);
	}
	int i = 0;
	int query;
	while(1){
		int fscnafreturn = fscanf(f,"%d",&query);
		//printf(" %d ",query);
		if(query == -1){
			break;
		}
		v.push_back(query);
	}
	fclose(f);
	return;
}
Set::Set(const std::vector<int> vec){
	Set::reset();
	for(int i=0;i<vec.size();i++){
		v.push_back(vec[i]);
	}
	return;
}

void Set::reduceSizeInPlace(double percentage){
	if(v.size() == 0){
		return;
	}
	int tempSize = nearestInteger(percentage * v.size());
    // if(tempSize == 0){
    //     tempSize = 1;
    // }
    if(tempSize > v.size()){
    	tempSize = v.size();
    }
    std::vector<int> B = selectKItems(v,v.size(),tempSize);
    
    v.clear();
    v.resize(tempSize);

    for(int i=0;i<tempSize;i++){
    	v[i] = B[i];
    }
    return;
}

void Set::reset(){
	v.clear();
	return;
}
int Set::getSize(){
	return v.size();
}
void Set::add(int element){
	v.push_back(element);
	return;
}
void Set::print(){
	printf("\n{");
	for(int i=0;i<v.size();i++){
		printf(" %d ", v[i]);
	}
	printf("}\n");
}
void Set::sort(){
	std::sort(v.begin(),v.end());
	return;
}
void Set::removeDuplicates(){
	std::sort( v.begin(), v.end() );
	v.erase( unique( v.begin(), v.end() ), v.end() );
}
Set Set::operator=(const Set &S){
	if(this == &S){
		return *this;
	}
	Set::reset();
	for(int i =0;i<S.v.size();i++){
		v.push_back(S.v[i]);
	}
	return *this;
}
Set Set::operator+(const Set &S){
	Set X;
	X.v.insert(X.v.end(),v.begin(),v.end());
	X.v.insert(X.v.end(),S.v.begin(),S.v.end());
	X.removeDuplicates();
	return X;
}
Set Set::operator*(const Set &A){
	Set S = Set(A);
	Set X;
	Set::sort();
	S.sort();

	int i = 0,j = 0;
	while(i<v.size() && j<S.v.size()){
		if(v[i] < S.v[j]){
			i++;
		}else if(S.v[j] < v[i]){
			j++;
		}else{
			X.v.push_back(v[i]);
			i++;
		}
	}
	X.removeDuplicates();
	return X;
}
Set Set::operator-(const Set &A){
	Set S = Set(A);
	Set X;
	Set::sort();
	S.sort();

	int i = 0,j = 0;

	while(i < v.size() & j < S.v.size()){
		if(v[i] < S.v[j]){
			X.add(v[i]);
			i++;
		}else if(v[i] > S.v[j]){
			j++;
		}else{
			i++;
			j++;
		}
	}

	while(i < v.size()){
		X.add(v[i]);
		i++;
	}
	X.removeDuplicates();
	return X;
}
int Set::getElement(int pos){
	if(pos<0 || pos >= v.size()){
		printf("\nERROR IN SET Index\n");
		exit(-1);
	}
	return v[pos];
}
std::vector<int> Set::SetToVector(){
	std::vector<int> vec;
	for(int i=0;i<v.size();i++){
		vec.push_back(v[i]);
	}
	return vec;
}