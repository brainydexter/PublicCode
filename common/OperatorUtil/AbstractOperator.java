package main.java.util;

public abstract class AbstractOperator {
	private char operator;
	private int priority;

	public AbstractOperator(char operator, int priority) {
		this.operator = operator;
		this.priority = priority;
	}

	public int GetPriority() {
		return this.priority;
	}

	public abstract int Execute(int... varArgs);

	public Character toCharacter() {
		return this.operator;
	}
}