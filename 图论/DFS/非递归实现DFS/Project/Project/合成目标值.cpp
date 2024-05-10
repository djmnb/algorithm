#include<iostream>
#include<stack>
#include<vector>
using namespace std;

void dfs() {
	vector<int> nums = { 1,2,3,10,11,12 };
	int target = 13;
	stack<vector<int>> st; // ��һ��ֵ����, �ڶ���ֵΪ�� ����Ϊѡ�����
	st.push({ -1,0 }); // ��Ӧ��ʽһ
	//st.push({ 0,0 }); // ��Ӧ��ʽ��
	while (!st.empty()) {
		vector<int> v = st.top();
		st.pop();
		if (v[1] == target) {  // ����ﵽĿ��ֵ�������
			for (int i = 2; i < v.size(); i++) {
				cout << v[i] << " ";
			}
			cout << endl;
			continue;
		}
		// ��ʽһ
		// ����ѡ�����ֵ, ���ﲻ���ٿ���ѡ�벻ѡ��,  ��Ϊ��ѭ�������ڿ���ѡ�벻ѡ��
		for (int i = v[0] + 1; i < nums.size(); i++) {
			vector<int> t = v;
			t[0] = i;
			t[1] += nums[i];
			t.push_back(nums[i]);
			if (t[1] > target)continue;  // dfs��֦����Ҫ
			st.push(t);
		}

		// ��ʽ��
		// ʹ��ѡ�벻ѡ
		//if (v[0] >= nums.size())continue;
		//vector<int> t = v;
		//t[0] += 1;
		//st.push(t); // ��ѡ
		//t[1] += nums[v[0]];  
		//t.push_back(nums[v[0]]);
		//st.push(t);  // ѡ
	}
}