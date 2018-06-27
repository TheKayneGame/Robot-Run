void sortOrder(int XC[sizeOfOrder], int YC[sizeOfOrder]) {
	int check = 0, orderCorrect;
	int sum[sizeOfOrder];

	for (int j = 0; j < sizeOfOrder; j++) {
		sum[j] = XC[j] + YC[j];
	}
	while (check != 1) {
		orderCorrect = 1;
		for (int i = 0; i < sizeOfOrder; i++) {
			if (sum[i] > sum[i + 1]) {
				swapOne(&sum[i], &sum[i + 1]);
				swapTwo(&XC[i], &XC[i + 1], &YC[i], &YC[i + 1]);
				orderCorrect = 0;
			} else if ((sum[i] == sum[i + 1]) && (YC[i] == YC[i + 1])) {
				if (XC[i] < XC[i + 1]) {
					swapOne(&sum[i], &sum[i + 1]);
					swapTwo(&XC[i], &XC[i + 1], &YC[i], &YC[i + 1]);
					orderCorrect = 0;
				} else if (YC[i] > YC[i + 1]) {
					swapOne(&sum[i], &sum[i + 1]);
					swapTwo(&XC[i], &XC[i + 1], &YC[i], &YC[i + 1]);
					orderCorrect = 0;
				}
			}
		}
		if (orderCorrect == 1) {
			check = 1;
		}

	}

}
