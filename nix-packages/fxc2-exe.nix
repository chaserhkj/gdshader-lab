{
  pkgsCross,
  fetchFromGitHub,
}: let stdenv = pkgsCross.mingw32.stdenv;
  in stdenv.mkDerivation {
  pname = "fxc2.exe";
  version = "rolling";
  src = fetchFromGitHub {
    owner = "chaserhkj";
    repo = "fxc2";
    rev = "424f4f605e148a28234ac912d85773cf1762a48f";
    hash = "sha256-7Ce5MG0Lxz6kpwd1co6xcWoIdTXWowKGVjygEcWRBNc=";
  };
  phases = [ "unpackPhase" "buildPhase" "installPhase" ];
  # Cross building w/ clang is broken in nix, use gcc instead
  buildPhase = ''
    i686-w64-mingw32-g++ -static fxc2.cpp -ofxc2.exe
  '';
  installPhase = ''
    mkdir -p $out
    install -m755 fxc2.exe $out/fxc2.exe
    install -m755 dll/d3dcompiler_47_32.dll $out/d3dcompiler_47.dll
  '';
}