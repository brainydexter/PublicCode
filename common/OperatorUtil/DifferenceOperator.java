package main.java.util;

public class DifferenceOperator extends AbstractOperator {

	public DifferenceOperator(char operator, int priority) {
		super(operator, priority);
	}

	@Override
	public int Execute(int... varArgs) {

		if (varArgs.length != 2)
			throw new NullPointerException(
					"DifferenceOperator: Execute():: Difference defined only for two operands");

		return varArgs[0] - varArgs[1];
	}

}
