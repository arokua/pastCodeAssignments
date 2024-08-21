int gcd(int a, int b){
    if ( a > b){
        return gcd(b, a);
    }
    if (a == 0){
        return b;
    }
    if ( b % a == 0){
        return a;
    }
    return gcd(a, b % a);
}