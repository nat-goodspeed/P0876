int a;
ctx::fiber g{[&a](ctx::fiber&& m){
    a=0;
    int b=1;
    for(;;){
        m.resume();
        int next=a+b;
        a=b;
        b=next;
    }
    return std::move(m);
}};
std::vector<int> v(10);
std::generate(v.begin(), v.end(), [&a,&g]() mutable {
    g.resume();
    return a;
});
std::cout << "v: ";
for (auto i: v) {
    std::cout << i << " ";
}
std::cout << "\n";

output: v: 0 1 1 2 3 5 8 13 21 34