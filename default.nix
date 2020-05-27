with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "braillefbm";
  src = ./.;
  installPhase = ''
    ./braillefbm
  '';
}
