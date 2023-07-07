#include <bits/stdc++.h>
const int MaxN = 50;
const int MaxM = 50;
const double up_alpha = 0.8, up_gamma = 0.5;
int N, M;
using namespace std;

double R[MaxN+MaxM][MaxN*MaxM][2], Q[MaxN+MaxM][MaxN*MaxM][2], QQ[MaxN*MaxM][2];
double QF[10010][10010] = {0,};
vector<int> X[MaxN+MaxM];
vector<int> NC[MaxN+MaxM], NS[MaxN*MaxM];
double P[MaxN*MaxM][2] = {0,};
int E[MaxN*MaxM] = {0,};

int Board[MaxN*MaxM] = {0,};
int lefts[10010] = {0,};
int minlefts[10010] = {0,};
int BoardHistory[10010][MaxN*MaxM] = {0,};

int iternum = 0;
int lastSelect = -1;

vector<int> arrangeV, arrangeW;

void next_two() {
	for(int i = 0; i<N; i++) {
		if(arrangeV[i]==0) {
			for(int j = 0; j<i; j++) {
				arrangeV[j] = 0;
			}
			arrangeV[i]++;
			return;
		}
	}
	arrangeV[0] = -1;
	return;
}

void make_first() {
	vector<int> narr;
	int cnt = 0;
	for(int i = 0; i<N; i++) {
		if(arrangeV[i]==0) {
			if(cnt!=0) narr.push_back(cnt);
			cnt = 0;
		}
		else {
			cnt++;
		}
	}
	if(cnt!=0) narr.push_back(cnt);
	arrangeW.clear();
	cnt = 0;
	int c1 = 0;
	
	for(int i = 0; i<N; i++) {
		if(cnt>=narr.size() || c1==narr[cnt]) {
			c1 = 0;
			cnt++;
			arrangeW.push_back(0);
		}
		else {
			c1++;
			arrangeW.push_back(1);
		}
	}
//	printf("%d\n", narr.size());
//	for(int i = 0; i<N; i++) {
//		printf("%d ", arrangeW[i]);
//	}
//	printf("\n");
}

int to_two_V() {
	int res = 0, cnt = 1;
	for(int i = 0; i<N; i++) {
		res += cnt * arrangeV[i];
		cnt *= 2;
	}
	return res;
}

int to_two_W() {
	int res = 0, cnt = 1;
	for(int i = 0; i<N; i++) {
		res += cnt * arrangeW[i];
		cnt *= 2;
	}
	return res;
}

int to_two_Cons(int t) {
	int cnt = 0;
	int c1 = 0;
	vector<int> temp;
	
	for(int i = 0; i<N; i++) {
		if(cnt>=X[t].size() || c1==X[t][cnt]) {
			c1 = 0;
			cnt++;
			temp.push_back(0);
		}
		else {
			c1++;
			temp.push_back(1);
		}
	}
	int res = 0; cnt = 1;
	for(int i = 0; i<N; i++) {
		res += cnt * temp[i];
		cnt *= 2;
	}
	return res;
}

void initAll() {
	for(int i = 0; i<MaxM+MaxN; i++) {
		for(int j = 0; j<MaxM*MaxN; j++) {
			R[i][j][0] = 0; R[i][j][1] = 0;
			Q[i][j][0] = 0; Q[i][j][1] = 0;
		}
		QQ[i][0] = 0; QQ[i][1] = 0;
		X[i].clear();
		NC[i].clear();
	}
	for(int i = 0; i<MaxM*MaxN; i++) {
		NS[i].clear();
		P[i][0] = 0;
		P[i][1] = 0;
		E[i] = 0;
		Board[i] = 0;
	}
	
	for(int i = 0; i<10000; i++) {
		lefts[i] = 0;
		minlefts[i] = 0;
		for(int j = 0; j<MaxM*MaxN; j++) {
			BoardHistory[i][j] = 0;
		}
	}
	
	iternum = 0;
	lastSelect = -1;
	
}

void initN() {
    for(int i = 0; i<N; i++) {
		for(int j = 0; j<M; j++) {
			NC[i].push_back(M*i+j);
		}
	}
	for(int i = 0; i<M; i++) {
		for(int j = 0; j<N; j++) {
			NC[N+i].push_back(i+M*j);
		}
	}
	
	for(int i = 0; i<N; i++) {
		for(int j = 0; j<M; j++) {
			NS[M*i+j].push_back(i);
			NS[M*i+j].push_back(N+j);
		}
	}
}

void initP() {
	for(int i = 0; i<N; i++) {
		for(int j = 0; j<M; j++) {
			P[M*i+j][0] = 1;
			P[M*i+j][1] = 1;
		}
	}
	for(int i = 0; i<N+M; i++) {
		for(int j = 0; j<N*M; j++) {
		    Q[i][j][0] = 1;
		    Q[i][j][1] = 1;
		}
	}
}

