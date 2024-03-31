

class IntegerSet {
    private:
        int max_cardinal_;
	int cardinal_;
        int *members_;
    
    public:
	IntegerSet();                                      
	IntegerSet(int amount);
	IntegerSet(int amount, int *neophytes, int lenth);
	IntegerSet(const IntegerSet &Original);
        ~IntegerSet();

	void SetMaxCardinal(int amount);
	void SetCardinal(int amount);
	void SetMembers(int * &neophytes, int lenth);
	void SetMembers(const IntegerSet &Set);
	void PrintCardinal();
	void PrintMembers();

	int GetCardinal();
	int *GetMembers();

	void operator=(const IntegerSet &Set1);
	void operator+(int num);

	friend IntegerSet operator+(const IntegerSet &Set1, const IntegerSet &Set2);

};
