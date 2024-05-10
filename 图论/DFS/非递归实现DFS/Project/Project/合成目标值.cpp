#include<iostream>
#include<stack>
#include<vector>
using namespace std;

void dfs() {
	vector<int> nums = { 1,2,3,10,11,12 };
	int target = 13;
	stack<vector<int>> st; // 第一个值索引, 第二个值为和 后续为选择组合
	st.push({ -1,0 }); // 对应方式一
	//st.push({ 0,0 }); // 对应方式二
	while (!st.empty()) {
		vector<int> v = st.top();
		st.pop();
		if (v[1] == target) {  // 如果达到目标值就输出它
			for (int i = 2; i < v.size(); i++) {
				cout << v[i] << " ";
			}
			cout << endl;
			continue;
		}
		// 方式一
		// 依次选择后续值, 这里不用再考虑选与不选了,  因为做循环就是在考虑选与不选了
		for (int i = v[0] + 1; i < nums.size(); i++) {
			vector<int> t = v;
			t[0] = i;
			t[1] += nums[i];
			t.push_back(nums[i]);
			if (t[1] > target)continue;  // dfs剪枝很重要
			st.push(t);
		}

		// 方式二
		// 使用选与不选
		//if (v[0] >= nums.size())continue;
		//vector<int> t = v;
		//t[0] += 1;
		//st.push(t); // 不选
		//t[1] += nums[v[0]];  
		//t.push_back(nums[v[0]]);
		//st.push(t);  // 选
	}
}