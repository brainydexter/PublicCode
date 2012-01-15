Language: JAVA 
Compiler/Platform: JDK 1.6
IDE: Eclipse Indigo

Objective:
- Evaluate given postfix notation

Dependency:
- Operator files are common and are found in /common/OperatorUtil/
- for this to work, files need to be downloaded as well

Algorithm:

int EvaluatePostfix(string str)
{
	Stack<int> S;
	foreach(ch in str)
	{
		if(ch is operand)
		{
			S.push( intValue(ch) );	// intValue : integer value of this char
		}
		else	// ch is operator
		{
			// pop the top two elements
			// evaluate with the operator
			// push the result back on stack
			
			int a = S.pop();
			int b = S.pop();	// not checking for errors for simplicity and assuming it's a valid postfix string
			
			Operator o = OperatorFactory.CreateOperator(ch);	// this would yield an object of type Sum or Product, etc
			int val = o.Execute(a,b);
			
			S.push(val);
		}
	}

	// at this point stack will contain one element with the result
	return S.pop();
}