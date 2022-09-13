class MinStack {
    
    private Stack<Integer> data;
    private Stack<Integer> mins;
    /** initialize your data structure here. */


  public void push(int x) {
    if (stack.isEmpty())
      stack.push(new int[] {x, x});
    else
      stack.push(new int[] {x, Math.min(x, stack.peek()[1])});
  }

  public void pop() {
    stack.pop();
  }

  public int top() {
    return stack.peek()[0];
  }

  public int getMin() {
    return stack.peek()[1];
  }

  private Stack<int[]> stack = new Stack<>(); // {x, min}
 }

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(val);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
