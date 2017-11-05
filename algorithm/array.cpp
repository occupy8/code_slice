/*
 * 输入两个整数n和m，从数列1，2，3，...n中随意取几个数，使其和等于m，
 * 要求将所有的可能组合列出来
 * 1.首先判断，如果n>m，则大于m的数不可能参与组合，此时置n = m;
 * 2.将最大数n加入且n == m，则满足条件，输出
 * 3.将n分两种情况求解，（1）n没有加入，取n=n-1；m=m；递归下去；
 *    （2）n加入，取n=n-1，m= m-n递归下去
 */
void findSum(int sum, int n){
    if(n < 1 || sum < 1)
        return;
    if(sum > n){
        list.add(n);
        findSum(sum-n, n-1); //n add
        list.pop();
        findSum(sum, n-1); //n not add
    }else{
        for(int i = 0; i < list.size(); i++){
            print(" ", list.get(i))
        }
    }
}
