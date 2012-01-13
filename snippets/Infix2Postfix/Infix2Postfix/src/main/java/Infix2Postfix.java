package main.java;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

import main.java.util.AbstractOperator;
import main.java.util.OperatorUtility;

/*
 * Convert Infix expression to Postfix expression
 * 2 + 3 * 4 => 2, 3, 4, *, +
 * 
 * Does NOT support paranthesis
 * Assumes valid infix expression as input
 * Assumes operands are int type
 * 
 * Supported operators:	Precedence
 * 		*	->	3
 * 		/	->	3
 * 		+	->	2
 * 		-	->	2
 */
public class Infix2Postfix {

	@org.junit.Test
	public String ConvertInfixToPostfix(String infixString) {
		// http://stackoverflow.com/questions/3958955/how-to-remove-duplicate-white-spaces-in-string-using-java
		infixString = infixString.replaceAll("\\s+", "");	

		Queue<Character> que = new LinkedList<Character>();
		Stack<AbstractOperator> stack = new Stack<AbstractOperator>();

		for (int i = 0; i < infixString.length(); ++i) {
			char ch = infixString.charAt(i);

			if (!OperatorUtility.GetInstance().isOperator(ch)) {
				que.add(ch);
			} else // ch is an operator
			{
				AbstractOperator operator = OperatorUtility.GetInstance()
						.GetOperator(ch);

				if (stack.isEmpty())
					stack.push(operator);
				else // stack is not empty
				{
					AbstractOperator topOperator = stack.peek();

					if (topOperator.GetPriority() > operator.GetPriority()) {
						AbstractOperator op = stack.pop();
						que.add(op.toCharacter());
					}
					stack.push(operator);
				}
			}
		}
		
		while(!stack.empty())
		{
			que.add(stack.pop().toCharacter());
		}

		return que.toString().replaceAll("\\s+", "");
	}
}
