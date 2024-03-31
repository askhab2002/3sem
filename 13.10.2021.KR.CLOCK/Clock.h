#define LEFT 1
#define RIGHT 2
#define EQUAL 3
#define YES 0
#define NOPE -1

class Clocks {
	private:
		int amount_of_processes_;
		int num_of_process_;
		int *vector_;
		Clocks() {
			vector_ = NULL;
			amount_of_processes_ = 0;
			num_of_process_ = 0;
		}	

	public:
		Clocks(int amount_of_processes, int num_of_process);
		Clocks(const Clocks &Clock1);
		~Clocks();

		void ReceiveVector(const  Clocks &Clock1) const;
		void AddOne() const;
		Clocks &Send_vector(); 	
		void PrintVector() const;
		Clocks &operator=(const Clocks &Clock1);

		friend int MeasureVectors(const  Clocks &Clock1, const  Clocks &Clock2);
		friend int OneSideMeasure(const  Clocks &Clock1, const  Clocks &Clock2);
		friend int Measure(const  Clocks &Clock1, const  Clocks &Clock2);
};
