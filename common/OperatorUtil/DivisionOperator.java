package main.java.util;

public class DivisionOperator extends AbstractOperator {

	public DivisionOperator(char operator, int priority) {
		super(operator, priority);
	}

	@Override
	public int Execute(int... varArgs) {

		if (varArgs.length != 2)
			throw new NullPointerException(
					"DivisionOperator: Execute():: Division only defined for 2 operands");

		return varArgs[0] / varArgs[1];
	}

}
