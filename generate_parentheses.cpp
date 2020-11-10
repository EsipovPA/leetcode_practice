#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {
private:
	vector<string> gen(int n, int opened, string input){
		if(n == 0){
			for(int i = 0; i < opened; i++){
				input += ")";
			}

			return { input };
		}else if(n < 0){
			return {};
		}else if(opened < 0){
			return {};
		}
		
		vector<string> op{ gen(n - 1, opened + 1, input + "(") };
		vector<string> cl{ gen(n, opened - 1, input + ")") };
		vector<string> res{};

		for(string o : op){
			res.push_back(o);
		}

		for(string c : cl){
			res.push_back(c);
		}

		return res;
	}


public:
    vector<string> generateParenthesis(int n) {
    	return gen(n - 1, 1, "(");
    }
};

void RunTests(const vector<int>& in, const vector<vector<string>>& out){
	for(int i = 0; i < in.size(); i++){
		vector<string> res = Solution().generateParenthesis(in[i]);

		if(res.size() != out[i].size()){
			cout << "test " << to_string(i) << " failure\n";
			continue;
		}

		bool failure{ false };
		for(int j = 0; j < res.size(); j++){
			if(res[j] != out[i][j]){
				failure = true;
				break;
			}
		}

		cout << "test " << to_string(i) << (failure ? " failure" : " success") << endl;
	}
}

int main(){
	vector<int> input{
		3,
		1,
		0
	};

	vector<vector<string>> output{
		{
			"((()))", "(()())", "(())()", "()(())", "()()()"
		},
		{
			"()"
		},
		{}
	};

	RunTests(input, output);

	return 0;
}