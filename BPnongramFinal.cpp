#include "NonogramSolverBP.hpp"

int main() {
	initAll();
	N = M = 6;
	readQF();
	for(int per = 25; per<=100; per+=5) {
		for(int tt = 0; tt<100; tt++) {
			initAll();
			ifstream readFile;
			readFile.open("Testcases/Test_6_"+ to_string(per) + "/Test_" + to_string(tt) + ".txt");
			
			string s;
			getline(readFile, s);
		    vector<string> MN = split(s, ' ');
		    
		    M = stoi(MN[0]); N = stoi(MN[1]);
		    
			printf("%d %d\n", M, N);
			
		    for(int i = 0; i < N+M; i++) {
		        getline(readFile, s);
		        vector<string> VS = split(s, ' ');
		        for(int j=0;j<VS.size();j++) {
		            X[i].push_back(stoi(VS[j]));
		        }
		    }
		    readFile.close();
		
			if(!checkCons()) {
		    	cout << ConsSum1() << '\n' << ConsSum2() << '\n';
		        cout << "Wrong Input\n";
		        return 0;
		    }
			cout << fixed;
			cout.precision(6);
			
//			clock_t st = clock();
			LearnQ(true);
		//	for(int i = 0; i<64; i++) {
		//		printf("%f ", QF[29][i]);
		//	}
//			NonogramSolve(true);
//			cout << '\n';
//			for(int i = 0; i<N; i++) {
//				for(int j = 0; j<M; j++) {
//					string ma = "бр";
//					if(Board[i*M+j]==1) ma = "бс";
//					else if(Board[i*M+j]==2) ma = "бу";
//					cout << ma;
//				}
//				cout << '\n';
//			}
//			cout << clock() - st << "ms" << "\n";
			writeQF();
			printf("Done: %d %d\n", per, tt);
		}
		writeQF2(per);
	}
}

