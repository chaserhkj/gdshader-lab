{
  stdenv,
  cmake,

  cli11,
  libhlslcc,

}: stdenv.mkDerivation {
  pname = "hlslcc-cli";
  version = "rolling";
  src = ./.;
  nativeBuildInputs = [cmake cli11];
  buildInputs = [libhlslcc];
}