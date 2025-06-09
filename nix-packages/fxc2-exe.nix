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
    rev = "6ec4ed467428a207e97797898e6fa6655571b077";
    hash = "sha256-M8v+aUpbn47XJVSImrakDzu3oDQ+ULNZOVpFaA+3W7g=";
  };
  phases = [ "unpackPhase" "buildPhase" "installPhase" ];
  # Cross building w/ clang is broken in nix, use gcc instead
  buildPhase = ''
    i686-w64-mingw32-g++ -static fxc2.cpp -ofxc2.exe
  '';
  installPhase = ''
    mkdir -p $out
    install -m755 fxc2.exe $out/fxc2.exe
    install -m755 dll/d3dcompiler_47.dll $out/d3dcompiler_47.dll
  '';
}