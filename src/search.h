int sequentialsearch(int vet[], int n, int search){
	for(int i = 0; i < n; i++) {
		if(vet[i] == search)
		return i + 1;
	} 
	return 0;
}

int binarysearch(int vet[], int n, int search){
	
	int first = 0;
	int last = n - 1;
	int middle = (first+last)/2;
 
	while (first <= last) {
		if (vet[middle] < search)
			first = middle + 1;    
		else if (vet[middle] == search) {
			return middle + 1;
		}
		else
			last = middle - 1;
 
		middle = (first + last)/2;
	}
	if (first > last)
		return 0;
}
