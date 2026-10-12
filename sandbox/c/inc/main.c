int main() {
  int a = 5;
  int b = a++ + ++a;
  __builtin_printf("%d\n", b);
  return 0;
}
