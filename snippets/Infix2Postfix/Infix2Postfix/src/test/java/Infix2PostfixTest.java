package test.java;

import static org.junit.Assert.assertEquals;
import main.java.Infix2Postfix;

import org.junit.Test;

public class Infix2PostfixTest {

	@Test
	public void testConvertInfixToPostfix() {
		Infix2Postfix obj = new Infix2Postfix();
		String str = obj.ConvertInfixToPostfix(" 3 +  2 * 4");
		System.out.println(str);

		assertEquals("[3,2,4,*,+]", str);
	}

}
