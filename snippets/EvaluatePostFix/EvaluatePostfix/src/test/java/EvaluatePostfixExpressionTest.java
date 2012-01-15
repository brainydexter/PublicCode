package test.java;

import static org.junit.Assert.*;

import main.java.EvaluatePostfixExpression;
import main.java.Infix2Postfix;

import org.junit.Test;

public class EvaluatePostfixExpressionTest {

	@Test
	public void test() {
		EvaluatePostfixExpression obj = new EvaluatePostfixExpression();
		int val = obj.EvaluateExpression(new Infix2Postfix().ConvertInfixToPostfix("3+2* 4"));
		
		System.out.println(val);
		assertEquals(11, val);
	}

}
