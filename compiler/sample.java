public class sample {


static class A {
  int x;
  void set(int y) { x = y; }
  int get() { return x; }
  void add(A other) { x = x + other.x; }
}

interface Setter {
  void set(int x);
}

static void main()
{
  A a;
  A b;
  a = new A();
  b = new A();
  a.set(5);
  b.set(6);

}

	
	
public static void main(String[] args) {
        main();
    }
}
