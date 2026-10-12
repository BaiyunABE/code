struct {
  int i;
  double j;
} x, y;

struct {
  int i;
  double j;
} z;

int main() {
  x = y;
  x = z;
  return 0;
}
