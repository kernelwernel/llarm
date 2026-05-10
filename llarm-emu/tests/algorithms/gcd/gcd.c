int main() {
    int a = 30;
    int b = 20;
    
    while (a != b) {
        if (a > b)
            a -= b;
        else
            b -= a;
    }
    return a;
}