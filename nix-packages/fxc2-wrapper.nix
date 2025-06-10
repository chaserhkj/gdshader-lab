{
  writeShellScriptBin,
  wine,
  fxc2-exe,
  ...}: writeShellScriptBin "fxc2" ''
# Suppress console outputs
export WINEDEBUG=-all
# Suppress user interaction by unsetting DISPLAY
unset DISPLAY
exec ${wine}/bin/wine ${fxc2-exe}/fxc2.exe "$@"
''