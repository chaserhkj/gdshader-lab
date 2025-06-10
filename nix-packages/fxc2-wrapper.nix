{
  writeShellScriptBin,
  wine,
  fxc2-exe,
  ...}: writeShellScriptBin "fxc2" ''
export WINEDEBUG=-all
exec ${wine}/bin/wine ${fxc2-exe}/fxc2.exe "$@"
''