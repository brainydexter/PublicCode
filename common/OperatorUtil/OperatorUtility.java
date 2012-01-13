package main.java.util;

import java.util.HashMap;

public class OperatorUtility {
	HashMap<Character, AbstractOperator> operatorDictionary;

	private static OperatorUtility singletonInstance;

	public boolean isOperator(char c) {
		return operatorDictionary.containsKey(c);
	}

	public AbstractOperator GetOperator(char ch) {
		AbstractOperator op = operatorDictionary.get(ch);

		if (op == null)
			throw new NullPointerException("Opeartor not found: " + ch);
		return op;
	}

	private OperatorUtility() {
		operatorDictionary = new HashMap<Character, AbstractOperator>();

		operatorDictionary.put('\\', new DivisionOperator('\\', 3));
		operatorDictionary.put('*', new MultiplicationOperator('*', 3));
		operatorDictionary.put('+', new SumOperator('+', 2));
		operatorDictionary.put('-', new DifferenceOperator('-', 2));
	}

	public static synchronized OperatorUtility GetInstance() {

		if (singletonInstance == null)
			singletonInstance = new OperatorUtility();

		return singletonInstance;
	}

	@Override
	protected Object clone() throws CloneNotSupportedException {
		throw new CloneNotSupportedException();
	}

}
