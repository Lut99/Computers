#ifndef TEST_COMPILATION_H
#define TEST_COMPILATION_H

namespace Test {
    class TestClass {
        private:
            const char *hello_world;
        public:
            TestClass(char *hello_world);
            
            void print();
    };
}

#endif