void initQ() {
	for(int i = 0; i<N+M; i++) {
		for(int j = 0; j<N*M; j++) {
		    Q[i][j][0] = 1;
		    Q[i][j][1] = 1;
		}
	}
}

void initQF() {
	int pn = pow(2, N);
	for(int i = 0; i<pn; i++) {
		for(int j = 0; j<pn; j++) {
			QF[i][j] = 0.01;
		}
	}
	
	arrangeV.clear();
	for(int i = 0; i<N; i++) {
		arrangeV.push_back(0);
	}
	while(1) {
		make_first();
		QF[to_two_W()][to_two_V()] = 1;
//		for(int i = 0; i<N; i++) {
//			printf("%d ", arrangeV[i]);
//		}
//		printf("\n");
		next_two();
		if(arrangeV[0]==-1) break;
	}
}

void next_arrangement(int m, bool horizontal) {
	int cnt = arrangeV.size()-1;
	int consum = X[m][cnt];
	while(cnt>=0) {
		arrangeV[cnt]++;
		if(horizontal)
			if(arrangeV[cnt]+consum-1>=M) {
				cnt--;
				consum += X[m][cnt]+1;
			}
			else{
				for(int i = cnt+1; i<arrangeV.size(); i++) {
					arrangeV[i] = arrangeV[i-1]+X[m][i-1]+1;
				}
				return;
			}
		else
			if(arrangeV[cnt]+consum-1>=N) {
				cnt--;
				consum += X[m][cnt]+1;
			}
			else{
				for(int i = cnt+1; i<arrangeV.size(); i++) {
					arrangeV[i] = arrangeV[i-1]+X[m][i-1]+1;
				}
				return;
			}
	}
	if(cnt<0) {
		arrangeV.clear();
		arrangeV.push_back(-1);
	}
}

vector<int> genArr(int m, bool horizontal) {
	vector<int> res;
	int cnt = 0;
	if(horizontal)
		for(int i = 0; i<M; i++) {
			if(cnt>=arrangeV.size()) {
				res.push_back(0);
				continue;
			}
			if(i<arrangeV[cnt]+X[m][cnt]) {
				if(arrangeV[cnt]<=i) res.push_back(1);
				else res.push_back(0);
			}
			else {
				res.push_back(0);
				cnt++;
			}
		}
	else
		for(int i = 0; i<N; i++) {
			if(cnt>=arrangeV.size()) {
				res.push_back(0);
				continue;
			}
			if(i<arrangeV[cnt]+X[m][cnt]) {
				if(arrangeV[cnt]<=i) res.push_back(1);
				else res.push_back(0);
			}
			else {
				res.push_back(0);
				cnt++;
			}
		}
	return res;
}

void printVec(vector<int> vec) {
	for(auto it: vec) {
		printf("%d ", it);
	}
	printf("\n");
	return;
}

vector<string> split(string str, char delimiter) {
    vector<string> ans;
    stringstream ss(str);
    string temp;
    while(getline(ss,temp,delimiter)) {
    	ans.push_back(temp);
    }
    return ans;
}

int ConsSum1() {
	int sum1 = 0;
    for(int i=0;i<N;i++) {
        for(int m : X[i]) sum1 += m;
    }
    return sum1;
}

int ConsSum2() {
	int sum2 = 0;
    for(int i=N;i<N+M;i++) {
        for(int m : X[i]) sum2 += m;
    }
    return sum2;
}

bool checkCons() {
    return ConsSum1() == ConsSum2();
}

bool checkConverge() {
	if(iternum==0) minlefts[iternum] = lefts[iternum];
	else minlefts[iternum] = minlefts[iternum-1]<lefts[iternum]?minlefts[iternum-1]:lefts[iternum];
	if(iternum<20) return false;
	if(iternum-lastSelect<10) return false;
	return minlefts[iternum]==minlefts[iternum-20];
}


