{inputs, ...}: {
  imports = [inputs.make-shell.flakeModules.default];
  perSystem = {self', pkgs, ...}: {
    make-shells.default = {
      packages = (with self'.packages; [
        fxc2-wrapper
      ]) ++ (with pkgs; [
        spirv-cross
      ]);
    };
  };
}