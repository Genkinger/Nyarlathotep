//
// Created by genkinger on 8/27/19.
//


#include <Nyarlathotep/Nyarlathotep.hpp>

using namespace ny;
using namespace ny::io;
using namespace ny::resources;

int main(int argc, char **argv) {
    ResourceManager manager(500);
    {
        auto txt = manager.Get<FileResource>("/home/genkinger/tmp/test.txt", true);

        String s = "\nTest.txt";
    }
    std::cout << "IF THIS IS DISPLAYED FIRST MAYBE FIX REFCOUNT ETC." << std::endl;
    return 0;
}