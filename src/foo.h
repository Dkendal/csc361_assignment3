#ifndef FOO
#define FOO
class Foo
{
public:
  Foo() {};
  virtual ~Foo() {};
  virtual int Bar() = 0;

private:
  /* data */
};
#endif
