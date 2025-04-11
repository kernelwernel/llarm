
int main() {
    long long int n = 10;

    long long int t1 = 0, t2 = 1, nextTerm;
    
    for (int i = 2; i <= n; i++) {
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }

    return t2;
}