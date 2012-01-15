package test.java;

import main.java.Infix2Postfix;

import org.junit.Assert;
import org.junit.Test;

public class Infix2PostfixTest {

	@Test
	public void testConvertInfixToPostfix() {
		Infix2Postfix obj = new Infix2Postfix();
		Character[] actual =  obj.ConvertInfixToPostfix(" 3 +  2 * 4");
		
		for (Character character : actual) {
			System.out.println(character);
		}
		
		Character[] expected = {'3','2','4','*','+'};

		Assert.assertArrayEquals(expected, actual);
	}

}