void IterSolve(bool willPrint) {
	for(int m = 0; m<2*N; m++) {
		// R update
		arrangeV.clear();
        
		for(int r = 0; r<M; r++) {
		   R[m][NC[m][r]][0] = 0;
		   R[m][NC[m][r]][1] = 0;
		   arrangeV.push_back(0);
		}
		
		while(1) {
			int cnt = 0;
			double val = 1;
			int nowind = to_two_Cons(m);
//			for(int i = 0; i<N; i++) {
//				printf("%d ", arrangeV[i]);
//			}
//			printf("\n");
//			for(int i: X[m]) {
//				printf("%d ", i);
//			}
//			printf("\n");
//			printf("%d %d: %f\n", nowind, to_two_V(), QF[nowind][to_two_V()]);
			for(int r = 0; r<M; r++) {
				val *= Q[m][NC[m][r]][arrangeV[r]];
				
			}
			
			for(int r = 0; r<M; r++) {
				if(Q[m][NC[m][r]][arrangeV[r]]!=0) {
					double newv = val / Q[m][NC[m][r]][arrangeV[r]] * QF[nowind][to_two_V()] * QF[nowind][to_two_V()] * QF[nowind][to_two_V()]; 
	//				if(newv>R[m][NC[m][r]][arrangeV[r]]) R[m][NC[m][r]][arrangeV[r]] = newv;
					R[m][NC[m][r]][arrangeV[r]] += newv;
//					printf("%d - %f %f PUT: %f\n", arrangeV[r], val, Q[m][NC[m][r]][arrangeV[r]], newv);
				}
				
			}
            
            next_two();
            
			if(arrangeV[0]==-1) break;
        }
        
        for(int n: NC[m]) {
			double sumR = R[m][n][0] + R[m][n][1];
			if(sumR != 0) {
				R[m][n][0] /= sumR;
				R[m][n][1] /= sumR;
            }
//            printf("%f %f\n", R[m][n][0], R[m][n][1]);
		}
	}
	
	// Q update
	for(int n = 0; n<N*M; n++) {
		for(int m: NS[n]) {
			double sumQ = 0;
			for(int k = 0; k<2; k++) {
				double res = 1;
				if(m==NS[n][0]) {
					res = R[NS[n][1]][n][k];
				}
				else {
					res = R[NS[n][0]][n][k];
				}
				res *= P[n][k];
				Q[m][n][k] = res;
				sumQ += res;
			}
			
			if(sumQ!=0) {
				Q[m][n][0] /= sumQ;
				Q[m][n][1] /= sumQ;
			}
//	       	printf("Q: %f %f\n", Q[m][n][0], Q[m][n][1]);
		}
	}
	
	bool fl = false;
	
	for(int n = 0; n<N*M; n++) {
		QQ[n][0] = R[NS[n][0]][n][0] * R[NS[n][1]][n][0] * P[n][0];
		QQ[n][1] = R[NS[n][0]][n][1] * R[NS[n][1]][n][1] * P[n][1];
		double sumQQ = QQ[n][0] + QQ[n][1];
		if(sumQQ!=0) {
			QQ[n][0] /= sumQQ;
			QQ[n][1] /= sumQQ;
		}
	}
	
	int left = 0;
	for(int n = 0; n<N*M; n++) {
		if((0.999<QQ[n][0] && QQ[n][0]<=1) || (0.999<QQ[n][1] && QQ[n][1]<=1)) {
			E[n] = 1;
		}
		else {
			E[n] = 0;
			left++;
		}
	}
//	if(willPrint)	printf("%d\n", left);
	
	for(int i = 0; i<N; i++) {
		for(int j = 0; j<M; j++) {
			Board[i*M+j] = 0;
			if(QQ[i*M+j][0]<QQ[i*M+j][1]) Board[i*M+j] = 1;
			 cout << QQ[i*M+j][1] << " ";
		}
		cout << '\n'; 
	}
	cout << '\n';
	
	lefts[iternum] = left;
	
	for(int i = 0; i<N; i++) {
		for(int j = 0; j<M; j++) {
			BoardHistory[iternum][i*M+j] = Board[i*M+j];
		}
	}
	
	if(checkConverge()) {
		for(int n = 0; n<N*M; n++) {
			if(E[n]==1) continue;
			if(E[n]==0) {
				if(QQ[n][0]>QQ[n][1]) P[n][1] = 0;
				else P[n][0] = 0;
//				if(willPrint) cout << "!!\n";
				lastSelect = iternum;
				break;
			}
		}
	}
	
	iternum++;	
}

double GetReward() {
	double res = 0;
	for(int i = 0; i<2*N; i++) {
		vector<int> temp;
		int cnt = 0;
		for(int j = 0; j<N; j++) {
			if(Board[NC[i][j]]==0) {
				if(cnt!=0) temp.push_back(cnt);
				cnt = 0;
			}
			else {
				cnt++;
			}
		}
		if(cnt!=0) temp.push_back(cnt);
		if(temp.empty()) temp.push_back(0);
		if(temp==X[i]) res+=1;
	}
	return res / (2*N);
}

void NonogramSolve(bool willPrint) {
    
	initN();
	initP();
	
	iternum = 0;
	while(true) {
		IterSolve(willPrint);
      	if(iternum>20 || lefts[iternum-1]==0 || (iternum>=100 && lefts[iternum-1]==N*M)) break;
	}
	
	for(int i = 0; i<N*M; i++) {
		Board[i] = BoardHistory[iternum-1][i];
	}
	
	return;
}

