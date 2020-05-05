#include<iostream>
using namespace std;
int main(){
		// 答案就是：autograder只看在所有测试用例上的输出是否正确。
		// 由于本题没有输入，输出也唯一，
		// 所以，如果我们知道了答案（例如人工地一一枚举过来）那我们就可以直接输出啦！结果如下：
		//       cout << "3" << endl << "D" << endl;
		// oj系统的autograder可辨识不了我们的程序使用的算法是否符合要求
		//（事实上，任何关于程序的非平凡性质都是不可判定的！
		//  ????等等，那autograder怎么工作呢？
		//  ????原来，autograder限制了程序运行的时间。其目的当然包括要求我们使用的算法不能太笨拙。
		//            更重要的是，如果我们允许最笨拙的方法并且对时间不作任何限制，
		//            那么autograder就不能正确判定所有的程序啦。）
		// 不过呢，这么输出是对autograder的一种错误使用方式，因为显然这不是本道题的考察内容。
		// 所以，我们还是老老实实地用“程序”来解这个问题的答案。

		// 用best枚举最好的车
		int best;    
	for(best = 1; best <= 4; best++){
		// a b c d记录四位专家的话
		bool a = (best == 2);
		bool b = (best == 4);
		bool c = !(best == 3);
		bool d = !b;                
		if (a + b + c + d != 1)
			continue; // 不符合只有1位专家说对的条件
		// 输出最佳的车
		cout << best << endl;
		// 输出判断正确的专家
		if ( a == 1)
			cout << "A" << endl;
		else if ( b == 1)
			cout << "B" << endl;
		else  if ( c == 1)
			cout << "C" << endl;
		else
			cout << "D" << endl;
	}        
	return 0;
}
