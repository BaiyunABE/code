int main() {
  void (*(*f[1])())();
  typedef void (*NonPramProc)();
  typedef NonPramProc (*Fn)();
  Fn a;
  f[0] = a;
  return 0;
}