void LearnQ(bool willPrint) {
    
	initN();
	initP();
	
	for(int i = 0; i<2*N; i++) {
		for(int j = 0; j<N; j++) {
			P[NC[i][j]][0] = 1;
			P[NC[i][j]][1] = 0;
		}
		while(1) {
			bool isDone = false;
			vector<int> temp;
			int tempcnt = 0;
			for(int k = 0; k<N; k++) {
				if(P[NC[i][k]][0]==1) {
					if(tempcnt!=0) temp.push_back(tempcnt);
					tempcnt = 0;
				}
				else {
					tempcnt++;
				}
			}
			if(tempcnt!=0) temp.push_back(tempcnt);
			if(temp.empty()) temp.push_back(0);
			double meanQs = 1;
			int nr = 0;
			if(temp!=X[i]) {
				initQ();
				iternum = 0;
				
				while(true) {
					IterSolve(willPrint);
			      	if(iternum>10 || lefts[iternum-1]==0 || (iternum>=20 && lefts[iternum-1]==N*M)) break;
				}
				
				for(int j = 0; j<N*M; j++) {
					Board[j] = BoardHistory[iternum-1][j];
				}
				
				
				
				
				for(int j = 0; j<2*N; j++) {
					if(i==j) continue;
					int nowind = to_two_Cons(j);
					int nr = 0, cnt = 1;
					for(int k = 0; k<N; k++) { 
						nr += cnt * Board[NC[j][k]]; 
						cnt *= 2;
					}
//					printf("%d %d - QF: %f\n", nowind, nr, QF[nowind][nr]);
					meanQs *= pow(QF[nowind][nr], 1.0/(2*N-1));
				}
				
				meanQs = pow(meanQs, up_gamma);
				
				int cnt = 1;
				for(int j = 0; j<N; j++) {
					nr += cnt * (1 - P[NC[i][j]][0]);
					cnt *= 2;
				}
				int nowind = to_two_Cons(i);
				if(GetReward()<0.99) {
					QF[nowind][nr] = pow(QF[nowind][nr], 1-up_alpha) * pow(GetReward() * meanQs, up_alpha);
				}
				if(QF[nowind][nr]<0.01) QF[nowind][nr] = 0.01;
//				printf("%f %f - QF: %f\n", GetReward(), meanQs, QF[nowind][nr]);
			}
			int j;
			for(j = 0; j<N; j++) {
				if(P[NC[i][j]][0] >= 0.99) {
					for(int k = 0; k<j; k++) {
						P[NC[i][k]][0] = 1;
						P[NC[i][k]][1] = 0;
					}
					P[NC[i][j]][0] = 0;
					P[NC[i][j]][1] = 1;
					break;
				}
			}
//			if(i==1) {
//				printf("%d\n", nr);
//				for(int i = 0; i<N; i++) {
//					for(int j = 0; j<M; j++) {
//						string ma = "бр";
//						if(Board[i*M+j]==1) ma = "бс";
//						else if(Board[i*M+j]==2) ma = "бу";
//						cout << ma;
//					}
//					cout << '\n';
//				}
//				printf("R: %f, meanQ: %f\n", GetReward(), meanQs);
//			}
//			printf("\n");
			if(j==N) break;
		}
		
		for(int j = 0; j<N; j++) {
			P[NC[i][j]][0] = 1;
			P[NC[i][j]][1] = 1;
		}
//		printf("%d\n", i);
	}
	
	return;
}

void readQF() {
	FILE* fdat = fopen("QData.dat", "rb");
    if(fdat==NULL) initQF();
    else {
    	for(int i = 0; i<pow(2,N); i++) {
    		fread(QF[i], sizeof(double), pow(2,N), fdat);
		}
		fclose(fdat);
	}
	
}

void readQF2(int p) {
	char dest[100] = "QData";
	strcat(dest, const_cast<char*>(to_string(p).c_str()));
	strcat(dest, ".dat");
	FILE* fdat = fopen(dest, "rb");
    if(fdat==NULL) initQF();
    else {
    	for(int i = 0; i<pow(2,N); i++) {
    		fread(QF[i], sizeof(double), pow(2,N), fdat);
		}
		fclose(fdat);
	}
	
}

void writeQF() {
	FILE* fdat = fopen("QData.dat", "wb");
	for(int i = 0; i<pow(2,N); i++) {
		fwrite(QF[i], sizeof(double), pow(2,N), fdat);
	}
	fclose(fdat);
}

void writeQF2(int p) {
	char dest[100] = "QData";
	strcat(dest, const_cast<char*>(to_string(p).c_str()));
	strcat(dest, ".dat");
	FILE* fdat = fopen(dest, "wb");
	for(int i = 0; i<pow(2,N); i++) {
		fwrite(QF[i], sizeof(double), pow(2,N), fdat);
	}
	fclose(fdat);
}

