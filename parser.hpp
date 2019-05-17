struct Parser {
    using State = string::const_iterator;
    using Result = int;
    class ParseError {};

    string s;

    Parser() {}
    Parser(string& s) : s(s) {}

    // beginがexpectedを指していたらbeginを一つ進める。
    void consume(State &begin, char expected) {
        if (*begin == expected) {
            begin++;
        } else {
            cerr << "Expected '" << expected << "' but got '" << *begin << "'"
                << endl;
            cerr << "Rest string is '";
            while (*begin) {
                cerr << *begin++;
            }
            cerr << "'" << endl;
            throw ParseError();
        }
    }

    Result run() {
        State begin = s.begin();
        return expr(begin);
    }

    Result expr(State& begin) {

    }
};
