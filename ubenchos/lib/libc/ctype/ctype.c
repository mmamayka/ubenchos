#define IN_RANGE(x, low, up) \
    (x >= low && x <= up)

int iscntrl(int c) {
    return IN_RANGE(c, 0x00, 0x1F) || c == 0x7F;
}

int isblank(int c) {
    return c == 0x09 || c == 0x20;
}

int isspace(int c) {
    return IN_RANGE(c, 0x09, 0x0D) || c == 0x20;
}

int isupper(int c) {
    return IN_RANGE(c, 0x41, 0x5A);
}

int islower(int c) {
    return IN_RANGE(c, 0x61, 0x7A);
}

int isalpha(int c) {
    return islower(c) || isupper(c);
}

int isdigit(int c) {
    return IN_RANGE(c, 0x30, 0x39);
}

int isxdigit(int c) {
    return isdigit(c) || IN_RANGE(c, 0x41, 0x46) || IN_RANGE(c, 0x61, 0x66);
}

int isalnum(int c) {
    return isalpha(c) || isdigit(c);
}

int ispunct(int c) {
    return IN_RANGE(c, 0x21, 0x2F) || IN_RANGE(c, 0x3a, 0x40) ||
        IN_RANGE(c, 0x5b, 0x60) || IN_RANGE(c, 0x7b, 0x7e);
}

int isgraph(int c) {
    return IN_RANGE(c, 0x21, 0x7e);
}

int isprint(int c) {
    return IN_RANGE(c, 0x20, 0x7e);
}

int toupper(int c) {
    if(islower(c)) {
        return c - 'a' + 'A';
    } else {
        return c;
    }
}

int tolower(int c) {
    if(isupper(c)) {
        return c - 'A' + 'a';
    } else {
        return c;
    }
}
