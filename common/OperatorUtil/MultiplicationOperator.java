package main.java.util;

public class MultiplicationOperator extends AbstractOperator {

	public MultiplicationOperator(char operator, int priority) {
		super(operator, priority);
	}

	@Override
	public int Execute(int... varArgs) {
		int result = 1;

		for (int i : varArgs) {
			result *= i;
		}
		return result;
	}

}
