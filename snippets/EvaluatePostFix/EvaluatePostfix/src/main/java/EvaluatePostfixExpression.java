package main.java;

import java.util.Stack;

import main.java.util.AbstractOperator;
import main.java.util.OperatorUtility;

public class EvaluatePostfixExpression {
	
	public int EvaluateExpression(Character[] expression)
	{
		Stack<Integer>	stack = new Stack<Integer>();
		
		for (Character ch : expression) {
			if(!OperatorUtility.GetInstance().isOperator(ch)){
				stack.push(Character.getNumericValue(ch));
			}
			else	// ch is an operator
			{
				if(stack.size() < 2)
				{
					throw new NullPointerException("Invalid Postfix expression");
				}
				
				int a = stack.pop();
				int b = stack.pop();
				
				AbstractOperator op = OperatorUtility.GetInstance().GetOperator(ch);
				int result = op.Execute(a,b);
				
				stack.push(result);
			}
		}
		
		if(stack.size() != 1)
			throw new NullPointerException("Invalid Postfix expression");
		
		return stack.pop();
	}

}
