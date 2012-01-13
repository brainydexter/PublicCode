Language: JAVA 
Compiler/Platform: JDK 1.6
IDE: Eclipse Indigo

Objective:
- Convert infix notation to postfix notation

Dependency:
- Operator files are common and are found in /common/OperatorUtil/
- for this to work, files need to be downloaded as well

Algorithm:

	Queue Q;	// Q which contains the postfix notation so far
	Stack S;	// operator stack

	foreach(char ch in str)
	{
		if( ch is not operator )	// ch is not a part of the operator dictionary
		{
			Q.EnQue(ch);
		}
		else		// ch is an operator
		{
			Operator o(ch);		//use some factory here to manufacture the correct Operator
			
			if( S.empty() )
			{
				S.push(o);
			}
			else	// operator stack is not empty
			{
				Operator top = S.top();
				// IF priority of operator at the top is greater than the new operator,
				// => top operator needs to be evaluated first
				// => pop and enqueue
				if( o.priority() < top.priority() )
				{
					Operator popO = S.pop();
					Q.EnQ(popO.toCh());
				}
				S.push(o);
			}
		}
	}

	// Whatever is left in Stack, flush it to enQueue
	while(!S.empty())
	{
		Q.EnQ(S.pop().toString());
	}
	
	return Q.toString();
}