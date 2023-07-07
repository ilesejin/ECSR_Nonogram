#include "NonogramSolverBP.hpp"

int main() {
	initAll();
	N = M = 6;
	readQF2(20);
	for(int per = 25; per<=25; per+=5) {
		
		for(int tt = 12; tt<13; tt++) {
			initAll();
			ifstream readFile;
			readFile.open("Testcases/Test_6_"+ to_string(per) + "/Test_" + to_string(tt) + ".txt");
			
			string s;
			getline(readFile, s);
		    vector<string> MN = split(s, ' ');
		    
		    M = stoi(MN[0]); N = stoi(MN[1]);
//			printf("%d %d\n", M, N);
			
		    for(int i = 0; i < N+M; i++) {
		        getline(readFile, s);
//		        cout << s << '\n';
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
//			LearnQ(true);
//			for(int k = 0; k<10; k++) {
//				for(int i = 0; i<32; i++) {
//					printf("%f ", QF[k][64]);
//				}
//				printf("\n");
//			}
			
			NonogramSolve(true);
			
			ofstream writeFile;
			
			writeFile.open("Results/Result_6_"+ to_string(per) + "/Result_" + to_string(tt) + ".txt");
			writeFile<<M<<" "<<N<<"\n";
//			cout << "\n\n"; 
			for(int i = 0; i<N+M; i++) {
				for(int x: X[i]) {
					writeFile<<x<<" ";
//					cout << x << " ";
				}
//				cout << "\n";
				writeFile<<"\n";
			}
			
			for(int i = 0; i<N; i++) {
				for(int j = 0; j<M; j++) {
					// string ma= "бр";
					writeFile << Board[i*M+j] << ' ';
				}
				writeFile << '\n';
			}
//			writeFile << iternum;
			writeFile.close();
			
//			cout << iternum << '\n';
			cout << '\n';
			for(int i = 0; i<N; i++) {
				for(int j = 0; j<M; j++) {
					string ma = "бр";
					if(Board[i*M+j]==1) ma = "бс";
					else if(Board[i*M+j]==2) ma = "бу";
					cout << ma;
				}
				cout << '\n';
			}
//			cout << clock() - st << "ms" << "\n";
//			printf("Done: %d %d\n", per, tt);
		}
		printf("Done: %d\n", per);
	}
}

