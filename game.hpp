class fruct{
	public:
		int x, y;
		
		
		
		
		
		void gen() {
			x = rand() % VM_N;
			y = rand() % VM_M;
			
			for(int i = 0; i < sh; i++)
				if(s[i].x == x && s[i].y == y)
					gen();
		}
		
		
		
		void draw() {
			glColor3f(1, 0, 0);
			glRecti(x * VM_Scale - 1, y * VM_Scale, (x + 1) * VM_Scale, (y + 1) * VM_Scale + 1);
		}
};



fruct fru;







class game {
	public:
		void over() {
			std::ofstream RO("save.snk");
			
			RO << myMX;
			
			RO.close();
			
			
			exit(0);
		}
		
		
		
		void drawField() {
			glColor3f(1, 1, 1);
			
			glBegin(GL_LINES);
				for(int i = 0; i < VM_N; i++) {
					glVertex2i(i * VM_Scale, 0);	glVertex2i(i * VM_Scale, VD_H);
				}
				for(int i = 0; i < VM_M; i++) {
					glVertex2i(0, i * VM_Scale);	glVertex2i(VD_W, i * VM_Scale);
				}
			glEnd();
				
		}



		void drawSnake() {
			glColor3f(1, 1, 0);
			glRecti(s[0].x * VM_Scale - 1, s[0].y * VM_Scale, (s[0].x + 1) * VM_Scale, (s[0].y + 1) * VM_Scale + 1);
			
			glColor3f(1, 0, 1);
			for(int i = 1; i < sh; i++)
				glRecti(s[i].x * VM_Scale - 1, s[i].y * VM_Scale, (s[i].x + 1) * VM_Scale, (s[i].y + 1) * VM_Scale + 1);
		}
		
		
		
		void stroke() {
			for(int i = sh; i > 0; i--) {
				s[i].x = s[i-1].x;
				s[i].y = s[i-1].y;
			}
			
			if(dir == 1)
				s[0].y += 1;
			if(dir == 2)
				s[0].x += 1;
			if(dir == 3)
				s[0].y -= 1;
			if(dir == 4)
				s[0].x -= 1;
			
			
			if(fru.x == s[0].x && fru.y == s[0].y) {
				sh++;
				fru.gen();
				
				if(sh > MX)
					myMX = sh;
				
				if(step > 1)
					step -= step / 20;
			}
			
			
			if(s[0].x < 0 || s[0].x >= VM_N || s[0].y < 0 || s[0].y >= VM_M)
				over();
			
			
			for(int i = 1; i < sh; i++)
				if(s[0].x == s[i].x && s[0].y == s[i].y)
					sh = i+1;
		}



		static void keyboard(int key, int a, int b) {
			switch(key) {
				case 101:
					if(dir != 3)
						dir = 1;
				break;
				
				case 102:
					if(dir != 4)
						dir = 2;
				break;
				
				case 103:
					if(dir != 1)
						dir = 3;
				break;
				
				case 100:
					if(dir != 2)
						dir = 4;
				break;
			}
		}
};
