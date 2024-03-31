class Restaurant {
	private:
		int num_;

		struct seat_ {
			int cellphone_;
			int booking_time_;
		};

		struct seat_array_ {
			int last_time_;
			int num_of_pairs_;
			seat_ *array_;
			int *time_array_;
		};

		seat_array_ *table_;   
	public:
		Restaurant();
		Restaurant(int num);
		Restaurant(const Restaurant &Res);
		~Restaurant();

		int SearchTime(int *free_seat, int time);
		void Add(int time, int cellphone);
		void AllBookingPrint();
		int IsThere(int cellphone);
		void operator=(const Restaurant &Res);
};
