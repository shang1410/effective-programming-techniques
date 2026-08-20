#pragma once
class RefCounter{
	public:
		RefCounter();
		void add();
		void dec();
		int get();

	private:
		int count;
};

