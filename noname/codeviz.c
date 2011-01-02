void b();
void d();
void f();
int main()
{
    b();
    return 0;
}

void b()
{
    d();
    f();
}

void d()
{

}

void f()
{
    d();
}
