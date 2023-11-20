vi kmppi(const string &p) {
    int m = p.size(), i = 0, j = -1;
    vi b(m + 1, -1);
    while(i < m) {
        while(j >= 0 && p[i] != p[j]) j = b[j];
        b[++i] = ++j; }
    return b; }
vi kmp(const string &s, const string &p) {
    int n = s.size(), m = p.size(), i = 0, j = 0;
    vi b = kmppi(p), a = vi();
    while(i < n) {
        while(j >= 0 && s[i] != p[j]) j = b[j];
        ++i; ++j;
        if(j == m) {
            a.push_back(i - j);
            j = b[j];
        }
    }
    return a; }
// vim: cc=60 ts=2 sts=2 sw=2: