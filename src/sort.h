void bubblesort(int vet[], int n) {
	
	int i;
	int j;
	int temp;
	int cond = 1;
	
	for (i=n-1; (i >= 1) && (cond == 1); i--) {
		
		cond = 0;
		
		for (j=0; j < i ;j++) {
			
			if (vet[j+1] < vet[j]) {
				temp = vet[j];
				vet[j] = vet[j+1];
				vet[j+1] = temp;
				cond = 1;
			}
		}
	}
}

void selectionsort(int vet[], int n) {
	
	int i;
	int j;
	int min;
	
	for (i = 0; i < (n-1); i++) {
		
		min = i;
		
		for (j = (i+1); j < n; j++) {
			
			if(vet[j] < vet[min]) {
				min = j;
			}
		}

		if (i != min) {
			int swap = vet[i];
			vet[i] = vet[min];
			vet[min] = swap;
		}
	}
}

void insertionsort(int vet[], int n){
	
	int j;
	int i;
	int key;
	
	for(j = 1; j < n; j++) {
		
		key = vet[j];
		i = j - 1;
		
		while(i >= 0 && vet[i] > key) {
			vet[i + 1] = vet[i];
			i = i - 1;
		}

		vet[i + 1] = key;
	}
}