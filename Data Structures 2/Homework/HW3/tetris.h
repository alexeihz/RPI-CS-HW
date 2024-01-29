class Tetris{
	public:
		Tetris();
		Tetris(int num);
		
		int get_width() const;
		int get_max_height() const;
		
		int count_squares();
		void add_piece(char type, int rotate, int horizontal);
		int remove_full_rows();
		void print() const;
		void destroy();
		
		void remove_left_column();
		void add_left_column();
		void remove_right_column();
		void add_right_column();
		
	private:
		int width;
		char **data;
		int *heights;
		
		void add_shape(int width, int height, char c, int horizontal);
};