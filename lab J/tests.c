void run_tests(void) {
    char buf[64];

    init_table();
    assert(!findEntry("foo"));                      // 1

    addEntry("foo");
    assert(findEntry("foo"));                      // 2

    addEntry("foo");
    assert(findEntry("foo"));                      // 3

    deleteEntry("foo");
    assert(!findEntry("foo"));                     // 4

    addEntry("foo");
    assert(findEntry("foo"));                      // 5

    addEntry("bar");
    assert(findEntry("bar"));                      // 6

    assert(!findEntry("baz"));                     // 7

    addEntry("baz");
    assert(findEntry("baz"));                      // 8

    deleteEntry("bar");
    assert(!findEntry("bar"));                     // 9

    addEntry("alpha");
    addEntry("beta");
    assert(findEntry("alpha"));                    // 10
    assert(findEntry("beta"));                     // 11

    deleteEntry("alpha");
    assert(!findEntry("alpha"));                   // 12

    for (int i = 0; i < 500; ++i) {
        snprintf(buf, sizeof(buf), "k%d", i);
        addEntry(buf);
    }
    for (int i = 0; i < 500; ++i) {
        snprintf(buf, sizeof(buf), "k%d", i);
        assert(findEntry(buf));                      // 13
    }

    for (int i = 0; i < 250; i += 1) {
        snprintf(buf, sizeof(buf), "k%d", i);
        deleteEntry(buf);
    }
    for (int i = 0; i < 500; ++i) {
        snprintf(buf, sizeof(buf), "k%d", i);
        if (i < 250) assert(!findEntry(buf));
        else         assert(findEntry(buf));          // 14
    }

    for (int i = 0; i < 250; ++i) {
        snprintf(buf, sizeof(buf), "k%d", i);
        addEntry(buf);
    }
    for (int i = 0; i < 500; ++i) {
        snprintf(buf, sizeof(buf), "k%d", i);
        assert(findEntry(buf));                       // 15
    }

    puts("All tests passed.");
}
