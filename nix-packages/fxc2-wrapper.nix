{
  writeShellScriptBin,
  wine,
  fxc2-exe,
  ...}: writeShellScriptBin "fxc2" ''
# Suppress console outputs
export WINEDEBUG=-all
# Use a different default wine prefix
[[ -z "$WINEPREFIX" ]] && export WINEPREFIX=$HOME/.fxc2-wine
# Suppress user interaction by unsetting DISPLAY
unset DISPLAY
exec ${wine}/bin/wine ${fxc2-exe}/fxc2.exe "$@"
''