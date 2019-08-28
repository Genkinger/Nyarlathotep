with import <nixpkgs> {};
{
  devEnv = stdenv.mkDerivation {
    name = "Nyarlathotep-0.1";
    nativeBuildInputs = [ cmake ];
    buildInputs =  [ (enableDebugging glfw) (enableDebugging glm) ];
  };
}