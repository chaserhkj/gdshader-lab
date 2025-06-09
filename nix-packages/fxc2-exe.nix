{
  stdenv,
  pkgsCross,
  fetchFromGitHub,
}: stdenv.mkDerivation {
  pname = "fxc2.exe";
  version = "rolling";
  src = fetchFromGitHub {
    owner = "chaserhkj";
    repo = "fxc2";
    rev = "6ec4ed467428a207e97797898e6fa6655571b077";
  };
  phases = [ "buildPhase" "installPhase" ];
  buildInputs = [
    pkgsCross.mingw32.buildPackages.clang
  ];
  buildPhase = ''
    make x86
  '';
  installPhase = ''
    mkdir -p $out
    install -m755 fxc2.exe $out/fxc2.exe
    install -m755 dll/d3dcompiler_47.dll $out/d3dcompiler_47.dll
  ''
}