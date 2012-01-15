package main.java.util;

public class SumOperator extends AbstractOperator {

	public SumOperator(char operator, int priority) {
		super(operator, priority);
	}

	@Override
	public int Execute(int... varArgs) {
		int result = 0;

		for (int i : varArgs) {
			result += i;
		}
		return result;
	}

}
