//stiva implementata ca lista de liste

template <typename T>
class Stack
{
	public:
		void push (T x)
		{
			stackList.addLast(x);
		}
		T pop()
		{
			return stackList.removeLast();
		}
		T peek ()
		{
			T aux = stackList.removeLast();
			stackList.addLast(aux);
			return aux;
		}
		int isEmpty()
		{
			if (stackList.isEmpty() == true) return 1;
			else return 0;
		}
	private:
		LinkedList<T> stackList;
};
