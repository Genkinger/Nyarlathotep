//
// Created by genkinger on 8/27/19.
//

#include <iostream>
#include <Nyarlathotep/Nyarlathotep.hpp>
#include <Nyarlathotep/Core/MessageBus/SampleMessage.hpp>


using namespace ny;

int main(int argc, char **argv) {
    auto string = io::Filesystem::ReadTextFile("/etc/nixos/configuration.nix");
    for(auto &line : string.lines()){
        std::cout << NString("Line: ")+line << std::endl;
    }
    return 0;
}