#include"Sudoku.h"
		void Sudoku::giveQuestion(){
			int q[9][9]={
				{8,0,0,0,0,0,0,0,0},
				{0,0,3,6,0,0,0,0,0},
				{0,7,0,0,9,0,2,0,0},
				{0,5,0,0,0,7,0,0,0},
				{0,0,0,0,4,5,7,0,0},
				{0,0,0,1,0,0,0,3,0},
				{0,0,1,0,0,0,0,6,8},
				{0,0,8,5,0,0,0,1,0},
				{0,9,0,0,0,0,4,0,0}};
			for(i=0;i<9;i++){
				for(j=0;j<9;j++){
					cout<<q[i][j]<<" ";
					if(j==8) cout<<endl;
				}
			}
		}
		void Sudoku::readIn(){
			int a,cnt=1;
//			cout<<endl;
			i=0;j=0;
			while(cin>>a){
				map[i][j]=a;
				cnt%9==0?(i=i+1,j=0):j++;
				cnt++;
				if(cnt==82) break;
			}
		
		/*	for(i=0;i<9;i++){
				for(j=0;j<9;j++){
					cout<<map[i][j]<<" ";
					  if(j==8) cout<<endl;
				}
			}*/ 		//test
		}
		void Sudoku::solve(){
			ans=0;
			ck();
			backtrace(0);
			if(ans==1){
				cout<<'1'<<endl;
				for(i=0;i<9;i++){
					for(j=0;j<9;j++){
						cout<<map2[i][j]<<' ';
					}
					cout<<endl;
				}
			}	
			else cout<<'0'<<endl;
		}
		void Sudoku::ck(){
			int tmpp=0,map3[81],rm[81],find=0,imp1[81][9],imp2[81][9],imp3[81][9];
			k=0;
			for(i=0;i<9;i++){
				for(j=0;j<9;j++){
					map3[k]=map[i][j];
					rm[k]=0;
					k++;				
				}
			}
			for(i=0;i<81;i++){
				for(j=0;j<9;j++)
					imp1[i][j]=0;
					imp2[i][j]=0;
					imp3[i][j]=0;
			}
			for(i=0;i<81;i++){
            	if(map3[i]) find++;
            	else{
            	for(j=0;j<9;j++){
          	 	 	if(map3[(i/9)*9+j]/*&&!imp[i][map3[(i/9)*9+j]-1]*/){
            			rm[i]++;
                        imp1[i][map3[(i/9)*9+j]-1]++;
					}
					if(map3[j*9+i%9]/*&&!imp[i][map3[j*9+i%9]-1]*/){
						rm[i]++;
						imp2[i][map3[j*9+i%9]-1]++;
					}
					tmpp=map3[((i/(9*3))*3+j/3)*9 + ((i%9)/3)*3+j%3] ;
					if(tmpp/*&&!imp[i][tmpp-1]*/){
						rm[i]++;
						imp3[i][tmpp-1]++;
					}
				}
				}
			}
			for(i=0;i<81;i++){
				for(j=0;j<9;j++){
					if(imp1[i][j]>1||imp2[i][j]>1||imp3[i][j]>1){
						cout<<'2'<<endl;
						exit(0);
					}
				}
			}
//			for(i=0;i<81;i++)
//				(i+1)%9==0?cout<<map3[i]<<endl:cout<<map3[i]<<' ';	
		}
		bool Sudoku::check(int count){
			int rr = count / 9;
			int cc = count % 9;
			int j;
			for(j = 0; j < 9; ++j){
				if(map[rr][j] == map[rr][cc] && j != cc){
					return false;
				}
			}
			for(j = 0; j < 9; ++j){
				if(map[j][cc] == map[rr][cc] && j != rr){
					return false;
				}
			}
			int tmp1 = rr / 3 * 3;
			int tmp2 = cc / 3 * 3;
			for(j = tmp1; j < tmp1 + 3;++j){
				for(int k = tmp2; k < tmp2 + 3; ++k){
					if(map[j][k] == map[rr][cc] && j != rr && k != cc){
						return false;
					}
				}
			}
			return true;
		}
		void Sudoku::backtrace(int count){
			if(count == 81){
				for(int i = 0; i < 9; ++i){
					for(int j =  0; j < 9; ++j){
						map2[i][j]=map[i][j];		
			//			cout<<map[i][j]<<" ";
					}
			//		cout<<endl;
				}
				ans++;
			//	return;
			}
			if(ans>1){
				cout<<'2'<<endl;
				exit(0);
			}
			int rr = count / 9;
			int cc = count % 9;
			if(map[rr][cc] == 0){
				for(int i = 1; i <= 9; ++i){
					map[rr][cc] = i;
					if(check(count)){
						backtrace(count+1);
					}
				}
				map[rr][cc] = 0;
			}else{
				backtrace(count+1);
			}
		}

		void Sudoku::changeNum(int a, int b){
			for(i=0;i<9;i++){
				for(j=0;j<9;j++){
					if(map[i][j]==a) map[i][j]=10; // 10 is temp
					if(map[i][j]==b) map[i][j]=a;
					if(map[i][j]==10) map[i][j]=b;
				}	
			}
		/*	for(i=0;i<9;i++){
				for(j=0;j<9;j++){
					cout<<map[i][j]<<" ";
					if(j==8) cout<<endl;
				}
			}*/ //test
		}
		void Sudoku::changeRow(int a, int b){
			if((a==0&&b==1)||(a==1&&b==0)){
				for(i=0;i<3;i++){
					for(j=0;j<9;j++){
						tmp[i+3][j]=map[i][j];
						tmp[i][j]=map[i+3][j];
						tmp[i+6][j]=map[i+6][j];
					}
				}
				for(i=0;i<9;i++){
					for(j=0;j<9;j++){
						map[i][j]=tmp[i][j];
					/*	cout<<map[i][j];
						j==8?cout<<endl:cout<<" ";*/ //test
					}
				}
			}
			if((a==1&&b==2)||(a==2&&b==1)){
				for(i=0;i<3;i++){
					for(j=0;j<9;j++){
						tmp[i][j]=map[i][j];
						tmp[i+6][j]=map[i+3][j];
						tmp[i+3][j]=map[i+6][j];
					}
				}
				for(i=0;i<9;i++){
					for(j=0;j<9;j++){
						map[i][j]=tmp[i][j];
					/*	cout<<map[i][j];
						j==8?cout<<endl:cout<<" "; */ //test
					}
				}
			}
			if((a==0&&b==2)||(a==2&&b==0)){
				for(i=0;i<3;i++){
					for(j=0;j<9;j++){
						tmp[i+6][j]=map[i][j];
						tmp[i+3][j]=map[i+3][j];
						tmp[i][j]=map[i+6][j];
					}
				}
				for(i=0;i<9;i++){
					for(j=0;j<9;j++){
						map[i][j]=tmp[i][j];
					/*	cout<<map[i][j];
						j==8?cout<<endl:cout<<" ";*/ //test
					}
				}
			}
		}
		void Sudoku::changeCol(int a, int b){
			if((a==0&&b==1)||(a==1&&b==0)){
				for(i=0;i<9;i++){
					for(j=0;j<3;j++){
						tmp[i][j+3]=map[i][j];
						tmp[i][j]=map[i][j+3];
						tmp[i][j+6]=map[i][j+6];
					}
				}
				for(i=0;i<9;i++){
					for(j=0;j<9;j++){
						map[i][j]=tmp[i][j];
				/*		cout<<map[i][j];
						j==8?cout<<endl:cout<<" ";*/ //test
					}
				}
			}
			if((a==1&&b==2)||(a==2&&b==1)){
				for(i=0;i<9;i++){
					for(j=0;j<3;j++){
						tmp[i][j]=map[i][j];
						tmp[i][j+6]=map[i][j+3];
						tmp[i][j+3]=map[i][j+6];
					}
				}
				for(i=0;i<9;i++){
					for(j=0;j<9;j++){
						map[i][j]=tmp[i][j];
					/*	cout<<map[i][j];
						j==8?cout<<endl:cout<<" ";*/ //test
					}
				}
			}
			if((a==0&&b==2)||(a==2&&b==0)){
				for(i=0;i<9;i++){
					for(j=0;j<3;j++){
						tmp[i][j+3]=map[i][j+3];
						tmp[i][j+6]=map[i][j];
						tmp[i][j]=map[i][j+6];
					}
				}
				for(i=0;i<9;i++){
					for(j=0;j<9;j++){
						map[i][j]=tmp[i][j];
					/*	cout<<map[i][j];
						j==8?cout<<endl:cout<<" ";*/ //test
					}
				}
			}
		}
		void Sudoku::rotate(int n){
			if(n%4==1){
				for(i=0;i<9;i++){
					for(j=0;j<9;j++){
						tmp[j][8-i]=map[i][j];
					}
				}
			}
			else if (n%4==2){
				for(i=0;i<9;i++){
					for(j=0;j<9;j++){
				 		tmp[8-i][8-j]=map[i][j];
				 	}
			 	}
			}
			else if(n%4==3){
				for(i=0;i<9;i++){
					for(j=0;j<9;j++){
						tmp[8-j][i]=map[i][j];
					}
				}
			}
			if(n%4!=0){
				for(i=0;i<9;i++){
					for(j=0;j<9;j++){
						map[i][j]=tmp[i][j];
					//	cout<<map[i][j];
					//	j==8?cout<<endl:cout<<" "; test
					}
				}
			}
		}
		void Sudoku::flip(int n){
			if(n==1){
				for(i=0;i<9;i++){
					for(j=0;j<9;j++)
						tmp[i][8-j]=map[i][j];
				}
			}
			else if(n==0){
				for(i=0;i<9;i++){
					for(j=0;j<9;j++)
						tmp[8-i][j]=map[i][j];
				}
			}
			if(n==1||n==0){
				for(i=0;i<9;i++){
					for(j=0;j<9;j++)
						map[i][j]=tmp[i][j];
				}
			}

		/*	cout<<endl;
			for(i=0;i<9;i++){
				for(j=0;j<9;j++){
					cout<<map[i][j]<<" ";
					if(j==8) cout<<endl;
				}
			}*/ //test
		}
		void Sudoku::transform(){
			srand(time(NULL));
			readIn();
			changeNum(rand()%9+1,rand()%9+1);
			changeRow(rand()%3,rand()%3);
			changeCol(rand()%3,rand()%3);
			rotate(rand()%101);
			flip(rand()%2);
			for(i=0;i<9;i++){
				for(j=0;j<9;j++){
					cout<<map[i][j]<<" ";	
				}
				cout<<endl;
			}
		}
