int arr[2048][2048];

int main() {
  int sum = 0;
  for (int i = 0; i < 2048; i++) {
    for (int j = 0; j < 2048; j += 8) {
      int sum1 = arr[i][j];
      int sum2 = arr[i][j + 1];
      int sum3 = arr[i][j + 2];
      int sum4 = arr[i][j + 3];
      int sum5 = arr[i][j + 4];
      int sum6 = arr[i][j + 5];
      int sum7 = arr[i][j + 6];
      int sum8 = arr[i][j + 7];
      sum += (sum1 + sum2 + sum3 + sum4 + sum5 + sum6 + sum7 + sum8);
    }
  }
  return 0;
}
